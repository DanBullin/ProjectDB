/*!
\file main.cpp
\brief Contains the entry point for the application
*/

/*! \mainpage ProjectDB - IMAT2906 Coursework
*
* This is the doxygen report from my IMAT2906 Coursework of a 2D Platformer\n
* By Dan Bullin
*/

#include "gtest/gtest.h"
#include "src/gtest.cc"
#include "src/gtest-death-test.cc"
#include "src/gtest-filepath.cc"
#include "src/gtest-matchers.cc"
#include "src/gtest-port.cc"
#include "src/gtest-printers.cc"
#include "src/gtest-test-part.cc"
#include "src/gtest-typed-test.cc"

#include <iostream>

#include "Game/GameTests.h"
#include "Level/LevelTests.h"
#include "Level/CollisionTests.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	std::cout << std::endl << "Press enter to continue" << std::endl;
	std::getchar();
	return 0;
}