## @file statkipy/views.py
#  @brief fasada library interface to client

"""
fasada library interface to client

export fasada results to client
"""
import fasada
import json
import pdb

class Data(object):
	id = ""
	gameState = ""
	myShips = []
	
	def __init__(self, id, state, list):
		self.id = id
		self.gameState = state
		self.myShips = list


def ConnectPlayer(params):
    """fasada from C++ library"""       
    srvResponse = fasada.ConnectPlayer()
    
    #pdb.set_trace()
    return {
            "ID" : srvResponse.ID,
            "GameMode" : srvResponse.GameMode,
            "MyShips" : srvResponse.MyShips,
            "MyShots" : srvResponse.MyShots,
            "EnemyShots" : srvResponse.EnemyShots
    }
