#include <iostream>
#include <cmath>
#include <fstream>

template<typename State,typename T, typename RHS,typename Callback>
auto solve_euler(State y0,T t0,T t1,T h, RHS f, Callback cb)
{

    T t=t0; State y=y0;

    while(t < t1)
    {
        if(t + h > t1){ h = t1 - t; }

        y = y + h * f(t, y);
        t = t + h; cb(t,y);
    }

    return y;
}

template<typename State, typename T, typename RHS, typename Callback>
auto solve_rk4(State y0, T t0, T t1, T h, RHS f, Callback cb)
{
    T t = t0; State y = y0;

    while(t < t1)
    {
        if(t + h > t1){ h = t1 - t; }

        State k1 = f(t, y);
        State k2 = f(t + h * (T)0.5, y + (h * (T)0.5) * k1);
        State k3 = f(t + h * (T)0.5, y + (h * (T)0.5) * k2);
        State k4 = f(t + h, y + h * k3);

        y = y + (k1 + k4 + (T)2 * (k2 + k3)) * (h / (T)6);
        t = t + h; cb(t, y);
    }
    return y;
}


//Megpróbáltam, de sajnos rosszabb eredményeket ad, mint az rk4.
template<typename State, typename T, typename RHS, typename Callback>
auto solve_rkf(State y0, T t0, T t1, T h0,State eps, RHS f, Callback cb)
{
    T t = t0; State y = y0; State z = y0; T h=h0;
    int i=0;
    
    if(t + h > t1){ h = t1 - t; }

    while(i != 1)
    {
        while(t < t1)
        {
            State k1 = h * f(t, y);
            State k2 = h * f(t + (T)0.25 * h, y + (T)0.25 * k1);
            State k3 = h * f(t + (((T)3)/((T)8)) * h, y + (((T)13)/((T)32)) * k1 + (((T)9)/((T)32)) * k2);
            State k4 = h * f(t + (((T)12)/((T)13)) * h, y + (((T)1932)/((T)2197)) * k1 - (((T)7200)/((T)2197)) * k2 + (((T)7296)/((T)2197)) * k3);
            State k5 = h * f(t + h, y + (((T)439)/((T)216)) * k1 - (T)8 * k2 + (((T)3680)/((T)513)) * k3 - (((T)845)/((T)4104)) * k4);
            State k6 = h * f(t + (T)0.5 * h, y - (((T)8)/((T)27)) * k1 + (T)2 * k2 - (((T)3544)/((T)2565)) * k3 + (((T)1859)/((T)4104)) * k4 - (((T)11)/((T)40)) * k5);

            y = y + (((T)25)/((T)216)) * k1 + (((T)1408)/((T)2565)) * k3 + (((T)2197)/((T)4101)) * k4 - (T)0.2 * k5;
            z = z + (((T)16)/((T)135)) * k1 + (((T)6656)/((T)12825)) * k3 + (((T)28561)/((T)56430)) * k4 - (((T)9)/((T)50)) * k5 + (((T)2)/((T)55)) * k6;

            t = t + h; cb(t, y, z);
        }
        T diff = std::abs(y-z);
        if(eps>=diff){ i = 1; }
        if(eps<diff)
        {   
            T s = std::pow((eps*h)/((T)2*diff),(T)0.25);
            h = s * h;
        }
    }
    return y;
}

template<typename State, typename T>
auto solve_analitic(State y0, T t0, T t1)
{
    T c1=std::atan(y0)-t0;

    State y=std::tan(t1+c1);

    return y;
}

template<typename T>
auto fun(T t,T y){return 1+y*y;}

template<typename T>
void cb(T t,T y){return;}

template<typename T>
void cb2(T t,T y1,T y2){return;}

int main(int, char**) 
{
    std::ofstream file;
    file.open("Integral.txt");

    std::cout<<"t\tEuler\tRK4\tAnalitikus\tRKF45\n";

    /*file<<"Euler\tRK4\tAnalitikus\n";
    std::cout<<"t\tEuler\tRK4\tAnalitikus\n";*/
    
    double t;
    double y0=0;
    double t0=0;
    double h=0.01;
    //double eps=0.001;

    for(t=0.4;t<=1.2;t+=0.01)
    {
        double y_Euler=solve_euler<double>(y0,t0,t,h,fun<double>,cb<double>);
        double y_rk4=solve_rk4<double>(y0,t0,t,h,fun<double>,cb<double>);
        double y_a=solve_analitic<double>(y0,t0,t);
        //double y_rkf45=solve_rkf<double>(y0,t0,t,h,eps,fun<double>,cb2<double>);

        /*std::cout<<t<<"\t"<<y_Euler<<"\t"<<y_rk4<<"\t"<<y_a<<"\t"<<y_rkf45<<"\n";
        file<<y_Euler<<"\t"<<y_rk4<<"\t"<<y_a<<"\t"<<y_rkf45<<"\n";*/

        std::cout<<t<<"\t"<<y_Euler<<"\t"<<y_rk4<<"\t"<<y_a<<"\n";
        file<<y_Euler<<","<<y_rk4<<","<<y_a<<"\n";
    }

    file.close();

    return 0;
}
