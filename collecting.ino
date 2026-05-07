// rock collection function
// servo angles and timing to be determined during testing

void scoop_rocks() { 

  scoop_servo.write(scoopLowerAngle);  // lower scoop into correct position
  delay(scoopLoweringTime);   // give scoop enough time to fully lower before continuing into the collection zone

  analogWrite(ENA, collectionSpeed);  // move slowly while collecting rocks 
  delay(collectionTime);

  analogWrite(ENA,0);  // stop robot after collection
  
  scoop_servo.write(scoopRaiseAngle);  // raise scoop after collection
  delay(scoopRaisingTime); // give scoop enough time to fully raise before moving to hopper platform

}
