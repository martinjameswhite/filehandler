# filehandler

Light-weight header library defining a class with only static methods to implement "files" which can store arrays of values indexed by keywords. In fact each file is a directory with the "keys" the individual files within the directory.
Currently only handles simple int, float, long and double arrays and assumes a POSIX file system.  There are two types of files, and two types of read/write routines.  The "default" set reads and writes 1D arrays.  The second set reads and write multidimensional arrays.  These arrays are actually stored and returned as 1D arrays, but the dimensions are also read/written by the routine.  Indexing into the multidimensional array is up to the user.

