/* Checks if theres a front wall, if there isn't, return. If there is, continue
   on to check peripherals
*/

void checkPeripherals(){
  if (analogRead(sensorM) >= FRONT_LIMIT){ //Wall up front   
    sensorReadingL = analogRead(sensorL);
    sensorReadingR = analogRead(sensorR);
     
     halt();
     if (sensorReadingR > 500  && sensorReadingL > 280) { // its at a dead end, IS WALL on left and right (U-turn)
          state = 2;
          directionSet = false;
          transitionUTurn();
          RIGHTPos = LEFTPos = 0;
          encoderTimer.begin(incrementEncoders, 750);
          encoderFlag.begin(uTurnFlagFunction, 250);
      }
     else if (sensorReadingL < 280){   // if there is NO WALL on left, IS WALL on right (left turn)
        state = 3;
        directionSet = false;
        RIGHTPos = LEFTPos = 0;
        transitionLeftTurn();
        encoderTimer.begin(incrementEncoders, 750);
        encoderFlag.begin(leftTurnFlagFunction, 250);
     }
     else if (sensorReadingR < 500){    // if there is NO WALL on left, IS WALL on right (left turn)
        state = 4;
        directionSet = false;
        RIGHTPos = LEFTPos = 0;
        transitionRightTurn();
        encoderTimer.begin(incrementEncoders, 750);
        encoderFlag.begin(rightTurnFlagFunction, 250);
     }
  }
}

bool leftPresent()
{
  if (analogRead(sensorL) >= LEFT_LIMIT)
      return true;
  else
      return false;
}

bool rightPresent()
{
  if (analogRead(sensorR) >= RIGHT_LIMIT)
      return true;
  else
      return false;
}

