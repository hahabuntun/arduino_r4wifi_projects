int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("UNO is ready");
}

void loop() {
  Serial.print("counter: ");
  Serial.print(counter);
  delay(500);
  counter++;
}


