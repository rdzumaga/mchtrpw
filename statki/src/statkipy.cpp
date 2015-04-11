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
BOOST_PYTHON_MODULE(statki)
{
	//! exports getNumber to Python
    boost::python::def( "getNumber", getNumber );

	boost::python::class_<Y>("Y", init<int>());

	boost::python::class_<X>("X", "This is X's docstring.",
		init<int, Y*>(args("x", "y"), "X.__init__'s docstring")[
			with_custodian_and_ward<1, 3>()]
				)
				//.def(init<double>());
				;
}



