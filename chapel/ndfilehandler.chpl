module ndfilehandler {

  use Assert;
  use FileSystem;


  // Helper routine -- to get column names
  proc getColumnName(type eltType, colname : string) {
    var fn : string;

    select eltType {
      when int(32) do fn = "%s.nd.i4".format(colname);
      when int(64) do fn = "%s.nd.i8".format(colname);
      when real(32) do fn = "%s.nd.f4".format(colname);
      when real(64) do fn = "%s.nd.f8".format(colname);
      otherwise halt("Unsupported type");
    }

    return fn;
  }

  // Generic return type
  proc readColumn(type eltType, param dim : int(32), colname : string) {

    var fn = getColumnName(eltType, colname);
    
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

  // Generic writer
  proc writeColumn(arr, filename : string, colname : string) {
    assert(isArrayType(arr.type));
  
    // Attempt to create the directory
    if !exists(filename) {
      mkdir(filename);
    }
    if !isDir(filename) then halt("Failed to create top-level directory");
    var fcname = "%s/%s".format(filename,colname);

    type eltType = arr.eltType;
    var rank : int(32) = arr.rank;
    var dom = arr.domain;

    // Open the file and start writing 
    var fn = getColumnName(eltType, fcname);
    var ff = openwriter(fn, kind=iokind.little, hints=IOHINT_SEQUENTIAL);
    ff.write(rank);
    for ii in 1..rank {
      var onedim : int(64) = dom.dim(ii).size;
      ff.write(onedim);
    }
    ff.write(arr);
    ff.close();
  }
        


}

