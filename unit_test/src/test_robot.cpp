#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-function-mocker.h>
#include <gmock/gmock-matchers.h>
#include "src/cmdproc.hpp"

using namespace std;

TEST(ToyRobot, Place) {
  ToyRobot tr;
  EXPECT_FALSE(tr.IsPlaced());
  tr.Place(0, 0, NORTH);
  EXPECT_TRUE(tr.IsPlaced());
  Report report = tr.CreateReport();
  EXPECT_EQ("NORTH", report.facingStr);
  EXPECT_EQ(0, report.x);
  EXPECT_EQ(0, report.y);
}


TEST(ToyRobot, EastMovement) {
  ToyRobot tr;
  tr.Place(0, 0, EAST);
  tr.Move();
  cerr << tr.CreateReport().y;
  cerr << tr.CreateReport().y;
  cerr << tr.CreateReport().facingStr;
  cerr << tr.CreateReport().placed << endl;
  EXPECT_EQ(1, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(2, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(3, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(4, tr.CreateReport().x);
  try {
	  tr.Move();
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "EXPECT_STREQ:" << e.what() << std::endl;
	  EXPECT_STREQ("Move East to position is beyond acceptable", e.what());
  }
}


TEST(ToyRobot, WestMovement) {
  ToyRobot tr;
  tr.Place(4, 0, WEST);
  tr.Move();
  EXPECT_EQ(3, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(2, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(1, tr.CreateReport().x);
  tr.Move();
  EXPECT_EQ(0, tr.CreateReport().x);
  try {
	  tr.Move();
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "EXPECT_STREQ:" << e.what() << std::endl;
	  EXPECT_STREQ("Move West to position is beyond acceptable", e.what());
  }
}


TEST(ToyRobot, SouthMovement) {
  ToyRobot tr;
  tr.Place(0, 0, SOUTH);
  tr.Move();
  EXPECT_EQ(1, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(2, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(3, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(4, tr.CreateReport().y);
  try {
	  tr.Move();
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "EXPECT_STREQ:" << e.what() << std::endl;
	  EXPECT_STREQ("Move South to position is beyond acceptable", e.what());
  }
}


TEST(ToyRobot, NorthMovement) {
  ToyRobot tr;
  tr.Place(0, 4, NORTH);
  tr.Move();
  EXPECT_EQ(3, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(2, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(1, tr.CreateReport().y);
  tr.Move();
  EXPECT_EQ(0, tr.CreateReport().y);
  try {
	  tr.Move();
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "EXPECT_STREQ:" << e.what() << std::endl;
	  EXPECT_STREQ("Move North to position is beyond acceptable", e.what());
  }
}


TEST(ToyRobot, LeftRight) {
  ToyRobot tr;
  tr.Place(0, 4, NORTH);
  EXPECT_EQ(NORTH, tr.GetFacing());
  tr.Left();
  EXPECT_EQ(WEST, tr.GetFacing());
  tr.Left();
  EXPECT_EQ(SOUTH, tr.GetFacing());
  tr.Left();
  EXPECT_EQ(EAST, tr.GetFacing());

  tr.Place(0, 4, NORTH);
  tr.Right();
  EXPECT_EQ(EAST, tr.GetFacing());
  tr.Right();
  EXPECT_EQ(SOUTH, tr.GetFacing());
  tr.Right();
  EXPECT_EQ(WEST, tr.GetFacing());
  tr.Right();
  EXPECT_EQ(NORTH, tr.GetFacing());
}



TEST(CommandProcessing, FaceStrToEnum) {
  ToyRobot tr;
  CommandProcessing cp(&tr);
  EXPECT_EQ(WEST, cp.faceStrToEnum("WEST"));
  EXPECT_EQ(SOUTH, cp.faceStrToEnum("SOUTH"));
  EXPECT_EQ(NORTH, cp.faceStrToEnum("NORTH"));
  EXPECT_EQ(EAST, cp.faceStrToEnum("EAST"));
  try {
	  cp.faceStrToEnum("SOME UNACCEPTABLEVALUE");
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "TEST:" << e.what() << std::endl;
	  EXPECT_STREQ("Incorrect Facing string value", e.what());
  }
}


class MockToyRobot: public ToyRobot {

public:
	MockToyRobot() {}

	MOCK_METHOD(bool, IsPlaced, (), (override));
	MOCK_METHOD(void, Place,(int x, int y, Facing f), (override));
	MOCK_METHOD(void, Move,(), (override));
	MOCK_METHOD(void, Left,(), (override));
	MOCK_METHOD(void, Right,(), (override));
	MOCK_METHOD(Report, CreateReport, (), (override));
};

TEST(CommandProcessing, ProperCalls) {
  MockToyRobot* mockTr = new MockToyRobot();
  CommandProcessing cp(mockTr);
  cp.process("REPORT");
  EXPECT_CALL(*mockTr, CreateReport).Times(testing::Exactly(1));
  cp.process("LEFT");
  EXPECT_CALL(*mockTr, Left).Times(testing::Exactly(1));
  cp.process("RIGHT");
  EXPECT_CALL(*mockTr, Right).Times(testing::Exactly(1));
  cp.process("PLACE   0 ,0,EAST");
  EXPECT_CALL(*mockTr, Place).Times(testing::Exactly(1));
  try {
	  cp.process("WRONGCALL");
	  FAIL() << "Expected exception";
  } catch(invalid_argument& e) {
	  cerr << "TEST:" << e.what() << std::endl;
	  EXPECT_STREQ("Incorrect command or number of parameters", e.what());
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
