#include "IMU_Fusion_SYC.h"

IMU imu(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  imu.begin(CHOOSE_MPU6050);
  imu.MPU6050_CalcGyroOffsets();
}

void loop() {
  imu.Calculate();
  Serial.print("\n*********************************************************\n");
  Serial.print("acc x: ");
  Serial.print(imu.getaccx());
  Serial.print("\t");
  Serial.print("acc y: ");
  Serial.print(imu.getaccy());
  Serial.print("\t");
  Serial.print("acc z: ");
  Serial.println(imu.getaccz());

  Serial.print("gyro x: ");
  Serial.print(imu.getgyrox());
  Serial.print("\t");
  Serial.print("gyro y: ");
  Serial.print(imu.getgyroy());
  Serial.print("\t");
  Serial.print("gyro z: ");
  Serial.print(imu.getgyroz());
  Serial.print("\t");
  Serial.print("\n*********************************************************\n");
  delay(1000);

}
