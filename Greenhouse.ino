int sensor_pin = A0;
int relay_pin = 7;
int dhtpin = 4;

#define DHTTYPE DHT11
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>


LiquidCrystal_I2C lcd(0x27,16,2);


DHT_Unified dht(dhtpin, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  pinMode(sensor_pin , INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(dhtpin,INPUT);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  lcd.init();
  lcd.backlight();
  delayMS = sensor.min_delay / 1000;

}

void loop() {

  delay(delayMS);
  int sensor_data = analogRead(sensor_pin);
  Serial.print("Sensor Data: ");
  Serial.print(sensor_data);

  sensors_event_t event;

  //lcd commands for temp and humidity
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.setCursor(2, 1);
  dht.humidity().getEvent(&event);
  lcd.print(event.relative_humidity);

  lcd.setCursor(8,1);
  lcd.print("T:");
  lcd.setCursor(10, 1);
  dht.temperature().getEvent(&event);
  lcd.print(event.temperature);

  float wetness = ((1023 - sensor_data) / 1023.0 * 100);

  if(sensor_data > 650){

    Serial.print("\t Low moisture, Soil is dry");
    digitalWrite(relay_pin, LOW);
    Serial.print("\t Temperature: ");
    dht.temperature().getEvent(&event);
    Serial.print(event.temperature);
    Serial.print("\t Humidity: ");
    dht.humidity().getEvent(&event);
    Serial.println(event.relative_humidity);

    //lcd commands
    lcd.setCursor(0,0);
    lcd.print("Moisture:");
    lcd.print(wetness);
    lcd.print("%");
    
  }
  else if(sensor_data < 650){
    Serial.print("\t Soil is wet");
    digitalWrite(relay_pin, HIGH);
    Serial.print("\t Temperature: ");
    dht.temperature().getEvent(&event);
    Serial.print(event.temperature);
    Serial.print("\t Humidity: ");
    dht.humidity().getEvent(&event);
    Serial.println(event.relative_humidity);

    //lcd commands
    lcd.setCursor(0,0);
    lcd.print("Moisture:");
    lcd.print(wetness);
    lcd.print("%");

  }

}