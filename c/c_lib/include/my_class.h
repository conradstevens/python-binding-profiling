#ifndef C_LIB_MY_CLASS_H
#define C_LIB_MY_CLASS_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
    double x;
    double y;

    Py_ssize_t n;
    PyObject* fib;
} MyClassObject;

extern PyTypeObject MyClass_Type;
#define MyClass_Check(op) PyObject_TypeCheck((op), &MyClassType)

#endif //C_LIB_MY_CLASS_H