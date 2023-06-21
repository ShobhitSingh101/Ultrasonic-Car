#include <AFMotor.h>

#define S1Trig A0
#define S2Trig A1
#define S3Trig A2
#define S1Echo A3
#define S2Echo A4
#define S3Echo A5

#define Speed 160

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
 
  pinMode(S1Trig, OUTPUT);
  pinMode(S2Trig, OUTPUT);
  pinMode(S3Trig, OUTPUT);
  
  pinMode(S1Echo, INPUT);
  pinMode(S2Echo, INPUT);
  pinMode(S3Echo, INPUT);
  
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);
}

void loop() {
  int centerSensor = sensorTwo();
  int leftSensor = sensorOne();
  int rightSensor = sensorThree();

  if (8 >= centerSensor) {
    Stop();
    Serial.println("Stop");
    delay(1000);
    if (leftSensor > rightSensor) {
      left();
      Serial.println("Left");
      delay(500);
    } else {
      right();
      Serial.println("Right");
      delay(500);
    }
  }
  Serial.println("Forward");
  forward();
}

int sensorOne() {
  
  digitalWrite(S1Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S1Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S1Trig, LOW);

  long t = pulseIn(S1Echo, HIGH);
  int cm = t / 29 / 2;
  return cm;
}

int sensorTwo() {
  
  digitalWrite(S2Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S2Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S2Trig, LOW);

  long t = pulseIn(S2Echo, HIGH);
  int cm = t / 29 / 2;
  return cm;
}


int sensorThree() {
  
  digitalWrite(S3Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S3Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S3Trig, LOW);

  long t = pulseIn(S3Echo, HIGH);
  int cm = t / 29 / 2;
  return cm;
}

void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void left() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void right() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
