/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
#include <Wire.h>

const char *beacon1 = "vermillion1";
const char *beacon2 = "vermillion2";
const char *beacon3 = "vermillion3";
const int8_t arduino_addr = 8;

int beacon1_rssi = -51;
int beacon2_rssi = -51;
int beacon3_rssi = -51;

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(beacon1_rssi);
  Wire.write(beacon2_rssi);
  Wire.write(beacon3_rssi);
}
 
void setup() {
  Serial.begin(9600);
 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(2000);
  Serial.println("Setup done");

  Wire.begin();
  Wire.onRequest(requestEvent);
}
 
int value = 0;
 
void loop() {
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks > 0) {
    for (int i = 0; i < numNetworks; ++i) {
      if (WiFi.SSID(i).equals(beacon1)) {
        beacon1_rssi = WiFi.RSSI(i); //Signal strength in dBm  
      } else if (WiFi.SSID(i).equals(beacon2)) {
        beacon2_rssi = WiFi.RSSI(i); //Signal strength in dBm  
      } else if (WiFi.SSID(i).equals(beacon3)) {
        beacon3_rssi = WiFi.RSSI(i); //Signal strength in dBm  
      }
    }
  }

  Wire.beginTransmission(arduino_addr);
  Wire.write((signed char)beacon1_rssi);
  Wire.write((signed char)beacon2_rssi);
  Wire.write((signed char)beacon3_rssi);
  Wire.endTransmission();
  Serial.println("Transmitted");

  // Wait a bit before scanning again
  delay(100);
  WiFi.scanDelete();  
}
