/***************************************************************
   Motor driver function definitions - by James Nugen - modified by Jere Leman
   *************************************************************/

#ifdef MD04_MOTOR_DRIVER
  #define RIGHT_MOTOR_DRIVE 6
  #define LEFT_MOTOR_DRIVE  5

  
  #define RIGHT_MOTOR_DIR 10
  #define LEFT_MOTOR_DIR   9
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
