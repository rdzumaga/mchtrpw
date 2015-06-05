## @file statkipy/tests.py
#  @brief c++ calculation library Python API unit testing

import django.test
import fasada
import views

class StatkiPyLibraryTestCase(django.test.TestCase):
	"""test facade functions"""

	id = ""
	
	def test01connectPlayer(self):
		"""test if game state is correct after adding 1st player"""
		
		testResponse = fasada.ConnectPlayer()
		
		self.assertEqual(testResponse.GameMode, "WAITING")
		self.assertNotEqual(testResponse.ID, None)
		self.assertNotEqual(testResponse.MyShips, None)


	def test02connectSecondPlayer(self):
		"""test if game state is correct after adding 2nd player"""

		
		testResponse = fasada.ConnectPlayer()
		id = testResponse.ID
		self.assertEqual(testResponse.GameMode, "ONGOING")
		self.assertNotEqual(testResponse.ID, None)
		self.assertNotEqual(testResponse.MyShips, None)

	def test03getGameState(self):
		"""test if  GetGameState function return not empty data"""
		
		self.assertNotEqual(fasada.GetGameState("test"), "IDLE")

	def test04shoot(self):
		"""test if Shoot function returns not empty"""

		
		shotTestResponse = fasada.Shoot(self.id, 1, 1)
		self.assertNotEqual(shotTestResponse.TargetHit, None)
		self.assertNotEqual(shotTestResponse.GameMode, None)

	def test05update(self):
		"""test if Update function returns not empty data"""
		updateTestResponse = fasada.Update(self.id)
		self.assertNotEqual(updateTestResponse.GameMode, None)
		self.assertNotEqual(updateTestResponse.ID, None)
		self.assertNotEqual(updateTestResponse.EnemyShots, None)	


	
