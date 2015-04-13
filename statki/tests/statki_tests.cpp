/**
   statki library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <string>

#include "../src/statki.hpp"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE( statki_tests )

void addPlayer(Game* game, std::string id){
	game->addPlayer(id);

}

BOOST_AUTO_TEST_CASE( TestShotResponse )
{
	Game *game = new Game();
	std::string idA, idB;
	idA = "A";
	idB = "B";

	addPlayer(game, idA);
	addPlayer(game, idB);
	
	std::deque<Position*> shipsA = game->playerA->getShipsPos();
	std::deque<Position*> shipsB = game->playerB->getShipsPos();
	game->begin();

	int i, j;
	i = 0;
	j = 5;
	int response = game->shoot(i, j, idA);
	BOOST_CHECK_EQUAL(response, 0);
	j = 4;
	response = game->shoot(i, j, idB);
	BOOST_CHECK_EQUAL(response, 1);

}

BOOST_AUTO_TEST_SUITE_END()

