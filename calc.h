void ToPixC(double, double, int*, int*);
HRGN CreateCircleRgn(int,int,int);
void  DrawC  (HDC, double, double);
void ClearC  (HDC, double, double);
void DrawPTS (HDC, double*,double*);
void ClearPTS(HDC, double*,double*);
void CalcPTS (double*,double*,double*,double*, int&, int, int);
void FromTo  (double, double, double, double,
			  double*,double*,double*,double*, int);
void     BRFL(double, double, double, double,
		      double*,double*,double*, double*, int);
void Delay(UINT time);

void DrawWall (HDC hDC, int x);
void ClearWall (HDC hDC, int x);

void DrawScale (HDC hDC, int x0, int y0, int x1, int y1, int stepx, int stepy, int stept);
void DrawAxis (HDC hDC, int lx, int ly, int &stepx, int &stepy, int stept);
