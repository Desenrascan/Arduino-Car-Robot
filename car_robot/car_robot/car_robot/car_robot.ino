boolean alertSignal = false;
boolean wheelsRotating = false;

//Motor variables
const byte MOTOR_L_IN4 = 13;
const byte MOTOR_L_IN3 = 12;
const byte MOTOR_L_IN2 = 11;
const byte MOTOR_L_IN1 = 10;

const byte MOTOR_R_IN4 = 9;
const byte MOTOR_R_IN3 = 8;
const byte MOTOR_R_IN2 = 7;
const byte MOTOR_R_IN1 = 6;
//Bluetooth variables
byte receivedCommand = 0;

//HC-SR04 (Sensor) variables
const byte TRIG = 5;
const byte ECHO = 4;
unsigned long distanceDuration = 0;
byte centimeter = 0;

//Alert signal variables
const byte ALERT_SIGNAL = 3;
void setup() {
  //Set motor states
  pinMode(MOTOR_L_IN4, OUTPUT);
  pinMode(MOTOR_L_IN3, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_L_IN1, OUTPUT);
  
  pinMode(MOTOR_R_IN4, OUTPUT);
  pinMode(MOTOR_R_IN3, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);

  //HC-SR04 state
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //Alert signal
  pinMode(ALERT_SIGNAL, OUTPUT);
  Serial.begin(9600);
}

void loop() {
//  //Check if there is connection with bluetooth
  if(Serial.available() > 0) {
    receivedCommand = Serial.read();
  }

  if(receivedCommand != 0) {
      if(receivedCommand == 1) {
        //Move forward
        if(alertSignal) {
          turnOffAlertSignal();
          alertSignal = false;
        }
        moveForward();
      } else if(receivedCommand == 2) {
        //Move backward
        moveBackward();
        
        //Enable when user moves back
        detectionSensor();
        alertSignal = true;
      } else if(receivedCommand == 3) {
        //Move right
        if(alertSignal) {
          turnOffAlertSignal();
          alertSignal = false;
        }
        moveRight();
      } else if(receivedCommand == 4) {
        //Move left
        if(alertSignal) {
          turnOffAlertSignal();
          alertSignal = false;
        }
        moveLeft();
      }
  }
}

void moveForward() {
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_IN3, HIGH);
  digitalWrite(MOTOR_L_IN4, LOW);
  
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
}

void moveBackward() {
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_L_IN3, LOW);
  digitalWrite(MOTOR_L_IN4, HIGH);
  
  digitalWrite(MOTOR_R_IN1, HIGH);
  digitalWrite(MOTOR_R_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
}

void moveLeft() {
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_IN3, LOW);
  digitalWrite(MOTOR_L_IN4, LOW);
  
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
}

void moveRight() {
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, LOW);
  
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_IN3, HIGH);
  digitalWrite(MOTOR_L_IN4, LOW);
}

void stopMotors() {
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_L_IN3, LOW);
  digitalWrite(MOTOR_L_IN4, LOW);
  
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, LOW);
}

void detectionSensor() {
  digitalWrite(TRIG, LOW);
  delay(5);
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);

  pinMode(ECHO, INPUT);
  distanceDuration = pulseIn(ECHO, HIGH);
  centimeter = ( distanceDuration / 2 ) / 29.1;

  //Make alert
  if(centimeter < 20) {
     digitalWrite(ALERT_SIGNAL, HIGH);
     delay(40);
     digitalWrite(ALERT_SIGNAL, LOW);
     delay(40);
  } else {
     digitalWrite(ALERT_SIGNAL, HIGH);
  }
}

void turnOffAlertSignal() {
  digitalWrite(ALERT_SIGNAL, LOW);
}
