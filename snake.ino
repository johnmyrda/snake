/*
 * Simple remake of the classic Snake game, using Arduino and
 * an LED matrix, optimized for MAX7219 driver.
 * By GLGPrograms
 * GPL-3.0
*/

#include <ledMatrix.h>
#include "snake_class.h"

ledMatrix myMatrix(8,10,12);

Snake mySnake;

boolean eaten = true;
char val;
byte x;
byte y;

void setup()
{
  Serial.begin(9600);
  myMatrix.setBrightness(2);
  randomSeed( analogRead(A0) );
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
    mySnake.changeDir(UP);
    break;
  case 'a':
    mySnake.changeDir(LEFT);
    break;
  case 's':
    mySnake.changeDir(DOWN);
    break;
  case 'd':
    mySnake.changeDir(RIGHT);
    break;
  }

  mySnake.move();

  // If apple has been eaten, draw new one
  if( eaten )
  {
    mySnake.newApple();
    eaten = false;
  }
  // else check if the snake eats it
  else if ( mySnake.eat() )
  {
    eaten = true;
    mySnake.append();
  }

  snakePrint(mySnake);
  delay(500);
}

void snakePrint(const Snake& s)
{
  Snake::Dot *tmp = s.head;
  // Clear matrix
  myMatrix.flush();
  // Print snake
  for (byte i = 0; i < s.length; i++)
  {
    myMatrix.dot(tmp -> x, tmp -> y);
    tmp = tmp -> next;
  }
  // Print apple
  myMatrix.dot(s.apple[0], s.apple[1]);
  // Actually display matrix content
  myMatrix.load();
}

