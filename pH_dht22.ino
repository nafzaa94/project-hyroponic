//DHT SENSOR
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//PH SENSOR
#include <Anyleaf.h>
PhSensor phSensor;

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//RELAY
int relay = 7;

int pH = 0;

void setup() {
  
  Serial.begin(9600);
  lcd.init();
  dht.begin();
  pinMode(relay, OUTPUT);
  lcd.backlight();
  digitalWrite(relay , HIGH);

  phSensor = PhSensor();

  phSensor.calibrate_all(CalPt(0., 7., 25.), CalPt(0.17, 4., 25.));
}

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  pH = phSensor.read();
  

  if (h <= 60 ||  t <= 30){
    digitalWrite(relay, LOW);
  }

  if (h >= 70 || t >= 70){
    digitalWrite(relay,HIGH);
  }

  lcd.setCursor(1,0);
  lcd.print("PH= ");
  lcd.setCursor(5, 0);
  lcd.print("  ");
  lcd.setCursor(5, 0);
  lcd.print(pH);
  

  lcd.setCursor(0, 1);
  lcd.print("TEMP = ");
  lcd.setCursor(6, 0);
  lcd.print("    ");
  lcd.setCursor(6, 0);
  lcd.print(t, 1);

  lcd.setCursor(10, 0);
  lcd.print("HUM");
  lcd.setCursor(12, 1);
  lcd.print("   ");
  lcd.setCursor(10, 1);
  lcd.print("= ");
  lcd.setCursor(12, 1);
  lcd.print(h, 1);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" Temperature: ");
  Serial.print(t);
  Serial.println(" °C ");

  Serial.print("pH: "); 
  Serial.println(pH);
   

  delay(2000);
}
