#include "snake_class.h"

// Constructor
Snake::Snake()
{
  length = 1;
  head = new Dot;
  head -> dir = RIGHT;
  head -> x = 1;
  head -> y = 1;
  head -> next = NULL;
  tail = head;
  apple[0] = 0;
  apple[1] = 0;
}

// Add a "piece" of snake after eating an apple
void Snake::append()
{
  tail -> next = new Dot;
  Dot *tmp = tail -> next;
  tmp -> dir = tail -> dir;

  switch(tail -> dir)
  {
  case UP:
    tmp->x = tail->x;
    tmp->y = tail->y + 1;
    tmp->y = (tmp->y == 9) ? 1 : tmp->y;
    break;
  case RIGHT:
    tmp->y = tail->y;
    tmp->x = tail->x -1;
    tmp->x = (tmp->x == 0) ? 8 : tmp->x;
    break;
  case DOWN:
    tmp->x = tail->x;
    tmp->y = tail->y - 1;
    tmp->y = (tmp->y == 0) ? 8 : tmp->y;
    break;
  case LEFT:
    tmp->y = tail->y;
    tmp->x = tail->x +1;
    tmp->x = (tmp->x == 9) ? 1 : tmp->x;
    break;
  }

  tail = tail -> next;
  tail -> next = NULL;
  length++;
}

// Move the snake in the current direction
void Snake::move()
{
  Dot *p = head;
  direct tmp1 = p -> dir;
  direct tmp2 = p -> dir;
  for(byte i = 0; i < length; i++, p = p -> next)
  { 
    switch(p -> dir)
    {
    case UP:
      p -> y--;
      p -> y = (p -> y == 0) ? 8 : p -> y;
      break;
    case RIGHT:
      p -> x++;
      p -> x = (p -> x == 9) ? 1 : p -> x;
      break;
    case DOWN:
      p -> y++;
      p -> y = (p -> y == 9) ? 1 : p -> y;
      break;
    case LEFT:
      p -> x--;
      p -> x = (p -> x == 0) ? 8 : p -> x;
      break;
    }

    tmp2 = p -> dir;
    p -> dir = tmp1;
    tmp1 = tmp2;
  }
}

// Change direction
void Snake::changeDir(direct d)
{
  switch(d)
  {
  case UP:
    if( head->dir != DOWN )
      head->dir = d;
    break;
  case RIGHT:
    if( head->dir != LEFT )
      head->dir = d;
    break;
  case DOWN:
    if( head->dir != UP )
      head->dir = d;
    break;
  case LEFT:
    if( head->dir != RIGHT )
      head->dir = d;
    break;
  }
}

/*boolean Snake::posHead(byte x, byte y)
{
  return ((x == head->x) && (y == head->y)) ? true: false;
}*/

// Spawn a new apple
void Snake::newApple()
{
  do
  {
    apple[0] = random(1, 9);
    apple[1] = random(1, 9);
  }
  while( (apple[0] == head->x) && (apple[1] == head->y) );
}

// Check if snake is eating the apple (head over the apple)
boolean Snake::eat()
{
  if( (apple[0] == head->x) && (apple[1] == head->y) )
    return true;
  return false;
}

