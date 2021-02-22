#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "SIM800L.h"

#define ARDUINO_UNIQUE_KEY "arduino1"
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
String SERVER = "http://8d5945880567.ngrok.io";
String URL = SERVER+"/update/"+ARDUINO_UNIQUE_KEY;
String latitude,longitude;
unsigned long prev_time;
int delay_send = 3000;
bool buzzer = false;

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
  int panic_btn = digitalRead(PIN_PANIC_BTN);
  
  if (gps_serial.available() > 0){
    gps.encode(gps_serial.read());
    if (gps.location.isUpdated()){
      latitude = String(double(gps.location.lat()),6);
      longitude = String(double(gps.location.lng()),6);
//      Serial.println(latitude+longitude);
    }
  }

  if(millis()-prev_time > delay_send){
    gps_serial.flush();
    sim800_serial.listen();
    String query = "?latitude="+latitude+"&longitude="+longitude+"&panic_btn="+String(!panic_btn);
    String response = sendData(URL+query);
    buzzer = response.toInt(); 

    digitalWrite(PIN_BUZZER,buzzer);
    sim800_serial.flush();
    gps_serial.listen();
    prev_time = millis();
  }
}
