// ultrasonic sensor and search logic

// helper function for distance
float getDistanceCm() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  float timing = pulseIn(echoPin, HIGH); // measures return pulse time
  
  return (timing * 0.034) / 2;  // converts pulse time to cm
}


void search() {   

  rotation_stepper.step(-50);  // rotate sensor to intial position
  delay(300);
  
  for (int i = 0; i < 50; i++) {
    // rotate incrementally while scanning
    rotation_stepper.step(1);  // move motor 1 step , 50 steps is 90 degrees, then scan distance
    delay(10);

    current_angle = i; // records current scan step number 

    detected_distance = getDistanceCm();

    if (detected_distance < distance) { // collects and stores values for closest angle and distance 
      distance = detected_distance;
      angle = current_angle; 
    }   

  }

  rotations_stepper.step(-1*(50 - angle)) // rotate back to be in line with tube
}


