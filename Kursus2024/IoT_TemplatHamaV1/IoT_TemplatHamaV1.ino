#include <OneWire.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>

//----ISTIHAR GPIO PIN anda kumpulkan disini ---------------------------------------------------------------------------------

//---=on board internal conection to esp32 pin------
#define oneWireBus 15  //--SENSOR SUHU DS18B20
#define Relay01 27   //relay 1
#define Relay02 26   // relay 2
#define buzzer  25     // Buzzer

//--- device/sensor OFF board -----
#define analogLDR 34
//----------------------------------- end -------------------------------------------------------------


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// ISTIHAR SSD1306 I2C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//----ISTIHAR LCD I2C --------------------------------------------------------------
LiquidCrystal_I2C lcd(0x3f,20,4); //0x38

//----ISTIHAR SENSOR SUHU DS18B20 ---------------------------------------------------------------------
 
OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);
//----------------------------------- end -------------------------------------------------------------


//---- PENETAPAN WIFI ---------------------------------------------------------------------------------
// --- ubah mengikut wifi masing masing ----------
//const char* ssid = "GUEST";  
//const char* password = "";

//------WIFIiphone AZA---
//const char* ssid = "HaMa iPhone 13";  
//const char* password = "1234556790"; 

//------WIFIi lab IoT MM kksbj--
//const char* ssid = "iot";  
//const char* password = "iot@kksj2023"; 


//-------------------------------------------------------------------------------
WiFiClient espClient;                                                                          
PubSubClient client(espClient); //MQTT

const char* mqtt_server = "broker.hivemq.com";

//----------------------------------- end -------------------------------------------------------------



//---- PEMBOLEHUBAH DATA---------------------------------------------------------------------------------

char varPotString[8];
long lastMsg = 0;
char msg[50];
int value = 0;
float light;


//----------------------------------- end ---------------------------------------------


void setup() {
  pinMode (Relay01,OUTPUT);
  pinMode (Relay02,OUTPUT);
  pinMode (buzzer,OUTPUT);
 
  Serial.begin(115200);
 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ESP32 Project BOARD");


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ESP32 Project BOARD");
  display.display();
   
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(100);  
  
  DS18B20.begin();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ESP32 Project BOARD");
}


void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();


  long now = millis();

   

  if (now - lastMsg > 1000) {  
    lastMsg = now;


          //-----------------------------------------------------------------------
          //---mulakan sensor kod anda disini--
      

        sensorCahaya();
        sensorSuhu();
          //-------------------end ------------------------------------------------
  }
}