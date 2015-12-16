# filehandler

A light-weight, header library defining a class, with only static methods,
to implement "files" which can store arrays of values indexed by keywords.
In fact each file is a directory with the "keys" the individual files
within the directory.  This leverages the significant performance of modern
hierarchical storage systems while providing some of the functionality seen
in formats such as FITS or HDF5.  Keys can be easily added to existing files,
subsets of the data can be easily read or written.  Since the data format is
"flat files" under the hood, it is almost trivial to write a wrapper for
any language.

Currently only handles simple int, float, long and double arrays and
assumes a POSIX file system.
There are two types of files, and two types of read/write routines.
The "default" set reads and writes 1D arrays.
The second set reads and write multidimensional arrays (the .nd versions).
These arrays are actually stored and returned as 1D arrays, but the
dimensions are also read/written by the routine.  Indexing into the
multidimensional array is up to the user.

