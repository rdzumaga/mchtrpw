## @file statkipy/views.py
#  @brief fasada library interface to client

"""
fasada library interface to client

export fasada results to client
"""
import fasada

def ConnectPlayer(params):
    """fasada from C++ library"""    
    return {		
        "ID" : fasada.ConnectPlayer().ID,
		"GameState" : fasada.ConnectPlayer().GameMode,
		"MyShips" : fasada.ConnectPlayer().MyShips
		
    }
