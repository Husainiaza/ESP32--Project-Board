#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

//---DS18B20  pin connection---

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer  25
#define sensorLembab1 34
#define sensorLembab2 35


//----ISTIHAR LCD I2C --------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27,20,2);


void setup() {
  // # --- 1. Istihar digital I/O yang digunakan---
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

 Serial.begin(115200);

  //# --- Istihar Library LCD yang digunakan --- 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ESP32 - UJI LCD");
  delay(2000);
  lcd.clear();
}


void loop()
{

  digitalWrite(relay01,LOW);
  delay(1000);
  digitalWrite(relay01,HIGH);
  delay(1000);

int dataSensor1 = analogRead(sensorLembab1);
Serial.print("dataSensor1: ");
Serial.println(dataSensor1);
lcd.setCursor(0,0);
lcd.print("sensor 1 :");
lcd.setCursor(10,0);
lcd.print(dataSensor1);
delay(100);

int dataSensor2 = analogRead(sensorLembab2);
Serial.print("dataSenso21: ");
Serial.println(dataSensor2);
lcd.setCursor(0,1);
lcd.print("sensor 2 :");
lcd.setCursor(10,1);
lcd.print(dataSensor2);
delay(100);

}
