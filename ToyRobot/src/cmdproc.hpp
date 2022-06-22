#include <iostream>
#include "toyrobot.hpp"
using namespace std;


class CommandProcessing {
	ToyRobot* tr;
  public:
	CommandProcessing(ToyRobot* toyRobot) : tr(toyRobot) {}

	void process(string line);
	Facing faceStrToEnum(string sFacing);
};
