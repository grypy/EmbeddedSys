#include <arduino.h> 

int Echo = 12;  // Match to Elegoo Kit
int Trig = 13;  // Match to Elegoo Kit
int speed_A=70;  //initial speed Motor A
int speed_B=70;  //Initial speed Motor B



#define PIN_Motor_STBY 3
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_AIN_1 7
#define PIN_Motor_BIN_1 8

 




void setup() {

   pinMode(PIN_Motor_PWMA,OUTPUT);
   pinMode(PIN_Motor_AIN_1,OUTPUT);
   pinMode(PIN_Motor_PWMB,OUTPUT);
   pinMode(PIN_Motor_BIN_1,OUTPUT);
   pinMode(PIN_Motor_STBY,OUTPUT);

  // initialize serial communication:

  Serial.begin(9600);

}



void loop() {


  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:

  long duration, inches, cm, Fdistance;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds from pin 13.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  pinMode(Trig, OUTPUT);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  // Pin 12 is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.

  pinMode(Echo, INPUT);
  duration = pulseIn(Echo, HIGH);
  Fdistance = pulseIn(Echo, HIGH);  // Elegoo Checking

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);


  Serial.print(inches);
  Serial.print(" in, ");
  Serial.print(cm);
  Serial.print(" cm, ");
  Serial.println();

if (inches <= 18){ 

    //stop
    analogWrite(PIN_Motor_PWMA,0); //Speed Motor A
    analogWrite(PIN_Motor_PWMB,0); //Speed Motor B
    delay(1000);


  //go TURN RIGHT

  digitalWrite(PIN_Motor_STBY,HIGH);  // Turn Motor ON
  digitalWrite(PIN_Motor_AIN_1,LOW); //Motor A Forward
  digitalWrite(PIN_Motor_BIN_1,HIGH); //Motor B Forward


  // Motor A and B have same speed setting

  // speed = 50   PWM = 25% Duty Cycle
  analogWrite(PIN_Motor_PWMA,speed_A); //Speed Motor A
  analogWrite(PIN_Motor_PWMB,speed_B); //Speed Motor B
  delay(1000);



 //FORWARD

  digitalWrite(PIN_Motor_STBY,HIGH);  // Turn Motor ON
  digitalWrite(PIN_Motor_AIN_1,HIGH); //Motor A Forward
  digitalWrite(PIN_Motor_BIN_1,HIGH); //Motor B Forward

  // Motor A and B have same speed setting
  // speed = 64   PWM = 25% Duty Cycle

  analogWrite(PIN_Motor_PWMA,50); //Speed Motor A
  analogWrite(PIN_Motor_PWMB,50); //Speed Motor B
  delay(3000);


 //stop

    analogWrite(PIN_Motor_PWMA,0); //Speed Motor A
    analogWrite(PIN_Motor_PWMB,0); //Speed Motor B
    delay(5000);

  }

  else{

     //FORWARD

  digitalWrite(PIN_Motor_STBY,HIGH);  // Turn Motor ON
  digitalWrite(PIN_Motor_AIN_1,HIGH); //Motor A Forward
  digitalWrite(PIN_Motor_BIN_1,HIGH); //Motor B Forward


  // Motor A and B have same speed setting

  // speed = 64   PWM = 25% Duty Cycle

  analogWrite(PIN_Motor_PWMA,50); //Speed Motor A
  analogWrite(PIN_Motor_PWMB,50); //Speed Motor B
