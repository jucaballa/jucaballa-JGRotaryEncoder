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

#ifndef JGRotaryEncoder_h
#define JGRotaryEncoder_h

#include "Arduino.h"

class JGRotaryEncoder {
public:
  // ----- Constructor -----
  JGRotaryEncoder(int dataPin, int clockPin);
  JGRotaryEncoder(int dataPin, int clockPin, int switchPin);

  // hardware initazization
  init(int dataPin, int clockPin, int switchPin);

  // configure operation mode
  void setSinglePhase(int8_t singlePhase);

  // adjust the current position
  void setInversion(int newInversion);

  // adjust the current position
  void setPosition(long newPosition);

  // simple retrieve of the direction the knob was rotated at. 0 = No rotation, 1 = Clockwise, -1 = Counter Clockwise
  int8_t getDirection();

  // retrieve the current position
  long  getPosition();

  // simple retrieve of switch. 1 = clicked.
  int8_t getSwitch();

  // call this function every some milliseconds or by using an interrupt for handling state changes of the rotary encoder.
  void tick(void);

private:
  int _dataPin, _clockPin;         // Arduino pins used for the encoder. 

  volatile int8_t _oldState;
  volatile int8_t _lastDirection;
  volatile int8_t _singlePhase;
  volatile int8_t _switchPin;
  volatile int8_t _oldSwitchState;
  volatile int8_t _switchClicked;
  volatile long _position;
  volatile long _inverted;

  void positionUpdate(int direction);
};

#endif

// End
