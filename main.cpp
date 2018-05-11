#include "one.h"

HWND hEdit1,hEdit2,hEdit3,hEdit4,hEdit5;
HWND hStatic;
HWND hButParam,hButStart,hButClose;

double Pi_, vel_, Lenx_, Leny_, xST_, yST_;//the relative values
int nPts_, times_, dx_, dy_, Lx_, Ly_, Cradius_, x0_, y0_, lx_, ly_, pressure;//in the pixels
double *X_, *Y_, *coA_,*siA_;

int APIENTRY _tWinMain(HINSTANCE hI, HINSTANCE hI2, LPSTR lp, int n)
{
return DialogBox(hI,MAKEINTRESOURCE(IDD_DIALOG1),NULL,(DLGPROC)DlgProc);
}




