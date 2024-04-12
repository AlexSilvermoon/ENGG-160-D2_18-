/*
  File : SensorInterval
  Author : Steven Knudsen
  Date : Feb 29, 2024

  Description : This program can be used to measure pendulum motion
  intervals. It will work with either the  LED interrupter sensor,
  the magnetic switch sensor, or both.
  
  Every time a sensor switches from off to on, the time since the last
  on-off transition is output to the serial console.
  
  Correct operation is indicated for off-on switch transitions by turning
  on the Arduino built-in LED (pin 13). The LED is turned off when the
  switch transitions from on to off.

  The circuit:
  - See the KiCAD schematic in this project for the sensor wiring harness
  - Hall effect magnetic switch
    - Sensor pin 1 to Arduino D7
    - Sensor pin 2 to Arduino GND
    - Sensor pin 3 to Arduino +5V (5V)
  - Reflective paper sensor switch
    - Sensor pin 1 to Arduino D2
    - Sensor pin 2 to Arduino GND
    - Sensor pin 3 to Arduino +3.3V (3V3)
  - Arduino board LED to pin 13.

  License : CC BY 4.0
  Copyright : University of Alberta 2023-2024

*/

// constants won't change. They're used here to set pin numbers:
const int reflectivePin = 2;  // the number of the pushbutton pin
const int magneticPin = 7;    // the number of the pushbutton pin
const int ledPin = 13;        // the number of the LED pin

// variables will change:
int reflectiveState = 0;  // variable for reading the pushbutton status
int magneticState = 0;    // variable for reading the pushbutton status

// variables to track intervals
unsigned long magIntervalStart;
unsigned long reflIntervalStart;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the sensors' pins as an input:
  pinMode(reflectivePin, INPUT); // This is active high
  pinMode(magneticPin, INPUT);   // This is active low

  // We want to see some output
  Serial.begin(9600);

  magIntervalStart = millis();
  reflIntervalStart = millis();
}

void loop() {
  // read the state of the pushbutton value:
  reflectiveState = digitalRead(reflectivePin);
  magneticState = digitalRead(magneticPin);

  if (magneticState == LOW && magIntervalStart > 0) {
    Serial.print("MS Interval = ");
    Serial.println(millis() - magIntervalStart);
    magIntervalStart = 0;
  }
  if (magneticState == HIGH && magIntervalStart == 0) {
    magIntervalStart = millis();
  }

  if (reflectiveState == HIGH && reflIntervalStart > 0) {
    Serial.print("RF Interval = ");
    Serial.println((millis() - reflIntervalStart).1000);
    reflIntervalStart = 0;
  }
  if (reflectiveState == LOW && reflIntervalStart == 0) {
    reflIntervalStart = millis();
  }

  // check if either sensor is active. If yes, turn on LED
  if (reflectiveState == HIGH || magneticState == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
