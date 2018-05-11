
#include "one.h"
#include "ext.h"

const int wallWeight = 20; //ширина стены
//const int wallStep = 5;
const int holeRadius = 100; //диаметр дыры
const int dt = 16; //сдвиг от края области до координатных осей в графике
const int dl = 5; //длина риски на оси в графике
const int yscale = 20; //масштабирование по у (точек на одно деление)

void ToPixC(double x, double y, int*xC, int*yC) //преобразование координат точки от абсолютных к области рисования
{*xC=int((x/Lenx_)*(Lx_+dx_-1))+dx_+Cradius_+1;
 *yC=int((y/Leny_)*(Ly_+dy_-1))+dy_+Cradius_+1; return;}
//------------------
HRGN CreateCircleRgn(int x,int y,int r){return CreateEllipticRgn(x-r,y-r,x+r,y+r);} //отрисовка кружочка
//------------------
void DrawAxis(HDC hDC, int lx, int ly, int &stepx, int &stepy, int stept) //отрисовка осей (область рисования, длина, ширина, шаг делений по осям, фактический шаг времени на деление)
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(0, 0, 0);
	HBRUSH hBrBk = CreateBrushIndirect(&lb);	//создание чёрной кисти
	//---отрисовка двух осей
	/*MoveToEx(hDC, dt, dt, NULL);
	LineTo(hDC, lx - dt, dt);
	MoveToEx(hDC, dt, dt, NULL);
	LineTo(hDC, dt, ly - dt);
	//----------------------
	RECT rc; //область для вывода текста
	rc.bottom = dt; rc.top = 1; rc.left = 1; rc.right = dt;
	char buf[5];
	strcpy(buf, "0");
	DrawText(hDC, buf, 1, &rc, DT_CENTER); //обозначаем 0 на осях
	stepx = (lx - 2 * dt) / (times_ / stept); //вычисляем шаг по х на основании заданного времени
	for (int i = stepx, j = stept; i < lx - dt; i += stepx, j += stept) { //рисуем деления
		MoveToEx(hDC, i + dt, dt, NULL); //само деление
		LineTo(hDC, i + dt, dl + dt);
		rc.left = i + dt / 2; rc.right = i + 1.5*dt;
		itoa(j, buf, 10);
		DrawText(hDC, buf, strlen(buf), &rc, DT_LEFT); //подпись
	}
	rc.left = 1; rc.right = dt;
	for (int i = yscale, j = stepy; i < ly - dt; i += yscale, j += stepy) { //аналогично по у
		MoveToEx(hDC, dt, i + dt, NULL);
		LineTo(hDC, dl + dt, i + dt);
		rc.top = i + dt / 2; rc.bottom = i + 1.5*dt;
		itoa(j, buf, 10);
		DrawText(hDC, buf, strlen(buf), &rc, DT_LEFT);
	}
	DeleteObject(hBrBk);*/
}

/*void DrawScale (HDC hDC, int x0, int y0, int x1, int y1, int stepx, int stepy, int stept) //отрисовка очередной линии в графике (область, координаты предыдущей и новой точек, шаги по осям для масштабирования значений)
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(255,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
	MoveToEx (hDC, x0*stepx/stept+dt, y0*yscale/stepy+dt, NULL);
	LineTo (hDC, x1*stepx/stept+dt, y1*yscale/stepy+dt); //рисуем линию от предыдущей точки к новой, учитывая масштабирования
	DeleteObject(hBrBk); 
}*/

void DrawWall (HDC hDC, int x) //отрисовка стены на уровне х
{
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(255,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
	if (x-wallWeight>(lx_-x0_)/2) { //если стена не достигла середины области
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_); //рисуем без дыры
		FillRgn(hDC, w, hBrBk);
		DeleteObject (w);
	} else { //достигла середины
		HRGN w = CreateRectRgn (x-wallWeight, y0_, x, ly_/2-holeRadius/2);
		FillRgn(hDC, w, hBrBk); //рисуем верхнюю часть
		DeleteObject (w);
		w = CreateRectRgn (x-wallWeight, ly_/2+holeRadius/2, x, ly_);
		FillRgn(hDC, w, hBrBk); //рисуем нижнюю часть
		DeleteObject (w);
	}	
	DeleteObject(hBrBk);
}

