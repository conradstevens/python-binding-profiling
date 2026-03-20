#define PY_ARRAY_UNIQUE_SYMBOL MY_ARRAY_API
#include "c_package.h"


PyObject* c_package_addition(PyObject* self, PyObject* args, PyObject* kwargs) {
    static char* c_package_addition_kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", c_package_addition_kwlist, &x, &y))
        return NULL;

    double result = x + y;
    return PyFloat_FromDouble(result);
}

PyObject* c_package_addition_three_times(PyObject* self, PyObject* args,  PyObject* kwargs) {
    static char* c_package_addition_three_times_kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", c_package_addition_three_times_kwlist, &x, &y)) {
        return NULL;
    }

    double result = x + y;
    result /= 5;
    result *= 7;

    return PyFloat_FromDouble(result);
}

PyObject* c_package_fibonacci(PyObject* self, PyObject* args, PyObject* kwargs) {
    static char* c_package_fibonacci_kwlist [] = {"n", NULL};
    Py_ssize_t n;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "n", c_package_fibonacci_kwlist, &n)) {
        return NULL;
    }

    PyObject *fib = PyList_New(n);

    if (n > 0) {
        PyList_SetItem(fib, 0, PyFloat_FromDouble(1.0));

        if (n > 1) {
            PyList_SetItem(fib, 1, PyFloat_FromDouble(2.0));

            if (n > 2) {
                for (Py_ssize_t i = 2; i < n; i++) {
                    const double prev_1 = PyFloat_AsDouble(PyList_GET_ITEM(fib, i - 1));
                    const double prev_2 = PyFloat_AsDouble(PyList_GET_ITEM(fib, i - 2));
                    PyList_SetItem(
                        fib,
                        i,
                        PyFloat_FromDouble(
                            (prev_1 + prev_2) / n * i
                        )
                    );
                }
            }
        }
    }

    return fib;
}

static PyObject* fibonacci_numpy(PyObject* self, PyObject* args, PyObject* kwargs) {
    static char* c_package_fibonacci_numpy_kwlist[] = {"n", NULL};
    Py_ssize_t n;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "n", c_package_fibonacci_numpy_kwlist, &n)) {
        return NULL;
    }

    npy_intp dims[1] = {n};
    PyObject* fib = PyArray_SimpleNew(1, dims, NPY_DOUBLE);

    double* data = (double*)PyArray_DATA((PyArrayObject*)fib);

    if (n > 0) {
        data[0] = 1.0;

        if (n > 1) {
            data[0] = 1.0;
            data[1] = 2.0;

            if (n > 2) {
                for (Py_ssize_t i = 2; i < n; i ++) {
                    const double prev_1 = data[i - 1];
                    const double prev_2 = data[i - 2];
                    data[i] = (prev_2 + prev_1) / n * i;
                }
            }
        }
    }
    return fib;
}

static int MyClass_init(MyClassObject* self, PyObject* args, PyObject* kwargs) {
    static char* my_class_kwlist[] = {"x", "y", "n", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddn", my_class_kwlist, &self->x, &self->y, &self->n)) {
        return -1;
    }

    self->_fib_l = PyList_New(self->n);

    npy_intp dims[1] = {self->n};
    self->_fib_arr = PyArray_SimpleNew(1, dims, NPY_DOUBLE);

    return 0;
}

static void MyClass_dealloc(MyClassObject* self) {
    Py_XDECREF(self->_fib_l);
    Py_XDECREF(self->_fib_arr);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* MyClass_class_addition(MyClassObject* self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", kwlist, &x, &y)) {
        return NULL;
    }

    return PyFloat_FromDouble(self->x + self->y + x + y);
}

static PyObject* MyClass_class_addition_three_times(MyClassObject* self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {"x", "y", NULL};
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd", kwlist, &x, &y)) {
        return NULL;
    }

    double result = x + y;
    result /= 5;
    result *= 7;

    return PyFloat_FromDouble(result);
}

static PyObject* MyClass_class_fibonacci(MyClassObject* self, PyObject* Py_UNUSED(ignored)) {

    if (self->n > 0) {
        PyList_SetItem(self->_fib_l, 0, PyFloat_FromDouble(1.0));

        if (self->n > 1) {
            PyList_SetItem(self->_fib_l, 1, PyFloat_FromDouble(2.0));

            if (self->n > 2) {
                for (Py_ssize_t i = 2; i < self->n; i++) {
                    const double prev_1 = PyFloat_AsDouble(PyList_GET_ITEM(self->_fib_l, i - 1));
                    const double prev_2 = PyFloat_AsDouble(PyList_GET_ITEM(self->_fib_l, i - 2));
                    PyList_SetItem(
                        self->_fib_l,
                        i,
                        PyFloat_FromDouble(
                            (prev_1 + prev_2) / self->n * i
                        )
                    );
                }
            }
        }
    }

    Py_INCREF(self->_fib_l);
    return self->_fib_l;
}

