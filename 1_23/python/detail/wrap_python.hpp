//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  This file serves as a wrapper around <Python.h> which allows it to be
//  compiled with GCC 2.95.2 under Win32 and which disables the default MSVC
//  behavior so that a program may be compiled in debug mode without requiring a
//  special debugging build of the Python library.


//  To use the Python debugging library, #define BOOST_DEBUG_PYTHON on the
//  compiler command-line.

// Revision History:
// 05 Mar 01  Suppress warnings under Cygwin with Python 2.0 (Dave Abrahams)
// 04 Mar 01  Rolled in some changes from the Dragon fork (Dave Abrahams)
// 01 Mar 01  define PyObject_INIT() for Python 1.x (Dave Abrahams)


#include <patchlevel.h>

#ifdef _DEBUG
# ifndef BOOST_DEBUG_PYTHON
#  undef _DEBUG // Don't let Python force the debug library just because we're debugging.
#  define DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# endif
#endif

//
// Some things we need in order to get Python.h to work with compilers other
// than MSVC on Win32
//
#if defined(_WIN32)
# ifdef __GNUC__

typedef int pid_t;
#  define WORD_BIT 32
#  define hypot _hypot
#  include <stdio.h>
#  if !defined(PY_MAJOR_VERSION) || PY_MAJOR_VERSION < 2
#   define HAVE_CLOCK
#   define HAVE_STRFTIME
#   define HAVE_STRERROR
#  endif
#  define NT_THREADS
#  define WITH_THREAD
#  ifndef NETSCAPE_PI
#   define USE_SOCKET
#  endif

#  ifdef USE_DL_IMPORT
#   define DL_IMPORT(RTYPE) __declspec(dllimport) RTYPE
#  endif

#  ifdef USE_DL_EXPORT
#   define DL_IMPORT(RTYPE) __declspec(dllexport) RTYPE
#   define DL_EXPORT(RTYPE) __declspec(dllexport) RTYPE
#  endif

#  define HAVE_LONG_LONG 1
#  define LONG_LONG long long

# elif defined(__MWERKS__)

#  ifndef _MSC_VER
#   define PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H 1
#   define _MSC_VER 900
#  endif

# elif defined(_MSC_VER)
#  include <limits> // prevents Python.h from defining LONGLONG_MAX, LONGLONG_MIN, and ULONGLONG_MAX
# endif

#endif // _WIN32

#include <Python.h>

#ifdef PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H
# undef _MSC_VER
#endif

#ifdef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# undef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# define _DEBUG
#endif

#if !defined(PY_MAJOR_VERSION) || PY_MAJOR_VERSION < 2
# define PyObject_INIT(op, typeobj) \
	( (op)->ob_type = (typeobj), _Py_NewReference((PyObject *)(op)), (op) )
#endif
