int LED_COUNT = 10;
int led_pins[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };


void setup() {
  for (int i = 0; i < LED_COUNT; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < LED_COUNT; i++)
  {
    turn_on_led_turn_off_others(i);
    delay(1000);
  }
}


void turn_on_led_turn_off_others(int led)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    digitalWrite(led_pins[i], LOW);
  }
  digitalWrite(led_pins[led], HIGH);
}