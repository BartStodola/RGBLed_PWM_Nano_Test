#include <Arduino.h>
// Init the Pins used for PWM arduino nano
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int nextCount =0;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
//   Serial.begin(9600);
//  Serial.println("setup done");
}

int c=0;
int bl=0;
bool up = true;

void fadeR()
{
  if (nextCount != 0) return;
  if (bl == 0) up = true;
  if (bl == 1024) up = false;
  if (up)bl++;
  else bl--;
  int r=bl;

// Write the color to each pin using PWM and the value gathered above
  analogWrite(redPin, map( r, 0, 1024, 0, 255 ));
  analogWrite(bluePin, 0);
  analogWrite(greenPin, 0);

  if (bl == 0 && !up) nextCount++;
}

void fadeG()
{
  if (nextCount != 1) return;
  if (bl == 0) up = true;
  if (bl == 1024) up = false;
  if (up)bl++;
  else bl--;
  int b=bl;

// Write the color to each pin using PWM and the value gathered above
  analogWrite(redPin, 0);
  analogWrite(bluePin, map( b, 0, 1024, 0, 255 ));
  analogWrite(greenPin, 0);

  if (bl == 0 && !up) nextCount++;
}

void fadeB()
{
  if (nextCount != 2) return;
  if (bl == 0) up = true;
  if (bl == 1024) up = false;
  if (up)bl++;
  else bl--;
  int g=bl;

// Write the color to each pin using PWM and the value gathered above
  analogWrite(redPin, 0);
  analogWrite(bluePin, 0);
  analogWrite(greenPin, map( g, 0, 1024, 0, 255 ));

  if (bl == 0 && !up) nextCount++;
}
void fadeWhite()
{
  if (nextCount != 3) return;
  if (bl == 0) up = true;
  if (bl == 1024) up = false;
  if (up)bl++;
  else bl--;
  int g=bl;

// Write the color to each pin using PWM and the value gathered above
  analogWrite(redPin,   map( g, 0, 1024, 0, 255 ));
  analogWrite(bluePin,  map( g, 0, 1024, 0, 255 ));
  analogWrite(greenPin, map( g, 0, 1024, 0, 255 ));

  if (bl == 0 && !up) nextCount++;
}
void loop()
{
  fadeR();
  fadeG();
  fadeB();
  fadeWhite();
  if (nextCount == 4) nextCount =0;

  delay(1);
}
