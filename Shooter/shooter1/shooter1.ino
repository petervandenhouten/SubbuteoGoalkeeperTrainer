#include <Servo.h>

int servo1Pin = 9;
int servo2Pin = 8;
int switchPin =2;

int active = 0;

// Servo
// brown  = gnd
// red    = 5v
// orange = signal
Servo servo1;
Servo servo2;

int force=60;
int movement=200;
int correction=15;

void setup() 
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(switchPin, INPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  Serial.println();
  Serial.println("Setup"); 
  Serial.print("force="); Serial.println(force);
  Serial.print("movement="); Serial.println(movement);
  Serial.print("correction="); Serial.println(correction);

  randomSeed(analogRead(0));

  //servo.write(90-delta);
  //delay(move_delay);
  //servo.write(90+delta);
  //delay(move_delay);
  stop_center();

  servo2.writeMicroseconds(1300);

  Serial.println("Ready"); 
}

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int lastDebounceTime = 0;  // the last time the output pin was toggled
int debounceDelay = 50;    // the debounce time; increase if the output 

void loop() 
{
  int reading = digitalRead(switchPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) 
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) 
    {
      buttonState=reading;
      if ( active==0 )
      {
        active=1;
        Serial.println("Start kicking");         
        delay(2000);
      }
      else
      {
        active=0;
        Serial.println("Stop kicking");         
      }
    }
  }
  lastButtonState = reading;

  if (active)
  {
      releaseball();
      random_wait();
      kickball();
  }
}

void stop_center()
{
  Serial.println("Stop and center"); 
  servo1.write(90);
  delay(50);
}

void releaseball()
{
  Serial.println("Release ball"); 
  servo2.writeMicroseconds(1700);
  delay(150);
  servo2.writeMicroseconds(1300);
  delay(150);
}

void random_wait()
{
  int r = random(2);
  int randWait = 0;
  if (r==1) randWait = 50;
  Serial.print("randWait="); Serial.println(randWait);
  delay(randWait);
}

void kickball()
{
  Serial.println("Kick!"); 

  servo1.write(90-force);
  delay(movement);

  servo1.write(90);
  delay(700);

  Serial.println("Pull back"); 
  servo1.write(90+force);
  delay(movement+correction);

  Serial.println("Kicked"); 

  stop_center();
  Serial.println("Ready"); 
}
