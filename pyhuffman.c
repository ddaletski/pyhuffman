//#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <numpy/arrayobject.h>
#include <huffman.h>

typedef unsigned char uchar;
typedef unsigned int uint;

static PyObject* EncodingError;
static PyObject* DecodingError;

static PyObject* encode(PyObject* self, PyObject* args) {
    uchar* in_data;
    uchar* out_data;
    uint input_size, output_size, word_size = 8;

    if(!PyArg_ParseTuple(args, "s#|i", &in_data,
                &input_size, &word_size))
        return NULL;

    out_data = (uchar*) malloc(input_size + 392);
    output_size = Huffman_Compress(in_data, out_data, input_size);
    out_data = (uchar*) realloc(out_data, output_size);

    return PyString_FromStringAndSize(out_data, output_size);
}

static PyObject* decode(PyObject* self, PyObject* args) {
    uchar* in_data;
    uchar* out_data;
    uint input_size, output_size, word_size = 8;

    if(!PyArg_ParseTuple(args, "s#|i", &in_data,
                &input_size, &word_size))
        return NULL;

    output_size = ((uint*) in_data)[0];
    out_data = (uchar*) malloc(output_size);
    if (Huffman_Uncompress(in_data, out_data) < 0) {
        PyErr_SetString(DecodingError, "DecodingError");
        return NULL;
    }

    return PyString_FromStringAndSize(out_data, output_size);
}


static PyMethodDef ModuleMethods[] = {
    {"encode", encode, METH_VARARGS,
     "encode data"},
    {"decode", decode, METH_VARARGS,
     "decode encoded data"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

/* ============= module ============== */

#ifdef __cplusplus
extern "C"
#endif
#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC inithuffman(void)
{
    PyObject *module = Py_InitModule("huffman", ModuleMethods);
    import_array();

    EncodingError = PyErr_NewException("huffman.EncodingError", NULL, NULL);
    Py_INCREF(EncodingError);
    PyModule_AddObject(module, "EncodingError", EncodingError);

    DecodingError = PyErr_NewException("huffman.DecodingError", NULL, NULL);
    Py_INCREF(DecodingError);
    PyModule_AddObject(module, "DecodingError", DecodingError);
}
