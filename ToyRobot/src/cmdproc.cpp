#include <stdio.h>
#include <iostream>
#include "cmdproc.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

Facing CommandProcessing::faceStrToEnum(string sFacing) {
	if (0 == sFacing.compare("NORTH")) {
		return NORTH;
	} else if (0 == sFacing.compare("SOUTH")) {
		return SOUTH;
	} else if (0 == sFacing.compare("WEST")) {
		return WEST;
	} else if (0 == sFacing.compare("EAST")) {
		return EAST;
	} else {
		throw invalid_argument("Incorrect Facing string value");
	}
}



void CommandProcessing::process(string line) {
	std::vector<std::string> tokens;
	boost::split(tokens, line, boost::is_any_of(" ,\t\n\r"));

	// exclude empty tokens
	auto it = tokens.begin();
	while (it != tokens.end()) {
		// remove odd numbers
		if (it->size() == 0) {
			it = tokens.erase(it);
		}
		// Notice that the iterator is incremented only on the else part (why?)
		else {
			++it;
		}
	}

	if(1 == tokens.size() && 0 == line.compare("MOVE")) {
		tr->Move();
	} else if(4 == tokens.size() && tokens[0].compare("PLACE") == 0) {
		tr->Place(stoi(tokens[1]), stoi(tokens[2]), faceStrToEnum(tokens[3]));
	} else if(1 == tokens.size() && tokens[0].compare("LEFT") == 0) {
		tr->Left();
	} else if(1 == tokens.size() && tokens[0].compare("RIGHT") == 0) {
		tr->Right();
	} else if(1 == tokens.size() && tokens[0].compare("REPORT") == 0) {
		Report report = tr->CreateReport();
		cout << "Output: " << report.x << "," << report.y <<"," << report.facingStr << endl;
	} else {
		throw invalid_argument("Incorrect command or number of parameters");
	}
}
