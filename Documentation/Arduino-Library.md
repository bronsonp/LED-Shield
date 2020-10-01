# Introduction to the `LED_Shield` Arduino library

Quick-start: open the `Animation_template` project in the `Software` folder.

Otherwise read on for documentation of all functions.

## LED control functions

Minimal example Arduino program:
```C++
#include "LED_Shield.h"
LED_Shield led_shield;

void setup() {
  led_shield.begin();
}

void loop() {
    led_shield.allOff(); // turn all LEDs off
    led_shield.on(0); // turn LED 0 on
    led_shield.write(); // write these settings to the driver chips
    // ...
}
```

The library maintains an internal list of which LEDs are on and which are off. Functions like `on` and `off` update this internal list. Once all the required changes have been made, call `led_shield.write()` to transfer these settings to the LED drivers. 

### Function `led_shield.on(n)`
The given LED will be turned on when `led_shield.write()` is next called. 

Example:
```C++
// turn on LEDs 10 and 11 and leave all the other unchanged
led_shield.on(10);
led_shield.on(11);
led_shield.write();
```

### Function `led_shield.off(n)`
The given LED will be turned off when `led_shield.write()` is next called.

Example:
```C++
// turn off LED 20 and leave all the others unchanged
led_shield.off(20);
led_shield.write();
```

### Function `led_shield.toggle(n)`
The given LED will be swapped between on and off states when `led_shield.write()` is next called. 

Example:
```C++
// change the state of LED 21 but leave all others unchanged
led_shield.toggle(21);
led_shield.write();
```

### Function `led_shield.allOn()`
All LEDs will be turned on the next time that `led_shield.write()` is called.

This function can be combined with `on` and `off`, for example:
```C++
// turn all LEDs on except for number 8
led_shield.allOn();
led_shield.off(8);
led_shield.write();
```

### Function `led_shield.allOff()`
All LEDs will be turned off the next time that `led_shield.write()` is called.

This function can be combined with `on` and `off`, for example:
```C++
// turn all LEDs off except for number 9
led_shield.allOff();
led_shield.on(9);
led_shield.write();
```

### Function `led_shield.write()`
This function transmits the latest changes to the LED driver chips. Changes to the LEDs do not take effect until this function is called. This allows you to update multiple LEDs and then instantly switch to the new configuration without any flickering. 

### Function `led_shield.get(n)`
Return true or false to indicate whether the given LED is on or off. 

Example:
```C++
if (led_shield.get(0)) {
    // LED 0 is on
} else {
    // LED 0 is off
}
```

## Joystick functions

There are two joysticks, which are named "left" and "right". Each joystick has two axes of motion that can be measured independently, and they can also be pressed down as a button.

### Function `led_shield.left_joystick_x()`
Returns the X axis position of the left joystick. The result is an integer in the range of 0 to 1023. In the neutral position, the value is approximately the midpoint of this range (but there is some variation from board to board).

### Function `led_shield.left_joystick_y()`
Returns the Y axis position of the left joystick. The result is an integer in the range of 0 to 1023. In the neutral position, the value is approximately the midpoint of this range (but there is some variation from board to board).

### Function `led_shield.right_joystick_x()`
Returns the X axis position of the right joystick. The result is an integer in the range of 0 to 1023. In the neutral position, the value is approximately the midpoint of this range (but there is some variation from board to board).

### Function `led_shield.right_joystick_y()`
Returns the Y axis position of the right joystick. The result is an integer in the range of 0 to 1023. In the neutral position, the value is approximately the midpoint of this range (but there is some variation from board to board).

### Function `led_shield.left_joystick_pressed()`
Returns true if the left joystick is currently pressed down. It will continue to return true for as long as the user holds the joystick pressed.


### Function `led_shield.right_joystick_pressed()`
Returns true if the right joystick is currently pressed down. It will continue to return true for as long as the user holds the joystick pressed.

## Switch functions
There are four small switches labelled `SW1`, `SW2`, `SW3` and `SW4`. These can be read using the functions below:

### Function `led_shield.read_SW1()`
Returns true if SW1 is currently pressed down. 

### Function `led_shield.read_SW2()`
Returns true if SW2 is currently pressed down. 

### Function `led_shield.read_SW3()`
Returns true if SW3 is currently pressed down. 

### Function `led_shield.read_SW4()`
Returns true if SW4 is currently pressed down. 