/*void ClearWall (HDC hDC, int x) //удаление стены
{//аналогично отрисовке, но белым цветом
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

void MoveWall (int& x, int wallStep) //вычислеие новой координаты стены
{
	if (x-wallWeight>(lx_-x0_)/2) x-=wallStep; //двигаем, если не достигли середины области
}*/
//------------------
void DrawC(HDC hDC, double x, double y){ //отрисовка частицы
	LOGBRUSH lb; lb.lbStyle = BS_SOLID;	lb.lbColor = RGB(0,0,0);
	HBRUSH hBrBk = CreateBrushIndirect( &lb );
int xC, yC; ToPixC(x,y,&xC,&yC);

HRGN C=CreateCircleRgn(xC,yC,Cradius_);FillRgn(hDC,C,hBrBk);
DeleteObject(C);DeleteObject(hBrBk); return;}
//------------------
void ClearC(HDC hDC, double x, double y){ //удаление частицы
LOGBRUSH lb; lb.lbStyle = BS_SOLID;lb.lbColor = RGB(255,255,255);
HBRUSH hBrWh = CreateBrushIndirect( &lb );
int xC, yC; ToPixC(x,y,&xC,&yC);
HRGN C=CreateCircleRgn(xC,yC,Cradius_); FillRgn(hDC,C,hBrWh);
DeleteObject(C);DeleteObject(hBrWh); return;}
//------------------
void DrawPTS(HDC hDC, double *X, double *Y){ //отрисовка всего массива частиц
for(int i=0; i<nPts_;i++) DrawC(hDC,X[i],Y[i]);	return;}
//------------------
void ClearPTS(HDC hDC, double *X, double *Y){ //удаление всего массива частиц
for(int i=0; i<nPts_;i++) ClearC(hDC,X[i],Y[i]);	return;}
//------------------
void CalcPTS(double *X, double *Y, double *siA, double *coA, int &wallPos, int wallStep, int t){
	//вычисление новых координат для каждой частицы
	if (t==0){  //начальная инициализация, если вызов при времени = 0
		double A;A=2*Pi_/nPts_;
		for(int i=0;i<nPts_;i++){X[i]=xST_;Y[i]=yST_;siA[i]=sin(A*i);coA[i]=cos(A*i);}
		return;
	}
	double x0,y0,s0,c0, x1,y1,s1,c1;
	MoveWall (wallPos, wallStep); //двигаем стену
	for(int i=0;i<nPts_;i++){ //вычисляем координаты
		x0=X[i];y0=Y[i];s0=siA[i];c0=coA[i]; 
		FromTo(x0,y0,s0,c0,&x1,&y1,&s1,&c1, wallPos);
		X[i]=x1;Y[i]=y1;siA[i]=s1;coA[i]=c1; }
return; }
//------------------
void FromTo(double x0, double y0, double s0, double c0, //фактическое вычисление новых координат по формуле
			double*x1, double*y1, double*s1, double*c1, int wallPos){
		*x1=x0+vel_*c0;*y1=y0+vel_*s0;*c1=c0;*s1=s0; //вычисление новых координат
		BRFL( s0, c0, x0, y0, x1, y1, s1, c1, wallPos ); //проверка на столкновения с препятствиями
	return; }

