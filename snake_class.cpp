#include "snake_class.h"

// Constructor
Snake::Snake(int fieldWidth, int fieldHeight)
{
  construct(fieldWidth, fieldHeight);
}

void Snake::construct(int width, int height) {
  maxLength = 255;
  length = 1;
  head = new Dot;
  head -> dir = RIGHT;
  head -> x = random(0, width);
  head -> y = random(0, height);
  head -> next = NULL;
  tail = head;
  newApple();
  fieldWidth = width;
  fieldHeight = height;
}

void Snake::setMaxLength(int length){
    maxLength = length;
  }

//contain a value within [0, limit)
int wrapPosition(int position, int limit){
    if(position >= limit){
      return 0;
    } else if (position < 0){
      return limit - 1;
    } else {
      return position;
    }
  }

// Add a "piece" of snake after eating an apple
void Snake::append()
{
  if(length >= maxLength){
    reset();  
  } else {
    tail -> next = new Dot;
    Dot *tmp = tail -> next;
    tmp -> dir = tail -> dir;
  
    switch (tail -> dir)
    {
      case UP:
        tmp->x = tail->x;
        tmp->y = wrapPosition(tail->y + 1, fieldHeight);
        break;
      case RIGHT:
        tmp->y = tail->y;
        tmp->x = wrapPosition(tail->x + 1, fieldWidth);
        break;
      case DOWN:
        tmp->x = tail->x;
        tmp->y = wrapPosition(tail->y - 1, fieldHeight);
        break;
      case LEFT:
        tmp->y = tail->y;
        tmp->x = wrapPosition(tail->x - 1, fieldWidth);
        break;
    }
  
    tail = tail -> next;
    tail -> next = NULL;
    length++;
  }
}

void Snake::reset(){
    Dot * tempNode = head->next;
    //free all except the head Dot
    while(tempNode!=NULL)
    {   
        head->next = tempNode->next;
        tempNode->next = NULL;
        free(tempNode);
        tempNode = head->next;
    }

    length = 1;
    tail = head;
  }

// Move the snake in the current direction
void Snake::move()
{
  Dot *p = head;
  direct tmp1 = p -> dir;
  direct tmp2 = p -> dir;
  for (byte i = 0; i < length; i++, p = p -> next)
  {
    switch (p -> dir)
    {
      case UP:
        p -> y = wrapPosition(p -> y - 1, fieldHeight);
        break;
      case RIGHT:
        p -> x = wrapPosition(p -> x - 1, fieldWidth);
        break;
      case DOWN:
        p -> y = wrapPosition(p -> y + 1, fieldHeight);
        break;
      case LEFT:
        p -> x = wrapPosition(p -> x + 1, fieldWidth);
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
  switch (d)
  {
    case UP:
      if ( head->dir != DOWN )
        head->dir = d;
      break;
    case RIGHT:
      if ( head->dir != LEFT )
        head->dir = d;
      break;
    case DOWN:
      if ( head->dir != UP )
        head->dir = d;
      break;
    case LEFT:
      if ( head->dir != RIGHT )
        head->dir = d;
      break;
  }
}

/*boolean Snake::posHead(byte x, byte y)
  {
  return ((x == head->x) && (y == head->y)) ? true: false;
  }*/

direct Snake::aiMove(){
    
    if(head->dir == UP || head->dir == DOWN && apple[0] != head->x){
      if(apple[1] == head->y){
          if(modularDistance(LEFT, head->x, apple[0]) < fieldWidth/2){
            return LEFT;
          } else {
            return RIGHT;
          }
        }
    } else 
      if(head->dir == LEFT || head->dir == RIGHT && apple[1] != head->y){
      if(apple[0] == head->x){
          if(modularDistance(DOWN, head->y, apple[1]) < fieldHeight/2){
            return DOWN;
          } else {
            return UP;
          }
        }
    } else {
      return head->dir;
    }
        
  }

//given a direction, what is the distance from point a to b
int Snake::modularDistance(direct dir, int a, int b){
    int dist = b - a;
    switch (dir)
    {
      case UP:
        dist = (dist + fieldHeight) % fieldHeight;
        break;
      case RIGHT:
        dist = (dist + fieldWidth) % fieldWidth;
        break;
      case DOWN:
        dist = dist * -1;
        dist = (dist + fieldHeight) % fieldHeight;        
        break;
      case LEFT:
        dist = dist * -1;
        dist = (dist + fieldWidth) % fieldWidth;
        break;
    }
    return dist;
  }

// Spawn a new apple
void Snake::newApple()
{
  do
  {
    apple[0] = random(0, fieldWidth);
    apple[1] = random(0, fieldHeight);
  }
  while ( (apple[0] == head->x) && (apple[1] == head->y) );
}

// Check if snake is eating the apple (head over the apple)
boolean Snake::eat()
{
  if ( (apple[0] == head->x) && (apple[1] == head->y) )
    return true;
  return false;
}

