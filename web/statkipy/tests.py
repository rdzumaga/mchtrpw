## @file statkipy/tests.py
#  @brief c++ calculation library Python API unit testing

import django.test
import fasada
import views

class StatkiPyLibraryTestCase(django.test.TestCase):
	"""test facade functions"""
	
	def test01connectPlayer(self):
		
		testResponse = fasada.ConnectPlayer()
		
		self.assertEqual(testResponse.GameMode, "WAITING")

