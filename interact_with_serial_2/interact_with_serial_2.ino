char input_char;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
  {
    input_char = Serial.read();
    Serial.print("received: ");
    Serial.println(input_char);
  }
}
