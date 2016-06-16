//#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <numpy/arrayobject.h>
#include <huffman.h>

typedef unsigned char uchar;
typedef unsigned int uint;

static PyObject* CompressError;
static PyObject* DecompressError;

/* ============= compress/decompress ============ */

static PyObject* compress(PyObject* self, PyObject* args) {
    uchar* in_data;
    uchar* out_data;
    int input_size, output_size;

    if(!PyArg_ParseTuple(args, "s#", &in_data,
                &input_size))
        return NULL;

    if((out_data = huffman_compress(in_data, input_size,
                &output_size)) == NULL) {
        PyErr_SetString(CompressError, "Compressing error");
        return NULL;
    }

    PyObject* result = PyString_FromStringAndSize(out_data, output_size);
    free(out_data);
    return result;
}

static PyObject* decompress(PyObject* self, PyObject* args) {
    uchar* in_data;
    uchar* out_data;
    int input_size, output_size;

    if(!PyArg_ParseTuple(args, "s#", &in_data,
                &input_size))
        return NULL;

    output_size = ((int*) in_data)[0];
    if ((out_data = huffman_decompress(in_data)) == NULL) {
        PyErr_SetString(DecompressError, "decompressing error");
        return NULL;
    }

    PyObject* result = PyString_FromStringAndSize(out_data, output_size);
    free(out_data);
    return result;
}


static PyMethodDef ModuleMethods[] = {
    {"compress", compress, METH_VARARGS,
     "compress data"},
    {"decompress", decompress, METH_VARARGS,
     "decompress compressed data"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

/* ============= module ============== */

#ifdef __cplusplus
extern "C"
#endif
#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC initpyhuffman(void)
{
    PyObject *module = Py_InitModule("pyhuffman", ModuleMethods);
    import_array();

    CompressError = PyErr_NewException("pyhuffman.CompressError", NULL, NULL);
    Py_INCREF(CompressError);
    PyModule_AddObject(module, "CompressError", CompressError);

    DecompressError = PyErr_NewException("pyhuffman.DecompressError", NULL, NULL);
    Py_INCREF(DecompressError);
    PyModule_AddObject(module, "DecompressError", DecompressError);
}
