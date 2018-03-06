//Chris Luginbuhl - Mar 6/18 - uses cap touch pad to trigger Star Trek communicator sound.
//Based on code and sound from Adafruit demos

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

#include "trek.h" // Star Trek TNG communicator noise
#define PAD 1
#define NUM_AVGS 100

int threshold = 600;

boolean capButton(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > threshold ) {
    return true;
  } else {
    return false;
  }
}

void setup() {
  long sum = 0;
  CircuitPlayground.begin();
  for (int i = 0; i < NUM_AVGS; i++) {
     sum += CircuitPlayground.readCap(PAD);
    }
    threshold = 1.25* sum / NUM_AVGS; //note this is integer addition - probably ok here!
                                 //adding 25% to threshold to minimize false triggers
  
}

void loop() {
  if (capButton(PAD)) {

    Serial.println("Touched!");


    // Play sound data in the audio[] array (declared in one of the .h files).
    // This function "blocks" -- that is, program flow stops until sound is
    // done playing -- it does not play in the background.

    CircuitPlayground.speaker.playSound(audio, sizeof(audio), SAMPLE_RATE);

    // Calling speaker.end() after playing a sound is optional -- this will
    // turn off the pin 13 LED (it's connected to a microcontroller pin that's
    // also related to the speaker), but there's a small audible click when it
    // turns off.  Tradeoffs!
    CircuitPlayground.speaker.end();
    delay(1000);
  }
}

