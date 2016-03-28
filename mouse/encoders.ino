void incrementEncoders(){
  trackRightIncrement();
  trackLeftIncrement();
}

 void trackRightIncrement(){
   rightEncoder = digitalRead(encoderRIGHT_A);
   if ((RIGHT_PinALast == LOW) && (rightEncoder == HIGH)){
       ++RIGHTPos;
   }
   RIGHT_PinALast = rightEncoder;
 }

void trackLeftIncrement(){
  leftEncoder = digitalRead(encoderLEFT_A);  // set my current signal to 'left'
  if ((LEFT_PinALast == LOW) && (leftEncoder == HIGH)){
    ++LEFTPos;
  }
  LEFT_PinALast = leftEncoder;
}

void trackLeftDecrement(){
  leftEncoder = digitalRead(encoderLEFT_A);  // set my current signal to 'left'
  if ((LEFT_PinALast == LOW) && (leftEncoder == HIGH)){
    --LEFTPos;
  }
  LEFT_PinALast = leftEncoder;
}




