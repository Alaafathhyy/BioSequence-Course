#include <iostream>
#include <cstdio>
#include <algorithm>

#define  endl  "\n"
using namespace std;
int const N = 1e6 + 5;
char *str = new char[N];
int n;
int *id = new int[N];
int *vals = new int[N];
int *temp = new int[N];

void writeOnFile(const char FileName[]) {
// this function takes file name and write  id array  on it

    FILE *pFile;
    pFile = fopen(FileName, "w");
    // iterate over the global id which it hold the answer
    for (int i = 0; i < n; ++i)
        fprintf(pFile, "%d ", id[i]);

    fclose(pFile);
}


void ReadGenome(const char FileName[]) {
    FILE *pFile;
    pFile = fopen(FileName, "r");
    int sz = 0;
    fgets(str, 100, pFile); // skip the  first line which is the id of genome
    while (true) {
        unsigned char x = getc(pFile);
        if (x == '>' || sz >= N)break; // until the second genome or we reach the maximum limit of memory
        if (x != '\n') str[sz++] = x;
    }

    n = sz;

}

void Read1E4Char(const char FileName[]) {
    FILE *pFile;
    pFile = fopen(FileName, "r");
    int sz = 0;

    fgets(str, 100, pFile); // skip the first line which is the id of genome
    while (sz < (int) 1e4) {
        // iterate over the file char by char
        unsigned char x = getc(pFile);
        if (x != '\n') str[sz++] = x;
    }
    n = sz;

}

bool cmp(int i, int j) {
    // comparison depend on true if the first one is lexicographical minmum than the other
    for (; i < n && j < n; j++, i++) {
        if (str[i] == str[j])continue; //the two string are the same till ith character
        if (str[i] < str[j])return 1;
        else return 0;
    }
    // if the first is prefix of the second
    return j < n;
}

void NaiveSolution() {

    // init the inidices of the start positions of all substrings
    for (int i = 0; i < n; i++)
        id[i] = i;


    // sort the array of id on lexicographically order
    sort(id, id + n, cmp);
}

int idx;

bool cmp2(int &suffix1, int &suffix2) {
    // i,j are the suffix of id i and j
    //sort depend on value in case of the values aren't equal
    //other wise sort on the idxth val
    if (vals[suffix1] == vals[suffix2]) {
        if (suffix1 + idx < n && suffix2 + idx < n) // make sure doesn't access out of bound
            return vals[suffix1 + idx] < vals[suffix2 + idx];
        else return suffix2 + idx < n; // if the first suffix is prefix of the second one
    }
    return vals[suffix1] < vals[suffix2];
}


void PerfixDoubling() {
    idx = 0;
    // intially give all suffix an id, and value which is equal to the value of char at index i at string
    for (int i = 0; i < n; ++i) {
        id[i] = i;
        vals[i] = str[i];
    }
    // first sort depend on the first character
    sort(id, id + n, cmp2);

    idx = 1;
    temp[0] = temp[n - 1] = 0;
    /* intially the first and last suffix equal zero
    *to make sure it enters the while loop and the order of the first suffix is 0
    */
    // untill all the suffixs take a unique id
    for (; temp[n - 1] != n - 1; idx += idx) {

        sort(id, id + n, cmp2);

        /*
        * update the value for each suffix at temporary array which name is temp
        *two suffix take the same value if they value and the idxth charater of them  are the same
        * other wise the current suffix take the previousValue+1
        */
        for (int i = 1; i < n; i++) {
            /* updateing the values for each suffix at temporary array to make the compare works correctly
             * as function compare depend on the previous value  for each suffix
             * */
            temp[i] = temp[i - 1] + (int) cmp2(id[i - 1], id[i]);

        }
        // update tha values of suffixs

        for (int i = 0; i < n; ++i)
            vals[id[i]] = temp[i];

    }

}

void Output(bool flag) {
    // determine which function call
    if (flag) NaiveSolution();
    else PerfixDoubling();

    // id is the function that we save answer at
    for (int i = 0; i < n; ++i)
        cout << id[i] << " ";

    cout << endl;

}

