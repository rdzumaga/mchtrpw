## @file calcpy/views.py
#  @brief calculation library interface to client

"""
calc library interface to client

export calculation results to client
"""
import calc


def getNumber(params):
    """the calculation from C++ library"""
    return {
        "number" : calc.getNumber()
    }


def getParam(params):
    """the calculation from C++ library"""

    data = (params.dict())
    _var1 = int(data['x'])
    _var2 = int(data['y'])
    return {
        "param" : calc.getParam(_var1,_var2)
    }

