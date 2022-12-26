
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

char val;
int md1=2;
int md2=3;
int mg1=5;
int mg2=4;
int vit=100;




void setup(){
Serial.begin(9600);
pinMode(md1,OUTPUT);
pinMode(md2,OUTPUT);
pinMode(mg1,OUTPUT);
pinMode(mg2,OUTPUT);
Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n"); 
} 


void left(){
analogWrite(md1,LOW);
analogWrite(md2,vit);
analogWrite(mg1,LOW);
analogWrite(mg2,vit);
  }
void right(){
analogWrite(md1,vit );
analogWrite(md2,LOW);
analogWrite(mg1,vit);
analogWrite(mg2,LOW);
  }
  void back(){
analogWrite(md1,LOW);
analogWrite(md2,vit);
analogWrite(mg1,vit);
analogWrite(mg2,LOW);
}
void forward(){
analogWrite(md1,vit);
analogWrite(md2,LOW);
analogWrite(mg1,LOW);
analogWrite(mg2,vit);
}
void stoop(){
analogWrite(md1,LOW);
analogWrite(md2,LOW);
analogWrite(mg1,LOW);
analogWrite(mg2,LOW);
}


void loop(){
  mpu.update();
  
  if((millis()-timer)>10){ // print data every 10ms
  Serial.println(mpu.getAngleZ());
  timer = millis();  
  }

 int zero=mpu.getAngleZ();

while(abs(mpu.getAngleZ()-(zero+90))>1){
   mpu.update();
   Serial.println(mpu.getAngleZ());
   if(mpu.getAngleZ()-(zero+90)<0){
   left();}else{
    
    right();
    }
  
}



stoop();
delay(1000);
mpu.update();
   Serial.println(mpu.getAngleZ());

 delay(2000);
if(Serial.available())
{val=Serial.read(); 
Serial.println(val);


if(val=='R'){                
 right();

}
if(val=='L'){            
left();
}
if(val=='B'){                  
back();

} 
if(val=='F'){             
forward();
}
if(val=='S'){             
stoop();
}



}




}
