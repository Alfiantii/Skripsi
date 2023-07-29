#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Inisialisasi objek LCD

const int triggerPin = 13;  // Pin trigger sensor ultrasonik
const int echoPin = 12;     // Pin echo sensor ultrasonik
const int relayPin = 8;    // Pin relay

const int brightLevel = 255;  // Kecerahan layar (0-255)

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Selamat datang!");
  delay(2000);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  
  if (distance < 21) {
    digitalWrite(relayPin, HIGH);  // Mematikan relay
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ketinggian Air");
    lcd.setCursor(0, 1);
    lcd.print("sudah penuh");
  } else {
    digitalWrite(relayPin, LOW);  // Menyalakan relay
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ketinggian Air");
    lcd.setCursor(0,1); 
    lcd.print(distance);
    lcd.setCursor(3,1);
    lcd.print("cm");
    delay(1000);
  }

  
  analogWrite(9, brightLevel);  // Mengatur kecerahan layar menjadi terang
  delay(1000);
}
 
