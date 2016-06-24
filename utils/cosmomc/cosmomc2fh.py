#!/usr/bin/env python
""" A simple converter of cosmomc output files to 
filehandler format.

The column names are extracted from the .paramnames file. The
first two columns are assumed to be weight and negLogLike.

Everything is assumed to be float32 type

Usage :
    cosmomc2fh <chainname> <chainnum> <outname>

Read in <chainname>_<chainnum>.txt and write out columns to <outname>

"""

import ndfilehandler as ND
import numpy as np
import string
import sys



def parse_colnames(chainname):
    col1 = ["weight","negLogLike"]
    ff = open(chainname+".paramnames","r")
    lines = ff.read().splitlines()
    col2 = [(l1.split()[0]).strip('*'+string.whitespace) for l1 in lines]
    ff.close()
    return col1+col2


def convert_cosmo2fh(chainname, chainnum, outname):
    colnames=parse_colnames(chainname)
    ncols = len(colnames)
    fn = chainname+"_%d.txt"%chainnum
    data = np.loadtxt(fn,dtype='f4')
    if data.shape[1]!=ncols:
        print "Expected %d columns, got %d columns..."%(ncols, data.shape[1])
        raise RuntimeError, "Incorrect number of columns found"
    d = {}
    for ii,icol in enumerate(colnames):
        d[icol] = data[:,ii]
    ND.write_file(outname,d)

if __name__=="__main__":
    if len(sys.argv)!=4 :
        raise RuntimeError, "cosmomc2fh.py <chainname> <chainnum> <outname>"
    cname = sys.argv[1]
    cnum = int(sys.argv[2])
    outname = sys.argv[3]
    convert_cosmo2fh(cname, cnum, outname)
    

