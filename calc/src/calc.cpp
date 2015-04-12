/**
 * \file calc.cpp
 * \brief the C++ file with example calculation library
 */
#include "calc.hpp"

//implementation
CALC_DLL( int getNumber() ) {
	return 1234;
}
CALC_DLL( int getParam(int x, int y) ) {
	return x+999-y;
}