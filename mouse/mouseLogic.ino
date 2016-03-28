int returnReverseFacing(){
    if(facing == 0)
      return 2;
    else if(facing == 2)
      return 0;
    else if(facing == 1)
      return 3;
    else if(facing == 3)
      return 1;

    else return -1;
  }

  void transitionUTurn(){
    if(facing == 0)
      facing = 2;
    else if(facing == 2)
      facing = 0;
    else if(facing == 1)
      facing = 3;
    else if(facing == 3)
      facing = 1;
  }

  void transitionRightTurn(){
    facing = returnIncrementedFacing();
  }

  void transitionLeftTurn(){
    facing = returnDecrementedFacing();
  }

  int returnDecrementedFacing(){
    if(facing == 0)
      return 3;
    else
      return facing - 1;
  }

  int returnIncrementedFacing(){
    if(facing == 3)
      return 0;
    else
      return facing + 1;
  }

  void setFacing(int f){
    facing = f;
  }

  String returnDirectionName(){
    if(facing == 0)
      return "North";
    else if(facing == 2)
      return "South";
    else if(facing == 1)
      return "East";
    else if(facing == 3)
      return "West";

    else return "dead";
  }



  
