// -----
// JGRotaryEncoder.h - Library for using rotary encoders.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Jorge Augusto Gallo
//
// Repository: https://github.com/jucaballa/jucaballa-JGRotaryEncoder
//
// -----
// 08.03.2020 created by Jorge Augusto Gallo
// -----

#include "Arduino.h"
#include "JGRotaryEncoder.h"

// ----- Initialization and Default Values -----

// Constructor whithout switch
JGRotaryEncoder::JGRotaryEncoder(int dataPin, int clockPin) {
  init(dataPin, clockPin, 255);  // 255 = no switch
}

// Constructor whit switch
JGRotaryEncoder::JGRotaryEncoder(int dataPin, int clockPin, int switchPin) {
  init(dataPin, clockPin, switchPin);
}

// Initialize encoder
JGRotaryEncoder::init(int dataPin, int clockPin, int switchPin) {
  // Remember Hardware Setup
  _dataPin = dataPin;
  _clockPin = clockPin;
  _switchPin = switchPin;
  
  // Setup the input pins and turn on pullup resistor
  pinMode(dataPin, INPUT_PULLUP);
  pinMode(clockPin, INPUT_PULLUP);
  
  // whith switch ?
  if (_switchPin !=255) {
    pinMode(_switchPin, INPUT_PULLUP);
  }

  // when not started in motion, the current state of the encoder should be 3 (or 0)
  _oldState = 0;
  _oldSwitchState = 0;

  // start with 0 stopped;
  _lastDirection = 0;
  
  // wait a phase change on any input signal by notch
  _singlePhase = 0;
  
  // set when switch clicked
  _switchClicked = 0;
  
  // encoder counter
  _position = 0;

  // direction inversion
  _inverted = 0;
}

// Set encoder mode
void JGRotaryEncoder::setSinglePhase(int8_t singlePhase) {
  // set operation mode
  _singlePhase = singlePhase;
}

void JGRotaryEncoder::setInversion(int newInversion) {
  _inverted = newInversion;
}

void JGRotaryEncoder::setPosition(long position) {
  // only adjust the external part of the position.
  _position = position;
}

// Get move direction. 1 = CW, 2 = CCW
int8_t JGRotaryEncoder::getDirection() {
  int8_t ret = _lastDirection;
  _lastDirection = 0;
  return ret;
}

// Get position
long  JGRotaryEncoder::getPosition() {
  return _position;
}

// Get switch click. 1 = clicked
int8_t JGRotaryEncoder::getSwitch() {
  int8_t ret = _switchClicked;
  _switchClicked = 0;
  return ret;
}

// encoder monitor - call this at each 1ms
void JGRotaryEncoder::tick(void) {
  int dataState = digitalRead(_dataPin);
  int clockState = digitalRead(_clockPin);
  int8_t thisState = clockState | (dataState << 1);
  if (_oldState != thisState) {
    if (thisState == 0) {
      if (_oldState == 1) {
        positionUpdate(1);
      } else if (_oldState == 2) {
        positionUpdate(-1);
      }
    } else if ((thisState == 3) & (_singlePhase)) {
      if (_oldState == 2) {
        positionUpdate(1);
      } else if (_oldState == 1) {
        positionUpdate(-1);
      }
    }
    _oldState = thisState;
  }
  
  if (_switchPin !=255) {
    int switchkState = digitalRead(_switchPin);
    if (_oldSwitchState != switchkState) {
      _oldSwitchState = switchkState;
      if (!switchkState) {
        _switchClicked = 1;
      }
    }
  }
}

void JGRotaryEncoder::positionUpdate(int direction) {
  if (!_inverted) {
    _lastDirection = direction;
    _position += direction;
  } else {
    _lastDirection = -direction;
    _position -= direction;
  }
}

// End
