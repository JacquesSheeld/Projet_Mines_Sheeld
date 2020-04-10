#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

int main()
{
    ifstream f("arkw.p3", ios::binary | ios::in);
    char c;
    char a;
    while (f.get(c))
    {
        for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
            cout << ((c >> i) & 1);
        a = getchar();
    }


}