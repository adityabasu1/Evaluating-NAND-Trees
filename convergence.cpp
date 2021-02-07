#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    double p = 0.5; 

    int n = 15,i;

    cout<<p<<endl;
    for(i=1; i<n; i++)
    {
        p = 1 - pow(p,2); // evaluates P1(n)
        cout<<p<<endl;
    }

    return 0;
}

