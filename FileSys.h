
#pragma once

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <process.h>

#define MODE_READTEXT "rt"
#define MODE_READBINARY "rb"
#define MODE_APPENDBINARY "a+b"
#define MODE_WRITETEXT "wt"
#define MODE_WRITEBINARY "wb"

struct FileSysData {
  FILE *handle;
  long attempts;
  char fname[80];
  char mode[5];
};

class FileSys {
public:
  FileSysData *fdata;
  long count,max;
  HANDLE filemutex;

  FileSys(void);
  ~FileSys(void);

  FILE* open(const char *fname,const char *mode);
  bool close(FILE *handle);
  long FindOpenFile(const char *fname);
private:
  void expand(long amt);
  void Delete(long index);
};

extern FileSys filesys;