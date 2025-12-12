#include <Servo.h>

#define trig 2
#define echo 4

Servo Danuja; // base
Servo Dinugi; // shoulder
Servo Chandi; // elbow
Servo ma;     // gripper

int danujaPos = 0;
int dinugiPos = 0;
int chandiPos = 0;
int maPos     = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Danuja.attach(6);
  Dinugi.attach(9);
  Chandi.attach(10);
  ma.attach(11);

  // Set initial positions
  Danuja.write(danujaPos);
  Dinugi.write(dinugiPos);
  Chandi.write(chandiPos);
  ma.write(maPos);
}

void loop() {
  long duration;
  int distance;

  // === Ultrasonic Distance Measurement ===
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // === Run Servo Logic Only If Object Detected (within 15 cm) ===
  if (distance > 0 && distance < 15) {
    delay(500);

    smoothMove(Danuja, 90, 60, 10);  
    smoothMove(Dinugi, 40, 60, 10);   
    smoothMove(Chandi,50, 80, 10);   
    delay(1000);
    smoothMove(ma, 20, 45, 10);           
    delay(300);

    smoothMove(ma, 45, 0, 10);            
    delay(1000);

    smoothMove(Chandi, 80, 50, 10);   
    smoothMove(Dinugi, 60, 40, 10);   
    delay(1000);

    smoothMove(Danuja, 60, 90, 10);   
    smoothMove(Dinugi, 40, 60, 10);   
    smoothMove(Chandi, 50, 80, 10);   
    delay(500);

    smoothMove(ma, 0, 45, 10);           maPos = 45;
    delay(1000);

    smoothMove(Chandi, 80, 50, 10);   
    smoothMove(Dinugi, 60, 40, 10);   
    delay(500);

    
  }

  delay(200); // small delay before next check
}

void smoothMove(Servo &servo, int fromAngle, int toAngle, int speedDelay) {
  if (fromAngle < toAngle) {
    for (int pos = fromAngle; pos <= toAngle; pos++) {
      servo.write(pos);
      delay(speedDelay);
    }
  } else {
    for (int pos = fromAngle; pos >= toAngle; pos--) {
      servo.write(pos);
      delay(speedDelay);
    }
  }
}
