int led_pin = 9;
int button_pin = 12;
bool is_led_on = false;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop() {
  if (digitalRead(button_pin) == LOW)
  {
    delay(10);
    if (digitalRead(button_pin) == LOW)
    {
      reverse_LED();
      
      while (digitalRead(button_pin) == LOW){}
      delay(10);
    }
  }
}


void reverse_LED()
{
  if (is_led_on)
  {
    digitalWrite(led_pin, LOW);
  }
  else
  {
    digitalWrite(led_pin, HIGH);
  }
  is_led_on = !is_led_on;
}