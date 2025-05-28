/**
Author: Chloe Farr
Date: May 26, 2025
Notes: Infrared codes for the Onn Universal 4-Device Remote are imported from IRCodes.h.
*/

#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <IRremote.h> //https://github.com/Arduino-IRremote/Arduino-IRremote
#include "IRCodes.h"
#include <LiquidCrystal.h>
	
struct SunData {
  uint8_t r, g, b;
};

#define RED_PIN 10
#define BLUE_PIN 9
#define GREEN_PIN 8

#define IR_PIN 13

IRrecv irrecv(IR_PIN);
decode_results results;

bool powerOn = false;
bool inTimelapse = true;

float currentHour = 0.0;
unsigned long lastStepTime = 0;
unsigned long interval = 2000; // one hour simulated as 2 seconds
static uint32_t prevCode = 0;

//track duration between button presses
unsigned long lastIRTime = 0;
const unsigned long irCooldown = 300; // 300ms between presses

LiquidCrystal lcd(2,3,A5,A4,A3,A2);
int reply;

SunData dayData[24] = {
  {0, 0, 0},   // 0:00
  {10, 10, 30},   // 1:00
  {20, 10, 40},   // 2:00
  {40, 20, 50},   // 3:00
  {80, 50, 60},   // 4:00
  {120, 80, 70},  // 5:00
  {180, 120, 90}, // 6:00
  {201, 226, 255},// 7:00 overcast sky
  {255, 255, 255},// 8:00 direct sun
  {255, 255, 255},// 9:00
  {255, 255, 255},// 10:00
  {255, 255, 255},// 11:00
  {255, 255, 251},// 12:00 high noon
  {255, 255, 255},// 13:00
  {255, 255, 255},// 14:00
  {255, 255, 255},// 15:00
  {64, 156, 255},// 16:00 clear blue sky
  {255, 160, 100},// 17:00
  {255, 120, 80}, // 18:00
  {180, 80, 60},  // 19:00
  {120, 50, 40},  // 20:00
  {60, 20, 30},   // 21:00
  {20, 10, 20},   // 22:00
  {10, 10, 20}    // 23:00
};

// --- Function Prototypes ---
void newCol(uint8_t r, uint8_t g, uint8_t b);
void print_col(float hour, SunData a);
float scrubHour(int dir);
void timelapseStep();
void handleIR(uint32_t code);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the IR receiver
  Serial.println("IR receiver ready");

  //set LED channels
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  inTimelapse = false;

  lcd.begin(16, 2); 
  print_lcd("Turned Off", "POWER: turn on");
}

//LERP color helper
uint8_t lerp(uint8_t a, uint8_t b, float t) {
  return a + (b - a) * t;
}

void print_lcd(String rowA, String rowB){
  lcd.clear();

  lcd.setCursor(0, 0);       // Column 0, Row 0
  lcd.print(rowA);

  lcd.setCursor(0, 1);       // Column 0, Row 1
  lcd.print(rowB);
}
void timelapseStep() {
  if (millis() - lastStepTime >= 50 && currentHour < 23.99) {
    lastStepTime = millis();

    currentHour += (50.0 / interval); // Advance by fraction of an hour

    int h = floor(currentHour);
    int next = (h + 1) % 24;
    float t = currentHour - h; // How far between hour and next

    SunData a = dayData[h];
    SunData b = dayData[next];
    uint8_t r = lerp(a.r, b.r, t);
    uint8_t g = lerp(a.g, b.g, t);
    uint8_t b_ = lerp(a.b, b.b, t);
  
    SunData bData = dayData[next];
    newCol(r, g, b_);

    if (currentHour >= 23.99) {
      inTimelapse = false; // auto-stop
      Serial.println("Timelapse COMPLETE");
      print_lcd("Day has ended", "");
      currentHour = 0;
      turnLightOff();
    }
    else{
      print_col(currentHour, bData);
      String hourString = "Lapse | Hr: " + String(currentHour);
      print_lcd(hourString, "STOP or PAUSE");
    }
  }
}

