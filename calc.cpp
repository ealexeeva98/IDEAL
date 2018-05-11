
#include "one.h"
#include "ext.h"

const int wallWeight = 20; //������ �����
//const int wallStep = 5;
const int holeRadius = 100; //������� ����
const int dt = 16; //����� �� ���� ������� �� ������������ ���� � �������
const int dl = 5; //����� ����� �� ��� � �������
const int yscale = 20; //��������������� �� � (����� �� ���� �������)

void ToPixC(double x, double y, int*xC, int*yC) //�������������� ��������� ����� �� ���������� � ������� ���������
{*xC=int((x/Lenx_)*(Lx_+dx_-1))+dx_+Cradius_+1;
 *yC=int((y/Leny_)*(Ly_+dy_-1))+dy_+Cradius_+1; return;}
//------------------
HRGN CreateCircleRgn(int x,int y,int r){return CreateEllipticRgn(x-r,y-r,x+r,y+r);} //��������� ��������
//------------------
void DrawAxis(HDC hDC, int lx, int ly, int &stepx, int &stepy, int stept) //��������� ���� (������� ���������, �����, ������, ��� ������� �� ����, ����������� ��� ������� �� �������)
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(0, 0, 0);
	HBRUSH hBrBk = CreateBrushIndirect(&lb);	//�������� ������ �����
	//---��������� ���� ����
	/*MoveToEx(hDC, dt, dt, NULL);
	LineTo(hDC, lx - dt, dt);
	MoveToEx(hDC, dt, dt, NULL);
	LineTo(hDC, dt, ly - dt);
	//----------------------
	RECT rc; //������� ��� ������ ������
	rc.bottom = dt; rc.top = 1; rc.left = 1; rc.right = dt;
	char buf[5];
	strcpy(buf, "0");
	DrawText(hDC, buf, 1, &rc, DT_CENTER); //���������� 0 �� ����
	stepx = (lx - 2 * dt) / (times_ / stept); //��������� ��� �� � �� ��������� ��������� �������
	for (int i = stepx, j = stept; i < lx - dt; i += stepx, j += stept) { //������ �������
		MoveToEx(hDC, i + dt, dt, NULL); //���� �������
		LineTo(hDC, i + dt, dl + dt);
		rc.left = i + dt / 2; rc.right = i + 1.5*dt;
		itoa(j, buf, 10);
		DrawText(hDC, buf, strlen(buf), &rc, DT_LEFT); //�������
	}
	rc.left = 1; rc.right = dt;
	for (int i = yscale, j = stepy; i < ly - dt; i += yscale, j += stepy) { //���������� �� �
		MoveToEx(hDC, dt, i + dt, NULL);
		LineTo(hDC, dl + dt, i + dt);
		rc.top = i + dt / 2; rc.bottom = i + 1.5*dt;
		itoa(j, buf, 10);
		DrawText(hDC, buf, strlen(buf), &rc, DT_LEFT);
	}
	DeleteObject(hBrBk);*/
}

/*void DrawScale (HDC hDC, int x0, int y0, int x1, int y1, int stepx, int stepy, int stept) //��������� ��������� ����� � ������� (�������, ���������� ���������� � ����� �����, ���� �� ���� ��� ��������������� ��������)
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(255,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
	MoveToEx (hDC, x0*stepx/stept+dt, y0*yscale/stepy+dt, NULL);
	LineTo (hDC, x1*stepx/stept+dt, y1*yscale/stepy+dt); //������ ����� �� ���������� ����� � �����, �������� ���������������
	DeleteObject(hBrBk); 
}*/

void DrawWall (HDC hDC, int x) //��������� ����� �� ������ �
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(255,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
	if (x-wallWeight>(lx_-x0_)/2) { //���� ����� �� �������� �������� �������
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_); //������ ��� ����
		FillRgn(hDC, w, hBrBk);
		DeleteObject (w);
	} else { //�������� ��������
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_/2-holeRadius/2);
		FillRgn(hDC, w, hBrBk); //������ ������� �����
		DeleteObject (w);
		w = CreateRectRgn (x-wallWeight, ly_/2+holeRadius/2, x, ly_);
		FillRgn(hDC, w, hBrBk); //������ ������ �����
		DeleteObject (w);
	}	
	DeleteObject(hBrBk);
}

