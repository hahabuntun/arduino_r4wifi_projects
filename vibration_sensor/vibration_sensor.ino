int buzzer_pin = 13;
int switch_pin = 3;

bool is_vibrating = false;


void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(switch_pin), vibrate, FALLING);
}

void loop() {
  if (is_vibrating)
  {
    is_vibrating = false;
    digitalWrite(buzzer_pin, HIGH);
    delay(50);
  }
  else
  {
    digitalWrite(buzzer_pin, LOW);
  }
}

void vibrate()
{
  is_vibrating = true;
}
