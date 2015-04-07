/**
 * \file statki.hpp
 * \brief the C++ statki library interface
 */

#ifndef STATKI_HPP
#define STATKI_HPP

#ifdef STATKI_EXPORTS
/** Workaround for Windows DLL library exports */
#define STATKI_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define STATKI_DLL(X) X
#endif

//! Example C++ calculation. This function return a number.
STATKI_DLL( int getNumber(); )


class Y;
class X
{
public:
	X(int x, Y* y) : m_y(y) {}
	X(double);
private:
	Y* m_y;
};


#endif //STATKI_HPP