/*void ClearWall (HDC hDC, int x) //�������� �����
{//���������� ���������, �� ����� ������
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(255,255,255);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
	if (x-wallWeight>(lx_-x0_)/2) {
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_);
		FillRgn(hDC, w, hBrBk);
		DeleteObject (w);
	} else {
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_/2-holeRadius/2);
		FillRgn(hDC, w, hBrBk);
		DeleteObject (w);
		w = CreateRectRgn (x-wallWeight, ly_/2+holeRadius/2, x, ly_);
		FillRgn(hDC, w, hBrBk);
		DeleteObject (w);
	}	
	DeleteObject(hBrBk);
}

void MoveWall (int& x, int wallStep) //��������� ����� ���������� �����
{
	if (x-wallWeight>(lx_-x0_)/2) x-=wallStep; //�������, ���� �� �������� �������� �������
}*/
//------------------
void DrawC(HDC hDC, double x, double y){ //��������� �������
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(0,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
int xC, yC; ToPixC(x,y,&xC,&yC);

HRGN C=CreateCircleRgn(xC,yC,Cradius_);FillRgn(hDC,C,hBrBk);
DeleteObject(C);DeleteObject(hBrBk); return;}
//------------------
void ClearC(HDC hDC, double x, double y){ //�������� �������
LOGBRUSH lb; lb.lbStyle = BS_SOLID;lb.lbColor = RGB(255,255,255);
HBRUSH hBrWh = CreateBrushIndirect( &lb );
int xC, yC; ToPixC(x,y,&xC,&yC);
HRGN C=CreateCircleRgn(xC,yC,Cradius_); FillRgn(hDC,C,hBrWh);
DeleteObject(C);DeleteObject(hBrWh); return;}
//------------------
void DrawPTS(HDC hDC, double *X, double *Y){ //��������� ����� ������� ������
for(int i=0; i<nPts_;i++) DrawC(hDC,X[i],Y[i]);	return;}
//------------------
void ClearPTS(HDC hDC, double *X, double *Y){ //�������� ����� ������� ������
for(int i=0; i<nPts_;i++) ClearC(hDC,X[i],Y[i]);	return;}
//------------------
void CalcPTS(double *X, double *Y, double *siA, double *coA, int &wallPos, int wallStep, int t){
	//���������� ����� ��������� ��� ������ �������
	if (t==0){  //��������� �������������, ���� ����� ��� ������� = 0
		double A;A=2*Pi_/nPts_;
		for(int i=0;i<nPts_;i++){X[i]=xST_;Y[i]=yST_;siA[i]=sin(A*i);coA[i]=cos(A*i);}
		return;
	}
	double x0,y0,s0,c0, x1,y1,s1,c1;
	MoveWall (wallPos, wallStep); //������� �����
	for(int i=0;i<nPts_;i++){ //��������� ����������
		x0=X[i];y0=Y[i];s0=siA[i];c0=coA[i]; 
		FromTo(x0,y0,s0,c0,&x1,&y1,&s1,&c1, wallPos);
		X[i]=x1;Y[i]=y1;siA[i]=s1;coA[i]=c1; }
return; }
//------------------
void FromTo(double x0, double y0, double s0, double c0, //����������� ���������� ����� ��������� �� �������
			double*x1, double*y1, double*s1, double*c1, int wallPos){
		*x1=x0+vel_*c0;*y1=y0+vel_*s0;*c1=c0;*s1=s0; //���������� ����� ���������
		BRFL( s0, c0, x0, y0, x1, y1, s1, c1, wallPos ); //�������� �� ������������ � �������������
	return; }

//------------------
void BRFL( double s0, double c0, double x0, double y0, //��������� ��������� ������������ �����������
		   double*x1, double*y1, double*s1, double*c1, int wallPos )
{
	double mylx = ((wallPos-wallWeight+1-dx_-Cradius_-1)*Lenx_)/(Lx_+dx_-1);//��������� �����
	double mylx_r = ((wallPos+1-dx_-Cradius_-1)*Lenx_)/(Lx_+dx_-1);//��������� ����� ������
	double myh0 = ((ly_/2-holeRadius/2-dy_-Cradius_-1)*Leny_)/(Ly_+dy_-1); //��������� ����
	double myh1 = ((ly_/2+holeRadius/2-dy_-Cradius_-1)*Leny_)/(Ly_+dy_-1);
	//���� ���
	if (wallPos-wallWeight>(lx_-x0_)/2) {
		if(*x1<0) { //������� � ����� �������
			*x1=-*x1;
			*c1=-c0;
			pressure++;
		}
		if(*x1>mylx) { //������� � �����
			*x1=mylx-(*x1-mylx);
			*c1=-c0;
		}
		if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //������� � ������ �������
		if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //� ������
	} else {	//���� ����
	//�� ����� �� �����
		if (x0<mylx_r) { //�� � ����� ������ ������� ����� � �� �� ������ ����
			if(*x1<0) { //� �����
				*x1=-*x1;
				*c1=-c0;
				pressure++;
			}
			if(*x1>mylx && !(*y1>myh0 && *y1<myh1)) { //������� � ����� ����� � �� ������ � ����
				*x1=mylx-(*x1-mylx);
				*c1=-c0;
			}
			if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //������
			if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //������
		} else 	if (x0>mylx) { //�� � ������ ����� ������� ����� � �� �� ������ ����
	//�� ������ �� �����
			if(*x1<mylx_r && !(*y1>myh0 && *y1<myh1)) { //������� � ����� ������ � �� ������ � ����
				*x1=mylx_r+(mylx_r-*x1);
				*c1=-c0;
			}
			if(*x1>Lenx_) { //������� � ������ �������
				*x1=Lenx_-(*x1-Lenx_);
				*c1=-c0;
			}
			if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //�������
			if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //������
		} else if (x0>=mylx && x0<=mylx_r && y0>myh0 && y0<myh1) { //������������ � �������� ����
	//�� � ����
			if(*y1<myh0    ) {*y1=-*y1;*s1=-s0;} //������� � ������� ������� ����
			if(*y1>myh1) {*y1=myh1-(*y1-myh1);*s1=-s0;} //� ������ ������� ����
		}
	}
			



	//if(*x1<0    ) {*x1=-*x1;*c1=-c0;}
	//if(*x1>mylx) { //���� �������� �����, ���� ��������� ������� ����
	//	if (wallPos-wallWeight>(lx_-x0_)/2) { //���� ���
	//		*x1=mylx-(*x1-mylx);
	//		*c1=-c0;
	//	} else { //���� ����
	//		if (*x1>mylx_r) {  //������ �� ����
	//			if(*x1>Lenx_) {*x1=Lenx_-(*x1-Lenx_);*c1=-c0;} //��������� ������� �������
	//		} else if (*x1>=mylx && *x1<=mylx_r) {*x1=mylx_r-(*x1-mylx_r); *c1=-c0;}
	//		//} else if (*x1>=mylx && *x1<=mylx_r && *y1>myh0 && *y1<myh1) { //������ � ����
	//			//if(*x1>Lenx_) {*x1=Lenx_-(*x1-Lenx_);*c1=-c0;} //��������� ������� �������
	//		 if (!(*y1>myh0 && *y1<myh1)) { //�� ������ � ���� � �� ����� �� ��
	//			*x1=mylx-(*x1-mylx);
	//			*c1=-c0;
	//		}
	//	}
	//}
	//if(*y1<0    ) {*y1=-*y1;*s1=-s0;}
	//if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;}
}
//------------------
void Delay(UINT pause){int t=GetTickCount();while ((GetTickCount()-t)<pause){};return;} //�������� ��� �������� ��������
//------------------

