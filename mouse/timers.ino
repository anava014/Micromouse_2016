void uTurnFlagFunction(){
  if(LEFTPos + RIGHTPos > 295) {
    halt();
    state = 1;
    encoderTimer.end();
    encoderFlag.end();
    LEFTPos = 0;
  }
}
//TRY WITH BOTH SUMMING TO IT
void leftTurnFlagFunction(){
  if(LEFTPos + RIGHTPos > 115) {
    halt();
    state = 1;
    encoderTimer.end();
    encoderFlag.end();
    
    LEFTPos = 0;
    //delay(500);
  }
}

void rightTurnFlagFunction(){
  if(LEFTPos + RIGHTPos > 138){
    halt();
    state = 1;
    encoderTimer.end();
    encoderFlag.end();
    RIGHTPos = 0;
    //delay(500);
  }
}

