#include <Arduino.h>

// Init the Pins used for PWM arduino nano
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

// for ATTiny85
// on button pressed fade led in stay for n-sec. and fade out

//int brightness[] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 16, 18, 21, 23, 26, 30, 33, 37, 42, 47, 53, 59, 66, 74, 83, 93, 104, 116, 130, 145, 162, 181, 203, 227, 255 };
int brightness[] = { 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 9, 11, 13, 15, 18, 22, 26, 31, 37, 44, 53, 62, 74, 87, 104, 123, 145, 172, 203, 240, 255 };
//int brightness[] = { 0, 0, 0, 0, 1, 2, 2, 3, 4, 6, 8, 10, 13, 16, 21, 26, 33, 42, 53, 66, 83, 104, 130, 162, 203, 255 };
int count = (sizeof(brightness)/sizeof(*brightness));

const int triggerPin =3;//LED
//const int ledPin = 1;  // LED
const int inputPin = 2;// button or PIR-Sensor
const int potiPin = 4;

int processing = -1;
int maxProcessingCount = 10;

void FadeIn(int delayMsec)
{
  for (int i= 0; i<255;++i)
  {
    analogWrite(redPin, i);
    analogWrite(greenPin, i);
    delay(delayMsec);
  }
}

// fade from red to black.
void FadeOut(int delayMsec)
{
  for (int i= 0; i<255;++i)
  {
    analogWrite(redPin, 255-i);
    analogWrite(greenPin, 0);
    delay(delayMsec);
  }
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
}

boolean IsTriggerSet()
{
  if (digitalRead(inputPin) == HIGH) {
    // turn LED on:
    return true;
  } else {
    // turn LED off:
    return false;
  }
}

void BlinkTriggerLed(int msec)
{
  digitalWrite(triggerPin, HIGH);
  delay(msec);
  digitalWrite(triggerPin, LOW);
}

void setup() {

  pinMode(inputPin, INPUT);
  pinMode(potiPin, INPUT);

  pinMode(triggerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  processing = -1;
}

void loop() {
  analogWrite(bluePin, 0);
  maxProcessingCount = map(analogRead(potiPin), 0,1023, 0,200);

  if (IsTriggerSet())
  {
    if (processing == -1)
    {
      BlinkTriggerLed(500);

      /// --- fade in
      ///
      processing = maxProcessingCount;
      FadeIn(10);
    }
    if (processing > -1)
    {
      // set re-trigger count
      BlinkTriggerLed(500);
      processing = maxProcessingCount;
    }
  }

  if (processing > 0)
  {
    /// --- illuminate (slowly fade from yellow to red)
    ///
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255-255/(processing+1));
    delay(200);

    processing -= 1;
  }
  if (processing == 0)
  {
    /// --- fade out
    ///
    FadeOut(10);
    processing =-1;
  }
}
