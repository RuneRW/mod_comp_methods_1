#include "FUN_class.hpp"

int main(int, char**) 
{
    std::vector<double> y;
    int n=100000;
    double x0=0.0;
    double x1=100;
    double h=(x1-x0)/n;

    int i;
    for(i=0;i<n;i++)
    {
        double x=x0+i*h;
        double y_i=std::sin(x);
        y.push_back(y_i);
    }

    std::cout<<"Demonstrating the functionalities of FUN Class Objects via the sin function\n\n";
    std::string f_name="f.dat";
    FUN<double> f_sin={x0,x1,y};
    std::cout<<"Function class object created! Writing to file "<<f_name<<"...\n";
    f_sin.to_FILE(f_name);
    int N=10;
    std::cout<<"Writing complete!\nPrinting first "<<N<<" lines\n";
    f_sin.print(N);

    std::string df_name="df.dat";
    FUN<double> df=f_sin.diff();
    std::cout<<"\nDerivative created! Writing to file "<<f_name<<"...\n";
    df.to_FILE(df_name);
    std::cout<<"Writing complete!\nPrinting first "<<N<<" lines\n";
    df.print(N);

    std::string F_name="f_integral.dat";
    int C=-1;
    FUN<double> F=f_sin.integral(C);
    std::cout<<"\nPrimitive function created with C="<<C<<"! Writing to file "<<F_name<<"...\n";
    F.to_FILE(F_name);
    std::cout<<"Writing complete!\nPrinting first "<<N<<" lines\n";
    F.print(N);

    double pi=3.14159265358979323846;
    double a=pi/2;
    double b=3*pi/2;

    double Y=f_sin.integrate(a,b);
    double y_1=f_sin.value(a);
    double y_2=f_sin.interpolate(b);

    std::cout<<"\nDefinite integral from a="<<a<<" to b="<<b<<":\n"<<Y<<"\n\nFunction value at x="<<a<<":\n"<<y_1<<"\nFunction value at x="<<b<<":\n"<<y_2<<"\n\n";


    std::vector<double> zero=f_sin.where(0);
    int len_zero=static_cast<int>(zero.size());

    std::cout<<"\nPrinting all solutions for f(x)=0:\n";
    for(i=0;i<len_zero;i++)
    {
        std::cout<<zero[i]<<","<<f_sin.value(zero[i])<<"\n";
    }

    std::cout<<"\n\n";

    std::cout<<"\nPrinting all local minimum places and values:\n";
    std::vector<double> mins=f_sin.local_mins();
    int len_mins=static_cast<int>(mins.size());

    for(i=0;i<len_mins;i++)
    {
        std::cout<<mins[i]<<","<<f_sin.value(mins[i])<<"\n";
    }

    std::cout<<"\n\n";

    std::cout<<"\nPrinting all global maximum places and values:\n";
    std::vector<double> maxs=f_sin.maxs();
    int len_maxs=static_cast<int>(maxs.size());

    for(i=0;i<len_maxs;i++)
    {
        std::cout<<maxs[i]<<","<<f_sin.value(maxs[i])<<"\n";
    }
    std::cout<<"\n\n\n";
    std::system("pause");
}
