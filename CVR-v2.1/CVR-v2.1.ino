#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Mouse.h>

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
  if(initL0X() == false){
    while (true) {;}
  }else if (initIMU() == false){
    while (true) {;}
  }
  Mouse.begin();
}

void loop() {
  if (millis() > prevLoopStart + loopGoal){
    prevLoopStart = millis();

    updateIMU();
    dis_mm = updateL0X();

    Mouse.move(map(gyro.z(), -4000, 4000, 80, -80), map(gyro.x(), -4000, 4000, 110, -110), 0);
    
  }
}
