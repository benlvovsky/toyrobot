#include <stdio.h>
#include <iostream>
#include "toyrobot.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

bool ToyRobot::IsPlaced() {
  return this->placed;
}


void ToyRobot::Place(int x, int y, Facing f) {
	if (x < 0 || x > 4) {
		throw invalid_argument("Placing to position is beyond acceptable");
	}
	this->x = x;
	this->y = y;
	this->facing = f;
	this->placed = true;
}

void ToyRobot::Move() {
	if (!placed) {
		throw invalid_argument("Has to be placed before");
	}

	switch(this->facing) {
		case NORTH:
			if (y <= 0) {
				throw invalid_argument("Move North to position is beyond acceptable");
			} else {
				y--;
			}
			break;
		case SOUTH:
			if (y >= 4) {
				throw invalid_argument("Move South to position is beyond acceptable");
			} else {
				y++;
			}
			break;
		case WEST:
			if (x <= 0) {
				throw invalid_argument("Move West to position is beyond acceptable");
			} else {
				x--;
			}
			break;
		case EAST:
			if (x >= 4) {
				throw invalid_argument("Move East to position is beyond acceptable");
			} else {
				x++;
			}
			break;
		default:
			throw invalid_argument("unacceptable direction");
	}
}

void ToyRobot::Left() {
	if (!placed) {
		throw invalid_argument("Has to be placed before");
	}

	switch(this->facing) {
		case NORTH:
			this->facing = WEST;
			break;
		case SOUTH:
			this->facing = EAST;
			break;
		case WEST:
			this->facing = SOUTH;
			break;
		case EAST:
			this->facing = NORTH;
			break;
		default:
			throw invalid_argument("unacceptable direction");
	}
}

void ToyRobot::Right() {
	if (!placed) {
		throw invalid_argument("Has to be placed before");
	}

	switch(this->facing) {
		case NORTH:
			this->facing = EAST;
			break;
		case SOUTH:
			this->facing = WEST;
			break;
		case WEST:
			this->facing = NORTH;
			break;
		case EAST:
			this->facing = SOUTH;
			break;
		default:
			throw invalid_argument("unacceptable direction");
	}
}

Report ToyRobot::CreateReport() {
	struct Report report;
	report.placed = this->placed;
    report.facingStr = this->FaceASStr();
    report.x = this->x;
    report.y = this->y;

    return report;
}

string ToyRobot::FaceASStr() {
	if (this->facing == NORTH) return "NORTH";
	if (this->facing == SOUTH) return "SOUTH";
	if (this->facing == EAST) return "EAST";
	if (this->facing == WEST) return "WEST";
	return "UNDETECTED";
}
