int button_pin = 12;
int led_pin = 9;


void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (digitalRead(button_pin) == HIGH)
  {
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    digitalWrite(led_pin, LOW);
  }
}
