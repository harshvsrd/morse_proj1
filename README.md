# Morse code translator
Demonstrating wireless optical signaling and basic signal decoding using arduino.Transmitter encodes text into morse code and transmits it using laser,receiver part uses LDR to detect light pulses and decode them back into text.


# Components Used

* Arduino Uno (2 units – transmitter and receiver)
* 0.96"OLED screen
* push button
* Laser diode
* LDR (Light Dependent Resistor)
* Resistors
* Breadboards
* Jumper wires
* USB cables

# Working Principle

1. The transmitter Arduino converts user given text(can be edited) into Morse code.
2. The laser diode switches ON and OFF according to the Morse pattern when push button presssed.
3. The receiver Arduino reads light intensity using the LDR.
4. Changes in light levels are interpreted as dots and dashes.
5. The decoded message is displayed on the OLED sccreen.

# Transmitter

* Laser diode connected to a digital output pin of the Arduino.
* a push button that initiates the entered message.
* The Arduino controls the laser based on Morse timing.(dot, dash, letter & word gap)

### Receiver

* LDR connected in a voltage divider circuit.
* The analog pin reads light intensity values.
* A threshold is used to detect laser ON/OFF states.

## Features

* Wireless communication using light
* Morse code encoding and decoding
* Real-time message display on serial monitor
* Simple and low-cost hardware implementation


### Hardware images

(Morse_proj_image_1.jpeg)

(Morse_proj_image_2.jpeg)

(Morse_proj_image_3.jpeg)



# Files in this Repository

* `transmitter.ino` – Arduino code for sending Morse code via laser
* `MORSE_CODE_OLED.ino` – Arduino code for decoding Morse signals from LDR

# Future Improvements

* Use photodiode instead of LDR for faster response
* Add error detection
* Increase communication range
* Implement data transmission instead of only text
