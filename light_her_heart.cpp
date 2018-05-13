#include <iostream>
#include <ctime>
#include <string>
using namespace std;
void delay(double interval)
{       
    clock_t start_time;
    start_time = clock();
    while ((clock()- start_time) <interval * CLOCKS_PER_SEC){}
}
double sqrt(double n){
    double EPS = 0.000001;
    double x = n;
    double xpre;
    while(true){
        xpre = x;
        x = x - x/2.0 + n/(2.0*x);
        if (x-xpre < EPS && x-xpre > -EPS) break;
    }
    return x;
}
double f(double x, double y, double z){
    double a = x*x + 9.0/4*y*y + z*z - 1;
    return a*a*a - x*x*z*z*z - 9.0/80*y*y*z*z*z;
}
double h(double x, double z){
    for(double i=1.0; i>0.0; i-=0.001){
        if(f(x, i, z) <= 0){
            return i;
        }
    }
    return 0.0;
}
int main()
{
    double v, y0, ny, nx, nz, nd, d;
    string s;
    for(double z=1.5; z>-1.5; z-=0.1){
        for(double x=-1.5; x<1.5; x+=0.05){
            v = f(x, 0, z);
            if (v<=0){
                y0 = h(x, z);
                ny = 0.01;
                nx = h(x + ny, z) - y0;
                nz = h(x, z + ny) - y0;
                nd = 1.0/sqrt(nx*nx+ny*ny+nz*nz);
                d = (nx + ny - nz)*nd*0.5 + 0.5;
                string s = ".:-=+*#%@";
                cout<<s[(int)(5*d)];
                delay(0.0001);
            }
            else
                cout<<' ';

        }
        delay(0.05);
        cout<<endl;
    }

    return 0;
}