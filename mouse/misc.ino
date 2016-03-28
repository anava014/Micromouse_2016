/*Calibrates mouse after detecting finger wave*/
void liftOff(){
  while(analogRead(sensorM) < WAVE_VALUE) {}
  Serial1.println("Liftoff");
}

void printPeripherals() {
//  regulateSensorL();
//  regulateSensorR();

  sensorReadingL = analogRead(sensorL);
  sensorReadingR = analogRead(sensorR);
  
  if(sensorReadingR < 500 && sensorReadingL < 280){
      Serial1.println("no walls");
      Serial1.print("Left: ");
      Serial1.println(sensorReadingL);
      Serial1.print("Right: ");
      Serial1.println(sensorReadingR); 
  }
  else if(sensorReadingR < 500 ){ // without right wall Right will be greater than 250
      Serial1.println("no right wall");
      Serial1.print("Left: ");
      Serial1.println(sensorReadingL);
      Serial1.print("Right: ");
      Serial1.println(sensorReadingR); 
  }
  else if(sensorReadingL < 280){ // without left wall Left will be greater than 150
    Serial1.println("no left wall");
    Serial1.print("Left: ");
    Serial1.println(sensorReadingL);
    Serial1.print("Right: ");
    Serial1.println(sensorReadingR);
  }
  //OLD STATEMENT && sensorReadingR > sensorReadingL  && sensorReadingR - sensorReadingL > 150
  
  
  else if(sensorReadingL > sensorReadingR && sensorReadingL - sensorReadingR > 10){ //Too close to left with walls
      regulateSensorL();
      regulateSensorR();
      Serial1.println("Too close to left with walls");
      Serial1.print("Left: ");
      Serial1.println(sensorReadingL);
      Serial1.print("Right: ");
      Serial1.println(sensorReadingR); 
  }
  else if(sensorReadingR > sensorReadingL && sensorReadingR - sensorReadingL > 10){ //Too close to right with walls
      regulateSensorL();
      regulateSensorR();
      Serial1.println("Too close to right with walls");
      Serial1.print("Left: ");
      Serial1.println(sensorReadingL);
      Serial1.print("Right: ");
      Serial1.println(sensorReadingR); 
  }
  else{
    Serial1.println("");
      Serial1.print("Left: ");
      Serial1.println(sensorReadingL);
      Serial1.print("Right: ");
      Serial1.println(sensorReadingR); 
  }

}

void bluetoothRead(){
//  while(!Serial1.available()) {}
//    Serial1.read();
  delay(1000);
}
