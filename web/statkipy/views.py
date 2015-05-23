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
        "GameData" : fasada.ConnectPlayer()
    }