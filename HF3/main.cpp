#include <iostream>
#include <fstream>
#include <cmatH>

template<typename T>
T f(T x)
{
    T F=900;
    T q=1.8;
    T a=200;
    T h0=35;

    return F/q*(std::cosh((q/F)*x)-std::cosh((q*a)/(2*F)))+h0;
}

template<typename T>
T S(T x,T h=0.001)
{
    T f1=f(x+2*h);
    T f2=f(x+h);
    T f3=f(x-h);
    T f4=f(x-2*h);

    return (-f1+8*f2-8*f3+f4)/(12*h);
}

template<typename T>
T df(T x,T h=0.001)
{
    T S1=S(x,h/2);
    T S2=S(x,h);

    return (16*S1-S2)/15;

}

template<typename T>
T d_arc(T x, T h=0.001)
{
    return std::sqrt(1+std::pow(df(x,h),2));
}

template<typename F, typename T>
T integrate_M(F fun,T A,T B,int n, T h=0.001)
{  
    T dx=(B-A)/n;
    T integral=0;

    int i;
    T m_i=A+0.5*dx;

    for(i=0;i<n;i++)
    {
        integral+=fun(m_i,h)*dx;
        m_i+=dx;
    }

    return integral;
}

template<typename F, typename T>
T integrate_T(F fun,T A,T B,int n, T h=0.001)
{
    
    T dx=(B-A)/n;
    T integral=fun(A,h)*dx/2;

    int i;
    T x_i=A;

    for(i=1;i<n;i++)
    {
        x_i+=dx;
        integral+=fun(x_i,h)*dx;
    }

    return integral;
}


template<typename F, typename T>
T integrate_S(F fun,T A,T B,int n, T h=0.001)
{
    return (2*integrate_M(fun,A,B,n,h)+integrate_T(fun,A,B,n,h))/3;
}


int main(int, char**) 
{
    int n=1000;

    double a=200;

    double A=-a/2;
    double B=a/2;

    double arc_M=integrate_M(d_arc<double>,A,B,n);
    double arc_T=integrate_T(d_arc<double>,A,B,n);
    double arc_S=integrate_S(d_arc<double>,A,B,n);

    std::ofstream file;
    file.open("ivhossz.txt");
    file<<arc_M<<","<<arc_T<<","<<arc_S;
    file.close();

    std::cout<<"Ivhossz kozeppontos modszerrel szamolva:\n"<<arc_M<<"\n\n";
    std::cout<<"Ivhossz trapez modszerrel szamolva:\n"<<arc_T<<"\n\n";
    std::cout<<"Ivhossz 1/3 Simpson szabaly segitsegevel szamolva:\n"<<arc_S<<"\n\n";
    std::cout<<"Eredmenyek fajlba irva\n";

    std::system("pause");
    return 0;
}
