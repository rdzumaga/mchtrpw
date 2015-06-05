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


    return {
            "ID" : srvResponse.ID,
            "GameMode" : srvResponse.GameMode,
            "MyShips" : srvResponse.MyShips            
    }

def GetGameState(params):
    data = (params.dict())
    _playerID = str(data['playerID'])
    return { "GameMode" : fasada.GetGameState(_playerID) }

def Shoot(params):
    data = (params.dict())
    _playerID = str(data['playerID'])
    _pos_i = int(data['pos_i'])
    _pos_j = int(data['pos_j'])


    srvResponse = fasada.Shoot(_playerID, _pos_i, _pos_j)
    #pdb.set_trace()
    return {
            "GameMode" : srvResponse.GameMode,
            "TargetHit" : srvResponse.TargetHit }


def Update(params):
    data = (params.dict())
    _playerID = str(data['playerID'])



    srvResponse = fasada.Update(_playerID)
    #pdb.set_trace()
    return {
            "GameMode" : srvResponse.GameMode,
            "ID" : srvResponse.ID,
            "EnemyShots" : srvResponse.EnemyShots }

