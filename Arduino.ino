#include <WS2812FX.h>
int av=1;
#define LED_COUNT 10
#define LED_PIN A0
#define TIMER_MS 5000
bool relayval=0;
int ss=0;

int data; //Initialized variable to store recieved data
int State = 1;
bool servo=0;
int trigPin = 13;      // trig pin of HC-SR04
int echoPin = 2;     // Echo pin of HC-SR04
long duration, distance;
#include <MotorDriver.h>
int relayPin=A1;

#include <Servo.h>

Servo myservo0;  // create servo object to control a servo
Servo myservo1;  // create servo object to control a servo

int val0=0;    // variable to read the value from the analog pin
int val1=0;    // variable to read the value from the analog pin

MotorDriver m;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  //Serial Begin at 9600 Baud
  Serial.begin(9600);
  Serial.println("hi");
  myservo0.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object
  pinMode(relayPin, OUTPUT);         // set trig pin as output
digitalWrite(relayPin,HIGH);
relayval=1;
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves

  m.motor(1, BRAKE, 255);
  m.motor(2, BRAKE, 255);
  m.motor(3, BRAKE, 255);

  m.motor(4, BRAKE, 255);
  
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_RAINBOW);
  ws2812fx.start();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();

    myservo1.write(10);                  // sets the servo position according to the scaled value
    myservo0.write(169);                  // sets the servo position according to the scaled value

}

void loop() {

  
    ws2812fx.service();
if(digitalRead(A2)==1){
   if (Serial.available() > 0) {

  data = Serial.read(); //Read the serial data and store it
  Serial.write(data);
  
    }


    if(data == '8'){
      State=1;
    }

    
    if(data == '9'){
      State=0;
    }
    
    if(data == 'e'){
  State++;
  if(State>2){State=0;}
  Serial.print(State);
}

if(State == 1){
obstracle();
  digitalWrite(relayPin,LOW);
  relayval=0;
av=1;
}else if(State == 2){

  manual();

av=1;
  
}else if(State==0 && av==1){
av=0;
  digitalWrite(relayPin,HIGH);
relayval=1;
  m.motor(1, RELEASE, 255);
  m.motor(2, RELEASE, 255);
  m.motor(3, RELEASE, 255);
  m.motor(4, RELEASE, 255);
  
  ws2812fx.setColor(0xFFFF00);
  ws2812fx.setMode(FX_MODE_BREATH);
}

ss=0;

}else{

  if(ss==0){
  ws2812fx.setColor(0xFF0000);
  ws2812fx.setMode(FX_MODE_BLINK);
  ss=1;
  }
  m.motor(1, RELEASE, 255);
  m.motor(2, RELEASE, 255);
  m.motor(3, RELEASE, 255);
  m.motor(4, RELEASE, 255);
}

}



void  manual(){

if(data == 'a'){

  m.motor(1, RELEASE, 255);
  m.motor(2, RELEASE, 255);
  m.motor(3, RELEASE, 255);
  m.motor(4, RELEASE, 255);
servo=!servo;
  
  
}
if(servo==0){


  ws2812fx.setColor(0xFFFFFF);
  ws2812fx.setMode(FX_MODE_STATIC);


  
if(data == 'U'){

  m.motor(1, FORWARD, 255);
  m.motor(2, FORWARD, 255);
  m.motor(3, FORWARD, 200);
  m.motor(4, FORWARD, 255);
  
}

if(data == 'D'){

  m.motor(1, BACKWARD, 255);
  m.motor(2, BACKWARD, 255);
  m.motor(3, BACKWARD, 255);
  m.motor(4, BACKWARD, 255);
  
}




if(data == 'L'){

  m.motor(1, FORWARD, 255);
  m.motor(2, FORWARD, 255);
  m.motor(3, BACKWARD, 255);
  m.motor(4, BACKWARD, 255);
  
}
if(data == 'R'){

  m.motor(1, BACKWARD, 255);
  m.motor(2, BACKWARD, 255);
  m.motor(3, FORWARD, 255);
  m.motor(4, FORWARD, 255);
  
}
  
}else{



if(data == 'U'){
val0=val0+8;
if(val0 > 168){
  val0=168;
}
    myservo0.write(val0);                  // sets the servo position according to the scaled value

}

if(data == 'D'){

 val0=val0-8;
if(val0 < 110){
  val0=110;
}
    myservo0.write(val0);                  // sets the servo position according to the scaled value

}




if(data == 'L'){

 val1=val1-8;
if(val1 < 10){
  val1=10;
}
    myservo1.write(val1);                  // sets the servo position according to the scaled value

}
if(data == 'R'){

val1=val1+8;
if(val1 > 98){
  val1=98;
}
    myservo1.write(val1);                  // sets the servo position according to the scaled value

}
  
}
  if(data == 'T'){
    relayval=!relayval;
      digitalWrite(relayPin,relayval);
      
  }

}


