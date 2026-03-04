/**********************************************************************
  Filename    : Sketch_21.2.1_4_Digit_7-Segment_Display
  Description : 4-digit 7-segment Display
  Author      : www.freenove.com
  Modification: 2024/08/05
**********************************************************************/

int latchPin = 12;          // Pin connected to ST_CP of 74HC595 (Pin12)
int clockPin = 13;          // Pin connected to SH_CP of 74HC595 (Pin11)
int dataPin = 11;           // Pin connected to DS of 74HC595 (Pin14)
int comPin[] = {7, 6, 5, 4};// Common pin (anode) of 4 digit 7-segment display

// Define the encoding of characters 0-F of the common-anode 7-Segment Display
byte num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void setup() {
  // Set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(comPin[i], OUTPUT);
  }
}

void loop() {
  // Array of digits to display on each of the 4 7-segment displays
  byte digits[] = {5, 6, 7, 8};  // Change this array to display other numbers, e.g., {1, 2, 3, 4}

  for (int i = 0; i < 4; i++) {
    // Select a single 7-segment display
    chooseCommon(i);
    // Send data to 74HC595 (using the corresponding number from the digits array)
    writeData(num[digits[i]]);
    delay(10);  // Increase delay to allow the display to update
    // Clear the display content (turn it off temporarily)
    writeData(0xff);
  }
}

// Function to select which 7-segment display to activate
void chooseCommon(byte com) {
  // Close all single 7-segment displays
  for (int i = 0; i < 4; i++) {
    digitalWrite(comPin[i], LOW);
  }
  // Open the selected single 7-segment display
  digitalWrite(comPin[com], HIGH);
}

// Function to write data to the 74HC595 shift register
void writeData(int value) {
  // Make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  // Make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}