//============================================================================
// Name        : ToyRobot.cpp
// Author      : Benjamin Lvovsky
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cmdproc.hpp"

using namespace std;

int main() {
	string line;
	cout << "Toy Robot Test exercise" << endl;
	ToyRobot tr;
	CommandProcessing cp(&tr);

	while (true) {
		cout << "Enter one of command one per line:\n PLACE X,Y,F or MOVE or LEFT or RIGHT or REPORT:" << endl;
		if (!getline(cin, line)) {
			break;
		}
		try {
			cp.process(line);
		} catch (invalid_argument& e) {
			cout << "Exception at line " << line << "   :" << e.what() << endl << endl;
		}
	}
	return 0;
}
