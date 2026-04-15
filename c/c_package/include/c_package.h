#ifndef C_PACKAGE_H
#define C_PACKAGE_H
#include <structmember.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define PY_ARRAY_UNIQUE_SYMBOL MY_ARRAY_API
#include <numpy/arrayobject.h>

PyObject* c_package_addition(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* clib_addition_three_times(PyObject* self, PyObject* args, PyObject* kwargs);
PyObject* clib_fibonacci(PyObject* self, PyObject* args, PyObject* kwargs);

typedef struct {
    PyObject_HEAD
    double x;
    double y;
    Py_ssize_t n;

    PyObject* _fib_l;
    PyObject* _fib_arr;

} MyClassObject;

extern PyTypeObject MyClass_Type;
#define MyClass_Check(op) PyObject_TypeCheck((op), &MyClassType)

#endif