#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include<AFMotor.h>

AF_DCMotor motor_r(3);
AF_DCMotor motor_l(4);
RH_ASK driver;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor_l.setSpeed(255);
  motor_l.run(RELEASE);
  motor_r.setSpeed(255);
  motor_r.run(RELEASE);

  //motor_f.setSpeed(255);
  //motor_f.run(RELEASE);
  driver.init();
}

void loop() {
  uint8_t buf[20];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) {
    Serial.print("Message : ");
    Serial.println((char*)buf);
    int w = buf[0] - '0';
    int a = buf[1] - '0';
    int s = buf[2] - '0';
    int d = buf[3] - '0';
    int speedx = buf[4] * 100 + buf[5] * 10 + buf[6];
    Serial.print("W:");
    Serial.println(w);
    Serial.print("A:");
    Serial.println(a);
    Serial.print("S:");
    Serial.println(s);
    Serial.print("D:");
    Serial.println(d);
    if (w == 1 && a == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_r.run(RELEASE);
      motor_l.run(FORWARD);
    }
    else if (w == 1 && d == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_r.run(FORWARD);
      motor_l.run(RELEASE);
    }
    else if (s == 1 && a == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_l.run(BACKWARD);
      motor_r.run(RELEASE);
    } else if (s == 1 && d == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_l.run(RELEASE);
      motor_r.run(BACKWARD);

    }
    else if (w == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_l.run(FORWARD);
      motor_r.run(FORWARD);
    }
    else if (s == 1) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_r.run(BACKWARD);
      motor_l.run(BACKWARD);  
    }
    else if (w == 0 && s == 0 && a == 0 && d == 0) {
      motor_l.setSpeed(speedx);
      motor_r.setSpeed(speedx);
      motor_l.run(RELEASE);
      motor_r.run(RELEASE);
    }
    delay(600);
  }
}
