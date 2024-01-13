#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//---DS18B20  pin connection---
#define SENSOR_PIN  15 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer 25

//---Analog Sensor  pin connection---
#define sensorLDR 34
#define sensorVAR 36

//---Neopixel  pin connection---
#define NeoPIN    17
#define NUMPIXELS 8 

//---ultrasonic  pin connection---
#define trigPin  2
#define echoPin  4

Adafruit_NeoPixel pixels(NUMPIXELS, NeoPIN, NEO_GRB + NEO_KHZ800);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit
int dataLDR;
int distance;

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  Serial.begin(115200); // initialize serial

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
 
 pixels.begin(); // INITIALIZE NeoPixel 
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ESP32 Project BOARD");
//  display.setCursor(40, 20);
  display.display();
  delay(500);

 DS18B20.begin();    // initialize the DS18B20 sensor

   delay(2000);

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

  int dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.print(dataLDR);   
  
  int dataVAR = analogRead(sensorVAR);
  Serial.print("Cahaya: ");
  Serial.print(dataVAR);   

   pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(200); // Pause before next pass through loop
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2; 

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


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
  display.setCursor(0,45);
  display.print("BACAAN VAR  :");
  display.print(dataVAR);
  display.setCursor(0, 55);
  display.println("JARAK: ");
  display.setCursor(80, 55);
  display.println(distance);
  display.display();  
}
