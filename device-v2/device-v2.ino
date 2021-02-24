#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "SIM800L.h"

#define ARDUINO_UNIQUE_KEY "DVC2FT"
#define RX_GPS 9
#define TX_GPS 8
#define RX_SIM800 10
#define TX_SIM800 11
#define RST_SIM800 12
#define PIN_PANIC_BTN 2
#define PIN_BUZZER 3

TinyGPSPlus gps;
SoftwareSerial gps_serial(RX_GPS, TX_GPS);
SoftwareSerial sim800_serial(RX_SIM800, TX_SIM800);

SIM800L* sim800l;

String APN = "indosatooredoo.com";
String SERVER = "http://famstrack.herokuapp.com";
String URL = SERVER+"/devices/"+ARDUINO_UNIQUE_KEY+"/key";
String latitude,longitude;
unsigned long prev_time;
int delay_send = 3000;
bool buzzer = false, gpsIsReady = false;

void setup(){
  pinMode(PIN_PANIC_BTN,INPUT_PULLUP);
  pinMode(PIN_BUZZER,OUTPUT);
  
  Serial.begin(9600);
  gps_serial.begin(9600);
  sim800_serial.begin(9600);
  setupModule();
//  Serial.println("---"+sendData(SERVER)+"---");
  gps_serial.listen();
  prev_time = millis();
}

void loop(){
//  int panic_btn = digitalRead(PIN_PANIC_BTN);
  
  if (gps_serial.available() > 0){
    gps.encode(gps_serial.read());
    if (gps.location.isUpdated()){
      latitude = String(double(gps.location.lat()),6);
      longitude = String(double(gps.location.lng()),6);
      gpsIsReady = true;
//      Serial.println(latitude+longitude);
    }
  }

  if (gpsIsReady){
    if(millis()-prev_time > delay_send){
      gps_serial.flush();
      sim800_serial.listen();
      String query = "?latitude="+latitude+"&longitude="+longitude;
      Serial.println("sending latitude, longitude to server...");
      String response = sendData(URL+query);
      buzzer = response.toInt();

      digitalWrite(PIN_BUZZER,buzzer);
      sim800_serial.flush();
      gps_serial.listen();
      prev_time = millis();
    }
    if(!digitalRead(PIN_PANIC_BTN)){
      delay(80);
      while(!digitalRead(PIN_PANIC_BTN)){}
      gps_serial.flush();
      sim800_serial.listen();
      
      String query = "?latitude="+latitude+"&longitude="+longitude+"&panicStatus=1";
      Serial.println("sending panic to server...");
      String response = sendData(URL+query);
      buzzer = response.toInt();
      
      sim800_serial.flush();
      gps_serial.listen(); 
    }
  }
}
