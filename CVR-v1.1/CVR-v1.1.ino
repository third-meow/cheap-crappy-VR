#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//gyro data (degrees/s)
imu::Vector<3> gyro;
//orientation data (degrees)
imu::Vector<3> euler;
//accelerometer data (degrees/s)
imu::Vector<3> accel;

//distance data - internal
VL53L0X_RangingMeasurementData_t dis_measurement;

//distance data - "global"
int16_t dis_mm;

String outData;

uint32_t prevLoopStart;
uint16_t loopGoal = 30;

//create BNO055
Adafruit_BNO055 godwit = Adafruit_BNO055(19, 0x29);

//create L0X
Adafruit_VL53L0X owl = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  
  if(initL0X() == false){
    Serial.print("Error: L0X not connecting");
    while (true) {;}
  }else if (initIMU() == false){
    Serial.print("Error: IMU not connecting");
    while (true) {;}
  }
}

void loop() {
  if (millis() > prevLoopStart + loopGoal){
    prevLoopStart = millis();

    updateIMU();
    dis_mm = updateL0X();

    outData = "$,";
    outData.concat(euler.x());
    outData.concat(",");
    outData.concat(euler.y());
    outData.concat(",");
    outData.concat(euler.z());
    outData.concat(",");
    outData.concat(accel.x());
    outData.concat(",");
    outData.concat(accel.y());
    outData.concat(",");
    outData.concat(accel.z());
    outData.concat(",");
    outData.concat(dis_mm);
    outData.concat(",");
    outData.concat("#");

    Serial.println(outData);
  }
}
