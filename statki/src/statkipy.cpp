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
    def( "getNumber", getNumber );

	//boost::python::class_<Y>("Y", init<int>());

	class_<X>("X", "This is X's docstring.",
		init<int, Y*>(args("x", "y"), "X.__init__'s docstring")[
			with_custodian_and_ward<1, 3>()]
				)
				//.def(init<double>());
				;

			enum_<Mode>("Mode")
				.value("IDLE", IDLE)
				.value("WAITING", WAITING)
				.value("ONGOING", ONGOING)
				.value("FINISHED", FINISHED)
				;

	class_<Attack>("Attack", "TODO Description", 
		init<Position*, bool, std::string>(args("pos", "successful", "attackerId"), "TODO:description")[
			with_custodian_and_ward<1, 2>()]
				)
				;

			class_<GameState>("GameState", "TODO: description")
				.def_readwrite("mode", &GameState::mode)
				.def_readwrite("attackingPlauyerId", &GameState::attackingPlayerId)
				.def_readwrite("attackedPlayerId", &GameState::attackedPlayerId)
				.def_readwrite("attacks", &GameState::attacks)
				;

			//class_<Game>("Game", "TODO: description")
			//	.def("addPlayer", &Game::addPlayer)


}



