#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int BULB_PIN = 8;      // Forward movement trigger pin
const int TURN_RIGHT_PIN = 9; // New pin for turning right

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Waiting...");

  pinMode(BULB_PIN, OUTPUT);
  pinMode(TURN_RIGHT_PIN, OUTPUT);

  digitalWrite(BULB_PIN, LOW);
  digitalWrite(TURN_RIGHT_PIN, LOW);
}

void loop() {
  if (BT.available()) {
    char key = BT.read();
    Serial.print("Received: ");
    Serial.println(key);

    lcd.clear();

    if (key == '*') {
      // Forward move
      digitalWrite(BULB_PIN, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Robot Moving...");
      delay(500); 
      digitalWrite(BULB_PIN, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Waiting...");
    } 
    else if (key == '#') {
      // Right turn
      digitalWrite(TURN_RIGHT_PIN, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Turning Right...");
      delay(500); 
      digitalWrite(TURN_RIGHT_PIN, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Waiting...");
    } 
    else {
      displayBiscuitShelf(key);
    }
  }
}

void displayBiscuitShelf(char key) {
  String shelf, biscuit;

  switch (key) {
    case '1': shelf = "Shelf 1"; biscuit = "Crackers"; break;
    case '2': shelf = "Shelf 2"; biscuit = "Chocolate"; break;
    case '3': shelf = "Shelf 3"; biscuit = "Butter"; break;
    case '4': shelf = "Shelf 4"; biscuit = "Digestive"; break;
    case '5': shelf = "Shelf 5"; biscuit = "Ginger"; break;
    case '6': shelf = "Shelf 6"; biscuit = "Wafers"; break;
    case '7': shelf = "Shelf 7"; biscuit = "Coconut"; break;
    case '8': shelf = "Shelf 8"; biscuit = "Marie"; break;
    case '9': shelf = "Shelf 9"; biscuit = "Shortbread"; break;
    case '0': shelf = "Shelf 10"; biscuit = "SugarFree"; break;
    default: shelf = "Unknown"; biscuit = ""; break;
  }

  lcd.setCursor(0, 0);
  lcd.print(shelf);
  lcd.setCursor(0, 1);
  lcd.print(biscuit);
}
