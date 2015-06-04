/**
   statki library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <string>
#include<iostream>

#include "../src/game.h"


using namespace boost;
using boost::unit_test::test_suite;



BOOST_AUTO_TEST_SUITE( game_tests )


BOOST_AUTO_TEST_CASE (TestGetInfo) {
	Game& game = Game::getInstance();
	game.reset();
	
	//check if info is correct when there are no players added
	Info info=game.getInfo("whatever");
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 0);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, true);	
	BOOST_CHECK_EQUAL(info.gameMode, IDLE);	
	
	
	//check if info is correct when only one player is connected
	std::string id1 = "1";
	game.addPlayer(id1);
	info=game.getInfo(id1);
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 0);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, false);	
	BOOST_CHECK_EQUAL(info.gameMode, WAITING);	
	
	//check if info is correct when both players are connected
	std::string id2 = "2";
	game.addPlayer(id2);
	
	//for player 1
	info=game.getInfo(id1);
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 0);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, false);	
	BOOST_CHECK_EQUAL(info.gameMode, ONGOING);	
	
	//for player 2
	info=game.getInfo(id2);
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 0);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, true);	
	BOOST_CHECK_EQUAL(info.gameMode, ONGOING);	
	
	//check if info ok after an attack
	game.shoot(5,6);
	
	//for player 1
	info=game.getInfo(id1);
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 0);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, true);	
	BOOST_CHECK_EQUAL(info.gameMode, ONGOING);
	
	
	//for player 2
	info=game.getInfo(id2);
	std::cout << info.receivedAttacks.size()<< std::endl;
	std::cout << info.playerIsUnderAttack << std::endl;
	std::cout << info.gameMode << std::endl;
	std::cout<<"----------------------\n";
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 1);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, false);	
	BOOST_CHECK_EQUAL(info.gameMode, ONGOING);
	
	//?
	info=game.getInfo(id2);
	std::cout << info.receivedAttacks.size()<< std::endl;
	std::cout << info.playerIsUnderAttack << std::endl;
	std::cout << info.gameMode << std::endl;
	std::cout<<"----------------------\n";
	BOOST_CHECK_EQUAL(info.receivedAttacks.size(), 1);	
	BOOST_CHECK_EQUAL(info.playerIsUnderAttack, false);	
	BOOST_CHECK_EQUAL(info.gameMode, ONGOING);
	
	int buff2;
	std::cin>>buff2;
}

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
	int buff;
	std::cin>>buff;
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

*/

