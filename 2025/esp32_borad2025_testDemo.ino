#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//---Actuator and Relay  pin connection---
#define relay01 26 
#define relay02 27
#define buzzer 25
#define sensorVar 35
#define sensorLDR 36
#define SENSOR_PIN  15 // DS18B20 sensor's DAQ pin


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

LiquidCrystal_I2C lcd(0x27,20,4);

//---istihar variable yang hendak digunakan
float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);
 
  Serial.begin(115200); // initialize serial
  DS18B20.begin();      // initialize the DS18B20 sensor

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ESP32 Project BOARD");
  display.display();

  lcd.init();        // initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("- ESP32 Board -");
  delay(5000);
  lcd.clear();
}

void loop() {

  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
  tempF = tempC * 9 / 5 + 32; // convert °C to °F

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  lcd.setCursor(0,1);
  lcd.print("SUHU :");
  lcd.setCursor(8,1);
  lcd.print(tempC);

  digitalWrite(buzzer,HIGH);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,HIGH);
  lcd.setCursor(0,0);
  lcd.print("BUZ ON  RLY OFF ");  
  delay (1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,HIGH);
  lcd.setCursor(0,0);
  lcd.print("BUZ OFF RLY 1 ON");  
  delay (1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,LOW);
  lcd.setCursor(0,0);
  lcd.print("BUZ OFF RLY 2 ON");  
  delay (1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,HIGH);
  lcd.setCursor(0,0);
  lcd.print("BUZ OFF RLY  OFF"); 
  delay (1000);

  display.clearDisplay();

  int dataVar = analogRead(sensorVar);
  Serial.print("Data Var: ");
  Serial.println(dataVar);

  int dataLDR = analogRead(sensorLDR);
  Serial.print("Data LDR: ");
  Serial.println(dataLDR);

  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println(" IoT Project Board");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(0,25);
  display.print("BACAAN SUHU :");
  display.print(tempC,1);
   
  display.setCursor(0,35);
  display.print("BACAAN Var :");
  display.print(dataVar);

  display.setCursor(0,45);
  display.print("BACAAN Var :");
  display.print(dataLDR);

  display.display();  
}
