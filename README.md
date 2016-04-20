# filehandler

A light-weight, header library defining a class, with only static methods,
to implement "files" which can store arrays of values indexed by keywords.
In fact each file is a directory with the "keys" the individual files
within the directory.  This leverages the significant performance of modern
hierarchical storage systems while providing some of the functionality seen
in formats such as FITS or HDF5.  Keys can be easily added to existing files,
subsets of the data can be easily read or written.  Since the data format is
"flat files" under the hood, it is almost trivial to write a wrapper for
any language.  The directories can be packaged into e.g. tar files for
transport or storage using standard utilities.

Currently only handles simple int, float, long and double arrays and
assumes a POSIX file system.
There are two types of files, and two types of read/write routines.
The "default" set reads and writes 1D arrays.
The second set reads and write multidimensional arrays (the .nd versions).
These arrays are actually stored and returned as 1D arrays, but the
dimensions are also read/written by the routine.  Indexing into the
multidimensional array is up to the user.


ND Filehandler Format
=====================

* Each "file" is actually stored as a directory, with individual "columns"
stored as separate files inside the directory.
* "Column"-files are named <colname>.nd.<type> where <colname> is the name of 
the column, and <type> is the type of data stored inside. Types supported are listed below.
* The file format is a simple binary format (little endian)
  * Ndim : number of dimensions : 4-byte integer
  * [Dims] : list of dimensions : Ndim 8-byte integers
  * [Data] : data, stored as a contiguous block. The user is assumed to know the row-ordering, 
      usually C.

An example :

```
boss-galaxies/
   ra.nd.f8
   dec.nd.f8
   z.nd.f4
   id.nd.i4
```

The columns above are ra, dec,z, and id.

Implementations :
* The C++ code takes in an optional list of dimensions and then reads/writes in the nd filehandler format
* Python : ndfilehandler.py is a Python module to read and write nd files. There is an example in "test_ndfilehandler.py"
* Chapel : The Chapel implementation only handles the ND format.


Supported Types 
===============

1. i4 : 4 byte integers
2. i8 : 8 byte integers
3. f4 : 4 byte floats (C float)
4. f8 : 8 byte floats (C double)
