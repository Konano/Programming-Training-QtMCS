#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
#include <QDebug>

#include "calculate.h"

using namespace std;

#define rep(i, r) for(int i=0; i<r; i++)
#define clr(x, c) memset(x,c,sizeof(x))

#define maxn 8
#define maxs 200
#define exp 1e-6

int num, EDGENUM, inputID[2], outputID[3], inputFlow[2]; double R[maxs];
int MatirxSize; double Matirx[maxs][maxs], V[maxs];

void init()
{
	rep(i, maxs) rep(j, maxs) Matirx[i][j] = 0;
}

inline int getID(int x, int y) { return x*num+y; }
inline double Left(int x, int y, int &ID)
{
	if (x == 0) return 0;
	ID = getID(x-1,y);
	return R[num*(num-1) + (x-1)*num + y];
}
inline double Right(int x, int y, int &ID)
{
	if (x == num-1) return 0;
	ID = getID(x+1,y);
	return R[num*(num-1) + x*num + y];
}
inline double Up(int x, int y, int &ID)
{
	if (y == 0)
	{
		if (x!=inputID[0] && x!=inputID[1]) return 0;
		int tmp = (x == inputID[1]);
		ID = num*num+tmp;
		return R[EDGENUM-5+tmp];
	}
	ID = getID(x,y-1);
	return R[x*(num-1) + y-1];
}
inline double Down(int x, int y, int &ID)
{
	if (y == num-1)
	{
		if (x!=outputID[0] && x!=outputID[1] && x!=outputID[2]) return 0;
		int tmp = (x == outputID[0] ? 0 : (x == outputID[1] ? 1 : 2));
		ID = num*num+3;
		return R[EDGENUM-3+tmp];
	}
	ID = getID(x,y+1);
	return R[x*(num-1) + y];
}

void makeMatrix()
{
	MatirxSize = num*num+2;
	int ID, itID; double r; rep(i, num) rep(j, num)
	{
		itID = getID(i,j);
		if ((r = Left(i,j,ID))>exp)
			Matirx[itID][ID]-=1.0/r, Matirx[itID][itID]+=1.0/r;
		if ((r = Right(i,j,ID))>exp)
			Matirx[itID][ID]-=1.0/r, Matirx[itID][itID]+=1.0/r;
		if ((r = Up(i,j,ID))>exp)
			Matirx[itID][ID]-=1.0/r, Matirx[itID][itID]+=1.0/r;
		if ((r = Down(i,j,ID))>exp)
			Matirx[itID][ID]-=1.0/r, Matirx[itID][itID]+=1.0/r;
	}
	Matirx[num*num][num*num+2] += inputFlow[0];
	Matirx[num*num][num*num] += 1.0/R[EDGENUM-5];
	Matirx[num*num][getID(inputID[0],0)] -= 1.0/R[EDGENUM-5];

	Matirx[num*num+1][num*num+2] += inputFlow[1];
	Matirx[num*num+1][num*num+1] += 1.0/R[EDGENUM-4];
	Matirx[num*num+1][getID(inputID[1],0)] -= 1.0/R[EDGENUM-4];
}

void calMatrix()
{
	rep(o, MatirxSize)
	{
		bool Find = false;
		for(int i=o; i<MatirxSize; i++) if (fabs(Matirx[i][o])>exp)
		{
			Find = true;
			if (i == o) break;
			rep(j, MatirxSize+1) swap(Matirx[i][j], Matirx[o][j]);
			break;
		}
		if (!Find) continue;
		rep(i, MatirxSize) if (fabs(Matirx[i][o])>exp && i!=o)
		{
			double tmp = Matirx[i][o]/Matirx[o][o];
			rep(j, MatirxSize+1) Matirx[i][j]-=Matirx[o][j]*tmp;
		}
	}
}

