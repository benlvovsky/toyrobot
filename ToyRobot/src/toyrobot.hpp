#include <iostream>
using namespace std;


enum Facing {
	NORTH, SOUTH, EAST, WEST
};

struct Report {
    bool placed;
    string facingStr;
    int x;
    int y;
};


class ToyRobot {
  private:
    int x, y;
    Facing facing;
    bool placed;

  public:
    ToyRobot() : x(0), y(0), facing(NORTH), placed(false) {}
    virtual ~ToyRobot() {};

    virtual bool IsPlaced();
    virtual Facing GetFacing() {return facing;}

    virtual void Place(int x, int y, Facing f);
    virtual void Move();
    virtual void Left();
    virtual void Right();
    virtual Report CreateReport();
	virtual string FaceASStr();
};
