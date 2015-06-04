/**
   statki library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <string>

#include "../src/game.h"


using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE( game_tests )


BOOST_AUTO_TEST_CASE (TestAddPlayer) {

	//test if first player connects and gets the ships'positions
	const int expectedShipsPositionsNum = 5 + 4 + 4 + 3 + 3 + 3 + 2 + 2 + 2 + 2;
	std::string id = "1";
	std::deque<Position*> shipsPos;

	Game& game = Game::getInstance();
	game.reset();
	shipsPos = game.addPlayer(id);
	
	BOOST_CHECK_EQUAL(shipsPos.size(), expectedShipsPositionsNum);
	if (shipsPos.size()==0)
		BOOST_ERROR("Error! Player 1 wasn't added to the game even though he should have been\n");


	//test if second player connects and gets the ships'positions
	id = "2";
	shipsPos = game.addPlayer(id);	
	BOOST_CHECK_EQUAL(shipsPos.size(), expectedShipsPositionsNum);
	if (shipsPos.size() == 0)
		BOOST_ERROR("Error! Player 2 wasn't added to the game even though he should have been\n");

	//test if second player connects and gets the ships' positions
	id = "3";
	shipsPos = game.addPlayer(id);
	BOOST_CHECK_EQUAL(shipsPos.size(), 0);	
}
BOOST_AUTO_TEST_SUITE_END()


/*
BOOST_AUTO_TEST_CASE( TestShotResponse )
{
	Game& game = Game::getInstance();
	game.reset();
	std::string idA, idB;
	idA = "A";
	idB = "B";

	addPlayer(game, idA);
	addPlayer(game, idB);
	
	std::deque<Position*> shipsA = game.playerA->getShipsPos();
	std::deque<Position*> shipsB = game.playerB->getShipsPos();

	int i, j;
	i = 0;
	j = 5;
	int response = game.shoot(i, j, idA);
	BOOST_CHECK_EQUAL(response, 0);
	j = 4;
	response = game.shoot(i, j, idB);
	BOOST_CHECK_EQUAL(response, 1);

}

BOOST_AUTO_TEST_SUITE_END()*/

