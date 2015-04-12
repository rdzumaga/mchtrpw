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

			class_<Game>("Game", "TODO: description")
				.def("addPlayer", &Game::addPlayer)
				.def("getGameState", &Game::getGameState, return_value_policy<reference_existing_object>()) 
				.def("shoot", &Game::shoot)
				.def("begin", &Game::begin)
				;

			class_<Position>("Position", "TODO Description")
				.def(init<int, int>())
				.def("get_i", &Position::get_i)
				.def("get_j", &Position::get_j)
				;

			class_<Field>("Field", "TODO Description")
				.def("attach", &Field::attach, with_custodian_and_ward<1, 2>())
				.def("notify", &Field::notify)
				;

			class_<Board>("Board", "TODO Description")
				.def("shootField", &Board::shootField)
				;


			enum_<Ship::Orientation>("Orientation")
				.value("HORIZONTAL", Ship::HORIZONTAL)
				.value("VERTICAL", Ship::VERTICAL)
				//.export_values()
				;

			class_<Ship>("Ship", "TODO Description",
				init<Player*, int, Ship::Orientation, int, int>(args("player", "lenght", "or", "i", "j"))[
					with_custodian_and_ward<1, 2>()])
						.def("update", &Ship::update)
						.def("getPositions", &Ship::getPositions)
			//
				;
			
}