vector<double> caluconspeed (int _num, vector<double>&length, int i1, int i2, int o1, int o2, int o3, int if0, int if1)
{
	init();

	num = _num;
	EDGENUM = (num-1)*num*2 + 5;
	rep(i, EDGENUM) R[i] = length[i];

	inputID[0] = i1;
	inputID[1] = i2;
	outputID[0] = o1;
	outputID[1] = o2;
	outputID[2] = o3;
	inputFlow[0] = if0;
	inputFlow[1] = if1;

	makeMatrix();
	calMatrix();

	// bool NoSolution = false;

	rep(i, MatirxSize)
	{
		if (fabs(Matirx[i][i])>exp)
			V[i] = Matirx[i][MatirxSize]/Matirx[i][i];
		// else if (fabs(Matirx[i][MatirxSize])>exp)
		// 	NoSolution = true;
		else V[i] = 0;
	}
	// if (NoSolution) return vector<double>(EDGENUM,0);

	vector<double> ans;
	rep(i, num) rep(j, num-1) if (R[i*(num-1)+j]>exp) ans.push_back(V[getID(i,j)]-V[getID(i,j+1)]); else ans.push_back(0);
	rep(i, num-1) rep(j, num) if (R[num*(num-1)+i*num+j]>exp) ans.push_back(V[getID(i,j)]-V[getID(i+1,j)]); else ans.push_back(0);
	ans.push_back(V[num*num]-V[getID(inputID[0],0)]);
	ans.push_back(V[num*num+1]-V[getID(inputID[1],0)]);
	ans.push_back(V[getID(outputID[0],num-1)]);
	ans.push_back(V[getID(outputID[1],num-1)]);
	ans.push_back(V[getID(outputID[2],num-1)]);
	return ans;
}




int inputConcen[2], in[maxs]; double F[maxs], G[maxs][4], C[maxs][4], L[maxs][4];

void init_calconcen()
{
	clr(in,0); clr(F,0); clr(G,0); clr(C,0); clr(L,0);
}

void nodeCal(int o)
{
	int count[2]={0,0};
	double Ctot[2]={0,0};
	double Gtot[2]={0,0};
	rep(i, 4) if (fabs(G[o][i])>exp)
	{
		count[G[o][i]>0]++;
		Ctot[G[o][i]>0] += C[o][i]*fabs(G[o][i]);
		Gtot[G[o][i]>0] += fabs(G[o][i]);
	}
	if (count[0]<2 || count[1]<2)
	{
		rep(i, 4) if (fabs(G[o][i])>exp && G[o][i] > 0)
			C[o][i] = Ctot[0]/Gtot[0];
	}
	else if ((G[o][0] < 0 && G[o][2] < 0) ||
			(G[o][1] < 0 && G[o][3] < 0))
	{
		rep(i, 4) if (G[o][i] > 0)
			C[o][i] = Ctot[0]/Gtot[0];
	}
	else
	{
		int tmp = 0;
		while (G[o][tmp] > 0 || G[o][(tmp+1)%4] > 0) tmp++;
		if (fabs(G[o][tmp]) >= G[o][(tmp+3)%4])
		{
			C[o][(tmp+3)%4] = C[o][tmp];
			Ctot[0] -= C[o][(tmp+3)%4]*G[o][(tmp+3)%4];
			Gtot[0] -= G[o][(tmp+3)%4];
			C[o][(tmp+2)%4] = Ctot[0]/Gtot[0];
		}
		else
		{
			C[o][(tmp+2)%4] = C[o][(tmp+1)%4];
			Ctot[0] -= C[o][(tmp+2)%4]*G[o][(tmp+2)%4];
			Gtot[0] -= G[o][(tmp+2)%4];
			C[o][(tmp+3)%4] = Ctot[0]/Gtot[0];
		}
	}
}

void nodeCal2(int o)
{
	int tot=0;
	double a[4]={0,0,0,0};
	rep(i, 4) if (C[o][i]>-0.1)
		a[tot++]=C[o][i];
    // qDebug() << o << L[o][0] << L[o][1] << L[o][2] << L[o][3] << C[o][0] << C[o][1] << C[o][2] << C[o][3]
			 // << tot << a[0] << a[1] << a[2] << a[3];

	if (tot == 0 || tot == 4) return;
	else if (tot <= 2)
	{
		rep(i, 4) if (L[o][i] && C[o][i]<-0.1)
			C[o][i] = a[0];
	}
	else
	{
		sort(a, a+tot);
		rep(i, 4) if (L[o][i] && C[o][i]<-0.1)
			C[o][i] = a[1];
	}
}

