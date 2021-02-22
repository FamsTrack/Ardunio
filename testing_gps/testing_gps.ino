#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 9, TXPin = 8;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial gps_serial(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  gps_serial.begin(GPSBaud);
  delay(2000);
}
String dataposisi;
void loop(){
  while (gps_serial.available() > 0){
    gps.encode(gps_serial.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);      
    }
  }
}
