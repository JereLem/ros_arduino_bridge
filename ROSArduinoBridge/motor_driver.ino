/***************************************************************
   Motor driver - modified by Jere Leman
***************************************************************/

#ifdef USE_BASE

#ifdef A100_MOTOR_DRIVER

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float voltage = 0.0;
 
// Float for Reference Voltage
float ref_voltage = 24.0;
 
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


// Read analog voltage from motor driver
float readVoltage() {
  int adc_value = analogRead(VOLTAGE_PIN);  // Read the Analog Input
  float divider_factor = 1.8;               // Scaling factor for voltage divider
  
  // Determine voltage at ADC input
  float adc_voltage = (adc_value * ref_voltage) / 1023.0;
  
  // Calculate the actual voltage at the motor using the scaling factor
  float voltage = adc_voltage * divider_factor;
  
  return voltage;
}


// Read analog temp from motor driver thermistor
float readTemp() {
  const int ThermistorPin = TEMP_PIN; // Define TEMP_PIN globally
  int Vo = analogRead(ThermistorPin);

  if (Vo == 0) {
    Serial.println("Invalid temperature reading");
    return -1; // Return an error value for invalid reading
  }

  float R1 = 10000; // Resistor value
  float logR2, R2, T, Tc;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;  // Convert from Kelvin to Celsius

  return Tc;
}


// Read analog current from motor driver
float readCurrent() {
  int adc_value = analogRead(CURRENT_PIN);
  float sensor_scaling = 13;               
  
  // Calculate the voltage at the CS pin
  float cs_voltage = (adc_value * ref_voltage) / 1023.0;
  
  // Convert the CS voltage to current (A)
  float current = cs_voltage / sensor_scaling;

  return current;
}


void monitorMotorParameters() {
  float current = readCurrent();
  float voltage = readVoltage();
  float temperature = readTemp();

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.print(" A, Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V, Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");
  
  delay(1000); // Update rate 0.1s
}

#endif // End of 100A_MOTOR_DRIVER check

#else
#error A motor driver must be selected!

#endif // End of USE_BASE check