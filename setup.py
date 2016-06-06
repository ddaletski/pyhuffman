from distutils.core import setup, Extension

huffman = Extension(
    'huffman',
    include_dirs=['../libhuffman'],
    library_dirs=['../libhuffman', "."],
    sources = ['pyhuffman.c'],
    libraries = ["huffman"],
    extra_compile_args = ['-D__STDC_CONSTANT_MACROS']
)


setup (
    name = 'huffman',
    version = '0.1',
    description = 'huffman compression/decompression library',
    ext_modules = [huffman]
)
