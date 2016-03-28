 void counterClockwise()
{
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(RIGHTMotorEN, HIGH);
  analogWrite(LEFTlogic1, MOTOR_FULL_SPEED);
  analogWrite(LEFTlogic2, 0);
  analogWrite(RIGHTlogic1, 0);
  analogWrite(RIGHTlogic2, MOTOR_FULL_SPEED - RIGHT_MOTOR_SPEED_OFFSET);
}

void clockwise()
{
  digitalWrite(LEFTMotorEN, HIGH);
  analogWrite(LEFTlogic1, 0);
  analogWrite(LEFTlogic2, MOTOR_FULL_SPEED);
  
  digitalWrite(RIGHTMotorEN, HIGH);
  analogWrite(RIGHTlogic1, MOTOR_FULL_SPEED - RIGHT_MOTOR_SPEED_OFFSET);
  analogWrite(RIGHTlogic2, 0);
}

void forward(int leftMotorSpeed, int rightMotorSpeed){
  digitalWrite(LEFTMotorEN, HIGH);
  analogWrite(LEFTlogic1, 0);
  analogWrite(LEFTlogic2, leftMotorSpeed);
  
  digitalWrite(RIGHTMotorEN, HIGH);
  analogWrite(RIGHTlogic1, 0);
  analogWrite(RIGHTlogic2, rightMotorSpeed - RIGHT_MOTOR_SPEED_OFFSET);
}

void reverse(int leftMotorSpeed, int rightMotorSpeed){
  digitalWrite(LEFTMotorEN, HIGH);
  analogWrite(LEFTlogic1, leftMotorSpeed);
  analogWrite(LEFTlogic2, 0);
  
  digitalWrite(RIGHTMotorEN, HIGH);
  analogWrite(RIGHTlogic1, rightMotorSpeed);
  analogWrite(RIGHTlogic2, 0);
}

void halt() {
//  digitalWrite(LEFTMotorEN, LOW);
//  digitalWrite(RIGHTMotorEN, LOW);

  for(int i = MOTOR_FULL_SPEED - 30; i > 0; i = i - 10){
      forward(i,i);
      delay(10);
      reverse(i,i);
      delay(10);
  }
  digitalWrite(LEFTMotorEN, LOW);
  digitalWrite(RIGHTMotorEN, LOW);

}

void forward(){
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);
  
  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}
