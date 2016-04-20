use ndfilehandler;

// Write a test file
{
  var iarr : [0.. #5]int(32) = 1;
  writeColumn(iarr, "ndtest","iarr");
  var darr : [0.. #5, 0.. #3]real(64) = 3.14;
  writeColumn(darr, "ndtest", "darr");
  var farr : [0..2, 0..1, 0..3]real(32) = 2.7 : real(32);
  writeColumn(farr, "ndtest", "farr");
}
  

// Read test
{
  var iarr = readColumn(int(32),1,"ndtest/iarr");
  writeln(iarr);
  writeln(iarr.domain);
  var darr = readColumn(real(64),2,"ndtest/darr");
  writeln(darr);
  writeln(darr.domain);
  var farr = readColumn(real(32),3,"ndtest/farr");
  writeln(farr);
  writeln(farr.domain);
}
