#include <Arduino.h>
#include <ledMatrix.h>

enum direct {
  UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2};

// The snake is a list of Dot elements, with both head and tail pointer
class Snake
{
  friend void snakePrint(const Snake& s);
  struct Dot
  {
    direct dir;
    byte x;
    byte y;
    Dot *next;
  };

  byte length;
  Dot *head;
  Dot *tail;
  byte apple[2];
public:
  Snake();
  void move();
  void changeDir(direct d);
  void append();
  //boolean posHead(byte x, byte y);
  void newApple();
  boolean eat();
  //void print();
  //~Snake();
};
