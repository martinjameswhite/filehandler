#!/usr/bin/env python
""" A special case to process the WMAP9 chains stored in tarfiles.

Usage :
    wmap2fh.py <wmap .tar.gz> <outfn>

This attempts to convert all columns, except description.txt, if it finds that one.
"""

import ndfilehandler as ND
import tarfile
import numpy as np
import sys

def convert_wmap2fh(wmapfn, outfn):
    ff = tarfile.open(wmapfn)
    d = {}
    for fn1 in ff.getnames():
        if fn1=="description.txt":
            continue
        buf = ff.extractfile(fn1)
        print "Extracting %s....."%fn1
        d[fn1]=np.loadtxt(buf,dtype='f4')[:,1]
    ff.close()
    ND.write_file(outfn, d)


if __name__=="__main__":
    if len(sys.argv)!=3 :
        raise RuntimeError, "wmap2fh.py <chainname> <outname>"
    cname = sys.argv[1]
    outname = sys.argv[2]
    convert_wmap2fh(cname, outname)

    
