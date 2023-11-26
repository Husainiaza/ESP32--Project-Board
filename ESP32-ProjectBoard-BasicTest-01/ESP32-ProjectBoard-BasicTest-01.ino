#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SENSOR_PIN  15 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin
#define relay01 27 
#define relay02 26
#define buzzer 25
#define sensorLDR 25

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit
int dataLDR;

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(115200); // initialize serial

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
  delay(500);

  DS18B20.begin();    // initialize the DS18B20 sensor
  delay(500);

}

void loop() {

  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
  tempF = tempC * 9 / 5 + 32; // convert °C to °F

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  ");  // separator between °C and °F
  Serial.print(tempF);    // print the temperature in °F
  Serial.println("°F");
  
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,HIGH);
  delay (500);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,HIGH);
  delay (500);
  digitalWrite(relay02,HIGH);
  digitalWrite(relay01,HIGH);
  delay (500);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,LOW);
  delay (500);
  digitalWrite(buzzer,HIGH);
  delay (500);
  digitalWrite(buzzer,LOW);
  delay (500);
  display.clearDisplay();

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
  display.print("BACAAN LDR  :");
  display.print(dataLDR);
  display.display();  
}
