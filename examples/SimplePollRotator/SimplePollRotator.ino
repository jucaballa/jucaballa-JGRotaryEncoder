// -----
// SimplePollRotator.ino - Example for the JGRotaryEncoder library.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Jorge Augusto Gallo
//
// Repository: https://github.com/jucaballa/jucaballa-JGRotaryEncoder
//
// -----
// 08.03.2020 created by Jorge Augusto Gallo
// -----

// This example checks the state of the rotary encoder in the loop() function.
// The current direction and position is printed on output when changed.

// Hardware setup:
// Attach a rotary encoder with output pins to A2,A4 and A4(push switch).
// The common contact should be attached to ground.

#include <JGRotaryEncoder.h>

// Setup a RoraryEncoder for pins A2, A3 and A4:
JGRotaryEncoder encoder(A2, A3, A4);

void setup() {
  Serial.begin(115200);
  Serial.println("SimplePollRotator example for the JGRotaryEncoder library.");
}

// Read the current direction and position of the encoder and print out when changed.
void loop() {
  encoder.tick();
  delay(2);
  int direction = encoder.getDirection();
  int click = encoder.getSwitch();
  int position = encoder.getPosition();
  if (direction) {
    Serial.print("Direction: ");
    Serial.print(direction);
    Serial.print("  Position: ");
    Serial.println(position);
  } // if
  if (click) {
    Serial.println("Click");
  }
}

// End
