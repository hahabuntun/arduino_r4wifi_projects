int led1_pin = 5;
int led2_pin = 6;
int led3_pin = 9;
int led4_pin = 10;

void setup() {
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);
  pinMode(led4_pin, OUTPUT);
}

void loop() {
  analogWrite(led1_pin, map(2, 0, 100, 0, 255));
  analogWrite(led2_pin, map(10, 0, 100, 0, 255));
  analogWrite(led3_pin, map(50, 0, 100, 0, 255));
  analogWrite(led4_pin, map(100, 0, 100, 0, 255));
}
