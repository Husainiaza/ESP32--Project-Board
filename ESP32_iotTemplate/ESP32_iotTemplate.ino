#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>

//----ISTIHAR GPIO PIN anda kumpulkan disini ---------------------------------------------------------------------------------

//---=on board------
#define oneWireBus 15  //--SENSOR SUHU DS18B20
#define Relay01 27   //relay 1
#define Relay02 26   // relay 2
#define buzzer  25     // Buzzer

//--- device/sensor OFF board ------
#define analogSensor1 33
#define analogSensor2 35
#define analogSensor3 36
//----------------------------------- end -------------------------------------------------------------


//----ISTIHAR LCD I2C --------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27,20,4);




//----ISTIHAR SENSOR SUHU DS18B20 ---------------------------------------------------------------------
 
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
//----------------------------------- end -------------------------------------------------------------




//---- PENETAPAN WIFI ---------------------------------------------------------------------------------
// --- ubah mengikut wifi masing masing ----------
const char* ssid = "GUEST";  
const char* password = "";


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
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  namakan projek anda  ");
   
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(100);  
   
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Namakan projek anda ");
}


void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();


  long now = millis();


  if (now - lastMsg > 5000) {  
    lastMsg = now;


          //-----------------------------------------------------------------------
          //---mulakan sensor kod anda disini--
         
          //-------------------end ------------------------------------------------
  }
}
