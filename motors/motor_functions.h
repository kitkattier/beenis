int directionPinA = 12;
int pwmPinA = 3;
int brakePinA = 9;

int directionPinB = 13;
int pwmPinB = 11;
int brakePinB = 8;

float SPEED = 1;

void move_forward() {
    // Motor A
    digitalWrite(directionPinA, HIGH);
    digitalWrite(brakePinA, LOW);
    digitalWrite(pwmPinA, SPEED);

    // Motor B
    digitalWrite(directionPinB, HIGH);
    digitalWrite(brakePinB, LOW);
    digitalWrite(pwmPinB, SPEED);
}

void move_backward() {
    // Motor A
    digitalWrite(directionPinA, LOW);
    digitalWrite(brakePinA, LOW);
    digitalWrite(pwmPinA, SPEED);

    // Motor B
    digitalWrite(directionPinB, LOW);
    digitalWrite(brakePinB, LOW);
    digitalWrite(pwmPinB, SPEED);
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
