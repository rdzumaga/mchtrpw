## @file statkipy/views.py
#  @brief statki library interface to client

"""
statki library interface to client

export statki results to client
"""
import statki

def getNumber(params):
    """statki from C++ library"""
    return {
        "number" : statki.getNumber()
    }