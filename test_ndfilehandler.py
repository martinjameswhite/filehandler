from __future__ import print_function
from ndfilehandler import read_file, write_file;
import numpy as np

## Write out a file
data = {}
data['farr'] = np.arange(10,dtype='f8')
data['iarr'] = np.arange(27,dtype='i4').reshape((3,3,3))
write_file("ndtest",data)

## Read in the file
data2 = read_file("ndtest",None)
print(data['farr']==data2['farr'])
print(data['iarr']==data2['iarr'])
print(data2['iarr'].shape)
