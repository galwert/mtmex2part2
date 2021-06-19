cmake_minimum_required(VERSION 3.16)
project(hw2part2  VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
add_executable(hw2part2 Auxiliaries.cpp autoGameTester.cpp partC_tester.cpp gameTest.cpp Game.cpp Soldier.cpp Medic.cpp Sniper.cpp Exceptions.cpp Character.cpp)