static PyObject* MyClass_fibonacci_numpy(MyClassObject* self, PyObject* Py_UNUSED(ignored)) {

    double* data = (double*)PyArray_DATA((PyArrayObject*)self->_fib_arr);

    if (self->n > 0) {
        data[0] = 1.0;

        if (self->n > 1) {
            data[0] = 1.0;
            data[1] = 2.0;

            if (self->n > 2) {
                for (Py_ssize_t i = 2; i < self->n; i ++) {
                    const double prev_1 = data[i - 1];
                    const double prev_2 = data[i - 2];
                    data[i] = (prev_2 + prev_1) / self->n * i;
                }
            }
        }
    }

    Py_INCREF(self->_fib_arr);
    return self->_fib_arr;
}

static PyMethodDef MyClass_methods[] = {
    {
        "class_addition",
        (PyCFunction)MyClass_class_addition,
        METH_VARARGS | METH_KEYWORDS,
        "Returns self.x + self.y + x + y"
    },
    {
    "class_addition_three_times",
    (PyCFunction)MyClass_class_addition_three_times,
    METH_VARARGS | METH_KEYWORDS,
    "Return simple addition between x and y with some extra steps"
    },
    {
    "class_fibonacci",
    (PyCFunction)MyClass_class_fibonacci,
    METH_VARARGS | METH_KEYWORDS,
    "Generate first n numbers of Fibonacci sequence with some extra steps"
    },
{
    "class_fibonacci_numpy",
    (PyCFunction)MyClass_fibonacci_numpy,
    METH_VARARGS | METH_KEYWORDS,
    "Generate first n numbers of Fibonacci sequence using numpy with some extra steps"
    },
    {
        NULL
    }
};

static PyMethodDef methods[] = {
{
        "addition",
        (PyCFunction)c_package_addition,
        METH_VARARGS | METH_KEYWORDS,
        "Add two numbers together"
    },
    {
        "addition_three_times",
        (PyCFunction)c_package_addition_three_times,
        METH_VARARGS,
        "Add two numbers together followed by some extra computations"
    },
    {
    "fibonacci",
    (PyCFunction)c_package_fibonacci,
    METH_VARARGS,
    "custom fibbonaci function for profiling"
},
{
    "fibonacci_numpy",
    (PyCFunction)fibonacci_numpy,
    METH_VARARGS | METH_KEYWORDS,
    "custom fibbonaci function using numpy for profiling"
},
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

static PyMemberDef MyClass_members[] = {
    {"x",   T_DOUBLE,    offsetof(MyClassObject, x),   0, "x value"},
    {"y",   T_DOUBLE,    offsetof(MyClassObject, y),   0, "y value"},
    {"n",   T_PYSSIZET,  offsetof(MyClassObject, n),   0, "n value"},
    {"_fib_l", T_OBJECT_EX, offsetof(MyClassObject, _fib_l),   0, "fib list"},
    {"_fib_arr", T_OBJECT_EX, offsetof(MyClassObject, _fib_arr),   0, "fib array"},
    {NULL}
};

PyTypeObject MyClass_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name      = "c_package.MyClass",
    .tp_basicsize = sizeof(MyClassObject),
    .tp_itemsize  = 0,
    .tp_flags     = Py_TPFLAGS_DEFAULT,
    .tp_new       = PyType_GenericNew,
    .tp_init      = (initproc)MyClass_init,
    .tp_dealloc   = (destructor)MyClass_dealloc,
    .tp_members   = MyClass_members,
    .tp_methods   = MyClass_methods,
};

static struct PyModuleDef c_package = {
    PyModuleDef_HEAD_INIT,
    "c_package",
    "simple python C library for profiling",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_c_package(void) {
    import_array();

    if (PyType_Ready(&MyClass_Type) < 0)
        return NULL;

    PyObject* m = PyModule_Create(&c_package);
    if (m == NULL)
        return NULL;

    Py_INCREF(&MyClass_Type);
    if (PyModule_AddObject(m, "MyClass", (PyObject*)&MyClass_Type) < 0) {
        Py_DECREF(&MyClass_Type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}