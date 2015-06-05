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
	boost::python::def( "Shoot", Shoot );
	boost::python::def( "ConnectPlayer", ConnectPlayer );
	boost::python::def( "GetGameState", GetGameState );
	boost::python::def( "Update", Update );
	
	
	
	
	class_<GameData>("GameData", "TODO Description")
				.def_readonly("ID", &GameData::ID)
				.def_readonly("GameMode", &GameData::GameMode)
				.def_readonly("MyShips", &GameData::MyShips)				
				;
				
	class_<ShotResponse>("ShotResponse", "TODO Description")
				.def_readonly("TargetHit", &ShotResponse::TargetHit)
				.def_readonly("GameMode", &ShotResponse::GameMode)
				;
				
	class_<UpdateResponse>("UpdateResponse", "TODO Description")
				.def_readonly("ID", &UpdateResponse::ID)
				.def_readonly("GameMode", &UpdateResponse::GameMode)
				.def_readonly("EnemyShots", &UpdateResponse::EnemyShots)
				;
						
}