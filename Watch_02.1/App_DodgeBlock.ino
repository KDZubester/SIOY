
#define NUM_BLOCKS 7
#define EMPTY_VAL 300
#define STARTING_X_VAL 129
#define ENDING_X_VAL -10

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BLOCK_SIDE 7
#define PLAYER_SIDE 10

#define MAX_Y_VAL SCREEN_HEIGHT + 3 - BLOCK_SIDE

//Coordinate variables for all blocks
int xVals[NUM_BLOCKS];
int yVals[NUM_BLOCKS];
int playerX;
int playerY;

//Counter for blocks dodged
int blocksDodged = 0;

// Delete a Block once it has passed the player
void deleteBlock(int index) {
    xVals[index] = EMPTY_VAL;
    yVals[index] = EMPTY_VAL;
}


// Delete all Blocks in the array, and initialize player location
void initializeBlocks() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
      deleteBlock(i);
    }
    playerX = 0;
    playerY = 20;
}


// Create a New block every so often
void createNewBlock() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
      if (xVals[i] == EMPTY_VAL) {
        xVals[i] = STARTING_X_VAL;
        yVals[i] = random(0, MAX_Y_VAL);
        break;
      }
    }
}

//Display title screen and player movement instructions
void titleScreen() {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(28, 35);
  u8g.print("Dodge Block");

  u8g.drawBitmap(LEFT_X, BOTTOM_ARROW_Y, 1, 8, getIcon(DOWN_ARROW));
  u8g.drawBitmap(LEFT_X, TOP_Y, 1, 8, getIcon(UP_ARROW));
}

//Display how many blocks the player dodged before losing
void scoreScreen() {
  //Print Player score
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(12, 35);
  char dodgedString[25] = "";
  sprintf(dodgedString, "Blocks Dodged: %d", blocksDodged);
  u8g.print(dodgedString);
}

//Draw all blocks to the screen
void drawGame() {
  //Draw enemy blocks
  for (int i = 0; i < NUM_BLOCKS; i++) {
    if (xVals[i] != EMPTY_VAL) {
      u8g.drawFrame(xVals[i], yVals[i], BLOCK_SIDE, BLOCK_SIDE);
    }
  }

  //Draw player
  u8g.drawFrame(playerX, playerY, PLAYER_SIDE, PLAYER_SIDE);
}

void dodgeBlock() {
  delay(100);

  //Display the Title screen and instructions
  newScreen(titleScreen);

  delay(3000);

  //Initialize all variables
  int genCount = 0;
  blocksDodged = 0;
  initializeBlocks();

  //Draw all existing blocks to the screen (just player block in this case)
  newScreen(drawGame);

  long unsigned time_0 = millis();

  //Keep running the game unless the player presses BTN_NE
  while (digitalRead(BTN_NE) == HIGH) {
    //BLOCK CODE//
    for (int i = 0; i < NUM_BLOCKS; i++) {

      //Move all enemy blocks that are currently active
      if (xVals[i] != EMPTY_VAL) {
        xVals[i] -= 2;

        //Delete any block that has left the screen
        if (xVals[i] <= ENDING_X_VAL) {
          deleteBlock(i);
          blocksDodged++;
        }
      }
    }
    //END BLOCK CODE//

    //Keep track of how many times through while loop
    genCount++;

    //Create New block every 12 cycles
    if (genCount == 12) {
      createNewBlock();
      genCount = 0;
    }


    //PLAYER CODE// Move the player depending on the button that the user presses
    if ((digitalRead(BTN_SW) == LOW) && (playerY + 2 + PLAYER_SIDE < SCREEN_HEIGHT)) {
      playerY += 2;
    }
    else if ((digitalRead(BTN_NW) == LOW) && (playerY - 2 > 0)) {
      playerY -= 2;
    }
    //END PLAYER CODE//

    //Display changes
    newScreen(drawGame);

    bool collision = false;

    //Check if any enemy  block has crossed the player block
    for (int i = 0; i < NUM_BLOCKS; i++) {
      if ((xVals[i] < PLAYER_SIDE) && (xVals[i] + BLOCK_SIDE > 0)) {
        if ((yVals[i] + BLOCK_SIDE > playerY) && (yVals[i] < playerY + PLAYER_SIDE)) {
          collision = true;
        }
      }
    }

    //If there was a collision, break out of the game loop
    if (collision == true) {
      break;
    }
  }

  delay(1000);

  //Display how many blocks the player dodged
  newScreen(scoreScreen);
  
  delay(3000);
}
