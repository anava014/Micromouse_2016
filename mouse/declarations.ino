

void setup()
{  
  pinMode(sensorR, INPUT);
  pinMode(sensorM, INPUT);
  pinMode(sensorL, INPUT);

  pinMode(LEFTMotorEN, OUTPUT);
  pinMode(LEFTlogic1, OUTPUT);
  pinMode(LEFTlogic2, OUTPUT);
  
  digitalWrite(LEFTMotorEN, LOW);
  
  pinMode(RIGHTMotorEN, OUTPUT);
  pinMode(RIGHTlogic1, OUTPUT);
  pinMode(RIGHTlogic2, OUTPUT);
  
  digitalWrite(RIGHTMotorEN, LOW);
  
  pinMode(encoderLEFT_A, INPUT);
  pinMode(encoderLEFT_B, INPUT);
  
  pinMode(encoderRIGHT_A, INPUT);
  pinMode(encoderRIGHT_B, INPUT);
 
  Serial1.begin(9600);
  liftOff();
  calibrate();
  delay(1000);
}