//------------------
void BRFL( double s0, double c0, double x0, double y0, //коррекция координат относительно препятствий
		   double*x1, double*y1, double*s1, double*c1, int wallPos )
{
	double mylx = ((wallPos-wallWeight+1-dx_-Cradius_-1)*Lenx_)/(Lx_+dx_-1);//положение стены
	double mylx_r = ((wallPos+1-dx_-Cradius_-1)*Lenx_)/(Lx_+dx_-1);//положение стены справа
	double myh0 = ((ly_/2-holeRadius/2-dy_-Cradius_-1)*Leny_)/(Ly_+dy_-1); //положение дыры
	double myh1 = ((ly_/2+holeRadius/2-dy_-Cradius_-1)*Leny_)/(Ly_+dy_-1);
	//дыры нет
	if (wallPos-wallWeight>(lx_-x0_)/2) {
		if(*x1<0) { //упёрлись в левую границу
			*x1=-*x1;
			*c1=-c0;
			pressure++;
		}
		if(*x1>mylx) { //упёрлись в стену
			*x1=mylx-(*x1-mylx);
			*c1=-c0;
		}
		if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //упёрлись в верхюю границу
		if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //в нижнюю
	} else {	//дыра есть
	//мы слева от стены
		if (x0<mylx_r) { //по х левее правой стороны стены и не на уровне дыры
			if(*x1<0) { //в левую
				*x1=-*x1;
				*c1=-c0;
				pressure++;
			}
			if(*x1>mylx && !(*y1>myh0 && *y1<myh1)) { //упёрлись в стену слева и не попали в дыру
				*x1=mylx-(*x1-mylx);
				*c1=-c0;
			}
			if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //верняя
			if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //нижняя
		} else 	if (x0>mylx) { //по х правее левой стороны стены и не на уровне дыры
	//мы справа от стены
			if(*x1<mylx_r && !(*y1>myh0 && *y1<myh1)) { //упёрлись в стену справа и не попали в дыру
				*x1=mylx_r+(mylx_r-*x1);
				*c1=-c0;
			}
			if(*x1>Lenx_) { //упёрлись в правую границу
				*x1=Lenx_-(*x1-Lenx_);
				*c1=-c0;
			}
			if(*y1<0    ) {*y1=-*y1;*s1=-s0;} //верхняя
			if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;} //нижняя
		} else if (x0>=mylx && x0<=mylx_r && y0>myh0 && y0<myh1) { //перемещаемся в пределах дыры
	//мы в дыре
			if(*y1<myh0    ) {*y1=-*y1;*s1=-s0;} //упёрлись в верхнюю границу дыры
			if(*y1>myh1) {*y1=myh1-(*y1-myh1);*s1=-s0;} //в нижнюю границу дыры
		}
	}
			



	//if(*x1<0    ) {*x1=-*x1;*c1=-c0;}
	//if(*x1>mylx) { //если достигли стены, надо проверить наличие дыры
	//	if (wallPos-wallWeight>(lx_-x0_)/2) { //дыры нет
	//		*x1=mylx-(*x1-mylx);
	//		*c1=-c0;
	//	} else { //дыра есть
	//		if (*x1>mylx_r) {  //справа от дыры
	//			if(*x1>Lenx_) {*x1=Lenx_-(*x1-Lenx_);*c1=-c0;} //проверяем границу области
	//		} else if (*x1>=mylx && *x1<=mylx_r) {*x1=mylx_r-(*x1-mylx_r); *c1=-c0;}
	//		//} else if (*x1>=mylx && *x1<=mylx_r && *y1>myh0 && *y1<myh1) { //попали в дыру
	//			//if(*x1>Lenx_) {*x1=Lenx_-(*x1-Lenx_);*c1=-c0;} //проверяем границу области
	//		 if (!(*y1>myh0 && *y1<myh1)) { //НЕ попали в дыру и мы слева от неё
	//			*x1=mylx-(*x1-mylx);
	//			*c1=-c0;
	//		}
	//	}
	//}
	//if(*y1<0    ) {*y1=-*y1;*s1=-s0;}
	//if(*y1>Leny_) {*y1=Leny_-(*y1-Leny_);*s1=-s0;}
}
//------------------
void Delay(UINT pause){int t=GetTickCount();while ((GetTickCount()-t)<pause){};return;} //задержка для эмуляции анимации
//------------------

