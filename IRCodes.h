/**
Author: Chloe Farr
Date: May 26, 2025
Notes: Infrared codes for the Onn Universal 4-Device Remote.

How to use:
Add the following to the top of your .ino script:
```
#include <IRremote.h> //https://github.com/Arduino-IRremote/Arduino-IRremote
#include "IRCodes.h"
```
*/
#pragma once


#define IR_POWER	0xFD020707
#define IR_YELLOW	0xEA150707
#define IR_BLUE 0xE9160707
#define IR_RED	0x936C0707
#define IR_GREEN 0xEB140707
#define IR_REWIND	0xBA450707
#define IR_FAST_FORWARD	0xB7480707
#define IR_PLAY	0xB8470707
#define IR_PAUSE	0xB54A0707
#define IR_MENU	0xE51A0707
#define IR_STOP	0xB9460707
#define IR_RECORD	0xB6490707
#define IR_HOME	0x86790707
#define IR_GUIDE	0xB04F0707
#define IR_PURPLE_LEFT	0x9A650707
#define IR_PURPLE_RIGHT	0x9D620707
#define IR_PURPLE_UP	0x9F600707
#define IR_PURPLE_DOWN	0x9E610707
#define IR_THIN_LEFT	0xA7580707
#define IR_INFO	0xE01F0707
#define IR_VOLUME_UP	0xF8070707
#define IR_VOLUME_DOWN	0xF40B0707
#define IR_CHANNEL_UP	0xED120707
#define IR_CHANNEL_DOWN	0xEF100707
#define IR_P_CH	0xEC130707
#define IR_MUTE	0xF00F0707
#define IR_1	0xFB040707
#define IR_2	0xFA050707
#define IR_3	0xF9060707
#define IR_4	0xF7080707
#define IR_5	0xF6090707
#define IR_6	0xF50A0707
#define IR_7	0xF30C0707
#define IR_8	0xF20D0707
#define IR_9	0xF10E0707
#define IR_BOTTOM_DOT	0xDC230707
#define IR_0	0xEE110707
#define IR_ENTER	0x97680707


void printIRLabel(uint32_t code) {
  switch(code){
    case IR_POWER: Serial.println("Power button"); break;
    case IR_YELLOW: Serial.println("Yellow button"); break;
    case IR_BLUE: Serial.println("Blue button"); break;
    case IR_GREEN: Serial.println("Green button"); break;
    case IR_REWIND: Serial.println("Rewind"); break;
    case IR_FAST_FORWARD: Serial.println("Fast Forward"); break;
    case IR_PLAY: Serial.println("PLAY"); break;
    case IR_PAUSE: Serial.println("PAUSE"); break;
    case IR_MENU: Serial.println("IR_MENU"); break;
    case IR_STOP: Serial.println("IR_STOP"); break;
    case IR_RECORD: Serial.println("IR_RECORD"); break;
    case IR_HOME: Serial.println("IR_HOME"); break;
    case IR_GUIDE: Serial.println("IR_GUIDE"); break;
    case IR_PURPLE_LEFT: Serial.println("IR_PURPLE_LEFT"); break;
    case IR_PURPLE_RIGHT: Serial.println("IR_PURPLE_RIGHT"); break;
    case IR_PURPLE_UP: Serial.println("IR_PURPLE_UP"); break;
    case IR_PURPLE_DOWN: Serial.println("IR_PURPLE_DOWN"); break;
    case IR_THIN_LEFT: Serial.println("IR_THIN_LEFT"); break;
    case IR_INFO: Serial.println("IR_INFO"); break;
    case IR_VOLUME_UP: Serial.println("IR_VOLUME_UP"); break;
    case IR_VOLUME_DOWN: Serial.println("IR_VOLUME_DOWN"); break;
    case IR_CHANNEL_UP: Serial.println("IR_CHANNEL_UP"); break;
    case IR_CHANNEL_DOWN: Serial.println("IR_CHANNEL_DOWN"); break;
    case IR_P_CH: Serial.println("IR_P_CH"); break;
    case IR_MUTE: Serial.println("IR_MUTE"); break;
    case IR_BOTTOM_DOT: Serial.println("IR_BOTTOM_DOT"); break;
    case IR_0: Serial.println("IR_0"); break;
    case IR_ENTER: Serial.println("IR_ENTER"); break;
    case IR_1: Serial.println("#1"); break;
    case IR_2: Serial.println("#2"); break;
    case IR_3: Serial.println("#3"); break;
    case IR_4: Serial.println("#4"); break;
    case IR_5: Serial.println("#5"); break;
    case IR_6: Serial.println("#6"); break;
    case IR_7: Serial.println("#7"); break;
    case IR_8: Serial.println("#8"); break;
  
    default:
      Serial.print("Unknown IR code: 0x");
      Serial.println(code, HEX);
      break;
  }
}