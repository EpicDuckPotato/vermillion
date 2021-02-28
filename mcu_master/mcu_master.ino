#include <Wire.h>
#include <Adafruit_LSM6DS33.h>

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

const int8_t self_addr = 8;

int rssi[3];

Adafruit_LSM6DS33 lsm6ds33;

void receiveEvent(int howMany)
{
  for (int i = 0; i < 3 && i < howMany; ++i) {
    if (!Wire.available()) {
      break;
    }
    rssi[i] = (signed char)Wire.read();
  }
}

void setup() {
  rssi[0] = -50;
  rssi[1] = -50;
  rssi[2] = -50;
  
  Serial.begin(9600);  // start serial for output
  Serial.println("hello world!");

  Wire.begin(self_addr);

  /*
  if (!!lsm6ds33.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find LSM6DS33 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DS33 Found!");
 
  lsm6ds33.setAccelRange(LSM6DS_ACCEL_RANGE_16_G);
  lsm6ds33.setGyroRange(LSM6DS_GYRO_RANGE_125_DPS);
  lsm6ds33.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  lsm6ds33.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  */

  Wire.onReceive(receiveEvent);
}

void loop() {
  // Get IMU

  /*
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);

  // Display the results (acceleration is measured in m/s^2)
  Serial.print("imu ");
  Serial.print(accel.acceleration.x);
  Serial.print(" ");
  Serial.print(accel.acceleration.y);
  Serial.print(" ");
  Serial.print(accel.acceleration.z);
 
  // Display the results (angular velocity is measured in rad/s)
  Serial.print(" ");
  Serial.print(gyro.gyro.x);
  Serial.print(" ");
  Serial.print(gyro.gyro.y);
  Serial.print(" ");
  Serial.print(gyro.gyro.z);
  Serial.print(" rssi");
  */
  
  for (int i = 0; i < 3; ++i) {
    Serial.print(" ");
    Serial.print(rssi[i]);
  }
  Serial.println();
  
  delay(10);
}
