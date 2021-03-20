#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#include "images/startScreen.h"
#include "images/endScreen.h"
#include "images/winScreen.h"
#include "images/ball.h"

typedef enum {
  START,
  PLAY,
  WIN,
  LOSE,
} GBAState;

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  GBAState state = START;

  Snake snake1;
  snake1.row = 80;
  snake1.col = 100;
  snake1.width = 5;
  snake1.height = 5;
  Snake snake2;
  snake2.row = 80;
  snake2.col = 105;
  snake2.width = 5;
  snake2.height = 5;
  Snake snake3;
  snake3.row = 80;
  snake3.col = 110;
  snake3.width = 5;
  snake3.height = 5;
  Snake snake4;
  snake4.row = 80;
  snake4.col = 115;
  snake4.width = 5;
  snake4.height = 5;
  Snake snake5;
  snake5.row = 80;
  snake5.col = 120;
  snake5.width = 5;
  snake5.height = 5;
  Snake snake6;
  snake6.row = 80;
  snake6.col = 125;
  snake6.width = 5;
  snake6.height = 5;
  Snake snake7;
  snake7.row = 80;
  snake7.col = 130;
  snake7.width = 5;
  snake7.height = 5;
  int lastButtons = 0;
  int randH = randint(2,13) * 10;
  int randW = randint(2,22) * 10;
  int score = 0;

  while (randW == 80) {
      randW = randint(2,22) * 10;
  }
  while (randH >= 100 && randH <= 120) {
      randH = randint(2,13) * 10;
  }

  while (1) {
    currentButtons = BUTTONS;

    switch (state) {
      case START:
        waitForVBlank();
        drawFullScreenImageDMA(startScreen);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
            fillScreenDMA(BLACK);
            snake1.row = 80;
            snake1.col = 100;
            snake1.width = 5;
            snake1.height = 5;
            snake2.row = 80;
            snake2.col = 105;
            snake2.width = 5;
            snake2.height = 5;
            snake3.row = 80;
            snake3.col = 110;
            snake3.width = 5;
            snake3.height = 5;
            snake4.row = 80;
            snake4.col = 115;
            snake4.width = 5;
            snake4.height = 5;
            snake5.row = 80;
            snake5.col = 120;
            snake5.width = 5;
            snake5.height = 5;
            snake6.row = 80;
            snake6.col = 125;
            snake6.width = 5;
            snake6.height = 5;
            snake7.row = 80;
            snake7.col = 130;
            snake7.width = 5;
            snake7.height = 5;
            lastButtons = 0;
            vBlankCounter = 0;
            randH = randint(2,13) * 10;
            randW = randint(2,22) * 10;
            while (randW == 80) {
                randW = randint(2,22) * 10;
            }
            while (randH >= 100 && randH <= 120) { 
                randH = randint(2,13) * 10;
            }
            score = 0;
            state = PLAY;
        }
        break;
      case PLAY:
        waitForVBlank(); 
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            state = START;
            break;
        } 
        if (vBlankCounter % 9 == 0) {
        drawRectDMA(9, 9, 221, 1, WHITE);
        drawRectDMA(9, 9, 1, 131, WHITE);
        drawRectDMA(9, 230, 1, 132, WHITE);
        drawRectDMA(140, 9, 221, 1, WHITE);
        if ((snake1.row == randH && snake1.col == randW) || (snake2.row == randH && snake2.col == randW) ||
         (snake3.row == randH && snake3.col == randW)) {
            score++;
            randH = randint(2,13) * 10;
            randW = randint(2,22) * 10;
            while (randW == snake1.col || randW == snake2.col || randW == snake3.col || randW == snake4.col || randW == snake5.col || 
              randW == snake6.col) {
              vBlankCounter ++;
              randW = randint(2,22) * 10;
            }
            while (randH == snake1.row || randH == snake2.row || randH == snake3.row || randH == snake4.row || randH == snake5.row || 
              randH == snake6.row) {
              vBlankCounter ++;
              randH = randint(2,13) * 10;
            }
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons) && lastButtons != BUTTON_RIGHT) {
            snake7 = snake6;
            snake6 = snake5;
            snake5 = snake4;
            snake4 = snake3;
            snake3 = snake2;
            snake2 = snake1;
            snake1.col = snake1.col - 5;
            lastButtons = BUTTON_LEFT;
            drawRectDMA(snake7.row, snake7.col, snake7.width, snake7.height, BLACK);
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && lastButtons != BUTTON_LEFT) {
            if (lastButtons == 0) {
              Snake copy1 = snake5;
              Snake copy2 = snake6;
              Snake copy3 = snake7;
              snake7 = snake1;
              snake6 = snake2;
              snake5 = snake3;
              snake3 = copy1;
              snake2 = copy2;
              snake1 = copy3; 
            } else {
              snake7 = snake6;
              snake6 = snake5;
              snake5 = snake4;
              snake4 = snake3;
              snake3 = snake2;
              snake2 = snake1;
              snake1.col = snake1.col + 5;
            }
            lastButtons = BUTTON_RIGHT;
            drawRectDMA(snake7.row, snake7.col, snake7.width, snake7.height, BLACK);
        }
        if (KEY_DOWN(BUTTON_UP, currentButtons) && lastButtons != BUTTON_DOWN) {
            snake7 = snake6;
            snake6 = snake5;
            snake5 = snake4;
            snake4 = snake3;
            snake3 = snake2;
            snake2 = snake1;
            snake1.row = snake1.row - 5;
            lastButtons = BUTTON_UP;
            drawRectDMA(snake7.row, snake7.col, snake7.width, snake7.height, BLACK);
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons) && lastButtons != BUTTON_UP) {
            snake7 = snake6;
            snake6 = snake5;
            snake5 = snake4;
            snake4 = snake3;
            snake3 = snake2;
            snake2 = snake1;
            snake1.row = snake1.row + 5;
            lastButtons = BUTTON_DOWN;
            drawRectDMA(snake7.row, snake7.col, snake7.width, snake7.height, BLACK);
        }
        if (snake1.row < 10 || snake1.row > 139 || snake1.col < 10 || snake1.col > 225
          || (snake1.row == snake3.row && snake1.col == snake3.col) || (snake1.row == snake4.row && snake1.col == snake4.col)
            || (snake1.row == snake5.row && snake1.col == snake5.col) || (snake1.row == snake6.row && snake1.col == snake6.col)
            || (snake1.row == snake2.row && snake1.col == snake2.col) || (snake1.row == snake7.row && snake1.col == snake7.col))  {
          state = LOSE;
          break;
        }
        if (score == 5) {
          state = WIN;
          break;
        }
        drawRectDMA(snake1.row, snake1.col, snake1.width, snake1.height, GREEN);
        drawRectDMA(snake2.row, snake2.col, snake2.width, snake2.height, GREEN);
        drawRectDMA(snake3.row, snake3.col, snake3.width, snake3.height, GREEN);
        drawRectDMA(snake4.row, snake4.col, snake4.width, snake4.height, GREEN);
        drawRectDMA(snake5.row, snake5.col, snake5.width, snake5.height, GREEN);
        drawRectDMA(snake6.row, snake6.col, snake6.width, snake6.height, GREEN);
        drawImageDMA(randW, randH, BALL_WIDTH, BALL_HEIGHT, ball);
        char buffer[2];
        drawString(150, 5, buffer, BLACK);
        sprintf(buffer, "Score: %d (Eat five food to win!)", score);
        drawString(150, 5, buffer, YELLOW);
        }
        break;
      case WIN:
        waitForVBlank();
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            state = START;
            break;
        }
        drawFullScreenImageDMA(winScreen);
        break;
      case LOSE:
        waitForVBlank();
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            state = START;
            break;
        }
        drawFullScreenImageDMA(endScreen);
        break;
    }

    previousButtons = currentButtons; 
  }

  return 0;
}
