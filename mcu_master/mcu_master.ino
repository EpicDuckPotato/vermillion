#include <Wire.h>
#include <Adafruit_LSM6DS33.h>

const int8_t wifi_addr = 8;
const int8_t imu_addr = 0x6A;
const int wifi_delay = 50; // Wifi takes a while to scan, so only request it every 0.5 seconds
int wifi_counter;

int rssi[3];

Adafruit_LSM6DS33 lsm6ds33;

void setup() {
  Serial.begin(9600);  // start serial for output
  Wire.begin();        // join i2c bus (address optional for master)
  wifi_counter = 0;
  rssi[0] = -50;
  rssi[1] = -50;
  rssi[2] = -50;

  if (!lsm6ds33.begin_I2C()) {
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
}

void loop() {
  // Get IMU
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("imu ");
  Serial.print(accel.acceleration.x);
  Serial.print(" ");
  Serial.print(accel.acceleration.y);
  Serial.print(" ");
  Serial.print(accel.acceleration.z);
 
  /* Display the results (rotation is measured in rad/s) */
  Serial.print(" ");
  Serial.print(gyro.gyro.x);
  Serial.print(" ");
  Serial.print(gyro.gyro.y);
  Serial.print(" ");
  Serial.println(gyro.gyro.z);

  wifi_counter++;
  if (wifi_counter > wifi_delay) {
    wifi_counter = 0;
    Wire.requestFrom(wifi_addr, 3);

     // slave may send less than requested, which is why
     // we call Wire.available()
    for (int i = 0; i < 3 && Wire.available(); ++i) {
      rssi[i] = Wire.read();
    }
    Serial.print("rssi ");
    Serial.print(rssi[0]);
    Serial.print(" ");
    Serial.print(rssi[1]);
    Serial.print(" ");
    Serial.println(rssi[2]);
  }
  
  delay(10);
}
