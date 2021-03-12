#include <iostream>

template<typename T,typename F,typename G>

T Newton(F f, G dfdx, T x0)
{
    T x=x0;
    int i;

    for(i=0;i<10;i++)
    {
        x-=f(x)/dfdx(x);
    }

    return x;
}

int main()
{
    double a;
    a=Newton([](double x){return x*x - 612.0;},[](double x){return 2.0*x;},10.0);

    std::cout << "a=" << a << std::endl;

    return 0;
}