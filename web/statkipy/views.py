## @file statkipy/views.py
#  @brief fasada library interface to client

"""
fasada library interface to client

export fasada results to client
"""
import fasada
#import pdb

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

def GetGameState(params):
    data = (params.dict())
    _playerID = str(data['playerID'])
    return { "GameMode" : fasada.GetGameState(_playerID) }
