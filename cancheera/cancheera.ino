//--------------------------------------------------------------------------
//----Seksyen 1 - HEADER  ------------- ----

//--------------------------------------------------------------------------
//-----a Library  include and define  yang diperlukan ----
//--------------------------------------------------------------------------

#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <MQTT.h>
#include "MAX30100_PulseOximeter.h"



//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer 25
#define SensorSuhu  4 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorLDR 34
//---Analog Sensor  pin connection---

//---Tentukan nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define REPORTING_PERIOD_MS     500

PulseOximeter pox;
uint32_t tsLastReport = 0;

//-----d.  - ISTIHAR  constant dan pembolehubah------------------------------

const char ssid[] = "OHNANANA";
const char pass[] = "ILOVEYOU555";

//const char ssid[] = "IoT";
//const char pass[] = "iot@kksj2023";

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---

unsigned long lastMillis = 0;

float dataSuhuC; // suhu dalam Celsius
int dataLDR;
float BPM, SpO2;
char statusSuhu[20];

//-----e. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature DS18B20(&oneWire);

//------------------------------Seksyen 1 - TAMAT --------------------- ----

//-----Seksyen 2 - Fungsi Setup --------------------------------------------
//--------------------------------------------------------------------------
void onBeatDetected()
{
    Serial.println("Beat!");
}
void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, pass);

  client.begin("broker.hivemq.com", net);
  client.onMessage(messageReceived);

  connect();

  Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);

  DS18B20.begin();    // initialize the DS18B20 sensor
  


}
//------------------------------Seksyen 2 - TAMAT --------------------- ----


//-----Seksyen 3 - Fungsi Utama (LOOP) --------------------------------------------
//--------------------------------------------------------------------------
void loop() {

 client.loop();
 // delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

// publish a message roughly every second.
// if (millis() - lastMillis > 1000) {
//  lastMillis = millis();

//------sensor OXY -------------------------------------------------------
  pox.update();
  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.println(" bpm / SpO2:");
       
        Serial.print(SpO2);
        Serial.println(" %");
        tsLastReport = millis();   

        client.publish("cancheera/bpm", String(BPM));
        client.publish("cancheera/spo", String(SpO2));

      
   DS18B20.requestTemperatures(); 
   dataSuhuC = DS18B20.getTempCByIndex(0);
  
  Serial.print(dataSuhuC);
   Serial.println(" ºC");
  client.publish("cancheera/temp", String(dataSuhuC));
}

//-----------------------------------------------------------


}

//------------------------------Seksyen 3 - TAMAT --------------------- ----