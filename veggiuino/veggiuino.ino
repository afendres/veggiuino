// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// include the library code:
#include <avr/pgmspace.h>
#include <Wire.h>

/** Begin DISPLAY  *********************************************************************************/
#include <LiquidCrystal.h>
/** End DISPLAY  ***********************************************************************************/

/** Begin RELOGIO  *********************************************************************************/
#include <RTClib.h>
RTC_DS1307 RTC;
/** End RELOGIO  ***********************************************************************************/


/**************** PINOS ****************/

/**** DIGITAIS ****/
#define DIGITAL_0 0
  #define DHT11PIN DIGITAL_0
#define DIGITAL_1 1
#define DIGITAL_2 2
#define DIGITAL_3 3
#define DIGITAL_4 4
  #define LCD_3 DIGITAL_4
#define DIGITAL_5 5
  #define LCD_4 DIGITAL_5
#define DIGITAL_6 6
  #define LCD_5 DIGITAL_6
#define DIGITAL_7 7
  #define LCD_6 DIGITAL_7
#define DIGITAL_8 8
  #define LCD_1 DIGITAL_8
#define DIGITAL_9 9
  #define LCD_2 DIGITAL_9
#define DIGITAL_10 10
#define DIGITAL_11 11
#define DIGITAL_12 12
#define DIGITAL_13 13


/*** ANALOGICOS ***/
#define ANALOG_0 A0
#define ANALOG_1 A1
  #define DHTPIN            A1         // Pin which is connected to the DHT sensor.
#define ANALOG_2 A2
#define ANALOG_3 A3
#define ANALOG_4 A4
#define ANALOG_5 A5


/************** FIM PINOS **************/

/***************************************************************************************************/
/** Begin DISPLAY  *********************************************************************************/

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystal lcd(LCD_1, LCD_2, LCD_3, LCD_4, LCD_5, LCD_6);




// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Wire.begin();
  RTC.begin();

  //if (! RTC.isrunning()) {
   // Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // RTC.adjust(DateTime(__DATE__, __TIME__));
  //}

  //set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  Serial.begin(9600); 
  // Initialize device.
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  DateTime now = RTC.now();
  
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");

    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(6,0);
    lcd.print(event.temperature);
    lcd.setCursor(10,0);
    //º alt 167 //lcd.print("\377C");
    //The degree symbol is 0xdf or 223 decimal or 337 octal vs 377 octal on my lcd.
    //lcd.print("\262C");
    //If you see greek alpha letter try typing 178 instead of 223.
    lcd.write(B11011111);
    lcd.print("C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
    
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.setCursor(9,1);
    lcd.print(event.relative_humidity);
    lcd.setCursor(14,1);
    lcd.print("%");
  }


}
