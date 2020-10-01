/**
 * Driver code for the JCU LED Shield soldering challenge
 * 
 * Bronson Philippa, September 2020
 * Driver version 1.0
**/

#include "Arduino.h"
#include "LED_Shield.h"


// Pins for the STP16CPC26XTR controllers
#define MOSI 11
#define MISO 12
#define CLK 13
#define LE 3
#define OE 4

// Pins for the buttons
#define SW1 8
#define SW2 7
#define SW3 6
#define SW4 5

// Pins for the left joystick
#define LEFT_JOYSTICK_PRESS 9
#define LEFT_JOYSTICK_X A2
#define LEFT_JOYSTICK_Y A3

// Pins for the right joystick
#define RIGHT_JOYSTICK_PRESS 10
#define RIGHT_JOYSTICK_X A0
#define RIGHT_JOYSTICK_Y A1

// Constructor
LED_Shield::LED_Shield() {

}

// Initialise hardware
void LED_Shield::begin() {
  pinMode(CLK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(OE, OUTPUT);

  // disable latch and output
  digitalWrite(LE, 0);
  digitalWrite(OE, 1);

  // set clock to idle high 
  digitalWrite(CLK, 1);

  // configure software pullups for switches
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);  

  // set all LEDs off
  this->allOff();
  this->write();
  delay(100); // give enough time for all capacitors to be charged

  // set the random seed
  randomSeed(this->left_joystick_x());
}

// Turn on a particular LED 
bool LED_Shield::on(int id) {
  if (id < 0 || id > 31) {
    id = 0;
  }
  bool oldValue = this->D[id];
  this->D[id] = true;
  return oldValue;
}

// Turn off a particular LED
bool LED_Shield::off(int id) {
  if (id < 0 || id > 31) {
    id = 0;
  }
  bool oldValue = this->D[id];
  this->D[id] = false;
  return oldValue;
}

// Toggle a particular LED
bool LED_Shield::toggle(int id) {
  if (id < 0 || id > 31) {
    id = 0;
  }
  bool newValue = !(this->D[id]);
  this->D[id] = newValue;
  return newValue;
}

// Get whether a given number is on or off
bool LED_Shield::get(int id) {
  if (id < 0 || id > 31) {
    id = 0;
  }
  return this->D[id];
}

// Turn all lights on
void LED_Shield::allOn() {
  for (int i = 0; i < 32; i++) {
    this->D[i] = true;
  }
}

// Turn all lights off
void LED_Shield::allOff() {
  for (int i = 0; i < 32; i++) {
    this->D[i] = false;
  }
}

// Read switch SW1 (returns true when switch is pressed)
bool LED_Shield::read_SW1() {
  return !digitalRead(SW1);
}

// Read switch SW2 (returns true when switch is pressed)
bool LED_Shield::read_SW2() {
  return !digitalRead(SW2);
}

// Read switch SW3 (returns true when switch is pressed)
bool LED_Shield::read_SW3() {
  return !digitalRead(SW3);
}

// Read switch SW4 (returns true when switch is pressed)
bool LED_Shield::read_SW4() {
  return !digitalRead(SW4);
}

// Read left joystick press (return true when pressed down)
bool LED_Shield::left_joystick_pressed() {
  return digitalRead(LEFT_JOYSTICK_PRESS);
}

// Read left joystick press (return true when pressed down)
bool LED_Shield::right_joystick_pressed() {
  return digitalRead(RIGHT_JOYSTICK_PRESS);
}

// Read left joystick X axis
int LED_Shield::left_joystick_x() {
  return analogRead(LEFT_JOYSTICK_X);
}

// Read left joystick Y axis
int LED_Shield::left_joystick_y() {
  return analogRead(LEFT_JOYSTICK_Y);
}

// Read right joystick X axis
int LED_Shield::right_joystick_x() {
  return analogRead(RIGHT_JOYSTICK_X);
}

// Read right joystick Y axis
int LED_Shield::right_joystick_y() {
  return analogRead(RIGHT_JOYSTICK_Y);
}

// The mapping between bits on the SPI shift register and LED numbers on the board
uint8_t sequence [] = {
  23, 22, 21, 20, 19, 18, 17, 16, 
  31, 30, 29, 28, 27, 26, 25, 24,
  15, 14, 13, 12, 11, 10,  9,  8,
   7,  6,  5,  4,  3,  2,  1,  0
};
void LED_Shield::write() {
  // Send the contents of the "D" array to the LED drivers 
  for (int i = 0; i < 32; i++) {
    // Send this bit
    digitalWrite(MOSI, this->D[sequence[i]]);
    digitalWrite(CLK, 0);
    delayMicroseconds(200);

    // Restore the clock
    digitalWrite(CLK, 1);
    delayMicroseconds(200);
  }

  // Latch the value 
  digitalWrite(LE, 1);
  delayMicroseconds(200);
  digitalWrite(LE, 0);
  delayMicroseconds(5);

  // Enable output
  digitalWrite(OE, 0);  
}
