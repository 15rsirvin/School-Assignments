#include <iostream>
using namespace std;

double eps = 1.0;
double lastval;

int main(){
    while(eps+1 != 1){
        lastval = eps;
        eps = eps/2;
              
    }
    cout<<"Value:"<<lastval<<endl;

    return 0;
}
//epsilon = 2.22045e-16
