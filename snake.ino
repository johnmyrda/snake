/*
 * Simple remake of the classic Snake game, using Arduino and
 * an LED matrix, optimized for MAX7219 driver.
 * By GLGPrograms
 * GPL-3.0
*/

#include <FastLED.h>
#include "snake_class.h"

// Define variable for FastLED usage
//#define NUM_LEDS 60
#define CHIPSET WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN A1

const CRGB SNAKE_COLOR = CRGB::White;
const CRGB APPLE_COLOR = CRGB::GreenYellow;

const uint8_t MatrixWidth  = 12;
const uint8_t MatrixHeight = 5;
const bool    MatrixSerpentineLayout = false;
const uint8_t BRIGHTNESS = 64;

const int NUM_LEDS = (MatrixWidth * MatrixHeight);
CRGB leds[NUM_LEDS];

Snake snake = Snake(MatrixWidth, MatrixHeight);

boolean eaten = true;
char val;
byte x;
byte y;

void setup()
{
  //Serial.begin(9600);
  snake.setMaxLength(10);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );  
  randomSeed( analogRead(A2) );
}

void loop()
{
  val = '0';
  if( Serial.available() > 0 )
  {
    val = Serial.read();
    // Flush the buffer
    while( Serial.available() )
      Serial.read();
  }

  switch(val)
  {
  case 'w':
    snake.changeDir(UP);
    break;
  case 'a':
    snake.changeDir(LEFT);
    break;
  case 's':
    snake.changeDir(DOWN);
    break;
  case 'd':
    snake.changeDir(RIGHT);
    break;
  }

  snake.changeDir(snake.aiMove());

  snake.move();

  // If apple has been eaten, draw new one
  if( eaten )
  {
    snake.newApple();
    eaten = false;
  }
  // else check if the snake eats it
  else if ( snake.eat() )
  {
    eaten = true;
    snake.append();
  }

  snakePrint(snake);
  delay(300);
}

void snakePrint(const Snake& s)
{
  Snake::Dot *tmp = s.head;
  // Clear matrix
  FastLED.clear();
  // Print snake
  for (byte i = 0; i < s.length; i++)
  {
    leds[XY(tmp -> x, tmp -> y)] = SNAKE_COLOR;
    tmp = tmp -> next;
  }
  // Print apple
  leds[XY(s.apple[0], s.apple[1])] = APPLE_COLOR;
  // Actually display matrix content
  FastLED.show();
}

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( MatrixSerpentineLayout == false) {
    i = (y * MatrixWidth) + x;
  } else {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (MatrixWidth - 1) - x;
      i = (y * MatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * MatrixWidth) + x;
    }
  }
  
  return i;
}
