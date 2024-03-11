#include <Adafruit_NeoPixel.h>

#define PIN            11
#define WIDTH          16
#define HEIGHT         16
#define NUMPIXELS      (WIDTH * HEIGHT)
#define BRIGHTNESS     150

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define UP     0
#define DOWN   1
#define LEFT   2
#define RIGHT  3

struct Point {
  int x;
  int y;
};

Point snake[256]; 
int snake_length = 3; // Initial snake length
int snake_direction = RIGHT; // Initial direction
Point food;


void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.show();
  snake[0].x = WIDTH / 2;
  snake[0].y = HEIGHT / 2;
  for (int i = 1; i < snake_length; i++) {
    snake[i].x = snake[0].x - i;
    snake[i].y = snake[0].y;
  }
  placeFood();
}

void placeFood() {
  while (true) {
    food.x = random(WIDTH);
    food.y = random(HEIGHT);
    bool isOnSnake = false;
    for (int i = 0; i < snake_length; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        isOnSnake = true;
        break;
      }
    }
    if (!isOnSnake) {
      break;
    }
  }
}

void loop() {
  
  //changing snake's speed based on snake's length
  switch(snake_length) {
    case 3:
      delay(500);
      break;
    case 4:
      delay(450);
      break;
    case 5:
      delay(400);
      break;
    case 6:
      delay(350);
      break;
    case 7:
      delay(300);
      break;
  }

  if(snake_length > 7 && snake_length <= 10) {
    delay(250);
  }

  if(snake_length > 10) {
  delay(200);
  }

  if (digitalRead(UP) == LOW && snake_direction != 4) {
    snake_direction = 3;
  } else if (digitalRead(DOWN) == LOW && snake_direction != 3) {
    snake_direction = 4;
  } else if (digitalRead(LEFT) == LOW && snake_direction != 1) {
    snake_direction = 2;
  } else if (digitalRead(RIGHT) == LOW && snake_direction != 2) {
    snake_direction = 1;
  }
  
  //moving the snake's tail forward 
    for (int i = snake_length - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }

    // Advance the snake's head
    switch(snake_direction) {
      case 3:
        snake[0].y--;
        break;
      case 4:
        snake[0].y++;
        break;
      case 2:
        snake[0].x--;
        break;
      case 1:
        snake[0].x++;
        break;
    }

    // Wall failiure
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
      
      // Game Over: Restart the game by showing red flag
      pixels.clear();
      for (int i = 0; i < 256; i++) {
      pixels.setPixelColor(i, pixels.Color(225, 0, 0));
      }
      pixels.show();
      delay(500);
      snake_length = 3;
      snake[0].x = WIDTH / 2;
      snake[0].y = HEIGHT / 2;
      snake_direction = RIGHT;
      for (int i = 1; i < snake_length; i++) {
        snake[i].x = snake[0].x - i;
        snake[i].y = snake[0].y;
      }
      placeFood();
    }

    // snake failiure
    for (int i = 1; i < snake_length; i++) {
      if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
        // Game Over: Restart the game by showing red flag
        pixels.clear();
        for (int i = 0; i < 256; i++) {
        pixels.setPixelColor(i, pixels.Color(225, 0, 0));
        }
        pixels.show();
        delay(500);

        snake_length = 4;
        snake[0].x = WIDTH / 2;
        snake[0].y = HEIGHT / 2;
        snake_direction = RIGHT;
        for (int i = 1; i < snake_length; i++) {
          snake[i].x = snake[0].x - i;
          snake[i].y = snake[0].y;
        }
        placeFood();
      }
    }

    //Eating food
    if (snake[0].x == food.x && snake[0].y == food.y) {
      placeFood();
      snake_length++;
      for (int i = snake_length - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }
    }

    // updating
    pixels.clear();
    for (int i = 0; i < snake_length; i++) {
      pixels.setPixelColor(snake[i].y * WIDTH + snake[i].x, pixels.Color(200, 55, 255));
      }
    pixels.setPixelColor(food.y * WIDTH + food.x, pixels.Color(34, 255, 255));
    pixels.show();
  }
