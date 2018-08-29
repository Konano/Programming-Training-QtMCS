#include <cstdio>
#include <cmath>
#include <algorithm>

#include "calculate.h"

using namespace std;

#define rep(i, r) for(int i=0; i<r; i++)

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
	Matirx[num*num][num*num+2] -= inputFlow[0];
	Matirx[num*num][num*num] += 1.0/R[EDGENUM-5];
	Matirx[num*num][getID(inputID[0],0)] -= 1.0/R[EDGENUM-5];

	Matirx[num*num+1][num*num+2] -= inputFlow[1];
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
	rep(i, num) rep(j, num-1) if (R[i*(num-1)+j]>exp) ans.push_back(fabs(V[getID(i,j)]-V[getID(i,j+1)])); else ans.push_back(0);
	rep(i, num-1) rep(j, num) if (R[num*(num-1)+i*num+j]>exp) ans.push_back(fabs(V[getID(i,j)]-V[getID(i+1,j)])); else ans.push_back(0);
	ans.push_back(fabs(V[num*num]-V[getID(inputID[0],0)]));
	ans.push_back(fabs(V[num*num+1]-V[getID(inputID[1],0)]));
	ans.push_back(fabs(V[getID(outputID[0],num-1)]));
	ans.push_back(fabs(V[getID(outputID[1],num-1)]));
	ans.push_back(fabs(V[getID(outputID[2],num-1)]));
	return ans;
}
