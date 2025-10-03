#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

#define TRIG1 12
#define ECHO1 13
#define TRIG2 2
#define ECHO2 3
#define RELAY 11

long duration;
int distance;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Wireless EV");
  lcd.setCursor(0, 1);
  lcd.print("Charging System");
  delay(2000);
  lcd.clear();

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(RELAY, LOW);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  int vehicleDetect = getDistance(TRIG1, ECHO1); 
  int parkingDistance = getDistance(TRIG2, ECHO2); 

  if (vehicleDetect < 20) {
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Detected ");
    delay(500);

    if (parkingDistance > 5 && parkingDistance < 30) { 
      lcd.setCursor(0, 1);
      lcd.print("Charging... ");
      digitalWrite(RELAY, HIGH);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Align Vehicle    ");
      digitalWrite(RELAY, LOW); 
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Vehicle       ");
    lcd.setCursor(0, 1);
    lcd.print("Waiting...       ");
    digitalWrite(RELAY, LOW);
  }

  delay(500);
}
