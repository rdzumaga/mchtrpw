/**
* \file statki.cpp
* \brief the Python interface for C++ statki library
*/

#include <boost/python.hpp>

#include "fasada.h"

using namespace boost::python;

/**
* Python wrapper using Boost.Python
*/
BOOST_PYTHON_MODULE(fasada)
{
	//! exports getNumber to Python
	boost::python::def( "ConnectPlayer", ConnectPlayer );

}