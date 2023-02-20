#include <iostream>
#include "luz.h"

using namespace std;

const int TIME_TO_SLEEP = 10;

int main()
{

    Luz luz1(1, 2);
    int ident[2];
    luz1.get_ident(ident);


    cout << "PLOT: " << ident[0] << endl;
    cout << "HIGHT: " << ident[1] << endl;
    cout << "STATUS: " << luz1.get_status() << endl;
    cout << "TIME: " << luz1.get_time() << endl;

    luz1.set_status(true);
    cout << "PLOT: " << ident[0] << endl;
    cout << "HIGHT: " << ident[1] << endl;
    cout << "STATUS: " << luz1.get_status() << endl;
    cout << "TIME: " << luz1.get_time() << endl;

    while(luz1.get_time() < 0.16){}
    cout << "TIME: " << luz1.get_time() << endl;

    return 0;
}
