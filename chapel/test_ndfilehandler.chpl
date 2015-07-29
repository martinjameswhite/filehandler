use ndfilehandler;

// Read in iarr 
var iarr = readColumn(int(32),3,"ndtest/iarr");
writeln(iarr);
var farr = readColumn(real(64),1,"ndtest/farr");
writeln(farr);
