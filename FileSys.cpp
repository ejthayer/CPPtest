
#include "FileSys.h"

FileSys filesys;

//--------------------------------------------------------------------------------------------
FileSys::FileSys(void) {
  max = 25;
  count = 0;
  fdata = new FileSysData[max];
}

//--------------------------------------------------------------------------------------------
FileSys::~FileSys(void) {
  delete [] fdata;
}

//--------------------------------------------------------------------------------------------
FILE* FileSys::open(const char *fname,const char *mode) {
  FILE *handle;

  WaitForSingleObject( filemutex, INFINITE );

  int i = FindOpenFile(fname);
  if ( i >= 0 ) {
    fdata[i].attempts++;
    ReleaseMutex(filemutex);
    return 0;
  }

  if ( count == max ) expand(25);
  fdata[count].handle = fopen(fname,mode);
  strcpy(fdata[count].fname,fname);
  strcpy(fdata[count].mode,mode);
  fdata[count].attempts = 1;
  if ( fdata[count].handle ) {
    handle = fdata[count].handle;
    count++;
    ReleaseMutex(filemutex);
    return handle;
  }
  ReleaseMutex(filemutex);
  return 0;
}

//--------------------------------------------------------------------------------------------
bool FileSys::close(FILE *handle) {

  WaitForSingleObject( filemutex, INFINITE );

  for ( int a = 0 ; a < count ; a++ ) {
    if ( fdata[a].handle == handle ) {
      fclose(fdata[a].handle);
      Delete(a);
      ReleaseMutex(filemutex);
      return true;
    }
  }
  ReleaseMutex(filemutex);
  return false;
}

//--------------------------------------------------------------------------------------------
long FileSys::FindOpenFile(const char *fname) {
  for ( int a = 0 ; a < count ; a++ ) {
    if ( strcmp(fdata[a].fname,fname) == 0 ) return a;
  }
  return -1;
}

//--------------------------------------------------------------------------------------------
void FileSys::expand(long amt) {
  FileSysData *temp;

  temp = new FileSysData[max+amt];
  for ( int a = 0 ; a < max ; a++ ) {
    temp[a] = fdata[a];
  }
  delete [] fdata;
  fdata = temp;
  max += amt;
}

//--------------------------------------------------------------------------------------------
void FileSys::Delete(long index) {
  if ( index < 0 || index >= count ) return;
  for ( int a = index ; a < count-1 ; a++ ) {
    fdata[a] = fdata[a+1];
  }
  count--;
}