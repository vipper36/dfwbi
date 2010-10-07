#include "distance.h"
#include <string.h>
#include <malloc.h>
#include <vector>
#include <algorithm>

//****************************
// Get minimum of three values
//****************************

int Distance::Minimum (int a, int b, int c)
{
     int mi;

     mi = a;
     if (b < mi) {
	  mi = b;
     }
     if (c < mi) {
	  mi = c;
     }
     return mi;

}

//**************************************************
// Get a pointer to the specified cell of the matrix
//************************************************** 

int *Distance::GetCellPointer (int *pOrigin, int col, int row, int nCols)
{
     return pOrigin + col + (row * (nCols + 1));
}

//*****************************************************
// Get the contents of the specified cell in the matrix 
//*****************************************************

int Distance::GetAt (int *pOrigin, int col, int row, int nCols)
{
     int *pCell;

     pCell = GetCellPointer (pOrigin, col, row, nCols);
     return *pCell;

}

//*******************************************************
// Fill the specified cell in the matrix with the value x
//*******************************************************

void Distance::PutAt (int *pOrigin, int col, int row, int nCols, int x)
{
     int *pCell;

     pCell = GetCellPointer (pOrigin, col, row, nCols);
     *pCell = x;

}

//*****************************
// Compute Levenshtein distance
//*****************************

int Distance::LD (const char *s, const char *t)
{
     int *d; // pointer to matrix
     int n; // length of s
     int m; // length of t
     int i; // iterates through s
     int j; // iterates through t
     char s_i; // ith character of s
     char t_j; // jth character of t
     int cost; // cost
     int result; // result
     int cell; // contents of target cell
     int above; // contents of cell immediately above
     int left; // contents of cell immediately to left
     int diag; // contents of cell immediately above and to left
     int sz; // number of cells in matrix

     // Step 1	

     n = strlen (s);
     m = strlen (t);
     if (n == 0) {
	  return m;
     }
     if (m == 0) {
	  return n;
     }
     sz = (n+1) * (m+1) * sizeof (int);
     d = (int *) malloc (sz);

     // Step 2

     for (i = 0; i <= n; i++) {
	  PutAt (d, i, 0, n, i);
     }

     for (j = 0; j <= m; j++) {
	  PutAt (d, 0, j, m, j);
     }

     // Step 3

     for (i = 1; i <= n; i++) {

	  s_i = s[i-1];

	  // Step 4

	  for (j = 1; j <= m; j++) {

	       t_j = t[j-1];

	       // Step 5

	       if (s_i == t_j) {
		    cost = 0;
	       }
	       else {
		    cost = 1;
	       }

	       // Step 6 

	       above = GetAt (d,i-1,j, n);
	       left = GetAt (d,i, j-1, n);
	       diag = GetAt (d, i-1,j-1, n);
	       cell = Minimum (above + 1, left + 1, diag + cost);
	       PutAt (d, i, j, n, cell);
	  }
     }

     // Step 7

     result = GetAt (d, n, m, n);
     free (d);
     return result;
	
}
int Distance::LD(const std::string s, const std::string t)
{
     size_t i=0,j=s.length(),k=t.length();
     if (j == 0) {
	  return k;
     }
     if (k == 0) {
	  return j;
     }
     int minlen=std::min(j,k);
     while(s[i]==t[i]&&i<minlen)
     {
	  i++;
     }
     while(s[j]==t[k]&&j>i&&k>i)
     {
	  j--;
	  k--;
     }
     std::string source=s.substr (i,j);
     std::string target=t.substr (i,k);
     const int n = source.length();
     const int m = target.length();
     if (n == 0) {
	  return m;
     }
     if (m == 0) {
	  return n;
     }

     // Good form to declare a TYPEDEF

     typedef std::vector< std::vector<int> > Tmatrix; 

     Tmatrix matrix(n+1);

     // Size the vectors in the 2.nd dimension. Unfortunately C++ doesn't
     // allow for allocation on declaration of 2.nd dimension of vec of vec

     for (int i = 0; i <= n; i++) {
	  matrix[i].resize(m+1);
     }

     // Step 2

     for (int i = 0; i <= n; i++) {
	  matrix[i][0]=i;
     }

     for (int j = 0; j <= m; j++) {
	  matrix[0][j]=j;
     }

     // Step 3

     for (int i = 1; i <= n; i++) {

	  const char s_i = source[i-1];

	  // Step 4

	  for (int j = 1; j <= m; j++) {

	       const char t_j = target[j-1];

	       // Step 5

	       int cost;
	       if (s_i == t_j) {
		    cost = 0;
	       }
	       else {
		    cost = 1;
	       }

	       // Step 6

	       const int above = matrix[i-1][j];
	       const int left = matrix[i][j-1];
	       const int diag = matrix[i-1][j-1];
	       int cell = std::min( above + 1, std::min(left + 1, diag + cost));

	       // Step 6A: Cover transposition, in addition to deletion,
	       // insertion and substitution. This step is taken from:
	       // Berghel, Hal ; Roach, David : "An Extension of Ukkonen's 
	       // Enhanced Dynamic Programming ASM Algorithm"
	       // (http://www.acm.org/~hlb/publications/asm/asm.html)

	       if (i>2 && j>2) {
		    int trans=matrix[i-2][j-2]+1;
		    if (source[i-2]!=t_j) trans++;
		    if (s_i!=target[j-2]) trans++;
		    if (cell>trans) cell=trans;
	       }

	       matrix[i][j]=cell;
	  }
     }

     // Step 7

     return matrix[n][m];
}

