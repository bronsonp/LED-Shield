# Light grid Arduino shield 

Open-source hardware and software for an Arduino shield with a grid of lights. Used at James Cook University for soldering practice and embedded systems programming practice.

![Photograph of constructed PCB](Documentation/Constructed-PCB.png)

This device consists of 32 individually controllable LEDs, two analog joysticks, and four switches. It can be controlled from an Arduino Uno or a NXP FRDM development board.

## Assembly instructions

If you received a board with the LEDs and other surface mount components already soldered, then please refer to the [through-hole assembly instructions](Documentation/Through-Hole-Assembly.md).

## Software instructions 

If you are using an Arduino to control the shield, there is a pre-made driver library and some example applications. You will need to install the [Arduino IDE](https://www.arduino.cc/en/Main/Software) and the [CH340 drivers](https://sparks.gogo.co.nz/ch340.html).

The two example applications are:
 * `Software\Animation_template`: A simple example of animating a pattern on the LEDs, intended to be a starting point for your own projects.
 * `Software\Games`: A game of pong and a game of snake, played with the joysticks. Press the left joystick (into the page) to swap between pong and snake games.

Refer to the [Arduino software instructions](Documentation/Arduino-Library.md) for more information.

## Technical documentation 

For technical details, refer to the [electrical schematic](Documentation/Schematic.pdf) for the circuit.
