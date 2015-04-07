/**
 * \file statki.hpp
 * \brief the C++ statki library interface
 */

#ifndef STATKI_HPP
#define STATKI_HPP

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

//! Example C++ calculation. This function return a number.
CALC_DLL( int getNumber(); )

#endif //STATKI_HPP
