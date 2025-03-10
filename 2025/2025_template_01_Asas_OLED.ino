/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/
//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//--------------------------------------------------------------------
//=  B. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01     27 
#define relay02     26
#define buzzer      25
#define SensorSuhu  15 // pin sambungan ke DS18B20 (ONEWIRE)

//---Penentuan nama Pembolehubah nama yg diumpukkan kepada satu nilai --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//=   C.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah/constant yg diumpukkan kepada satu nilai awal  --
unsigned long lastMillis = 0;

//-=   D. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

// Istihar objek bagi Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//##################  Seksyen 1 - TAMAT #############################

//-------------------------------------------------------------------
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial
   
}
//##################  Seksyen 2 - TAMAT #############################

//-------------------------------------------------------------------
//==============  Seksyen 3 - Fungsi Utama (LOOP) ===================
//-------------------------------------------------------------------
void loop() {

  
}
//##################  Seksyen 3 - TAMAT #############################
