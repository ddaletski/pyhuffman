from distutils.core import setup, Extension

huffman = Extension(
    'pyhuffman',
    include_dirs=['../libhuffman', '../containers'],
    library_dirs=['../libhuffman', '../containers', "."],
    sources = ['pyhuffman.c'],
    libraries = ["huffman", 'containers'],
    extra_compile_args = ['-D__STDC_CONSTANT_MACROS']
)

setup (
    name = 'pyhuffman',
    version = '0.1',
    description = 'huffman compression/decompression library',
    ext_modules = [huffman]
)
