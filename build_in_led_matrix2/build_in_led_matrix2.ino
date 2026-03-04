/**********************************************************************
  Filename    : LED_Matrix_Bounce_Game
  Description : LED Matrix Bounce Game
  Author      : www.freenove.com
  Modification: 2024/08/05
**********************************************************************/

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

uint8_t gameOverFrame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1 },
  { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
  { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
  { 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int ballY = 4;             // Ball's initial vertical position
int ballX = 4;             // Ball's initial horizontal position
int ballSpeedY = 1;        // Vertical speed of the ball
int ballSpeedX = 1;        // Horizontal speed of the ball
int batCenter = 0;         // Bat's center position (controlled by analog input)
int gameSpeed = 300;       // Initial game speed (delay between frames)

void loop() {
  batCenter = analogRead(A0) / 204;  // Map analog input to bat's position

  // Draw the bat
  frame[batCenter][11] = 1;
  frame[batCenter + 1][11] = 1;
  frame[batCenter + 2][11] = 1;

  // Draw the ball
  frame[ballY][ballX] = 1;
  matrix.renderBitmap(frame, 8, 12);
  delay(gameSpeed);

  // Clear previous positions
  frame[batCenter][11] = 0;
  frame[batCenter + 1][11] = 0;
  frame[batCenter + 2][11] = 0;
  frame[ballY][ballX] = 0;
  matrix.renderBitmap(frame, 8, 12);
  delay(1);

  // Ball bounce logic (vertical and horizontal)
  if (ballY == 7 || ballY == 0) ballSpeedY = -ballSpeedY;
  if (ballX == 0) ballSpeedX = -ballSpeedX;

  // Ball hits bat detection
  if (ballX == 10) {  // Ball is in front of the bat
    int anticipatedY = (ballY + ballSpeedY);
    if (anticipatedY == batCenter || anticipatedY == batCenter + 1 || anticipatedY == batCenter + 2) {
      ballSpeedX = -ballSpeedX;  // Ball hits the bat, reverse direction
      gameSpeed -= 20;  // Speed up the game
    } else {
      // Game over
      matrix.renderBitmap(gameOverFrame, 8, 12);
      delay(2000);
      ballX = 4;  // Reset ball
      ballY = 4;
      ballSpeedX = -1;
      ballSpeedY = -1;
      gameSpeed = 300;  // Reset speed
    }
  }

  // Update ball's position
  ballY += ballSpeedY;
  ballX += ballSpeedX;
}