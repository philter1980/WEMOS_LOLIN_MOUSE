/**
 * This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.
 */
#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


Adafruit_MPU6050 mpu;
BleMouse bleMouse;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define NUMFLAKES     10 // Number of snowflakes in the animation example
int previous = 0;
int sensorPin = A0; 


void setup() {
  //Serial.begin(115200);
  //Serial.println("Starting BLE work!");

  Wire.begin(5,4);
  bleMouse.begin();
  if (!mpu.begin()) {
    while (1) {
      delay(10);
      }
    }

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) { 
      while (1) {
      delay(10);
      }
    }

  //Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    break;
  case MPU6050_RANGE_4_G:
    break;
  case MPU6050_RANGE_8_G:
    break;
  case MPU6050_RANGE_16_G:
    break;
  }
  
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    break;
  case MPU6050_RANGE_500_DEG:
    break;
  case MPU6050_RANGE_1000_DEG:
    break;
  case MPU6050_RANGE_2000_DEG:
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    break;
  case MPU6050_BAND_184_HZ:
    break;
  case MPU6050_BAND_94_HZ:
    break;
  case MPU6050_BAND_44_HZ:
    break;
  case MPU6050_BAND_21_HZ:
    break;
  case MPU6050_BAND_10_HZ:
    break;
  case MPU6050_BAND_5_HZ:
    break;
  }





} //END SETUP




void loop() {
  sensors_event_t a, g, temp;

mpu.getEvent(&a, &g, &temp);

    /************************************/
  if(temp.temperature != previous) {
   // Clear the buffer.
  display.clearDisplay();
  
  // Draw temperature
    display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.print(temp.temperature);
  display.println(F(" degC"));
  display.display();      // Show initial text
  previous = temp.temperature;
  }
  /************************************/

  if(bleMouse.isConnected()) 
  {
    
   bleMouse.move(a.acceleration.x,a.acceleration.y);
    
   if (analogRead(sensorPin) > 10)
     {
     delay(200);
     if (analogRead(sensorPin) > 10)
      {
       bleMouse.click(MOUSE_LEFT);
      }
     }
  }
  delay(100);

}//******************** END LOOP
