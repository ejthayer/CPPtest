#include "dxstdafx.h"
#include "BaseDialog.h"

BaseDialog::BaseDialog(void) {
  Displayed = false;
}

BaseDialog::~BaseDialog(void) {
}

void WINAPI BaseDialog::StaticOnEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserData ) {
    BaseDialog* basedlg = (BaseDialog*) pUserData;
    if( basedlg ) basedlg->OnEvent( nEvent, nControlID, pControl );
}

bool BaseDialog::Load(char *fname) {
  FILE *infile;
  long a,controltype;
  long id,x,y,w,h,f,g;
  CDXUTStatic *pControl;
  CDXUTEditBox *pEditBox;
  char pathfname[100];

  sprintf(pathfname,"%s%s",guipath,fname);

  infile = fopen(pathfname,"rb");
  if ( !infile ) {
    return false;
  }

  dialog.RemoveAllControls();

  // load base screen object data
  fread(&dialog.m_width,4,1,infile);
  fread(&dialog.m_height,4,1,infile);
  fread(&dialog.m_backgroundType,4,1,infile);

  // load all screen objects
  while( true ) {
    fread(&controltype,4,1,infile);
    if ( feof(infile) ) break;
    switch ( controltype ) {
    case DXUT_CONTROL_BUTTON:
      fread(&id,4,1,infile);
      fread(text,100,1,infile);
      fread(messg,100,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      dialog.AddButton(id,WideChar(text),x,y,w,h,0,false,0);
      pControl = dialog.GetButton( id );
      dialog.GetButton( id )->SetText2(messg);
      if ( pControl ) pControl->GetElement(1)->iFont = f;
      break;
    case DXUT_CONTROL_STATIC:
      fread(&id,4,1,infile);
      fread(text,100,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      fread(&g,4,1,infile);
      dialog.AddStatic(id,WideChar(text),x,y,w,h,false,0);
      pControl = dialog.GetStatic( id );
      if ( pControl ) pControl->GetElement(0)->iFont = f;
      if ( pControl ) pControl->GetElement(0)->dwTextFormat = g;
      break;
    case DXUT_CONTROL_CHECKBOX:
      fread(&id,4,1,infile);
      fread(text,100,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      dialog.AddCheckBox(id,WideChar(text),x,y,w,h,false,0,false,0);
      pControl = dialog.GetCheckBox( id );
      if ( pControl ) pControl->GetElement(0)->iFont = f;
      break;
    case DXUT_CONTROL_RADIOBUTTON:
      fread(&id,4,1,infile);
      fread(text,100,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      fread(&g,4,1,infile);
      dialog.AddRadioButton(id,g,WideChar(text),x,y,w,h,false,0,false,0);
      pControl = dialog.GetRadioButton( id );
      if ( pControl ) pControl->GetElement(0)->iFont = f;
      break;
    case DXUT_CONTROL_COMBOBOX:
      fread(&id,4,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      dialog.AddComboBox(id,x,y,w,h,0,false,0);
      break;
    case DXUT_CONTROL_SLIDER:
      fread(&id,4,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      dialog.AddSlider(id,x,y,w,h,0,100,0,false,0);
      break;
    case DXUT_CONTROL_EDITBOX:
      fread(&id,4,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      dialog.AddEditBox(id,L"",x,y,w,h,false,0);
      pEditBox = dialog.GetEditBox( id );
      if ( pEditBox ) pEditBox->GetElement(0)->iFont = f;
      break;
    case DXUT_CONTROL_LISTBOX:
      fread(&id,4,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      dialog.AddListBox(id,x,y,w,h,0,0);
      dialog.GetListBox(id)->GetElement(0)->iFont = f;
      dialog.GetListBox(id)->UpdateRects();
      break;
    case DXUT_CONTROL_PANEL:
      fread(&id,4,1,infile);
      fread(&x,4,1,infile);
      fread(&y,4,1,infile);
      fread(&w,4,1,infile);
      fread(&h,4,1,infile);
      fread(&f,4,1,infile);
      dialog.AddPanel(id,x,y,w,h,0);
      dialog.GetPanel(id)->SetBackGround(f);
      break;
    }
  }

  fclose(infile);
  return true;

}