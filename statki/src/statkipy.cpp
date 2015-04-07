/**
 * \file statki.cpp
 * \brief the Python interface for C++ statki library
 */

#include <boost/python.hpp>

#include "statki.hpp"

using namespace boost::python;

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE( statki )
{
	//! exports getNumber to Python
    boost::python::def( "getNumber", getNumber );
}
