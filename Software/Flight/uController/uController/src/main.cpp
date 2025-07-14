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

#define THERMISTOR_SOURCE_PIN D22
#define THERMISTOR_ADC_PIN A0
const int THERMISTOR_DIVIDER_R = 10000;
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950

// default pins GPIO 4/5 work!
//#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

float thermistor_temp = 999.9;


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

  pinMode(THERMISTOR_SOURCE_PIN, OUTPUT);
  pinMode(THERMISTOR_ADC_PIN, INPUT);

}

float readTHermistor(){
  int reading = 99;
  digitalWrite(THERMISTOR_SOURCE_PIN, HIGH);
  delay(1000);
  reading = analogRead(THERMISTOR_ADC_PIN);
  digitalWrite(THERMISTOR_SOURCE_PIN, LOW);
  float reading_computed = reading;
  // convert the value to resistance
  reading_computed = THERMISTOR_DIVIDER_R / (4095/reading - 1);

  float steinhart;
  steinhart = reading_computed / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C

  return steinhart;
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

  thermistor_temp = readTHermistor();
  Serial.print("Thermistor Temp = ");
  Serial.print(thermistor_temp);
  Serial.println(" *C");

  //Read internal die temperature
  float internal_temp = 999.0;
  internal_temp = analogReadTemp();
  Serial.print("Internal Temp = ");
  Serial.print(internal_temp);
  Serial.println(" *C");


  delay(2000);
  
  Serial.println("Here");
  
}