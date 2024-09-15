// Motor control pins
const int motor1Pin1 = 5;  // Motor 1 control pin 1
const int motor1Pin2 = 6;  // Motor 1 control pin 2
const int motor2Pin1 = 9;  // Motor 2 control pin 1
const int motor2Pin2 = 10; // Motor 2 control pin 2

// IR sensor pins
const int leftIRPin   =   2;
const int centerIRPin =   3;
const int rightIRPin  =   4;

int light1 = 19,light2=20, light3=21;

// Threshold for car speed max speed is 255
int car_speed = 150;
char command;
int var = A0;
// Motor speed control for forward-backward and left-right.
int FB_speed = 100, LR_speed = 150;

// Ultrasonic sensors pins
int trig1 = 12, echo1 = 13, trig2 = 7, echo2 = 8, trig3 = 14, echo3 = 11;

float duration;
float distance1, distance2, distance3;
// Threashold distances for all three sensors 
const float set_distance1 = 35, set_distance2 = 35, set_distance3 = 35;


void setup() {
  // Set motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);

  // Set IR sensor pins as inputs
  pinMode(leftIRPin  , INPUT);
  pinMode(centerIRPin, INPUT);
  pinMode(rightIRPin , INPUT);
  
  // Set ultrasonic sensor pins
    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(trig3, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    pinMode(echo3, INPUT);


    pinMode(var, INPUT);
  Serial.begin(9600); // Start serial communication for debugging
}
int counter=0 , counter2 =0;
void loop() {
  int switch1 = analogRead(var);
  if(switch1 > 1000 && counter2 ==0)
  {
    counter++;
    counter2++;
  }
  else if(switch1 <1000)
  counter2 =0;
  if(counter ==0)
  {
    rc_robot();
    Serial.println("RC");
    digitalWrite(light1,HIGH);
  }
  else if(counter==1){
    self_driving();
    Serial.println("Self");
    digitalWrite(light2,HIGH);
    digitalWrite(light1,LOW);
  }
  else if(counter==2){
    line_following();
    Serial.println("LFR");
    digitalWrite(light3,HIGH);
    digitalWrite(light2,LOW);
  }
  else{
  counter=0;
  digitalWrite(light3,LOW);
  }

}


void line_following(){

  // Read IR sensor values
  int leftValue   =   digitalRead(leftIRPin);
  int centerValue =   digitalRead(centerIRPin);
  int rightValue  =   digitalRead(rightIRPin);

  // Print sensor values for debugging
  // Serial.print("Left: ");
  // Serial.print(leftValue);
  // Serial.print(" Center: ");
  // Serial.print(centerValue);
  // Serial.print(" Right: ");
  // Serial.println(rightValue);

  // Line following logic
  if (leftValue ==0 &&centerValue ==1 && rightValue==0)
    moveForward();// Move forward
  else if (leftValue ==1 && centerValue ==1&& rightValue==0)
    turnLeft();// Turn left
  else if (rightValue ==1&&centerValue ==1 && leftValue==0)
    turnRight();// Turn right
  else 
    stopMotors();// Stop
  
  delay(10); // Short delay to stabilize readings
}

void self_driving() {
    // Measure distances from ultrasonic sensors
    distance1 = dist_measure(trig1, echo1);
    distance2 = dist_measure(trig2, echo2);
    distance3 = dist_measure(trig3, echo3);

    if (distance2 > set_distance2)
        moveForward();              // Forward
    else if (distance1 > set_distance1 && distance1 > distance3)
        turnRight();                // Right turn
    else if (distance3 > set_distance3)               
        turnLeft();                 // Left turn
    else //if (distance1 < set_distance1 && distance2 < set_distance2 && distance3 < set_distance3)
        move_backward_until_clear();// No clear path, move backward until there is space
    
    // Serial.print("D1 ");
    // Serial.println(distance1);
    // delay(500);
    // Serial.print("D2 ");
    // Serial.println(distance2);
    // delay(500);
    // Serial.print("D3 ");
    // Serial.println(distance3);
    // delay(500);
    
}

void rc_robot(){

  // Check if data is available to read from Bluetooth module
  if (Serial.available()>0) {
    command = Serial.read(); // Read the incoming command
    speed_controle(command);
    // Process the received command
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
      case 'G':
        moveForward_L();
        break;
      case 'I':
        moveForward_R();
        break;
      case 'H':
        moveBackward_R();
        break;
      case 'J':
        moveBackward_L();
        break;
      default:
        break;
    }
  }
}

void speed_controle(char &command)
{
  switch(command)
  {
    case '0':
    car_speed = 0;
    break;
    case '1':
    car_speed = 25;
    break;
    case '2':
    car_speed = 50;
    break;
    case '3':
    car_speed = 75;
    break;
    case '4':
    car_speed = 100;
    break;
    case '5':
    car_speed = 125;
    break;
    case '6':
    car_speed = 150;
    break;
    case '7':
    car_speed = 175;
    break;
    case '8':
    car_speed = 200;
    break;
    case '9':
    car_speed = 255;
    break;
  }

}

void moveForward() {
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);
}

void turnLeft() {
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}

void turnRight() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);
}

void moveBackward_L() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, car_speed/4);
  analogWrite(motor2Pin2, LOW);
}

void moveBackward_R() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed/4);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}


void moveForward_R(){
  analogWrite(motor1Pin1, car_speed/4);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed);
}

void moveForward_L(){
  analogWrite(motor1Pin1, car_speed);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, car_speed/4);
}
void moveBackward() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, car_speed);
  analogWrite(motor2Pin1, car_speed);
  analogWrite(motor2Pin2, LOW);
}
void stopMotors() {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, LOW);
}


void move_backward_until_clear() {
    while (true) {

        // Measure distances again
        distance1 = dist_measure(trig1, echo1);
        distance3 = dist_measure(trig3, echo3);

        if (distance1 > set_distance1 || distance3 > set_distance3)
          break;
        

        // Move backward
        analogWrite(motor1Pin1, LOW);
        analogWrite(motor1Pin2, FB_speed);
        analogWrite(motor2Pin1, FB_speed);
        analogWrite(motor2Pin2, LOW);
        Serial.println("Reverse");
    }

    // Decide which way to turn
    if (distance1 > set_distance1 && distance1 > distance3) {
        turnRight();
    } else if (distance3 > set_distance3) {
        turnLeft();
    }
}

float dist_measure(int trig, int echo) {
    duration = 0;
    // Send a pulse to the trigger pin
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Measure the duration of the pulse on the echo pin
    duration = pulseIn(echo, HIGH);
    // Calculate the distance based on the duration of the pulse
    return ((duration * 0.034) / 2);
}