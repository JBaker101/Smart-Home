#include <Servo.h>

//Servo init
Servo myServo;

//Variables that will change
int rainValue = 0;
int rain = 0;
char incomingByte;
String rainOutput;

//constants
const int rainPin = 8;
const int relayPin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Setup servo that would control the window and connect it to pin 10
  myServo.attach(10);

  pinMode(rainPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  rainValue = analogRead(A0);
  rain = digitalRead(rainPin);

  //Code that reads serial sent from edge server and depending on input, 
  //turns the relay that controls the fan either on or off
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    //Output incoming serial byte (for testing)
    Serial.println(incomingByte);
    if (incomingByte == '1') {
      //Turn fan relay on
      digitalWrite(relayPin, HIGH);      
    } else {
      //Turn relay fan off
      digitalWrite(relayPin, LOW);
    }
    
  }

  //No rain
  if (rainValue > 550 || rain == 0) {
    myServo.write(0);
    rainOutput = rainValue;
    delay(1000);
    Serial.println(rainOutput  + "Window Fully Open");
  }

  //rain == 1 means it is raining (just a digital signal)
  //All the following Serial.println go the edge server and then are sent to the
  //ThingsBoard via MQTT
  if (rain == 1) {
    //Light rain
    if (rainValue <= 550 && rainValue > 350) {
      myServo.write(60);
      rainOutput = rainValue;
      delay(1000);
      Serial.println(rainOutput  + "Window 2/3 Open");
    }
    //Medium rain
    if (rainValue <= 350 && rainValue > 275) {
      myServo.write(120);
      rainOutput = rainValue;
      delay(1000);
      Serial.println(rainOutput  + "Window 1/3 Open");
    }
    //Heavy Rain
    if (rainValue <= 275) {
      myServo.write(180);
      rainOutput = rainValue;
      delay(1000);
      Serial.println(rainOutput  + "Window Closed");
    }
  }
}
