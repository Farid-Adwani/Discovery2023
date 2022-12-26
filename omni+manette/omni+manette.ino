/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

int m11=2;
int m12=3;
int m21=4;
int m22=5;
int m31=8;
int m32=9;
int vit=190;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void translaterRight(){
analogWrite(m11,vit);
analogWrite(m12,LOW);
analogWrite(m21,vit-120);
analogWrite(m22,LOW);
analogWrite(m31,LOW);
analogWrite(m32,vit-120);
  }

  void translaterLeft(){
analogWrite(m11,LOW);
analogWrite(m12,vit);
analogWrite(m21,LOW);
analogWrite(m22,vit-120);
analogWrite(m31,vit-120);
analogWrite(m32,LOW);
  }

void left(){
analogWrite(m11,LOW);
analogWrite(m12,vit);
analogWrite(m21,vit);
analogWrite(m22,LOW);
analogWrite(m31,LOW);
analogWrite(m32,vit);
  }
void right(){
analogWrite(m11,vit);
analogWrite(m12,LOW);
analogWrite(m21,LOW);
analogWrite(m22,vit);
analogWrite(m31,vit);
analogWrite(m32,LOW);
  }
  void back(){
analogWrite(m11,LOW);
analogWrite(m12,LOW);
analogWrite(m21,LOW);
analogWrite(m22,vit);
analogWrite(m31,LOW);
analogWrite(m32,vit);
}
void forward(){
analogWrite(m11,LOW);
analogWrite(m12,LOW);
analogWrite(m21,vit);
analogWrite(m22,LOW);
analogWrite(m31,vit);
analogWrite(m32,LOW);
}
void stoop(){
analogWrite(m11,LOW);
analogWrite(m12,LOW);
analogWrite(m21,LOW);
analogWrite(m22,LOW);
analogWrite(m31,LOW);
analogWrite(m32,LOW);
}

void setup() {
 pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
pinMode(m31,OUTPUT);
pinMode(m32,OUTPUT);
  Serial.begin(115200);


delay(10000);
//  byte status = mpu.begin();
//  Serial.print(F("MPU6050 status: "));
//  Serial.println(status);
//  while(status!=0){ } // stop everything if could not connect to MPU6050
//  
//  Serial.println(F("Calculating offsets, do not move MPU6050"));
//  delay(1000);
//  mpu.calcOffsets(); // gyro and accelero
//  Serial.println("Done!\n"); 

  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
//    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
//      Serial.print(F("\r\nLeftHatX: "));
//      Serial.print(PS3.getAnalogHat(LeftHatX));
//      Serial.print(F("\tLeftHatY: "));
//      Serial.print(PS3.getAnalogHat(LeftHatY));
//      if(PS3.getAnalogHat(LeftHatX) > 157){
//        right();
//        Serial.print(F("rrrr "));
//      }else if(PS3.getAnalogHat(LeftHatX) <97 ){
//        left();
//        Serial.print(F("lll "));
//      }
//      else if(PS3.getAnalogHat(LeftHatY) >157 ){
//        forward();
//        Serial.print(F("fff "));
//      }
//      else if(PS3.getAnalogHat(LeftHatY) <97 ){
//        back();
//        Serial.print(F("bbb "));
//      }
//      else if(PS3.getAnalogHat(LeftHatX) < 157 && PS3.getAnalogHat(LeftHatX) > 97 && PS3.getAnalogHat(LeftHatY) < 157 && PS3.getAnalogHat(LeftHatY) >97 ){
//        stoop();
//        Serial.print(F("sss "));
//        }
//      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
//        Serial.print(F("\tRightHatX: "));
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print(F("\tRightHatY: "));
//        Serial.print(PS3.getAnalogHat(RightHatY));
//        
//        if(PS3.getAnalogHat(LeftHatX) > 157){
//        translaterRight();
//        Serial.print(F("rrrr "));
//      }else if(PS3.getAnalogHat(LeftHatX) <97 ){
//        translaterLeft();
//        Serial.print(F("lll "));
//      }
//     
//      
//      }
//    }
//    else{
//        stoop();
//        Serial.print(F("sss "));
//        }

    // Analog button values can be read from almost all buttons
//    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
//      Serial.print(F("\r\nL2: "));
//      Serial.print(PS3.getAnalogButton(L2));
//      if (PS3.PS3Connected) {
//        Serial.print(F("\tR2: "));
//        Serial.print(PS3.getAnalogButton(R2));
//      }
//    }

//    if (PS3.getButtonClick(PS)) {
//      Serial.print(F("\r\nPS"));
//      PS3.disconnect();
//    }
//    else {
//      if (PS3.getButtonClick(TRIANGLE)) {
//        Serial.print(F("\r\nTriangle"));
//      }
      if (PS3.getButtonClick(CIRCLE)) {
        translaterRight();
        Serial.print(F("\r\nCircle"));
      }
      else if (PS3.getButtonClick(CROSS))
      {
        stoop();
        Serial.print(F("\r\nCross"));
      }
      else if (PS3.getButtonClick(SQUARE)){
      translaterLeft();
        Serial.print(F("\r\nSquare"));}

     else  if (PS3.getButtonClick(UP)) {
        forward();
//        Serial.print(F("\r\nUp"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED4);
//        }
      }
      else if (PS3.getButtonClick(LEFT)) {
        left();
//        Serial.print(F("\r\nLeft"));
//        mpu.update();
//         int zero=mpu.getAngleZ();
//
//            while(abs(mpu.getAngleZ()-(zero+90))>1){
//               mpu.update();
//               Serial.println(mpu.getAngleZ());
//               if(mpu.getAngleZ()-(zero+90)<0){
//               left();}else{
//                
//                right();
//                }
//              
//            }

      }
      else if (PS3.getButtonClick(DOWN)) {
        back();
//        Serial.print(F("\r\nDown"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED2);
//        }
      }
      else if (PS3.getButtonClick(RIGHT)) {
        right();
//        Serial.print(F("\r\nRight"));
//        mpu.update();
//         int zero=mpu.getAngleZ();
//
//            while(abs(mpu.getAngleZ()-(zero-90))>1){
//               mpu.update();
//               Serial.println(mpu.getAngleZ());
//               if(mpu.getAngleZ()-(zero-90)<0){
//               left();}else{
//                
//                right();
//                }
//              
//            }

      }
//      else{
//        stoop();
//      }

//      if (PS3.getButtonClick(L1))
//        Serial.print(F("\r\nL1"));
//      if (PS3.getButtonClick(L3))
//        Serial.print(F("\r\nL3"));
//      if (PS3.getButtonClick(R1))
//        Serial.print(F("\r\nR1"));
//      if (PS3.getButtonClick(R3))
//        Serial.print(F("\r\nR3"));
//
//      if (PS3.getButtonClick(SELECT)) {
//        Serial.print(F("\r\nSelect - "));
//        PS3.printStatusString();
//      }
//      if (PS3.getButtonClick(START)) {
//        Serial.print(F("\r\nStart"));
//        printAngle = !printAngle;
//      }
//    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
#if 0 // Set this to 1 in order to enable support for the Playstation Move controller
  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
#endif
}
