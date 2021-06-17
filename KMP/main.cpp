#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define  endl  "\n"
using namespace std;
int const N = 1e6 + 5;
char *text = new char[N], *pat = new char[N];
int n // size of text
,m // size of pattern
,sz ;// number of occurrence of the given pattern at text

int *fail = new int[N] // to save the failure links of pattern
,*ids = new int[N]; // to save the indices that the pattern exist at

void LongestLen(int &len, char x, int indx)
{
   // return the length of the longest prefix that also a suffix that end at index
    while (len && x != pat[len]) {
      
        len = fail[len - 1];
        cout << "(t" << indx << ", p" << len << ")" << endl;
    }
    len = len + (pat[len] == x);


}

void BuildFailure()
{

    fail[0] = 0;
    // compute the failure array for the pattern
    for (int i = 1; i < m; ++i)
    {
       
        int len = fail[i - 1];
        LongestLen(len, pat[i], i);
        fail[i] = len;
    }
   
}

void Search() {
    int len = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "(t" << i << ", p" << len << ")" << endl;


        LongestLen(len, text[i], i);


        if (len == m) {
            ids[sz++] = i + m - 1;
        }
    }
}
