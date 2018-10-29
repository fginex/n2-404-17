/*
**********************************************************
Program:    Garage Saver
            
The hc-sr04 distance sensor uses sound to measure distance
like a bat's radar. We are going use this sensor along
with an Arduino Uno, a piezo buzzer, an Led and this program
for the Arduino to create a device that can be used to help
our Mom park her car in our garage without smashing into the
wall again.

This program tells the Arduino to light up an led and make a 
beep whenever a large object comes within 10 centimeters of the
hc-sr04.

References:
-----------
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/

http://www.instructables.com/id/Using-a-SR04/

**********************************************************
*/

// -------------------------------------------------------
// PIN DEFINITIONS
// -------------------------------------------------------
#define trigPin 12
#define echoPin 13
#define vccPin 11
#define buzzerPin 3

// This is an analog pin but we can still 
// use it for the led! -nickg
#define ledPin A0 

#define buzzerToneFrequency 1000 // khz


// -------------------------------------------------------
// setup() - Called once when the Arduino starts.
// -------------------------------------------------------
void setup() {
  
  // hc-sr04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(vccPin, OUTPUT);
  
  // Buzzer pins
  pinMode(buzzerPin, OUTPUT); 
  
  // Led pins
  pinMode(ledPin, OUTPUT); 
  
  // Beep quickly a few times when starting.
  //
  // The 50 in the tone function is the length 
  // of the tone in milliseconds.
  tone(buzzerPin, buzzerToneFrequency, 50);
  delay(500); // Wait 1/2 second
  tone(buzzerPin, buzzerToneFrequency, 50); 
  delay(500); // Wait 1/2 second
  tone(buzzerPin, buzzerToneFrequency, 50); 
  
  delay(1000); // Wait 1 second
}

// -------------------------------------------------------
// loop() - After calling setup() the Arduino will call 
// this function and repeat calling it until it resets or  
// shuts off.
// -------------------------------------------------------
void loop() {
  

  // ----------------------------------------------------
  // Tell hc-sr04 to send a 10 microsecond pulse 
  //  
  // We got instructions on how to do this from jsvester's 
  // example code shown in the references above.
  //
  // ---
  // This is what the pulse looks like:
  // ---
  //               high
  //          ______________ 
  //         |              |
  //   low   |              |  low
  // --------  10 micro sec  ------->
  //
  digitalWrite(vccPin, HIGH); // power it up
  digitalWrite(trigPin, LOW); // set the output to low 
  delayMicroseconds(2);       // wait for 2 microseconds
  digitalWrite(trigPin, HIGH);// set the output to high
  delayMicroseconds(10);      // wait for 10 microseconds  
  digitalWrite(trigPin, LOW); // set the output to low again

  // ----------------------------------------------------
  // Read from the hc-sr04 distance sensor.
  //
  // We got the conversion formula from duration to 
  // distance from jsvester's example code shown in the
  // references above.
  // ----------------------------------------------------
  long duration = pulseIn(echoPin, HIGH); // Milli Seconds
  long distance = (duration/2) / 29.1; // Centimeters
  

  // ----------------------------------------------------
  // Check the distance and if it is too close then  
  // turn on an led and make a warning sound.
  //
  // Note: Change the alarmDistance variable to change
  // how far away the car has to be before sounding an
  // alarm.
  // ----------------------------------------------------
  const int alarmDistance = 10; // One unit is about one centimeter
  
  if (distance < alarmDistance) {  
  
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // OH NO! THE CAR IS TOO CLOSE!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    // Turn On the led
    digitalWrite(ledPin, HIGH); 
    
    // Make a warning sound. The 200 is the length
    // of time the tone is played in milliseconds
    tone(buzzerPin, buzzerToneFrequency, 200); 
  }
  else {
    
    // Nothing is near - everthing is ok so
    // turn off the led
    digitalWrite(ledPin, LOW); 
  }

  delay(500); // Wait 1/2 second
}


