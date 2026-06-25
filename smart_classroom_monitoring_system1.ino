#include <LiquidCrystal.h>

// LCD RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


const int pirPin = 7;      
const int buzzerPin = 8;   
const int fanPin = 9;      
const int ledPin = 10;    
const int tempPin = A0;    
const int ldrPin = A1;     


int motionCount = 0;        
bool lastMotionState = LOW; 

void setup() {
  
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

 
  lcd.begin(16, 2);
  lcd.print("Smart Classroom");
  delay(2000);
  lcd.clear();
}

void loop() {
  // (TMP36)
  int rawTemp = analogRead(tempPin);
  float voltage = rawTemp * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0+1.0;

  // (0-100%)
  int rawLight = analogRead(ldrPin);
  int lightPercent = map(rawLight, 0, 1023, 0, 100);

  
  int motion = digitalRead(pirPin);
  
  if (motion == HIGH && lastMotionState == LOW) {
    motionCount++; 
  }
  lastMotionState = motion;

 

  digitalWrite(fanPin, (tempC > 30) ? HIGH : LOW);

  digitalWrite(ledPin, (lightPercent < 20) ? HIGH : LOW);

  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print((int)tempC); lcd.print("C L:"); lcd.print(lightPercent); lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("Count:"); 
  lcd.print(motionCount);
  lcd.print(" Motion:");

  if (motion == HIGH) {
    lcd.print("YES");
    digitalWrite(buzzerPin, HIGH); 
  } else {
    lcd.print("NO ");
    digitalWrite(buzzerPin, LOW);  
  }

  delay(200);
}