#include	<cmath>
#include	<cstdlib>
#include	<vector>
#include	<string>
#include	<sstream>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<exception>

#include	"filehandler.h"





int main(int argc, char **argv)
{
  std::vector<int> iarr(16);
  for (int i=0; i<iarr.size(); ++i) iarr[i]=i+1;
  FileHandler::write_int("myfile","iarr",iarr);
  std::vector<float> farr(8);
  for (int i=0; i<farr.size(); ++i) farr[i]=0.5*i;
  FileHandler::write_float("myfile","farr",farr);

  std::vector<float> val=FileHandler::read_float("myfile","farr");
  for (int i=0; i<val.size(); ++i)
    std::cout<<"farr["<<i<<"]="<<val[i]<<std::endl;
  std::cout<<std::endl;

  std::vector<int> res=FileHandler::read_int("myfile","iarr");
  for (int i=0; i<res.size(); ++i)
    std::cout<<"iarr["<<i<<"]="<<res[i]<<std::endl;

  // This should crash.
  std::vector<long> oops=FileHandler::read_long("myfile","iarr");
}
