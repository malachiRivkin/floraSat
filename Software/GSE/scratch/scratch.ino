/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
//Vars
int epoch = 0;
int lastEpoch = 0;
int duration1 = 500;
int duration2 = 1000;
int duration3 = 2000;
int T = 10000;
byte input = 0;
bool lastState = LOW;
const byte command1 = 0x00;
const byte command2 = 0x01; 
const byte command3 = 0x02;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //setup serial port
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  if(Serial.available()){
    input = Serial.read();
    Serial.write(input);
    
    if(input == command1){
      T = duration1;
      Serial.println("command 1 executed");
      }
      else if(input == command2){
        T = duration2;
        Serial.println("command 2 executed");
      }
      else if(input == command3){
        T = duration3;
        Serial.println("command 3 executed");
    }
  }
  epoch = millis();

  if(epoch - lastEpoch > T){
    digitalWrite(LED_BUILTIN, !lastState);
    lastState = !lastState;
    lastEpoch = epoch;
    Serial.write("State Changed!");
  }


}
