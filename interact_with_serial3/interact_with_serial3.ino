int input_integer;
int counter = 0;
int led_pin = 11;


void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("UNO IS READY!!!");
}

void loop() {
  if (Serial.available())
  {
    String input_data = Serial.readStringUntil('\n');
    input_integer = input_data.toInt();
    Serial.print("UNO received: ");
    Serial.println(input_integer);

    analogWrite(led_pin, constrain(input_integer, 0, 255));
  }
}
