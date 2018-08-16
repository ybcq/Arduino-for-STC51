/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/
#include <51Arduino.h>
#include <51duino.h>

int pushButton = 2;

// the setup routine runs once when you press reset:
void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial_begin(9600);
    // make the pushbutton's pin an input:
    pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
    // read the input pin:
    int buttonState = digitalRead(pushButton);
    // print out the state of the button:
    Serial_println(buttonState);
    delay(1);        // delay in between reads for stability
}
