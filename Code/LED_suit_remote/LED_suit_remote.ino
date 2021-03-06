/*
   Code: Remote for LightVest
   Modified by Eben - smartbuilds.io
   Date: 22.02.21
   
    The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

   Description:
   Push buttons can be put on Pin 10 and 11 for indicator lights. More info: smartbuilds.io
*/

#include<Wire.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin_Left = 3;     // the number of the pushbutton pin
const int buttonPin_Right = 4;     // the number of the pushbutton pin

const int ledPin_Left =  8;      // the number of the LED pin
const int ledPin_Right =  7;      // the number of the LED pin


// variables will change:
int buttonState_Left = 0;         // variable for reading the pushbutton status
int buttonState_Right = 0;         // variable for reading the pushbutton status


const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

bool bool_caliberate = false;
int response_time = 400;


bool offset_pos = false;



void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin_Left, OUTPUT);
  pinMode(ledPin_Right, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin_Left, INPUT);
  pinMode(buttonPin_Right, INPUT);

  //  // variables will change:
  //  buttonState_Left = 0;         // variable for reading the pushbutton status
  //  buttonState_Right = 0;         // variable for reading the pushbutton status

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);// PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); Wire.begin();
  Serial.begin(9600);
  delay(1000);

}

void loop() {

  //debug modes
  // button_debug();
  MPU_debug();

  //create some time of peak offset that needs to be triggered first

  // read the state of the pushbutton value:
  buttonState_Left = digitalRead(buttonPin_Left);
  buttonState_Right = digitalRead(buttonPin_Right);
  //
  //    Serial.print("Left: ");
  //    Serial.print(buttonState_Left);
  //    Serial.print("\t");
  //    Serial.print("Right: ");
  //    Serial.println(buttonState_Right);



  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState_Left == HIGH) {
    // turn LED on:
    Serial.print("L");
    digitalWrite(ledPin_Left, HIGH);
    delay(500);
    buttonState_Right = 0;
  } else {
    // turn LED off:
    digitalWrite(ledPin_Left, LOW);
  }

  if (buttonState_Right == HIGH) {
    // turn LED on:
    Serial.print("R");
    digitalWrite(ledPin_Right, HIGH);
    delay(500);
    buttonState_Left = 0;

  } else {
    // turn LED off:
    digitalWrite(ledPin_Right, LOW);
    buttonState_Left = LOW;
    buttonState_Right = LOW;
  }



  //-------------------------------------
  GetMpuValue1(MPU_addr);

//
  if (offset_pos == false) {
    //  //  //Move right
    if ( GyZ > 15000) {
      Serial.println("L");
      digitalWrite(ledPin_Left, HIGH);
      digitalWrite(ledPin_Right, LOW);
      offset_pos = true;

      delay(response_time);
    }
  }

  if (offset_pos == true) {
    if ( GyZ > 15000) {
      Serial.println("L Offset centre");
      offset_pos = false;
      delay(response_time);
    }
  }


  if (offset_pos == true) {
    if ( GyZ < -15000) {
      Serial.println("R Offset centre");      ;
      delay(response_time);
      offset_pos = false;

    }
  }



  if (offset_pos == false) {
    //  //Move right
    if ( GyZ < -15000) {
      Serial.println("R");
      digitalWrite(ledPin_Right, HIGH);
      digitalWrite(ledPin_Left, LOW);
      delay(response_time);
      offset_pos = true;

    }
  }



}

void button_debug() {
  Serial.print("Left: ");
  Serial.print(buttonState_Left);
  Serial.print("\t");
  Serial.print("Right: ");
  Serial.println(buttonState_Right);

}


void GetMpuValue1(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers

  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 |  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4; //offset by 4 degrees to get back to zero
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

}

void MPU_debug() {

  //  Serial.print("AngleX= ");
  //  Serial.print(x);
  //  Serial.print("\t");
  //
  //  Serial.print("AngleY= ");
  //  Serial.print(y);
  //  Serial.print("\t");
  //
  //  Serial.print("AngleZ= ");
  //  Serial.println(z);
  //  Serial.print("\t");
  //  Serial.println("-----------------------------------------");

  //  Serial.print("AcX = ");
  //  Serial.print(AcX1);
  //  Serial.print(" | AcY = ");
  //  Serial.print(AcY1);
  //  Serial.print(" | AcZ = ");
  // Serial.print(AcZ1);

  //
//    Serial.print(" | GyX = ");
//    Serial.print(GyX);
//    Serial.print(" | GyY = ");
//    Serial.print(GyY);
//    Serial.print(" | GyZ = ");
//    Serial.println(GyZ);

}
