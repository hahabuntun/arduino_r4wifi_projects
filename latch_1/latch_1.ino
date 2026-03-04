int latch_pin = 12;
int clock_pin = 13;
int data_pin = 11;


void setup() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}


void loop() {
  byte x = 0x01;
  for (int j = 0; j < 8; j++)
  {
    digitalWrite(latch_pin, LOW);
    
    shiftOut(data_pin, clock_pin, LSBFIRST, x);
    digitalWrite(latch_pin, HIGH);

    x = (x << 1) | 1;
    delay(100);
  }
  delay(1000);
}
