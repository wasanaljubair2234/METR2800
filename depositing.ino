// rock deposition 
// uses the detected hopper distance returned by getDistanceCm() from the sensing/search function 
// need to convert angle_1 and angle_2 into step counts
// arm commands can only be confirmed once stepper drivers are confirmed

void deposit(float distance) { 

  float y = 360; // vertical distance between arm base and hopper

  // need to be measured
  float length_1 = ; 
  float length_2 = ; 
  float scoop_width = ; 

  // reach calculations
  float length_3 = sqrt(length_2*length_2 + Scoop_width*Scoop_width );
  float angle_offset = atan2(scoop_width, length_2); 

  // arm joint angles
  float angle_2_offset = acos((distance*distance + y*y - length_1*length_1 - length_3*length_3 )/ 2 *length_1 * length_3 );
  float angle_1 = atan2(y, distance) - atan(length_3 *sin(angle_2_offset), length_1 + length_3 * cos(angle_2_offset));
  float angle_2 = angle_2_offset - angle_offset;
  
  // acuate servos 
  // actuate angle 1, then 2  include some factor phi_1, phi_2 etc to calibrate realworld tests

  trapdoor_servo.write(trapdoorOpenAngle); // rotate servo position into open position to release the rocks
  delay(trapdoorOpenTime); // keep trapdoor open long enough to release all rocks 

  trapdoor_servo.write(trapdoorCloseAngle); // close trapdoor
  delay(trapdoorCloseTime);  // give enough time for trapdoor to fully close before next movement
  
}
