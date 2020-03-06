#include <LedControl.h>




/* Display PINs */
#define CLK     10
#define CS      11
#define DIN     12
#define left    3
#define right   4
#define up      5
#define down    6
char move_c,move_r;

#define SIZE    8
#define ADVANCE_DELAY 20


int snake[SIZE*SIZE][2];
int length;
int food[2], v[2];
bool is_game_over = false;
long current_time;
long prev_advance;
int blink_count;
const short messageSpeed = 5;


LedControl lc = LedControl(DIN, CLK, CS, 1);

void restart()
{  
  if(!digitalRead(down))
  {
  is_game_over = false;
  init_game();
  }

}
void init_game()
{
  prev_advance = current_time = 0;
  blink_count = 3;
  int half = SIZE / 2;
  length = SIZE / 3;

  for (int i = 0; i < length; i++)
  {
      snake[i][0] = half - 1;
      snake[i][1] = half + i;
  }

  food[0] = half + 1;
  food[1] = half - 1;

  move_r = 0;
  move_c = -1;

}

void render()
{
  for (int i = 0; i < length; i++) 
  {
    lc.setLed(0, snake[i][0], snake[i][1], 1);
  }
  lc.setLed(0, food[0], food[1], 1);
}

void clearScreen() 
{
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      lc.setLed(0, x, y, 0);
    }
  }
}

/**
 * moves the snake forward
 * returns true if the game is over
 */
bool advance() {
  int head[2] = {snake[0][0] + move_r, snake[0][1] + move_c};


  if (head[0] <= 0 ) {

  snake[0][0] <= 0 ? snake[0][0] +=  8 : 0;

  
 }
if( head[0] >= SIZE){
  snake[0][0] >= 7 ? snake[0][0] -=  8 : 0;
  
}


  if (head[1] <= 0 ) {


  snake[0][1] <= 0 ? snake[0][1] += 8 : 0;

  

 }

 if(head[1] >= SIZE){
  snake[0][1] >= 7 ? snake[0][1] -= 8 : 0;
 }



  for (int i = 0; i < length; i++)
  {
      if (snake[i][0] == head[0] && snake[i][1] == head[1])
      {
            delay(1000);
        showGameOverMessage();
          return true;
      }
  }

  bool grow = (head[0] == food[0] && head[1] == food[1]);
  if (grow) 
  {
      length++;  
      randomSeed(current_time);    
      food[0] = random(SIZE);
      food[1] = random(SIZE);
  }

  for (int i = length - 1; i >= 0; i--)
  {
      snake[i + 1][0] = snake[i][0];
      snake[i + 1][1] = snake[i][1];
  }
  snake[0][0] += move_r;
  snake[0][1] += move_c;
  return false;
}

void setup() 
{


  pinMode(left, INPUT);
  pinMode(right, INPUT);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);


  lc.shutdown(0, false);
  lc.setIntensity(0, 8);

  init_game();
  render();
}

void loop() {
  if (!is_game_over) {
    clearScreen();
    render();

    if (current_time - prev_advance > ADVANCE_DELAY) {
      is_game_over = advance();
      prev_advance = current_time;    
    }
  } else {
    
    while (blink_count > 0) {
      clearScreen();
      delay(300);
      render();
      delay(300);
      blink_count--;     
         
    }
restart();
  }
  readControls();
  current_time++;

  
}



void readControls() 
{
 if(!digitalRead(left))
 {
   move_r=0;
   move_c!=-1 ? move_c=-1 : move_c=1;
   while(!digitalRead(left));
 }
 if(!digitalRead(right))
 {
   move_r=0;
   move_c!=1 ? move_c=1 : move_c=-1;
   while(!digitalRead(right));
 }
 if(!digitalRead(up))
 {
   move_c=0;
   move_r!=-1 ? move_r=-1 : move_r=1;
   while(!digitalRead(up));
 }
 if(!digitalRead(down))
 {
   move_c=0;
   move_r!=1 ? move_r=1 : move_r=-1;
   while(!digitalRead(down));
 }
}





const PROGMEM bool gameOverMessage[8][90] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}
}; 
void showGameOverMessage() {
  for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {
    for (int col = 0; col < 8; col++) {
      delay(messageSpeed);
      for (int row = 0; row < 8; row++) {
        // this reads the byte from the PROGMEM and displays it on the screen
        lc.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d])));


       

      }
    }
  }

}
