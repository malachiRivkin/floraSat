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
#include "RTClib.h" //real time clock
#include <SD.h> // SD card library

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

// RTC setup
RTC_PCF8523 rtc;

//SD Card setup
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 17;
const int SPIO_TX = 19;
const int SPIO_SCK = 18;
const int SPIO_RX = 16;

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

  //thermistor
  pinMode(THERMISTOR_SOURCE_PIN, OUTPUT);
  pinMode(THERMISTOR_ADC_PIN, INPUT);

  delay(2000);
  //rtc
  if (! rtc.begin()) {
    delay(3000);
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(100);
  }
  /*
  if (! rtc.initialized() || rtc.lostPower()) {
    delay(5000);
    Serial.println("RTC is NOT initialized, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    //
    // Note: allow 2 seconds after inserting battery or applying external power
    // without battery before calling adjust(). This gives the PCF8523's
    // crystal oscillator time to stabilize. If you call adjust() very quickly
    // after the RTC is powered, lostPower() may still return true.
  }
  */
  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // uncomment this for plantsat reset!!!
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  //rtc.adjust(DateTime(2025, 7, 16, 18, 56, 0));
  // When the RTC was stopped and stays connected to the battery, it has
  // to be restarted by clearing the STOP bit. Let's do this to ensure
  // the RTC is running.
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  rtc.start();

  // SD Card setup
  SPI.setCS(chipSelect);
  SPI.setSCK(SPIO_SCK);
  SPI.setRX(SPIO_RX);
  SPI.setTX(SPIO_TX);

  delay(3000);
  Serial.print("Initializing SD Card!");
  if (!card.init(SPI_HALF_SPEED, chipSelect)){
    Serial.println("Initialization Failed. WOMP");
    while(1);
  }
  else {
    Serial.println("Wiring is correct and card is present.");
  }
  
  //print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1 KB)
  Serial.print("Volume size (KB):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (MB):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (GB):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();

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
  
  // read machine time

  // read utc time

  //read air temp and pressure
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

  //get time
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");


  delay(2000);
  
  Serial.println("Here - running latest script!");

  // make a string for assembling the data to log:
  String dataString = "";

  dataString += String(now.unixtime()) + "," + String(bmp.temperature);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  
}