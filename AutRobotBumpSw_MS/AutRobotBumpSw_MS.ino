

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 8;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 9;           //control pin 1 on the motor driver for the left motor

int switchPin = 7;             //switch to turn the robot on and off
int bumpPin = 2;                //pin connected to bump switch

//robot behaviour variables
int backupTime = 500;           //amount of time that the robot will back up when it senses an object
int turnTime = 500;             //amount that the robot will turn once it has backed up

/********************************************************************************/
void setup()
{
 
  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped
  pinMode(bumpPin, INPUT_PULLUP);   //set this as a pullup to sense whether the bump switch is triggered

  //set the motor contro pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

    
 // Serial.begin(9600);                       //begin serial communication with the computer
 // Serial.print("To infinity and beyond!");  //test the serial connection
}

/********************************************************************************/
void loop()
{
  if(digitalRead(switchPin) == LOW){  //if the on switch is flipped

    if(digitalRead(bumpPin) ==  LOW){                //if bump switch hits object goes low
      
      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(1000);

      //back up
      rightMotor(-150);
      leftMotor(-150);
      delay(backupTime);

      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(1000);
      
      //turn away from obsticle 
      rightMotor(150);
      leftMotor(-150);    
      delay(turnTime);

      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(1000);

    }else{                         //if no obstacle is detected drive forward
      rightMotor(150);
      leftMotor(150);
    }
  } else{                         //if the switch is off then stop

      //stop the motors
      rightMotor(0);
      leftMotor(0);
  }

  delay(50);                      //wait 50 milliseconds between readings
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backwar (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backwar (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}



