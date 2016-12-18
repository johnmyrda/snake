#include <Arduino.h>

enum direct {
  UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2};

// The snake is a list of Dot elements, with both head and tail pointer
class Snake
{
  friend void snakePrint(const Snake& s);
  struct Dot
  {
    direct dir;
    int x;
    int y;
    Dot *next;
  };

  
  byte length;
  Dot *head;
  Dot *tail;
  byte apple[2];
  int fieldWidth;
  int fieldHeight;
  bool xWrap;
  bool yWrap;
  
public:
  Snake(int fieldWidth, int fieldHeight);  
  void move();
  void changeDir(direct d);
  void append();
  //boolean posHead(byte x, byte y);
  void newApple();
  boolean eat();
  //void print();
  //~Snake();
private:
  void construct(int fieldWidth, int fieldHeight);
};
