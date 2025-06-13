#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4  // Data pin for the LED strip
#define NUM_LEDS 8 // Change to match strip
#define BRIGHTNESS 50 // Clamp brightness for optical safety and reduce power demand
#define LOG_INTERVAL 4 //print every 4 loops

MPU6050 mpu;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int interval = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(D3, D2); // SDA, SCL 

  // LED strip setup
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'

  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected");
  } else {
    Serial.println("MPU6050 connection failed");
  }

  delay(1000);
}

void print_angle_iLED(int angle, int index){
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | LED index");
    Serial.print(index);
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Simple roll calculation
  float roll = atan2(ay, az) * 180.0 / PI;

  // Map roll (-90 to 90) to LED index (0 to NUM_LEDS - 1)
  int ledIndex = map(roll, -90, 90, 0, NUM_LEDS - 1);
  ledIndex = constrain(ledIndex, 0, NUM_LEDS - 1);

  // Light only the corresponding LED
  strip.clear();
  strip.setPixelColor(ledIndex, strip.Color(255, 200, 50)); // warm light
  strip.show();

  if(interval == LOG_INTERVAL){
    print_angle_rgb(roll, ledIndex)
    interval = 0;
  }
  else{
    interval++;
  }
  delay(150);
}