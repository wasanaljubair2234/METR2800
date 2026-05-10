#include <Servo.h>
#include <Stepper.h>


// any hashes # requires the ports to be inputeded


// drive motor ports
int DR1 = #;
int DR2 = #;
int DR3 = #;
int DR4 = #;


// ultrasonic sensor ports
const int trigPin = #;
const int echoPin = #;
float timing = 0.0;
float detected_distance = 0.0;
float distance = 9999.0;


// set up servos 
Servo torsion_servo;
Servo scoop_servo;
Servo trapdoor_servo;


// A4988 steppers
const int stepsPerRevolution = 200;
const int rotationStepPin = #; 
const int rotationDirPin = #; 
const int limb1StepPin = #;
const int limb1DirPin = #;
const int limb2StepPin = #;
const int limb2DirPin = #;
float angle = 0.0; // in steps of motor not degrees
float current_angle = 0.0;


// constants 
const int initialSpeed = 100; // speed from start zone to collection zone
const int timeToCollectionZone = 3000; // time to reach collection zone from start zone

const int scoopLowerAngle = #; // angle to lower scoop to begin rock collection
const int scoopLoweringTime = #; // time it takes to fully lower scoop

const int scoopRaiseAngle = #; // angle to raise scoop after rock collection
const int scoopRaisingTime = #; // time it takes to fully raise scoop

const int collectionSpeed = #; // speed to travel at during rock collection, might be slower than initialSpeed
const int collectionTime = #; // time it takes to collect all rocks 

const int trapdoorOpenAngle = #; // servo position that opens the trapdoor
const int trapdoorCloseAngle = #; // servo positon that closes the trapdoor
const int trapdoorOpenTime = #; // how long the trapdoor stays open to release the rocks
const int trapdoorCloseTime = #; // how long it takes to close the trap door again

// varibales for tweeking, can add them into movement code, to account for overshoot, 
float phi_1 = 0.0; 
float phi_2 = 0.0; 
float phi_3 = 0.0; 
float phi_4 = 0.0; 
float phi_5 = 0.0; 
float phi_6 = 0.0; 


void moveStepper(int stepPin, int dirPin, int steps, bool direction) {
  ditigitalWrite(dirPin, direction);

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(#);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(#);
  }
}


void setup() {

  //ultrasonic set up
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  
  // set up servos ports
  torsion_servo.attach(#);
  scoop_servo.attach(#);
  trapdoor_servo.attach(#);
  
  pinMode(rotationStepPin, OUTPUT);
  pinMode(rotationDirPin, OUTPUT);

  pinMode(limb1StepPin, OUTPUT);
  pinMode(limb1DirPin, OUTPUT);

  pinMode(limb2StepPin, OUTPUT);
  pinMode(limb2DirPin, OUTPUT);
  

}


void loop() {
  // put your main code here, to run repeatedly:
  // proposed run sequence:
  // 1. drive to collection area
  // 2. collect rocks
  // 3. drive to platform
  // 4. align with hopper
  // 5. deposit rocks
  // 6. return to end zone/second run?

  drive_to_collection_zone();

  scoop_rocks();

  drive_to_hopper_platform();

  search();

  deposit(distance);

  return_to_start();

}

 
void return_to_start() {
 
  digitalWrite(DR1, LOW);      // sets direction , invert high and low for reverse
  digitalWrite(DR2, HIGH);
  digitalWrite(DR3, HIGH);      // sets direction , invert high and low for reverse
  digitalWrite(DR4, LOW);
  analogWrite(ENA, 100);  // speed setting goes up to 255
  delay(3000);          // time driving forward
  analogWrite(ENA, 0); // turns off motor

}
