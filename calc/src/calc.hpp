/**
 * \file calc.hpp
 * \brief the C++ calculation library interface
 */

#ifndef CALC_HPP
#define CALC_HPP

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X) X
#endif

//! Example C++ calculation. This function return a number.
CALC_DLL( int getNumber(); )

#endif //CALC_HPP
