

#include <Servo.h>
Servo myservo;  // create servo object to control a servo


#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 700;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

int total = 0;
int avgBPM = 0;
int counter = 0;
int numReadings = 5;

void setup() {   
  myservo.attach(9);                // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
   delay(200);
  myservo.write(180);
  delay(200);
  
  myservo.write(0);
  delay(550);
  
  myservo.write(180);
  delay(20);
}



void loop() {

 int BPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 


if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(BPM);                        // Print the value inside of myBPM. 
 total += BPM;
 counter ++ ;

  if (counter == numReadings )
  {
    counter = 0;
    avgBPM = total/numReadings;
    total = 0;
     Serial.print("avgBPM: ");                        // Print phrase "BPM: " 
     Serial.println(avgBPM);  
    if(avgBPM < 181)
    {
      int rotation = 180 - avgBPM;       //for clockwise rotation of servo according to BPM
      myservo.write(rotation);                  // sets the servo position
    }
    if(BPM > 180)
    {
      myservo.write(0);
    }
  }
} 

  delay(20);                    // considered best practice in a simple sketch.

}

  
