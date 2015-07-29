module ndfilehandler {

  use Assert;
 
  // Generic return type
  proc readColumn(type eltType, param dim : int(32), colname : string) {
    
    var fn : string;

    select eltType {
      when int(32) do fn = "%s.nd.i4".format(colname);
      when int(64) do fn = "%s.nd.i8".format(colname);
      when real(32) do fn = "%s.nd.f4".format(colname);
      when real(64) do fn = "%s.nd.f8".format(colname);
    }
    
    // Open the file
    var ff = openreader(fn, kind=iokind.little, hints=IOHINT_SEQUENTIAL);
    var idim : int(32);
    ff.read(idim);
    assert(idim==dim,"Expected dimension=%i, got %i\n".format(dim,idim));

    // Output array
    var dims : dim*range;
    var onedim : int(64);
    for param ii in 1..dim do {
      ff.read(onedim);
      dims(ii) = 0.. #onedim;
    }
    var D = {(...dims)};
    var arr : [D] eltType;
    ff.read(arr);
    ff.close();


    // Return 
    return arr;
  }
        


}

