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
    ls = list(srvResponse.MyShips)
    superlista = []
    for i, val in enumerate(ls):
            superlista.append([val.x, val.y])

    

    x = Data(srvResponse.ID, srvResponse.GameMode, superlista)
    pdb.set_trace()
    return {
            json.dumps(x.__dict__)
    }
