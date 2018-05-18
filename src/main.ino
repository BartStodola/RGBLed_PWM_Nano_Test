enum States
{
  IsIdle, FadeIn, TurnY2R, FadeOut
} state;
int fadeInCount=0;
int fadeOutCount=0;
int y2RCount=0;
int isReset = true;

// pins
const int potiPin = 1;
const int inputPin = 2;
const int triggerPin =3;//LED

// Init the Pins used for PWM arduino nano
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

const int fadeInDelayTime = 10;
const int fadeOutDelayTime = 20;

enum States TriggerSet()
{
  if (digitalRead(inputPin) == HIGH) {
    //-- motion detected.

    if (state == IsIdle)
    return FadeIn;
    else if (state != FadeIn) {ResetVariables(); return TurnY2R;}
  } else {
    // turn LED off:
   return state;
  }
}
void ResetVariables()
{
   fadeInCount=0;
   fadeOutCount=0;
   y2RCount=0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("setup");

  state = IsIdle;
  ResetVariables();

  pinMode(triggerPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inputPin), blink, HIGH);
}

void blink() {
  digitalWrite(triggerPin, HIGH);
  delay(500);
  digitalWrite(triggerPin, LOW);
}

void loop() {
  analogWrite(bluePin, 0);
  int fadeY2RDelayTime = map(analogRead(potiPin), 0,1023, 0,200);

  int potiVal = analogRead(potiPin);
  state = TriggerSet();

  if (state == FadeIn)
  {
    isReset = false;
    // fade in..
    analogWrite(redPin, fadeInCount);
    analogWrite(greenPin, fadeInCount);
    delay(fadeInDelayTime);

    if (fadeInCount++ == 255) state = TurnY2R;
  }

  if (state == TurnY2R)
  {
    // turn color yellow to red.
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255 - y2RCount);
    delay(fadeY2RDelayTime);

    if (y2RCount++ == 255) state = FadeOut;
  }

  if (state == FadeOut)
  {
    // fade in..
    analogWrite(redPin, 255 - fadeOutCount);
    analogWrite(greenPin, 0);
    delay(fadeOutDelayTime);

    if (fadeOutCount++ == 255) state = IsIdle;
  }

  if (state == IsIdle && !isReset)
  {
    isReset = true;
    ResetVariables();
  }

  // report status
//  Serial.print(state);
//  Serial.print(" -->> ");
//  Serial.print(fadeInCount);
//  Serial.print(", ");
//  Serial.print(y2RCount);
//  Serial.print(", ");
//  Serial.println(fadeOutCount);
}
