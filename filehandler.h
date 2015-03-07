#ifndef	_FILEHANDLER_H_
#define _FILEHANDLER_H_

#include	<cmath>
#include	<cstdlib>
#include	<vector>
#include	<string>
#include	<sstream>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<exception>
#include	<sys/stat.h>	// For the POSIX "stat" and "mkdir" functions.


inline	void	myexit(const int iflag) {
  exit(iflag);
}
inline void	myexception(std::exception& e) {
  std::cerr<<"Exception: "<<e.what()<<std::endl;
  myexit(1);
}



class FileHandler {
// Code to implement a simple file structure which can store "keywords"
// which are arrays of values.  The code makes each "file" a directory
// on the file system with files for each "keyword" stored in the
// appropriate directory.  Files have a type appended to their name as
// one level of error checking upon re-read.
//
// Author:	Martin White	(UCB)
private:
  static void make_dir(const char fname[]) {
    // Checks to see whether the file (actually a directory) exists already,
    // if not it makes it, else returns.
    struct stat statbuf;
    int ret = stat(fname,&statbuf);
    if (ret==-1) { // File doesn't exist, we need to make it.
      // Just choose some semi-random permissions here...
      ret = mkdir(fname,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      if (ret==-1) {
        std::cerr<<"Unable to make file "<<fname<<std::endl;
        myexit(1);
      }
    }
  }
public:
  static std::vector<int> read_int(const char fname[], const char field[]) {
    std::stringstream ss;
    ss << fname << "/" << field << ".i4";
    std::ifstream ifs(ss.str().c_str(),std::ios::binary);
    if (!ifs) {
      std::cerr<<"Unable to find int field "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize;
    ifs.read((char *)&nsize,sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read length for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    std::vector<int> ret;
    try {ret.resize(nsize);} catch(std::exception& e) {myexception(e);}
    ifs.read((char *)&ret[0],nsize*sizeof(int));
    if (ifs.fail()) {
      std::cerr<<"Unable to read data for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ifs.close();
    return(ret);
  }
  static std::vector<float> read_float(const char fname[], const char field[]){
    std::stringstream ss;
    ss << fname << "/" << field << ".f4";
    std::ifstream ifs(ss.str().c_str(),std::ios::binary);
    if (!ifs) {
      std::cerr<<"Unable to find float field "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize;
    ifs.read((char *)&nsize,sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read length for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    std::vector<float> ret;
    try {ret.resize(nsize);} catch(std::exception& e) {myexception(e);}
    ifs.read((char *)&ret[0],nsize*sizeof(float));
    if (ifs.fail()) {
      std::cerr<<"Unable to read data for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ifs.close();
    return(ret);
  }
  static std::vector<long> read_long(const char fname[], const char field[]){
    std::stringstream ss;
    ss << fname << "/" << field << ".i8";
    std::ifstream ifs(ss.str().c_str(),std::ios::binary);
    if (!ifs) {
      std::cerr<<"Unable to find long field "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize;
    ifs.read((char *)&nsize,sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read length for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    std::vector<long> ret;
    try {ret.resize(nsize);} catch(std::exception& e) {myexception(e);}
    ifs.read((char *)&ret[0],nsize*sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read data for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ifs.close();
    return(ret);
  }
  static std::vector<double> read_dble(const char fname[], const char field[]){
    std::stringstream ss;
    ss << fname << "/" << field << ".i8";
    std::ifstream ifs(ss.str().c_str(),std::ios::binary);
    if (!ifs) {
      std::cerr<<"Unable to find dble field "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize;
    ifs.read((char *)&nsize,sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read length for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    std::vector<double> ret;
    try {ret.resize(nsize);} catch(std::exception& e) {myexception(e);}
    ifs.read((char *)&ret[0],nsize*sizeof(long));
    if (ifs.fail()) {
      std::cerr<<"Unable to read data for "<<field<<" in "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ifs.close();
    return(ret);
  }
  static void write_int(const char fname[], const char field[],
                        std::vector<int> val) {
    make_dir(fname);
    std::stringstream ss;
    ss << fname << "/" << field << ".i4";
    std::ofstream ofs(ss.str().c_str(),std::ios::binary|std::ios::trunc);
    if (!ofs) {
      std::cerr<<ss.str().c_str()<<std::endl;
      std::cerr<<"Unable to write field "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize=val.size();
    ofs.write((char *)&nsize,sizeof(long));
    if (ofs.fail()) {
      std::cerr<<"Unable to write length for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.write((char *)&val[0],nsize*sizeof(int));
    if (ofs.fail()) {
      std::cerr<<"Unable to write data for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.close();
  }
  static void write_float(const char fname[], const char field[],
                          std::vector<float> val) {
    make_dir(fname);
    std::stringstream ss;
    ss << fname << "/" << field << ".f4";
    std::ofstream ofs(ss.str().c_str(),std::ios::binary|std::ios::trunc);
    if (!ofs) {
      std::cerr<<"Unable to write field "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize=val.size();
    ofs.write((char *)&nsize,sizeof(long));
    if (ofs.fail()) {
      std::cerr<<"Unable to write length for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.write((char *)&val[0],nsize*sizeof(float));
    if (ofs.fail()) {
      std::cerr<<"Unable to write data for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.close();
  }
  static void write_long(const char fname[], const char field[],
                         std::vector<long> val) {
    make_dir(fname);
    std::stringstream ss;
    ss << fname << "/" << field << ".i8";
    std::ofstream ofs(ss.str().c_str(),std::ios::binary|std::ios::trunc);
    if (!ofs) {
      std::cerr<<"Unable to write field "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize=val.size();
    ofs.write((char *)&nsize,sizeof(long));
    if (ofs.fail()) {
      std::cerr<<"Unable to write length for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.write((char *)&val[0],nsize*sizeof(long));
    if (ofs.fail()) {
      std::cerr<<"Unable to write data for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.close();
  }
  static void write_dble(const char fname[], const char field[],
                         std::vector<double> val) {
    make_dir(fname);
    std::stringstream ss;
    ss << fname << "/" << field << ".f8";
    std::ofstream ofs(ss.str().c_str(),std::ios::binary|std::ios::trunc);
    if (!ofs) {
      std::cerr<<"Unable to write field "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    long nsize=val.size();
    ofs.write((char *)&nsize,sizeof(long));
    if (ofs.fail()) {
      std::cerr<<"Unable to write length for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.write((char *)&val[0],nsize*sizeof(double));
    if (ofs.fail()) {
      std::cerr<<"Unable to write data for "<<field<<" to "<<fname<<std::endl;
      std::cerr.flush();
      myexit(1);
    }
    ofs.close();
  }
};
#endif
