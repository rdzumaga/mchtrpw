/**
 * \file calcpy.cpp
 * \brief the Python interface for C++ calculation library
 */

#include <boost/python.hpp>

#include "calc.hpp"

using namespace boost::python;

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( calc )
{
	//! exports getNumber to Python
    boost::python::def( "getNumber", getNumber );
	
	boost::python::def( "getParam", getParam );
}
