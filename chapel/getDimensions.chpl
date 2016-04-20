use ndfilehandler;

config const fn : string = "";

if fn=="" then halt("Specify a filename/colname with --col");

var ff = openreader(fn, kind=iokind.little, hints=IOHINT_SEQUENTIAL);
var idim : int(32);
ff.read(idim);
var dims : [0.. #idim] int(64);
for dim1 in dims {
  ff.read(dim1);
}
ff.close();

writeln("Dimensions : ", dims);
