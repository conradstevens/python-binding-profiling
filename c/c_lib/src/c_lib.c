#define PY_SSIZE_T_CLEAN
#include "c_lib.h"


PyObject* clib_addition(PyObject* self, PyObject* args, PyObject* kwargs) {
    static char* clib_addition_kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", clib_addition_kwlist, &x, &y))
        return NULL;

    double result = x + y;
    return PyFloat_FromDouble(result);
}

PyObject* clib_addition_three_times(PyObject* self, PyObject* args,  PyObject* kwargs) {
    static char* clib_addition_three_times_kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", clib_addition_three_times_kwlist, &x, &y)) {
        return NULL;
    }

    double result = x + y;
    result /= 5;
    result *= 7;

    return PyFloat_FromDouble(result);
}

PyObject* clib_fibonacci(PyObject* self, PyObject* args, PyObject* kwargs) {
    // TODO compare speed against using a c list and converting at the end.
    static char* clib_fibonacci_kwlist [] = {"n", NULL};
    size_t n;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "k", clib_fibonacci_kwlist, &n)) {
        return NULL;
    }

    PyObject *fib = PyList_New(n);

    if (n == 1) {
        PyList_SetItem(fib, 0, PyFloat_FromDouble(0));
    }
    else if (n > 1) {
        PyList_SetItem(fib, 0, PyFloat_FromDouble(1.0));
        PyList_SetItem(fib, 1, PyFloat_FromDouble(2.0));

        if (n > 2) {
            for (size_t i = 2; i < n; i++) {
                const double prev_1 = PyFloat_AsDouble(PyList_GET_ITEM(fib, i - 1));
                const double prev_2 = PyFloat_AsDouble(PyList_GET_ITEM(fib, i - 2));
                PyList_SetItem(
                    fib,
                    i,
                    PyFloat_FromDouble(
                        (prev_1 + prev_2) / (prev_2 + 1)
                    )
                );
            }
        }
    }

    return fib;
}


static PyMethodDef methods[] = {
{
        "addition",
        (PyCFunction)clib_addition,
        METH_VARARGS | METH_KEYWORDS,
        "Add two numbers together"
    },
    {
        "addition_three_times",
        (PyCFunction)clib_addition_three_times,
        METH_VARARGS,
        "Add two numbers together followed by some extra computations"
    },
    {
    "fibonacci",
    (PyCFunction)clib_fibonacci,
    METH_VARARGS,
    "custom fibbonaci function for profiling"
},
    {
        NULL,
        NULL,
        0,
        NULL
    }
};


static struct PyModuleDef c_lib = {
    PyModuleDef_HEAD_INIT,
    "c_lib",
    "simple python C library for profiling",
    -1,
    methods
};


PyMODINIT_FUNC PyInit_c_lib() {
    return PyModule_Create(&c_lib);
}