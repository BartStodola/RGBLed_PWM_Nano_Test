#include <Arduino.h>
// Init the Pins used for PWM arduino nano
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

int nextStep =0;
int colorVal=0;
bool doDelay = false;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  doDelay = false;
//   Serial.begin(9600);
//  Serial.println("setup done");
}

void Delay(int msec)
{
  if (doDelay)
  {
    doDelay=false;
    delay(msec);
  }
}

void FadeBlackToYellow()
{
  if (nextStep != 0) return;

  colorVal++;
  int val  = map( colorVal, 0, 1024, 0, 255 );
  analogWrite(redPin, val);
  analogWrite(greenPin, val);
  analogWrite(bluePin, 0);

  if (colorVal == 1024) {nextStep++;doDelay=true;colorVal=10240;}
}

void FadeYellowToRed()
{
  if (nextStep != 1) return;

  colorVal--;

  analogWrite(redPin, 255);
  analogWrite(greenPin, map( colorVal, 0, 10240, 0, 255 ));
  analogWrite(bluePin, 0);

  if (colorVal == 0) {colorVal = 1024; nextStep++;doDelay=true;}
}

void FadeRedToBlack()
{
  if (nextStep != 2) return;

  colorVal--;

  analogWrite(redPin, map( colorVal, 0, 1024, 0, 255 ));
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  if (colorVal == 0) {nextStep++;doDelay=true;}
}

// move from colorValack --> yellow --> red --> colorValack
void loop()
{
  FadeBlackToYellow();
  Delay(1000);
  FadeYellowToRed();
  Delay(1000);
  FadeRedToBlack();
  Delay(1000);

  if (nextStep == 3) nextStep =0;
  delay(2);
}
