#include <Servo.h>

// サーボモータが接続されているピン番号
int servoPin = 9;
// ボタンが接続されているピン番号
int buttonPin = 5;

Servo servo;
bool isButtonPressed = false;
int initialPosition = 90;
int rotatedPosition = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  servo.write(initialPosition); // サーボモータを初期位置に設定
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'r') {
      rotateServo(rotatedPosition);
    }
  }

  if (digitalRead(buttonPin) == LOW && !isButtonPressed) {
    isButtonPressed = true;
    rotateServo(rotatedPosition);
  }

  if (digitalRead(buttonPin) == HIGH)
  {
    isButtonPressed = false;
  }
}

void rotateServo(int position) {
  servo.write(position); // サーボモータを指定した位置に回転
  delay(5000); // 5秒待機
  servo.write(initialPosition); // サーボモータを初期位置に戻す
}