vector<double> calconcen(int _num, vector<double>&length, vector<double>&result, int i1, int i2, int o1, int o2, int o3, int ic0, int ic1)
{
	init_calconcen();

	num = _num;
    EDGENUM = (num-1)*num*2 + 5;
	rep(i, EDGENUM) F[i] = result[i];

	inputID[0] = i1;
	inputID[1] = i2;
	outputID[0] = o1;
	outputID[1] = o2;
	outputID[2] = o3;
	inputConcen[0] = ic0;
	inputConcen[1] = ic1;

	rep(i, num) rep(j, num) rep(o, 4) C[i*num+j][o] = -1;

	// 0 up 1 right 2 down 3 left
	rep(i, num) rep(j, num-1) if (fabs(F[i*(num-1)+j])>exp)
	{
		G[getID(i,j)][2] = F[i*(num-1)+j];
		G[getID(i,j+1)][0] = -F[i*(num-1)+j];
		in[getID(i, j+(F[i*(num-1)+j]>0))]++;
	}

	rep(i, num-1) rep(j, num) if (fabs(F[(num-1+i)*num+j])>exp)
	{
		G[getID(i,j)][1] = F[(num-1+i)*num+j];
		G[getID(i+1,j)][3] = -F[(num-1+i)*num+j];
		in[getID(i+(F[(num-1+i)*num+j]>0), j)]++;
	}

	G[getID(inputID[0],0)][0] = -F[EDGENUM-5];
	C[getID(inputID[0],0)][0] = inputConcen[0];

	G[getID(inputID[1],0)][0] = -F[EDGENUM-4];
	C[getID(inputID[1],0)][0] = inputConcen[1];

	G[getID(outputID[0],num-1)][2] = F[EDGENUM-3];
	G[getID(outputID[1],num-1)][2] = F[EDGENUM-2];
	G[getID(outputID[2],num-1)][2] = F[EDGENUM-1];

	queue<int> q;

	rep(i, num) rep(j, num) if (in[getID(i,j)] == 0) q.push(getID(i,j));
	while (!q.empty())
	{
		int o = q.front(); q.pop();
		nodeCal(o);
		int x = o/num, y = o%num;
		if (y && G[o][0]>exp)
		{
			C[getID(x,y-1)][2] = C[o][0];
			if (--in[getID(x,y-1)] == 0) q.push(getID(x,y-1));
		}
		if (x<num-1 && G[o][1]>exp)
		{
			C[getID(x+1,y)][3] = C[o][1];
			if (--in[getID(x+1,y)] == 0) q.push(getID(x+1,y));
		}
		if (y<num-1 && G[o][2]>exp)
		{
			C[getID(x,y+1)][0] = C[o][2];
			if (--in[getID(x,y+1)] == 0) q.push(getID(x,y+1));
		}
		if (x && G[o][3]>exp)
		{
			C[getID(x-1,y)][1] = C[o][3];
			if (--in[getID(x-1,y)] == 0) q.push(getID(x-1,y));
		}
	}

	//==============

	// qDebug("Start");

	rep(i, num) rep(j, num-1) if (R[i*(num-1)+j])
		L[getID(i,j)][2] = L[getID(i,j+1)][0] = 1;

	rep(i, num-1) rep(j, num) if (R[(num-1+i)*num+j])
		L[getID(i,j)][1] = L[getID(i+1,j)][3] = 1;

	L[getID(inputID[0],0)][0] = 1;
	L[getID(inputID[1],0)][0] = 1;

	rep(i, num*num) q.push(i);
	while (!q.empty())
	{
		int o=q.front(); q.pop();
		nodeCal2(o);
		int x = o/num, y = o%num;
		if (y && L[o][0] && C[getID(x,y-1)][2]<-0.1 && C[o][0]>-0.1)
		{
			C[getID(x,y-1)][2] = C[o][0];
			q.push(getID(x,y-1));
		}
		if (x<num-1 && L[o][1] && C[getID(x+1,y)][3]<-0.1 && C[o][1]>-0.1)
		{
			C[getID(x+1,y)][3] = C[o][1];
			q.push(getID(x+1,y));
		}
		if (y<num-1 && L[o][2] && C[getID(x,y+1)][0]<-0.1 && C[o][2]>-0.1)
		{
			C[getID(x,y+1)][0] = C[o][2];
			q.push(getID(x,y+1));
		}
		if (x && L[o][3] && C[getID(x-1,y)][1]<-0.1 && C[o][3]>-0.1)
		{
			C[getID(x-1,y)][1] = C[o][3];
			q.push(getID(x-1,y));
		}
	}

	// qDebug("End");

	vector<double> ans;

	rep(i, num) rep(j, num-1)
		ans.push_back(C[getID(i,j)][2]);

	rep(i, num-1) rep(j, num)
		ans.push_back(C[getID(i,j)][1]);

	ans.push_back(ic0); ans.push_back(ic1);
	rep(i, 3)
		ans.push_back(C[getID(outputID[i],num-1)][2]);

	return ans;
}
