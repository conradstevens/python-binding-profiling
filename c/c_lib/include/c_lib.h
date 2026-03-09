#ifndef CLIB_H
#define CLIB_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define PY_ARRAY_UNIQUE_SYMBOL MY_ARRAY_API
#include <numpy/arrayobject.h>

#include "my_class.h"

PyObject* clib_addition(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* clib_addition_three_times(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* clib_fibonacci(PyObject* self, PyObject* args, PyObject* kwargs);

#endif