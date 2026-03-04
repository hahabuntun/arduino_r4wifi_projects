#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 12;

int led_pin = 5;
int buzzer_pin = 13;

decode_results results;

void setup() {
  Serial.begin(9600);
  Serial.println("UNO is ready");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.command);
    handle_control(IrReceiver.decodedIRData.command);
    IrReceiver.resume();
  }
}


void handle_control(unsigned long value)
{
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  switch (value)
  {
    case 22: //0
      analogWrite(led_pin, 0);
      break;
    case 12: //1
      analogWrite(led_pin, 7);
      break;
    case 24: //2
      analogWrite(led_pin, 63);
      break;
    case 94: //3
      analogWrite(led_pin, 255);
      break;
  }
}
