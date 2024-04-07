#include <Servo.h>

//Servo init
Servo myServo;

//Variables that will change
int rainValue = 0;
int rain = 0;
String rainOutput;
String windowStatus;

//constants
const int rainPin = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myServo.attach(10);

  pinMode(rainPin, INPUT);
  myServo.write(0);
  windowStatus = "Window Fully Open";
}

void loop() {
  // put your main code here, to run repeatedly:
  rainValue = analogRead(A0);
  rainOutput = rainValue;

  Serial.println(rainOutput + windowStatus);

  int value = Serial.read();
  Serial.println("Serial Read: " + value);

  if (value == '1') {
    myServo.write(0);
    delay(10);
    rainOutput = rainValue;
    windowStatus = "Window Fully Open";
    //Serial.println(rainOutput + windowStatus);
    //Serial.println("Value 1");
  } else if (value == '2') {
    myServo.write(60);
    delay(10);
    rainOutput = rainValue;
    windowStatus = "Window 2/3 Open";
    //Serial.println(rainOutput + windowStatus);
    //Serial.println("Value 2");
  } else if (value == '3') {
    myServo.write(120);
    delay(10);
    rainOutput = rainValue;
    windowStatus = "Window 1/3 Open";
    //Serial.println(rainOutput + windowStatus);
    //Serial.println("Value 3");
  } else if (value == '4') {
    myServo.write(180);
    delay(10);
    rainOutput = rainValue;
    windowStatus = "Window Closed";
    //Serial.println(rainOutput + windowStatus);
    //Serial.println("Value 4");
  }

  delay(1000);

  //No rain
  // if (rainValue > 550 || rain == 0) {
  //   myServo.write(0);
  //   rainOutput = rainValue;
  //   //Serial.println("r" + rainOutput);
  //   delay(10);
  //   Serial.println(rainOutput  + "Window Fully Open");
  //   //Wait 1 seconds
  //   delay(1000);
  // }

  // if (rain == 1) {
  //   //Light rain
  //   if (rainValue <= 550 && rainValue > 350) {
  //     myServo.write(60);
  //     rain = true;
  //     rainOutput = rainValue;
  //     //Serial.println("r" + rainOutput);
  //     delay(10);
  //     Serial.println(rainOutput  + "Window 2/3 Open");
  //     //Wait 1 second
  //     delay(1000);
  //   }
  //   //Medium rain
  //   if (rainValue <= 350 && rainValue > 275) {
  //     myServo.write(120);
  //     rain = true;
  //     rainOutput = rainValue;
  //     //Serial.println("r" + rainOutput);
  //     delay(10);
  //     Serial.println(rainOutput  + "Window 1/3 Open");
  //     //Wait 1 second
  //     delay(1000);
  //   }
  //   //Heavy Rain
  //   if (rainValue <= 275) {
  //     myServo.write(180);
  //     rain = true;
  //     rainOutput = rainValue;
  //     //Serial.println("r" + rainOutput);
  //     delay(10);
  //     Serial.println(rainOutput  + "Window Closed");
  //     //Wait 1 seconds
  //     delay(1000);
  //   }
  // }
}
