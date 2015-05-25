/**
* \file statki.cpp
* \brief the Python interface for C++ statki library
*/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "fasada.h"

using namespace boost::python;

/**
* Python wrapper using Boost.Python
*/
BOOST_PYTHON_MODULE( fasada )
{
	//! exports getNumber to Python
	boost::python::def( "ConnectPlayer", ConnectPlayer );
	boost::python::def( "GetGameState", GetGameState );
	boost::python::def( "Shoot", Shoot );
	
	// class_<MapPosition>("MapPosition", "TODO Description")
				// .def_readonly("x", &MapPosition::x)
				// .def_readonly("y", &MapPosition::y)
				// ;	
				
	 // class_<ShotPosition>("ShotPosition", "TODO Description")
				// .def_readonly("x", &ShotPosition::x)
				// .def_readonly("y", &ShotPosition::y)
				// .def_readonly("TargetHit", &ShotPosition::TargetHit)
				// ;
				
	// class_<MapPos>("MapPos")
				// .def(vector_indexing_suite<MapPos>() );
	
	class_<GameData>("GameData", "TODO Description")
				.def_readonly("ID", &GameData::ID)
				.def_readonly("GameMode", &GameData::GameMode)
				.def_readonly("MyShips", &GameData::MyShips)
				.def_readonly("EnemyShots", &GameData::EnemyShots)
				.def_readonly("MyShots", &GameData::MyShots)
				;
				
	class_<ShotResponse>("ShotResponse", "TODO Description")
				.def_readonly("TargetHit", &ShotResponse::TargetHit)
				.def_readonly("GameMode", &ShotResponse::GameMode)
				;
						
}