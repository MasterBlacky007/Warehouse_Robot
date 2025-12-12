// Motor pins
const int motorA1 = 8;   // IN1
const int motorA2 = 9;   // IN2
const int motorB1 = 10;  // IN3
const int motorB2 = 11;  // IN4

const int ENA = 5;  
const int ENB = 6;  

// IR sensor pins
const int S1 = 2;   // Left
const int S2 = 3;
const int S3 = 4;   // Center
const int S4 = 7;
const int S5 = 12;  // Right

// Jump Button
const int trigger1 = A0;  
const int trigger2 = A1; 
const int trigger3 = A2;  

// Motor speed
const int motorSpeed = 150;  

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(trigger1, INPUT);
  pinMode(trigger2, INPUT);
  pinMode(trigger3, INPUT);
}

void loop() {
  
  if (digitalRead(trigger1) == HIGH || digitalRead(trigger2) == HIGH) {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
    delay(10);
    stopMotors();
    return;  
  }

  if (digitalRead(trigger3) == HIGH) {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(ENA, motorSpeed / 2); 
    analogWrite(ENB, motorSpeed);
    delay(10);
    stopMotors();
    return;  
  }

  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  if (s3 == LOW) {
    forward();
  } else if (s2 == LOW) {
    left();
  } else if (s4 == LOW) {
    right();
  } else if (s1 == LOW) {
    sharpLeft();
  } else if (s5 == LOW) {
    sharpRight();
  } else {
    stopMotors();
  }
}

void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void left() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(ENA, motorSpeed / 2); 
  analogWrite(ENB, motorSpeed);
}

void right() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed / 2); 
}

void sharpLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void sharpRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
