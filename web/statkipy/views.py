## @file statkipy/views.py
#  @brief fasada library interface to client

"""
fasada library interface to client

export fasada results to client
"""
import fasada
import pdb

def ConnectPlayer(params):
    """fasada from C++ library"""
    pdb.set_trace()
    return {		
        "GameData" : fasada.ConnectPlayer()
    }
