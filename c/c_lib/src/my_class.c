#include "my_class.h"
#include <structmember.h>

static int MyClass_init(MyClassObject* self, PyObject* args, PyObject* kwargs) {
    static char* my_class_kwlist[] = {"x", "y", "n", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddn", my_class_kwlist, &self->x, &self->y, &self->n)) {
        return -1;
    }

    return 0;
}

static void MyClass_dealloc(MyClassObject* self) {
    Py_XDECREF(self->fib);
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
    PyObject *fib = PyList_New(self->n);

    if (self->n == 1) {
        PyList_SetItem(fib, 0, PyFloat_FromDouble(0));
    }
    else if (self->n > 1) {
        PyList_SetItem(fib, 0, PyFloat_FromDouble(1.0));
        PyList_SetItem(fib, 1, PyFloat_FromDouble(2.0));

        if (self->n > 2) {
            for (Py_ssize_t i = 2; i < self->n; i++) {
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
        NULL
    }
};

static PyMemberDef MyClass_members[] = {
    {"x",   T_DOUBLE,    offsetof(MyClassObject, x),   0, "x value"},
    {"y",   T_DOUBLE,    offsetof(MyClassObject, y),   0, "y value"},
    {"n",   T_PYSSIZET,  offsetof(MyClassObject, n),   0, "n value"},
    {NULL}
};

PyTypeObject MyClass_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name      = "c_lib.MyClass",
    .tp_basicsize = sizeof(MyClassObject),
    .tp_itemsize  = 0,
    .tp_flags     = Py_TPFLAGS_DEFAULT,
    .tp_new       = PyType_GenericNew,
    .tp_init      = (initproc)MyClass_init,
    .tp_dealloc   = (destructor)MyClass_dealloc,
    .tp_members   = MyClass_members,
    .tp_methods   = MyClass_methods,
};