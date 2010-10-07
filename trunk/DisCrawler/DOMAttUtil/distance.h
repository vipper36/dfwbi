#ifndef __EDIT_DISTANCE_H__
#define __EDIT_DISTANCE_H__
#include <string> 
class Distance
{
public:
	int LD (const char*s, const char*t);
	int LD (const std::string s, const std::string t);	
private:
	int Minimum (int a, int b, int c);
	int *GetCellPointer (int *pOrigin, int col, int row, int nCols);
	int GetAt (int *pOrigin, int col, int row, int nCols);
	void PutAt (int *pOrigin, int col, int row, int nCols, int x);
}; 

#endif
