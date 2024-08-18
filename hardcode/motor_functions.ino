

int directionPinA = 12;
int pwmPinA = 3;
int brakePinA = 9;

int directionPinB = 13;
int pwmPinB = 11;
int brakePinB = 8;


void move_forward(int left_speed, int right_speed) {
    // Motor A
    digitalWrite(directionPinA, HIGH);
    digitalWrite(brakePinA, LOW);
    analogWrite(pwmPinA, left_speed);

    // Motor B
    digitalWrite(directionPinB, HIGH);
    digitalWrite(brakePinB, LOW);
    analogWrite(pwmPinB, right_speed);
}

void move_backward(int speed) {
    // Motor A
    digitalWrite(directionPinA, LOW);
    digitalWrite(brakePinA, LOW);
    analogWrite(pwmPinA, speed);

    // Motor B
    digitalWrite(directionPinB, LOW);
    digitalWrite(brakePinB, LOW);
    analogWrite(pwmPinB, speed);
}

void brake() {
    // Motor A
    digitalWrite(brakePinA, HIGH);
    digitalWrite(pwmPinA, LOW);

    // Motor B
    digitalWrite(brakePinB, HIGH);
    digitalWrite(pwmPinB, LOW);
}

void init_movement() {
    // Motor A
    pinMode(directionPinA, OUTPUT);
    pinMode(pwmPinA, OUTPUT);
    pinMode(brakePinA, OUTPUT);

    // Motor B
    pinMode(directionPinB, OUTPUT);
    pinMode(pwmPinB, OUTPUT);
    pinMode(brakePinB, OUTPUT);
}

void turn_right() {
    // A motors forward, B motors backward
    // will change if we wire it differently
    digitalWrite(directionPinA, HIGH);
    digitalWrite(brakePinA, LOW);
    digitalWrite(pwmPinA, 100);

    digitalWrite(directionPinB, LOW);
    digitalWrite(brakePinB, LOW);
    digitalWrite(pwmPinB, 100);
}

void turn_left() {
    // A motors backward, B motors forward
    // will change if we wire it differently
    digitalWrite(directionPinA, LOW);
    digitalWrite(brakePinA, LOW);
    digitalWrite(pwmPinA, 100);

    digitalWrite(directionPinB, HIGH);
    digitalWrite(brakePinB, LOW);
    digitalWrite(pwmPinB, 100);
}

void sensor_detection() {
  

  //calibrate();

}

void step() {
  move_forward(10, 10);
  delay(100);
  move_forward(80, 80);
  delay(100);
  brake();
  delay(1000);
}

void step_back() {
  move_backward(110);
  delay(100);
  move_backward(80);
  delay(100);
  brake();
  delay(1000);
}