int main() {
      ios_base::sync_with_stdio(0), cin.tie(0);

    Read1E4Char("input");

    NaiveSolution(); // time for naive is 0.009 sec for 1e4 Char
    writeOnFile("output1");

    /*
     * naive solution is faster  than perfix doubling with
    * a fewer secs because the GENOME is the best case so it runs alomst at o(n)
    */

    PerfixDoubling();// time for  perifxDoubling is 0.015 sec for 1e4 Char

    writeOnFile("output2");


    ReadGenome("input");
    PerfixDoubling(); // time for first genome is 0.527
    writeOnFile("output3");



    //   50 test case on a simple strings

    n = 21;
    str = "hqghumeaylnlfdxfircvs";
    Output(0); // for PerfixDoubling
    Output(1); // for NaiveSolution

    n = 12;
    str = "xggbwkfnqdux";
    Output(0);
    Output(1);


    n = 32;
    str = "fnfozvsrtkjprepggxrpnrvystmwcysy";
    Output(0);
    Output(1);

    n = 14;
    str = "cqpevikeffmzni";
    Output(0);
    Output(1);

    n = 14;
    str = "kkasvwsrenzkyc";
    Output(0);
    Output(1);


    n = 19;
    str = "fxtlsgypsfadpooefxz";
    Output(0);
    Output(1);

    n = 37;
    str = "coejuvpvaboygpoeylfpbnpljvrvipyamyehw";
    Output(0);
    Output(1);

    n = 10;
    str = "nqrqpmxujj";
    Output(0);
    Output(1);

    n = 31;
    str = "oovaowuxwhmsncbxcoksfzkvatxdknl";
    Output(0);
    Output(1);

    n = 14;
    str = "jyhfixjswnkkuf";
    Output(0);
    Output(1);

    n = 29;
    str = " uxxzrzbmnmgqooketlyhnkoaugzqr";
    Output(0);
    Output(1);

    n = 18;
    str = "ddiuteiojwayyzpvsc";
    Output(0);
    Output(1);

    n = 16;
    str = "psajlfvgubfaaovl";
    Output(0);
    Output(1);

    n = 21;
    str = "ylntrkdcpwsrtesjwhdiz";
    Output(0);
    Output(1);

    n = 38;
    str = "obzcnfwlqijtvdwvxhrcbldvgylwgbusbmborx";
    Output(0);
    Output(1);

    n = 35;
    str = "lhcsmpxohgmgnkeufdxotogbgxpeyanfetc";
    Output(0);
    Output(1);

    n = 12;
    str = "kepzshkljugg";
    Output(0);
    Output(1);

    n = 34;
    str = "ekjdqzjenpevqgxiepjsrdzjazujllchhb";
    Output(0);
    Output(1);

    n = 21;
    str = "qmkimwzobiwybxduunfsk";
    Output(0);
    Output(1);


    n = 24;
    str = "rsrtekmqdcyzjeeuhmsrqcoz";
    Output(0);
    Output(1);

    n = 20;
    str = "jipfioneeddpszrnavym";
    Output(0);
    Output(1);


    n = 32;
    str = "tatbdzqsoemuvnpppsuacbazuxmhecth";
    Output(0);
    Output(1);


    n = 27;
    str = "egrpunkdmbppweqtgjoparmowzd";
    Output(0);
    Output(1);


    n = 16;
    str = "yoxytjbbhawdydcp";
    Output(0);
    Output(1);


    n = 21;
    str = "jbxphoohpkwqyuhrqzhnb";
    Output(0);
    Output(1);


    n = 35;
    str = "fuvqnqqlrzjpxiogvliexdzuzosrkrusvoj";
    Output(0);
    Output(1);


    n = 31;
    str = "rzmwzpowkjilefraamdigpnpuuhgxpq";
    Output(0);
    Output(1);


    n = 35;
    str = "jwjmwaxxmnsnhhlqqrzudltfzotcjtnzxug";
    Output(0);
    Output(1);


    n = 31;
    str = "sdsmzcnockvfajfrmxothowkbjzwucw";
    Output(0);
    Output(1);


    n = 15;
    str = "jfrimpmyhchzriw";
    Output(0);
    Output(1);


    n = 28;
    str = "barxbgfcbceyhjugixwtbvtrehbb";
    Output(0);
    Output(1);


    n = 38;
    str = "pxifbxvfbcgkcfqckcotzgkubmjrmbsztsshfr";
    Output(0);
    Output(1);


    n = 26;
    str = "efwsjrxjhguzyupzwweiqurpix";
    Output(0);
    Output(1);


    n = 26;
    str = "qflduuveoowqcudhnefnjhaimu";
    Output(0);
    Output(1);

    n = 14;
    str = "zfskuiduburisw";
    Output(0);
    Output(1);


    n = 27;
    str = "strbrecuykabfcvkdzeztoidukuhjz";
    Output(0);
    Output(1);


    n = 18;
    str = "fczzzbfkqdpqzikfob";
    Output(0);
    Output(1);


    n = 34;
    str = "cdhthxdjgkjelrlpaxamceroswitdptpcc";
    Output(0);
    Output(1);


    n = 13;
    str = "ifkeljytihrcq";
    Output(0);
    Output(1);


    n = 38;
    str = "ybnefxnxvgzedyyhngycdrudmphmeckotrwosp";
    Output(0);
    Output(1);

    n = 32;
    str = "fghfozqvlqfxwwkmfxdyygmdcaszsgov";
    Output(0);
    Output(1);

    n = 18;
    str = "odkjghcwmbmxrmhuyf";
    Output(0);
    Output(1);

    n = 18;
    str = "qgajqkcklznayxqkqo";
    Output(0);
    Output(1);

    n = 28;
    str = "zwmyubzazcpkhktkydzivcuypurf";
    Output(0);
    Output(1);

    n = 22;
    str = "bisgekyrgzvxdhpoamvafy";
    Output(0);
    Output(1);

    n = 11;
    str = "arxsvkhtqdi";
    Output(0);
    Output(1);

    n = 17;
    str = "ersigbhzjzujxmmys";
    Output(0);
    Output(1);

    n = 31;
    str = "naraewkegjccvhhrjvbjtsqdjootgpk";
    Output(0);
    Output(1);

    n = 20;
    str = "ACTACTGCTCAATTTTTTTA";
    Output(0);
    Output(1);
    n = 12;
    str = "abcdeaabcdea";
    Output(0);
    n = 11;
    str = "abedeaacdea";
    Output(0);
    delete[]id;
    delete[] str;
    delete[] vals;
    delete[] temp;
}
