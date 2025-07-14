/***************************************************************************
  This is a library for the BMP3XX temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP388 Breakout
  ----> http://www.adafruit.com/products/3966

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

//BMP i2c Pins
#define I2C_SDA D20
#define I2C_SCL D21
#define BMP_ADDRESS 0x77

// default pins GPIO 4/5 work!
//#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Adafruit BMP388 / BMP390 test");
  delay(1000);
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  delay(1000);
  //if (!bmp.begin_I2C(0x77)) {   // hardware I2C mode, can pass in address & alt Wire
    //Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    //while (1);
  bmp.begin_I2C(BMP_ADDRESS, &Wire);
  //}

  // Set up oversampling and filter initialization
  //bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  //bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  //bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  //bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    delay(1000);
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");
  /*
  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  */
  Serial.println();
  delay(2000);
  
  Serial.println("Here");
}