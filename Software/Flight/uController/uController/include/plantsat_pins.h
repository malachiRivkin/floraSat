//pins for raspi pico 1

//BMP i2c Pins
#define I2C_SDA D20
#define I2C_SCL D21
#define BMP_ADDRESS 0x77

//Thermistor
#define THERMISTOR_SOURCE_PIN D22
#define THERMISTOR_ADC_PIN A0


// SD Card 
const int chipSelect = 17;
const int SPIO_TX = 19;
const int SPIO_SCK = 18;
const int SPIO_RX = 16;