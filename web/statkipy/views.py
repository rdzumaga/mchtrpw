## @file statkipy/views.py
#  @brief fasada library interface to client

"""
fasada library interface to client

export fasada results to client
"""
import fasada

## Exports ConnectPlayer from fasada library to client
def ConnectPlayer(params):
    
    srvResponse = fasada.ConnectPlayer()


    return {
            "ID" : srvResponse.ID,
            "GameMode" : srvResponse.GameMode,
            "MyShips" : srvResponse.MyShips            
    }

## Exports GetGameState from fasada library to client
def GetGameState(params):
    data = (params.dict())
    _playerID = str(data['playerID'])
    return { "GameMode" : fasada.GetGameState(_playerID) }

## Exports Shoot from fasada library to client
def Shoot(params):
    data = (params.dict())
    _playerID = str(data['playerID'])
    _pos_i = int(data['pos_i'])
    _pos_j = int(data['pos_j'])


    srvResponse = fasada.Shoot(_playerID, _pos_i, _pos_j)
    
    return {
            "GameMode" : srvResponse.GameMode,
            "TargetHit" : srvResponse.TargetHit }


## Exports Update from fasada library to client
def Update(params):
    data = (params.dict())
    _playerID = str(data['playerID'])



    srvResponse = fasada.Update(_playerID)
    
    return {
            "GameMode" : srvResponse.GameMode,
            "ID" : srvResponse.ID,
            "EnemyShots" : srvResponse.EnemyShots }

