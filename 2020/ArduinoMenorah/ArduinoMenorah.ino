// Arduino Menorah
// By Geoffrey Golden (@geoffreygolden)
//
// Thank you Mirabelle Jones, Jordan Gray, Amanda Meadows, my whole family, especially my dad, and everyone at Codame.
//
// I was always afraid of lighting matches as a kid, thinking I'd get burned, but I loved computers and tech.
// So this is a Chanukah gift to my past self. Happy Chanukah, Young Me!
//
// INSTRUCTIONS:
// 1. Upload this sketch to your Circuit Playground.
// 2. Face the Circuit Playground so the yellow lights are at the bottom. They're the base of the menorah.
// 3. Press the touch sensors to light the candles.
// 4. Press the left or right buttons to play the Chanukah prayer. (You cannot light candles while the prayer is playing.)
//
// NOTE: You're not supposed to blow out the Chanukah lights, but every year someone does it by accident, so I built in the feature.
 
#include <Adafruit_CircuitPlayground.h>
#include "pitches.h"

#define CAP_THRESHOLD   500
#define DEBOUNCE        250

float sound_value;
float THRESHOLD = 90.0;

uint8_t pads[] = {3, 2, 0, 1, 6, 9, 10};
uint8_t numberOfPads = sizeof(pads)/sizeof(uint8_t);

void takeAction(uint8_t pad) {
  
  switch (pad) {
    
    //  Labeled Pin A4
    case 3:
      CircuitPlayground.setPixelColor(1, 0xffff66);  
      break;
      
    //  Labeled Pin A5
    case 2:
      CircuitPlayground.setPixelColor(2, 0xffff66);  
      break;
      
    //  Labeled Pin A6
    case 0:
      CircuitPlayground.setPixelColor(3, 0xffff66);  
      break;
      
    //  Labeled Pin A7
    case 1:
      CircuitPlayground.setPixelColor(4, 0xffff66);   
      break;
      
    // Labeled Pin A1
    case 6:
      CircuitPlayground.setPixelColor(6, 0xffff66);
      CircuitPlayground.setPixelColor(5, 0xffff66);    
      break;
      
    // Labeled Pin A2 
    case 9:
      CircuitPlayground.setPixelColor(7, 0xffff66);  
      break;
      
    // Labeled Pin A3 
    case 10:
      CircuitPlayground.setPixelColor(8, 0xffff66);
      break;
      
    // It's nice to include a default case... just in case! 
    default:
      Serial.println("THIS SHOULD NEVER HAPPEN.");
  }
}

boolean capButton(uint8_t pad) {
  
  if (CircuitPlayground.readCap(pad) >= CAP_THRESHOLD) {
    return true;  
  } else {
    return false;
  }
  
}

void setup() {

  Serial.begin(9600); 
  CircuitPlayground.begin();

}

void base() {
  
  CircuitPlayground.setPixelColor(9, 0xffff00);
  CircuitPlayground.setPixelColor(0, 0xffff00);
  
}

void blow() {

 sound_value = CircuitPlayground.mic.soundPressureLevel(10);
  
 if (sound_value > THRESHOLD) { 
  CircuitPlayground.setPixelColor(1, 0x000000);
  CircuitPlayground.setPixelColor(2, 0x000000);
  CircuitPlayground.setPixelColor(3, 0x000000);
  CircuitPlayground.setPixelColor(4, 0x000000);
  CircuitPlayground.setPixelColor(5, 0x000000);
  CircuitPlayground.setPixelColor(6, 0x000000);
  CircuitPlayground.setPixelColor(7, 0x000000);
  CircuitPlayground.setPixelColor(8, 0x000000);
    }
}

void loop() {
  base();

  for (int i=0; i<numberOfPads; i++) {
    
    if (capButton(pads[i])) {
      takeAction(pads[i]);
      delay(DEBOUNCE);
    }
    prayer();
    blow();
  }
}

int melody[] = {
  NOTE_CS4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_CS4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4,
  NOTE_AS3, NOTE_B3, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5,   
  NOTE_CS5, NOTE_G4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4         
};

int tempo[] = {
  4, 2, 8, 4, 8, 8, 2,
  8, 8, 4, 4, 8, 8, 8, 8, 2,
  4, 2, 8, 8, 8, 8, 8, 8, 8, 8, 2,
  8, 8, 4, 2, 8, 8, 8, 2,
  4, 4, 4, 2, 4, 2
};

uint8_t numberOfNotes = sizeof(melody)/sizeof(int);

void prayer() {
  
    if (CircuitPlayground.leftButton() || CircuitPlayground.rightButton()) {
    for (int n=0; n<numberOfNotes; n++) {
      int noteDuration = 1000 / tempo[n];
      CircuitPlayground.playTone(melody[n], noteDuration);
      delay(0.3*noteDuration);
    }    
}

}
