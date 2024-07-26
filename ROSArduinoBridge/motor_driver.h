/***************************************************************
   Motor driver function definitions - by Jere Leman
   *************************************************************/

#ifdef IBT2
  #define RPWM_RIGHT 11
  #define LPWM_RIGHT 10
  
  #define RPWM_LEFT 3
  #define LPWM_LEFT 9
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
