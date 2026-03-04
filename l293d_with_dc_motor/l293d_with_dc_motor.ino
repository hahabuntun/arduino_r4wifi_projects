int in1_pin = 10;
int in2_pin = 9;
int enable1_pin = 11;

bool rotation_direction;
int rotation_speed; 

void setup() {
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  pinMode(enable1_pin, OUTPUT);
  Serial.begin(9600); // Начало работы с серийным монитором
}

void loop() {
  int pot_value = analogRead(A0);
  Serial.print("Potentiometer Value: ");
  Serial.println(pot_value); // Выводим значение потенциометра для отладки

  // Используем пороговые значения для направления
  if (pot_value > 550) {  // Пороговое значение для изменения направления
    rotation_direction = true;
  } else if (pot_value < 470) {  // Пороговое значение для изменения направления
    rotation_direction = false;
  }

  // Скорость вращения зависит от расстояния от середины
  rotation_speed = abs(pot_value - 512);
  Serial.print("Rotation Speed: ");
  Serial.println(rotation_speed); // Выводим скорость вращения

  drive_motor(rotation_direction, map(rotation_speed, 0, 512, 0, 255));
}

void drive_motor(bool direction, int speed) {
  if (direction) {
    digitalWrite(in1_pin, HIGH);
    digitalWrite(in2_pin, LOW);
  } else {
    digitalWrite(in1_pin, LOW);
    digitalWrite(in2_pin, HIGH);
  }

  analogWrite(enable1_pin, constrain(speed, 0, 255));
}