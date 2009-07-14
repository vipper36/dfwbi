#ifndef __EDIT_DISTANCE_H__
#define __EDIT_DISTANCE_H__

class Distance
{
public:
	int LD (const char*s, const char*t);
private:
	int Minimum (int a, int b, int c);
	int *GetCellPointer (int *pOrigin, int col, int row, int nCols);
	int GetAt (int *pOrigin, int col, int row, int nCols);
	void PutAt (int *pOrigin, int col, int row, int nCols, int x);
}; 

#endif
