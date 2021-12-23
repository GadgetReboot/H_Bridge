
// DC Motor H Bridge PWM Test
//
// Target Hardware:  Uno
//
// Connections:
// Uno Pin          H Bridge Control
//    2                    D
//    3                    C  (pwm)
//    4                    B
//    5                    A  (pwm)
//
// Tested with Arduino IDE 1.8.13
// Gadget Reboot
// https://www.youtube.com/gadgetreboot

const int D_Pin = 2;  // H Bridge D control pin
const int C_Pin = 3;  // H Bridge C control pin
const int B_Pin = 4;  // H Bridge B control pin
const int A_Pin = 5;  // H Bridge A control pin

void setup()
{
  digitalWrite(D_Pin, HIGH);  // turn pnp off
  digitalWrite(C_Pin, LOW);   // turn npn off
  digitalWrite(B_Pin, HIGH);  // turn pnp off
  digitalWrite(A_Pin, LOW);   // turn npn off

  pinMode(D_Pin, OUTPUT);
  pinMode(C_Pin, OUTPUT);
  pinMode(B_Pin, OUTPUT);
  pinMode(A_Pin, OUTPUT);
}

void loop()
{
  static byte pwm_duty = 120;     // value used to set the pwm duty on H Bridge

  // run motor in one direction at different speeds
  digitalWrite(D_Pin, LOW);       // turn on pnp

  for (int i = 0; i < 20; i++) {
    pwm_duty += 5;                // increase speed
    analogWrite(A_Pin, pwm_duty); // set pwm duty on npn
    delay(1500);
  }

  // disable motor (coast)
  digitalWrite(D_Pin, HIGH);
  digitalWrite(A_Pin, LOW);
  delay(3000);
  pwm_duty = 120;  // reset pwm speed

  // run motor in other direction at different speeds
  digitalWrite(B_Pin, LOW);       // turn on pnp

  for (int i = 0; i < 20; i++) {
    pwm_duty += 5;                // increase speed
    analogWrite(C_Pin, pwm_duty); // set pwm duty on npn
    delay(1500);
  }

  // disable motor (coast)
  digitalWrite(B_Pin, HIGH);
  digitalWrite(C_Pin, LOW);

  // brake motor (stop)
  digitalWrite(A_Pin, HIGH);
  digitalWrite(C_Pin, HIGH);

  delay(1000);

  // diable motor
  digitalWrite(A_Pin, LOW);
  digitalWrite(C_Pin, LOW);

  delay(500);
  pwm_duty = 120;  // reset pwm speed

}
