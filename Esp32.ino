#include "DHT.h"

//#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
//SoftwareSerial s(17,16);
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
//#define INCLUDE_MOTORCONTROL_MODULE
//#define BLYNK_PRINT Serial
//#include <TimeLib.h>

#define DHTPIN 4  
#define DHTTYPE DHT11   // DHT 11
// #include <WidgetRTC.h>
// WidgetRTC rtc;
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hlo12";
char pass[] = "1231231234";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "4PIwytFATuEVpua4zP6VHmUGYGrf35MR"; 
//



#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
#if defined(ARDUINO_ESP32S2_DEV)
int servoPin = 17;
#else
int servoPin = 18;
#endif

//uint8_t pinServo1 =  18;
//uint8_t pinServo2 =  19;
#include <DabbleESP32.h>
DHT dht(DHTPIN, DHTTYPE);

WidgetTerminal terminal(V10);
#include <SimpleTimer.h>

//SimpleTimer timer;



void setup() {

  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  //Serial S Begin at 9600 Baud
//  s.begin(9600);
pinMode(22,INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
    Serial.begin(9600);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MyEsp32");       //set bluetooth name of your device
//Serial.println("running");

//#define RXD2 16
//#define TXD2 17
//  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
//timer.setInterval(3000,temp);
//  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

}

void loop() {
//  timer.run();
    Blynk.run();

    Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

  //print '123' to Serial
             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.              //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
//  Controls.runServo1(pinServo1);
//  Controls.runServo2(pinServo2);

//  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print('U');
        Serial.println(' ');

//        Serial.print("Up");
delay(1000);

  }

  if (GamePad.isDownPressed())
  {
    Serial.print('D');
            Serial.println(' ');

//        Serial.print("Down");
delay(1000);

  }

  if (GamePad.isLeftPressed())
  {
    Serial.print('L');
            Serial.println(' ');

//        Serial.print("Left");
delay(1000);

  }

  if (GamePad.isRightPressed())
  {
    Serial.print('R');
            Serial.println(' ');

//        Serial.print("Right");
delay(1000);

  }

  if (GamePad.isSquarePressed())
  {
    Serial.print('Q');
            Serial.println(' ');

//        Serial.print("Square");
delay(1000);

  }

  if (GamePad.isCirclePressed())
  {
    Serial.print('C');
            Serial.println(' ');

//        Serial.print("Circle");
delay(1000);

  }

  if (GamePad.isCrossPressed())
  {
    Serial.print('O');
            Serial.println(' ');

//        Serial.print("Cross");
delay(1000);

  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print('T');
            Serial.println(' ');

//        Serial.print("Triangle");
delay(1000);

  }

  if (GamePad.isStartPressed())
  {
    Serial.print('a');
            Serial.println(' ');

//        Serial.print("Start");
delay(1000);

  }

  if (GamePad.isSelectPressed())
  {
    Serial.print('e');
            Serial.println(' ');

//        Serial.print("Select");
delay(1000);

  }
//  Serial.print('\t');
if(!digitalRead(22)){

Blynk.notify("Gas lekage detected");
delay(5000);
  
}






}


BLYNK_WRITE(V16){
String aah = param.asStr();
  if(aah == "0000"){

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }


    
    if(!digitalRead(26)){

Blynk.notify("no human presence detected");
delay(5000);
  
}else{
Blynk.notify("human presence detected");

  delay(5000);

}
  }else{
Serial.println(aah);

  }
}
BLYNK_READ(V1){

Blynk.virtualWrite(V1,dht.readHumidity());
  Blynk.virtualWrite(V2,dht.readTemperature());

}