void print_col(float hour, SunData a){
  Serial.print("Hour: ");
  Serial.println(hour);
  Serial.println("R: " + String(a.r) + " G: " + String(a.g) + " B: " + String(a.b));   
}


float scrubHour(int dir){ // 1 for forward, -1 for backward

  // Cannot go preceed start of day
  if(dir == 1 && currentHour > 23){
    Serial.println("Cannot go past end of day");
    print_lcd("End of day.", "STOP: restart");
    turnLightOff();
    return currentHour;
  }
  
  // Cannot go beyond end of day
  else if(dir == -1 && currentHour <= 0){
    Serial.println("Cannot go back before beginning of day");
    print_lcd("Beginning of day", "RIGHT: sun.");
    turnLightOff();
  	return currentHour;
  }
  
  // Step light back or forward one hour
  else{
    int h = floor(currentHour);
    int next = (h + dir) % 24;
    float t = currentHour - h; // How far between hour and next

    SunData a = dayData[h];
    SunData b = dayData[next];
    uint8_t r = lerp(a.r, b.r, t);
    uint8_t g = lerp(a.g, b.g, t);
    uint8_t b_ = lerp(a.b, b.b, t);

    newCol(r, g, b_);
    int newHr = currentHour + dir;
    print_col(newHr, b);
    String hourString = "Scrub | Hr: " + String(newHr);
    print_lcd(hourString, "LEFT or STOP");

    return currentHour + dir;
  }
}

//Easy Turn off
void turnLightOff(){
  newCol(0,0,0);
}

//set color helper
void newCol(uint8_t r, uint8_t g, uint8_t b) {
  float clamp = 0.7;
  analogWrite(RED_PIN, r*clamp);
  analogWrite(GREEN_PIN, g*clamp);
	analogWrite(BLUE_PIN, b*clamp);
}

void loop() {
  
  if (IrReceiver.decode()) { //if IR receiver gets input from remote
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    // Skip NEC repeat code
    if (code == 0xFFFFFFFF) {
      IrReceiver.resume();
      return;
    }

    // if more than 3 milliseconds have passed since repeat input... prevents repeat executions on long-press
    unsigned long now = millis();
    if (now - lastIRTime > irCooldown) {
      handleIR(code);
      printIRLabel(code);
      lastIRTime = now;
    }

    IrReceiver.resume();
  }

  //Continue timelapse if it has been started via Start button
  if (powerOn && inTimelapse) {
    timelapseStep();
  }
}


void handleIR(uint32_t code) {
  if (!powerOn && code != IR_POWER) return;

  switch (code) {
    case IR_POWER: // Allow light manipulation, or prevent it (turn the system on/off on the user side.)
      powerOn = !powerOn;
      Serial.println(powerOn ? "Power ON" : "Power OFF");
      powerOn? print_lcd("PLAY: timelapse", "RIGHT: scrub") : print_lcd("Turned Off", "POWER: turn on");
      turnLightOff();
      break;

    case IR_PLAY: //Start timelapse
      inTimelapse = true;
      lastStepTime = millis();
      Serial.println("Timelapse STARTED");
      print_lcd("Timelapse begun", "");
      break;

    case IR_STOP: //end timelapse
      if(inTimelapse){
        inTimelapse = false;
        currentHour = 0.0;
        Serial.println("Timelapse STOPPED");
        print_lcd("Timelapse halted", "");
      }
      currentHour = 0.0;
      Serial.println("Day restarted");
      print_lcd("Day restarted", "PLAY or RIGHT");
      turnLightOff();
      break;

    case IR_PAUSE: //pause timelapse (doesn't reset hour of day)
      inTimelapse = false;
      currentHour = floor(currentHour);
      Serial.println("Timelapse PAUSED");
      print_lcd("PLAY to restart", "or RIGHT or STOP");
      break;

    case IR_PURPLE_RIGHT: //pause timelapse and skip forward one hour
      inTimelapse = false;
      if(powerOn) currentHour = scrubHour(1);
      break;

    case IR_PURPLE_LEFT: //pause timelapse and skip backward one hour
      inTimelapse = false;
      if(powerOn) currentHour = scrubHour(-1);
      break;
  }
}