
#include "one.h"
#include "ext.h"

char Buf[BUFSIZE];

//------------------------------------------------------------------------
BOOL CALLBACK DlgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
				return InitPR(hwnd);			
		case WM_COMMAND:
			{
				switch (LOWORD(wParam))
				{
					case IDC_EDIT1:
						GetWindowText(hEdit1,Buf,BUFSIZE);  nPts_=int(atof(Buf));return TRUE;
					case IDC_EDIT2:
						GetWindowText(hEdit2,Buf,BUFSIZE);   xST_=atof(Buf);return TRUE;
					case IDC_EDIT3:
						GetWindowText(hEdit3,Buf,BUFSIZE);   yST_=atof(Buf);return TRUE;
					case IDC_EDIT4:
						GetWindowText(hEdit4,Buf,BUFSIZE);   vel_=atof(Buf);return TRUE;
					case IDC_EDIT5:
						GetWindowText(hEdit5,Buf,BUFSIZE); times_=int(atof(Buf));return TRUE;
					case IDC_GetParam:
				     		return GetParam(hwnd);
					case IDC_Start:
							return  Start(hwnd);
			}	}
		case IDC_Close:
				EndDialog(hwnd,0);return TRUE;
		case WM_CLOSE:			
				EndDialog(hwnd,0);return TRUE; 
	}
return FALSE;
}

//------------------
BOOL InitPR(HWND hwnd){
hEdit1=GetDlgItem(hwnd,IDC_EDIT1); hEdit2=GetDlgItem(hwnd,IDC_EDIT2);
hEdit3=GetDlgItem(hwnd,IDC_EDIT3); hEdit4=GetDlgItem(hwnd,IDC_EDIT4);
hEdit5=GetDlgItem(hwnd,IDC_EDIT5);
hStatic=GetDlgItem(hwnd,IDC_STATICZ);
	SetWindowText(hEdit1,"40");   SetWindowText(hEdit2,"0.2");
	SetWindowText(hEdit3,"0.5");  SetWindowText(hEdit4,"0.1");
	SetWindowText(hEdit5,"50");

hButParam=GetDlgItem(hwnd,IDC_GetParam);
hButStart=GetDlgItem(hwnd,IDC_Start);
hButClose=GetDlgItem(hwnd,IDC_Close);
	EnableWindow(hButStart,FALSE);
Pi_=4*atan(1.);Lenx_=1.5;Leny_=1.2; dx_=20;dy_=40; Lx_=400;Ly_=250;  Cradius_=5;
x0_ = dx_+1; y0_ = dy_+1; lx_ = Lx_+2*(dx_+Cradius_)-1; ly_ = Ly_+2*(dy_+Cradius_)-1;
pressure = 0;
return FALSE;}
//------------------
BOOL GetParam(HWND hwnd){
	GetWindowText(hEdit1,Buf,BUFSIZE);   nPts_=atoi(Buf);
	GetWindowText(hEdit2,Buf,BUFSIZE);    xST_=atof(Buf);
	GetWindowText(hEdit3,Buf,BUFSIZE);    yST_=atof(Buf);
	GetWindowText(hEdit4,Buf,BUFSIZE);    vel_=atof(Buf);
	GetWindowText(hEdit5,Buf,BUFSIZE);  times_=atoi(Buf);
if (xST_<0||xST_>Lenx_||yST_<0||yST_>Leny_)
	{MessageBox(hwnd,"Incorrect (xST,yST) position in SPACE!", "",MB_OK);return TRUE;}

	

EnableWindow(hEdit1,FALSE);	EnableWindow(hEdit2,FALSE);
EnableWindow(hEdit3,FALSE);	EnableWindow(hEdit4,FALSE);
EnableWindow(hEdit5,FALSE);
EnableWindow(hButParam,FALSE);
	EnableWindow(hButStart,TRUE);
return TRUE;}
//------------------
BOOL  Start(HWND hwnd) {
	UINT pause=150;//Milliseconds
	int  TS=1;
	pressure = 0;
	int sx0 = 0, sy0 = 0;
	int sw = 450, sh = 170;
	int step_time = 5, stepx, stepy = 5;
	
GetMemory();

	HDC hDC=GetDC(hwnd);
	Rectangle(hDC,dx_,dy_,Lx_+2*(dx_+Cradius_),Ly_+2*(dy_+Cradius_));

	HDC hDC1 = GetDC (GetDlgItem (hwnd, IDC_Scale)); 
	Rectangle(hDC1, 0, 0, sw, sh);
	DrawAxis (hDC1, sw, sh, stepx, stepy, step_time);

	int wallPos = Lx_+2*(dx_+Cradius_)-1; //начальное положение стены
	int wallStep = (lx_/2)/(times_/3); //скорость для стены

	CalcPTS(X_,Y_,siA_,coA_,wallPos,wallStep,0);DrawPTS(hDC,X_,Y_);DrawWall(hDC, wallPos);
		
	SetWindowText(hStatic,"PTS will start from the set!"); Delay(5*pause);
	SetWindowText(hStatic,"-THREE"); Delay(5*pause);
	SetWindowText(hStatic,"-TWO");   Delay(5*pause);
	SetWindowText(hStatic,"-ONE");   Delay(5*pause);
	SetWindowText(hStatic,"START"); Delay(5*pause);

	SetWindowText(hStatic,"PTS are moving");
					for (int ts=0;ts<times_;ts++) { 
						ClearPTS(hDC,X_,Y_); ClearWall (hDC, wallPos); 
						CalcPTS(X_,Y_,siA_,coA_, wallPos, wallStep, ts*TS);
					    DrawPTS(hDC,X_,Y_); DrawWall(hDC, wallPos); 
						if (ts%step_time==0) {
							DrawScale (hDC1, sx0, sy0, ts, pressure, stepx, stepy, step_time);
							sx0 = ts; sy0 = pressure; pressure = 0;
						}
						Delay(pause); 
					}
					DrawScale (hDC1, sx0, sy0, times_, pressure, stepx, stepy, step_time);

	SetWindowText(hStatic,"Time is over");Delay(8*pause);ClearPTS(hDC,X_,Y_);ClearWall (hDC, wallPos); 
	wallPos = Lx_+2*(dx_+Cradius_)-1;
	CalcPTS(X_,Y_,siA_,coA_, wallPos,wallStep,0);DrawPTS(hDC,X_,Y_);
	SetWindowText(hStatic,"PTS started from the set");

	ReleaseDC(hwnd,hDC);
	ReleaseDC(hwnd,hDC1);
EnableWindow(hEdit1,TRUE);EnableWindow(hEdit2,TRUE);
EnableWindow(hEdit3,TRUE);EnableWindow(hEdit4,TRUE);
EnableWindow(hEdit5,TRUE);

    EnableWindow(hButParam,TRUE);
	EnableWindow(hButStart,FALSE);
FreeMemory();
return TRUE;}

//------------------

/*void GetMemory(void){
	X_  =new double[nPts_];Y_  =new double[nPts_];
	siA_=new double[nPts_];coA_=new double[nPts_];
	return;}
//------------------

void FreeMemory(void){
	delete X_; delete Y_; delete siA_; delete coA_;
	return;}

//------------------*/