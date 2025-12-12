#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};

const int IR_PIN = 2;   
const int LED_PIN = 13;   
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int irState = digitalRead(IR_PIN);

  if (irState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  char key = keypad.getKey();
  if (key) {
    if (key == '*') {
      if (irState == HIGH) {
        BT.write(key);
        Serial.println("Sent: * (IR Active)");
      } else {
        Serial.println("* Pressed, IR OFF — Not Sent");
      }
    } else {
      BT.write(key);
      Serial.print("Sent: ");
      Serial.println(key);
    }
  }
}
