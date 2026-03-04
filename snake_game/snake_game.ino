#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();
}

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

// Global variables
byte ledMatrix[8][12];
byte currentDirection = RIGHT;
byte snakeLength = 2;
byte snakeColPositions[96];
byte snakeRowPositions[96];
byte foodCol = random(2, 12);
byte foodRow = random(1, 8);
byte movementSpeed = 500;
byte foodConsumed = 1;
byte emptyFrame[8][12];

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

int getSnakeDirection(){
  // Get joystick values (from ADC pins A0 and A1)
  int joystickX = analogRead(A0);
  int joystickY = analogRead(A1);

  if((joystickX >= 0) && (joystickX <= 300) && currentDirection != RIGHT){
    return LEFT;
  }
  else if((joystickX >= 723) && (joystickX <= 1023) && currentDirection != LEFT){
    return RIGHT;
  }
  else if((joystickY >= 0) && (joystickY <= 300) && currentDirection != DOWN){
    return UP;
  }
  else if((joystickY >= 723) && (joystickY <= 1023) && currentDirection != UP){
    return DOWN;
  }
  else return currentDirection;
}

void displayLedMatrix(){
  // Clear the matrix first - Turn off all LEDs
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 12; j++){
      ledMatrix[i][j] = 0;
    }
  }

  // Display the snake's body on the matrix
  for(int i = 0; i < snakeLength; i++){
    ledMatrix[snakeRowPositions[i]][snakeColPositions[i]] = 1;
  }

  // Display the food
  ledMatrix[foodRow][foodCol] = 1;

  // Render the updated LED matrix
  matrix.renderBitmap(ledMatrix, 8, 12);
}

void gameOverSequence(){
  // Pause the snake's movement and blink the LEDs for 5 times
  for(int i = 0; i < 5; i++){
    // Display current frame (paused movement)
    matrix.renderBitmap(ledMatrix, 8, 12);
    delay(100);
    // Display blank frame (to create blink effect)
    matrix.renderBitmap(emptyFrame, 8, 12);
    delay(100);
    matrix.renderBitmap(gameOverFrame, 8, 12);
    delay(2000);
  }
  // Reset the snake length after game over
  snakeLength = 2;
}

void checkForSnakeBodyCollision(){
  // Check if the head collides with any body part
  for(int i = 1; i < snakeLength; i++){
    if((snakeRowPositions[i] == snakeRowPositions[0]) && (snakeColPositions[i] == snakeColPositions[0])){
      gameOverSequence();
    }
  }
}

void checkForFoodConsumption(){
  // Logic to check if food is consumed
  if(snakeColPositions[0] == foodCol && snakeRowPositions[0] == foodRow){
    // Increase snake length if food is eaten
    snakeLength += 1;
    // Set foodConsumed flag to 1 to generate new food coordinates
    foodConsumed = 1;
  }
}

void updateSnakePosition(){
  // Logic to calculate the new position of the snake in the next frame
  // Move the body
  for(int i = snakeLength - 1; i > 0; i--){
    snakeColPositions[i] = snakeColPositions[i - 1];
    snakeRowPositions[i] = snakeRowPositions[i - 1];
  }

  // Move the head
  if(currentDirection == RIGHT) {
    // Wrap around to the left if it goes off the right edge
    if(snakeColPositions[0] == 11){
      snakeColPositions[0] = 0;
    }
    else {
      snakeColPositions[0] += 1;
    }
  }

  if(currentDirection == LEFT) {
    // Wrap around to the right if it goes off the left edge
    if(snakeColPositions[0] == 0){
      snakeColPositions[0] = 11;
    }
    else{
      snakeColPositions[0] -= 1;
    }
  }

  if(currentDirection == DOWN) {
    // Wrap around to the top if it goes off the bottom edge
    if(snakeRowPositions[0] == 7){
      snakeRowPositions[0] = 0;
    }
    else{
      snakeRowPositions[0] += 1;
    }
  }

  if(currentDirection == UP) {
    // Wrap around to the bottom if it goes off the top edge
    if(snakeRowPositions[0] == 0){
      snakeRowPositions[0] = 7;
    }
    else{
      snakeRowPositions[0] -= 1;
    }
  }
}

void generateFood(){
  // Generate new coordinates for food if it was eaten
  if(foodConsumed == 1){
    foodCol = random(0, 12);
    foodRow = random(0, 8);
    foodConsumed = 0;
  }
}

void loop() {
  // Get the direction of the snake from the joystick
  currentDirection = getSnakeDirection();

  // Display food and snake on the LED matrix
  displayLedMatrix();

  // Check if snake's body collided with the head
  checkForSnakeBodyCollision();

  // Check if the food was consumed
  checkForFoodConsumption();

  // Update the snake's position for the next frame
  updateSnakePosition();

  // Generate new food if necessary
  generateFood();

  // Control the speed of the snake movement
  delay(movementSpeed);
}