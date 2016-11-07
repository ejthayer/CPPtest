#pragma once

#include "globals.h"

class BaseDialog {
public:

  CDXUTDialog dialog;
  bool Displayed;

  BaseDialog(void);
  ~BaseDialog(void);

  static void WINAPI StaticOnEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserData );
  virtual void OnEvent( UINT nEvent, int nControlID, CDXUTControl* pControl ) = 0;
  virtual void Display(void) = 0;
  virtual void Close(void) = 0;
  virtual char* DialogName(void) = 0;
  bool Load(char *fname);
};
