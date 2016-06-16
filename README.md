# pyhuffman - python interface to libhuffman
## module methods
`compress(data)` - compress data
- **data**: *bytes* - data to compress
- **returns**: *bytes* - compressed data

`decompress(data)` - decompress data
- **data**: *bytes* - data to decompress
- **returns**: *bytes* - decompressed data

## exceptions
`CompressError` - is thrown when encoding was unsuccessful
`DecompressError` - is thrown when decoding was unsuccessful
