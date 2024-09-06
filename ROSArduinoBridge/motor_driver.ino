/***************************************************************
   Motor driver - modified by Jere Leman
***************************************************************/

#ifdef USE_BASE

#ifdef A100_MOTOR_DRIVER

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float voltage = 0.0;
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

void initMotorController() {
  // Initialize the motor pins as outputs
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);

  // IF basic arduino PWM needed use analogwrite()
  pwmWrite(RIGHT_PWM, 0);
  pwmWrite(LEFT_PWM, 0);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
}


// Sets the speed of one motor
void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;

  // Check if the speed is negative, which means reverse direction
  if (spd < 0) {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255) { // Limit speed to 255
    spd = 255;
  }

  // Set motor speed and direction based on the motor index (i)
  if (i == LEFT) {
    if (reverse == 0) {
      digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    } else {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    }
    // IF higher freq pwmWrite() is needed
    // IF basic arduino PWM needed use analogwrite()
    pwmWrite(LEFT_PWM, spd);
  }
  else if (i == RIGHT) {
    if (reverse == 0) {
      digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    } else {
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
    }
    // IF higher freq pwmWrite() is needed
    // IF basic arduino PWM needed use analogwrite()
    pwmWrite(RIGHT_PWM, spd);
  }
}


// Sets motor speeds for both motors
void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
}


// Tried reading voltage/current from motor driver, but the values dont seem to be correct
float readVoltage() {
  // Read the Analog Input
  adc_value = analogRead(VOLTAGE_PIN);
  
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1023.0;
  
  // Calculate voltage at divider input
  voltage = adc_voltage;

  return voltage;
}

float readCurrent() {
  const int numReadings = 10;
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(CURRENT_PIN);
    delay(100); // Short delay between readings
  }
  float average = sum / numReadings;
  return ((average * 5.0) / 1023.0);
}

void monitorMotorParameters() {
  float current = readCurrent();
  float voltage = readVoltage();

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.print(" A, Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  delay(500);
}

#endif // End of 100A_MOTOR_DRIVER check

#else
#error A motor driver must be selected!

#endif // End of USE_BASE check
