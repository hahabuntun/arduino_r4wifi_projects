int button_pin = 5;
int led_pin = 6;
bool is_on = false;
int sensor_state = 0;


void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}


void loop() {
  if (digitalRead(button_pin) == LOW)
  {
    delay(10);
    if (digitalRead(button_pin) == LOW)
    {
      change_state();
      while (digitalRead(button_pin) == LOW) {}
      delay(10);
    }
  }
  reverse_led();
}


void change_state()
{
  sensor_state++;
  if (sensor_state > 3)
  {
    sensor_state = 0;
  }
}


void reverse_led()
{
    switch (sensor_state) {
    case 1:
      analogWrite(led_pin, map(10, 0, 100, 0, 255));
      break;
    case 2:
      analogWrite(led_pin, map(50, 0, 100, 0, 255));
      break;
    case 3:
      analogWrite(led_pin, map(100, 0, 100, 0, 255));
      break;
    case 0:
      analogWrite(led_pin, map(0, 0, 100, 0, 255));
      break;
  }
}