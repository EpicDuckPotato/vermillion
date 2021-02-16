#include <ESP8266WiFi.h>
 
void setup() {
  Serial.begin(115200);
  delay(100);
 
  boolean result = WiFi.softAP("vermillion3"); // No password at the moment
  if (result) {
    Serial.println("WiFi access point established!");
  } else {
    Serial.println("Failed to establish WiFi access point.");
  }
}
 
void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
