int i = 0;
int j = 104;
int k = 209;
int x = 0;
int y = 0;
int z = 0;
int sinPWM[] = {1, 2, 5, 7, 10, 12, 15, 17, 19, 22, 24, 27, 30, 32, 34, 37, 39, 42,
                44, 47, 49, 52, 54, 57, 59, 61, 64, 66, 69, 71, 73, 76, 78, 80, 83, 85, 88, 90, 92, 94, 97, 99,
                101, 103, 106, 108, 110, 113, 115, 117, 119, 121, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146,
                148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 169, 171, 173, 175, 177, 178, 180, 182, 184, 185, 187, 188, 190, 192, 193,
                195, 196, 198, 199, 201, 202, 204, 205, 207, 208, 209, 211, 212, 213, 215, 216, 217, 219, 220, 221, 222, 223, 224, 225, 226, 227,
                228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 237, 238, 239, 240, 240, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246,
                247, 247, 247, 248, 248, 248, 248, 249, 249, 249, 249, 249, 255, 255, 255, 255, 249, 249, 249, 249, 249, 248,
                248, 248, 248, 247, 247, 247, 246, 246, 245, 245, 244, 244, 243, 243, 242, 242, 241, 240, 240, 239, 238, 237, 237, 236, 235, 234,
                233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 217, 216, 215, 213, 212, 211, 209, 208, 207, 205, 204,
                202, 201, 199, 198, 196, 195, 193, 192, 190, 188, 187, 185, 184, 182, 180, 178, 177, 175, 173, 171, 169, 168, 166, 164, 162, 160,
                158, 156, 154, 152, 150, 148, 146, 144, 142, 140, 138, 136, 134, 132, 130, 128, 126, 124, 121, 119, 117, 115, 113, 110, 108, 106,
                103, 101, 99, 97, 94, 92, 90, 88, 85, 83, 80, 78, 76, 73, 71, 69, 66, 64, 61, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 30,
                27, 24, 22, 19, 17, 15, 12, 10, 7, 5, 2, 1
               };

void setup() {
  Serial.begin(9600);

  pinMode(4, OUTPUT);  // phase 1+ A
  pinMode(13, OUTPUT); // phase 1- B
  pinMode(9, OUTPUT);  // phase 2+ A
  pinMode(10, OUTPUT); // phase 2- B
  pinMode(2, OUTPUT);  // phase 3+ A
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);  // phase 3- B

  cli();// stop interrupts
  TCCR0A = 0; //reset the value
  TCCR0B = 0; //reset the value
  TCNT0 = 0; //reset the value
  //0b allow me to write bits in binary
  TCCR0A = 0b10100001; //phase correct pwm mode
  TCCR0B = 0b00000010; //8 prescaler

  TCCR2A = 0; //reset the value
  TCCR2B = 0; //reset the value
  TCNT2 = 0; //reset the value
  //0b allow me to write bits in binary
  TCCR2A = 0b10100001; //phase correct pwm mode
  TCCR2B = 0b00000010; //8 prescaler

  TCCR3A = 0; //reset the value
  TCCR3B = 0; //reset the value
  TCNT3 = 0; //reset the value
  //0b allow me to write bits in binary
  TCCR3A = 0b10100001; //phase correct pwm mode
  TCCR3B = 0b00000010; //8 prescaler

  
  TCCR1A = 0; //reset the value
  TCCR1B = 0; //reset the value
  TCNT1 = 0; //reset the value
  OCR1A = 1052; // compare match value
  TCCR1B = 0b00001001; //WGM12 bit is 1 for CTC mode and no prescaler

  TIMSK1 |= (1 << OCIE1A); // enable interrupts

  sei();//start interrupts
}
ISR(TIMER1_COMPA_vect) { // interrupt when timer 1 match with OCR1A value
  if (i > 313) { // final value from vector for pin 13
    i = 0; // go to first value of vector
  }
  x = sinPWM[i]; // x take the value from vector corresponding to position i(i is zero indexed)
  i = i + 1; // go to the next position
    OCR0A = x; //enable pin 13 to corresponding duty cycle

    if (j > 313) { // final value from vector for pin 10
      j = 0; // go to first value of vector
    }

    y = sinPWM[j]; // y take the value from vector corresponding to position j(j is zero indexed)
    j = j + 1; // go to the next position

      OCR2A = y; //enable pin 10 to corresponding duty cycle
  
    if (k > 313 ) { // final value from vector for pin 5
      k = 0; // go to first value of vector
    }
    
    z = sinPWM[k]; // z take the value from vector corresponding to position k(k is zero indexed)
    k = k + 1; // go to the next position

      OCR3A = z; //enable pin 5 to corresponding duty cycle
  }

void loop() {

}