void nearstop(){


  
}




void obstracle(){


  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
  // If you dont get proper movements of your robot then alter the pin numbers
  if (distance >= 30)
  {

  ws2812fx.setColor(0x00FF00);
  ws2812fx.setMode(FX_MODE_STATIC);


      ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();



if(!digitalRead(A4)){

  m.motor(1, BRAKE, 255);
  m.motor(2, BRAKE, 255);
  m.motor(3, BRAKE, 200);
  m.motor(4, BRAKE, 255);

  
    myservo1.write(10);                  // sets the servo position according to the scaled value
    myservo0.write(169);                  // sets the servo position according to the scaled value

//      myservo1.write(10);                  // sets the servo position according to the scaled value

//        myservo0.write(169);                  // sets the servo position according to the scaled value

//    myservo0.write(169);                  // sets the servo position according to the scaled value
delay(1000);
    
    myservo1.write(110);

  delay(1000);
    myservo0.write(110);                  // sets the servo position according to the scaled value
  delay(1000);
    myservo1.write(10);

delay(1000);
//    delay(1000);// sets the servo position according to the scaled value
  
//delay(1000);
//    myservo1.write(98);  
//      myservo1.write(10);                  // sets the servo position according to the scaled value


  
}

if(!digitalRead(A3)){

  m.motor(1, BACKWARD, 255);
  m.motor(2, BACKWARD, 255);
  m.motor(3, BACKWARD, 200);
  m.motor(4, BACKWARD, 255);
  delay(50);
  
  m.motor(3, FORWARD, 255);
  m.motor(4, FORWARD, 255);
  m.motor(1, BACKWARD, 200);
  m.motor(2, BACKWARD, 255);
  
}



if(digitalRead(A3) && digitalRead(A4)){

  m.motor(1, FORWARD, 255);
  m.motor(2, FORWARD, 255);
  m.motor(3, FORWARD, 200);
  m.motor(4, FORWARD, 255);
  
}

  }

  if (distance < 30)
  {
    
    myservo1.write(10);                  // sets the servo position according to the scaled value
    myservo0.write(169);                  // sets the servo position according to the scaled value

  ws2812fx.setColor(0xFF0077);
  ws2812fx.setMode(FX_MODE_STATIC);
      ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();
    ws2812fx.service();

  m.motor(1, BRAKE, 255);
  m.motor(2, BRAKE, 255);
  m.motor(3, BRAKE, 255);
  m.motor(4, BRAKE, 255);
    delay(30);

  m.motor(1, BACKWARD, 255);
  m.motor(2, BACKWARD, 255);//back
  m.motor(3, BACKWARD, 255);
  m.motor(4, BACKWARD, 255);
    delay(300);

  m.motor(1, BRAKE, 255);
  m.motor(2, BRAKE, 255);
  m.motor(3, BRAKE, 255);
  m.motor(4, BRAKE, 255);
    delay(50);
  m.motor(1, BACKWARD, 255);
  m.motor(2, BACKWARD, 255);
  m.motor(3, FORWARD, 255);
  m.motor(4, FORWARD, 255);
    delay(800);
    
  m.motor(1, BRAKE, 255);
  m.motor(2, BRAKE, 255);
  m.motor(3, BRAKE, 255);
  m.motor(4, BRAKE, 255);
    delay(50);

//  m.motor(1, FORWARD, 255);
//  m.motor(2, FORWARD, 255);
//  m.motor(3, FORWARD, 200);
//  m.motor(4, FORWARD, 255);
//delay(800);
//
//  m.motor(1, BRAKE, 255);
//  m.motor(2, BRAKE, 255);
//  m.motor(3, BRAKE, 255);
//  m.motor(4, BRAKE, 255);
//    delay(100);
//  m.motor(1, BACKWARD, 255);
//  m.motor(2, BACKWARD, 255);
//  m.motor(3, FORWARD, 200);
//  m.motor(4, FORWARD, 255);
//    delay(800);
    
//  m.motor(1, BRAKE, 255);
//  m.motor(2, BRAKE, 255);
//  m.motor(3, BRAKE, 255);
//  m.motor(4, BRAKE, 255);
//    delay(100);
    
  }


}
