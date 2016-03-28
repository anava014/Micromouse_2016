/* Micromouse Code
Emilio Barreiro ebarr006@ucr.edu
Andrew Nava-Juarez anava014@ucr.edu
*/

#define WAVE_VALUE 450 
#define ARRAY_SIZE 1000

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

IntervalTimer encoderTimer;
IntervalTimer encoderFlag;

bool leftEncoderFreeze = true;
bool directionSet = false;
bool timerSet = false;

int timeLog[ARRAY_SIZE];
int iterator = 0;
int currentTime = 0;
int firstRun = 1;

int leftMotorDireciton = 0; //0 = CC, 1 = C
int rightMotorDirection = 1;

//......................... TESTING .......................//
int counter = 0;
//.........................................................//



int facing = 0;
int state = 1;

#define FRONT_LIMIT 400         
#define LEFT_LIMIT 120
#define RIGHT_LIMIT 120
#define MOTOR_FULL_SPEED 150
#define RIGHT_MOTOR_SPEED_OFFSET 0
#define LEFT_MOTOR_SPEED_OFSSET 15

double kp = .14; //Constant of Proportion
double rightKp = .3; 
int sensorR = A0;
int sensorM = A1;
int sensorL = A2;

int sensorReadingR = 0;
int sensorReadingM = 0;
int sensorReadingL = 0;

int permReadingL = 0;
int permReadingM = 0;
int permReadingR = 0;

int LEFTMotorEN = 7;
int LEFTlogic1 = 6;
int LEFTlogic2 = 5;

int RIGHTMotorEN = 8;
int RIGHTlogic1 = 3;
int RIGHTlogic2 = 4;

int encoderLEFT_A = A4;
int encoderLEFT_B = A3;
int LEFTPos = 0;
int LEFT_PinALast = LOW;
int leftEncoder = LOW;

int encoderRIGHT_A = A6;
int encoderRIGHT_B = A5;
int RIGHTPos = 0;
int RIGHT_PinALast = LOW;
int rightEncoder = LOW;

void loop(){
  if(state == 1){ //Forward State
    bluetoothRead();

    while(1){
      if(!timerSet){
        LEFTPos = 0;
        encoderTimer.begin(incrementEncoders, 750); //This method might be best
        timerSet = true;
      }
      pidControl(); // 7 MS
      if(LEFTPos + RIGHTPos > 520){ //Once Cell Traversed
        counter++;
        break;
      }
      if(analogRead(sensorM) > FRONT_LIMIT){ //Interrupted by Wall in front
        if(LEFTPos + RIGHTPos > 430) //Count as a cell traversal
          counter++;
        break;
      }
    }
    
    timerSet = false;
    encoderTimer.end();
    halt();
    RIGHTPos = LEFTPos = 0;
    //......................... TESTING .......................//
    Serial1.print("Counter: ");
    Serial1.println(counter);
    Serial1.print("facing: ");
    Serial1.println(returnDirectionName());
    //printLiveMaze();
    //.........................................................//
    checkPeripherals();
  }
  else if(state == 2){  //U Turn State
    if(!directionSet){
      counterClockwise();
      RIGHTPos = LEFTPos = 0;
      directionSet = true;
    }
  }
  else if(state == 3){  //Left Turn State
    if(!directionSet){
      counterClockwise();
      RIGHTPos = LEFTPos = 0;
      directionSet = true;
    }
  }
  else if(state == 4){  //Right Turn State
    if(!directionSet){
      clockwise();
      RIGHTPos = LEFTPos = 0;
      directionSet = true;
    }
  }
  
}



