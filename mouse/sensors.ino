void calibrate(){
  permReadingL = analogRead(sensorL);
  permReadingM = analogRead(sensorM);
  permReadingR = analogRead(sensorR);
}

void regulateSensorL(){
  sensorReadingL = analogRead(sensorL);
  sensorReadingL = sensorReadingL - permReadingL;
  if(analogRead(sensorL) - permReadingL < 0)
      sensorReadingL = ~sensorReadingL + 1;
}

void regulateSensorR(){
  sensorReadingR = analogRead(sensorR);
  sensorReadingR = sensorReadingR - permReadingR;
  if(sensorReadingR < 0)
      sensorReadingR = ~sensorReadingR + 1;
}

/* Centers the position of the mouse using PID
Currently, we are using proportional control
*/
void pidControl(){
  sensorReadingL = analogRead(sensorL);
  sensorReadingR = analogRead(sensorR);
  
  if(sensorReadingR < 500 && sensorReadingL < 280){
    forward(MOTOR_FULL_SPEED, MOTOR_FULL_SPEED);
    return;
  }
  else if(sensorReadingL < 280){ // without left wall
      sensorReadingR = analogRead(sensorR);
      sensorReadingR = sensorReadingR - permReadingR;
      if(sensorReadingR > 0){ // Too close to right wall, slow down left motor
        forward(MOTOR_FULL_SPEED - sensorReadingR * kp, MOTOR_FULL_SPEED);
      }
      else{ // too far to from right wall, slow down right motor
        sensorReadingR = ~sensorReadingR + 1;
        forward(MOTOR_FULL_SPEED, MOTOR_FULL_SPEED - (sensorReadingR * rightKp));
      }
      return;
  }
  else if(sensorReadingR < 500 ){ // without right wall
      //Serial1.println("no right wall");
      sensorReadingL = analogRead(sensorL);
      sensorReadingL = sensorReadingL - permReadingL;
       if(sensorReadingL > 0){ // Too close to left wall, slow down right motor
        forward(MOTOR_FULL_SPEED, MOTOR_FULL_SPEED - (sensorReadingL * rightKp));
      }
      else{ // too far to from left wall, slow down left motor
        sensorReadingL = ~sensorReadingL + 1;
        forward(MOTOR_FULL_SPEED - (sensorReadingL * rightKp), MOTOR_FULL_SPEED);
      }
      return;
  }
  regulateSensorL();
  regulateSensorR();
  
  if(sensorReadingL > sensorReadingR && sensorReadingL - sensorReadingR > 10){ //Too close to left with walls
      forward(MOTOR_FULL_SPEED, MOTOR_FULL_SPEED - ((sensorReadingL - sensorReadingR) * rightKp));
  }
  else if(sensorReadingR > sensorReadingL && sensorReadingR - sensorReadingL > 10){ //Too close to right with walls
      forward(MOTOR_FULL_SPEED - ((sensorReadingR - sensorReadingL) * kp), MOTOR_FULL_SPEED);
  }
  else
      forward(MOTOR_FULL_SPEED, MOTOR_FULL_SPEED);
}
