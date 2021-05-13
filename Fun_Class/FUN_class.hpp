#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

template<typename T>
class FUN
{
    public:
    T x0;
    T x1;
    std::vector<T> y;
    

    int size(void)
    {
        return static_cast<int>(y.size());
    }

    T h(void)
    {
        int n=this->size();
        return (x1-x0)/(n-1);
    }


    T interpolate(T x)
    {
        T h=this->h();

        int i=1;
        T x_1=x0+h;

        while(x_1<x)
        {
            x_1+=h; 
            i++;
        }

        T x_0=x_1-h;

        T& y_0=y[i-1];
        T& y_1=y[i];

        T Y=y_0+(x-x_0)*(y_1-y_0)/(x_1-x_0);


        return Y;
    }

    T value(T x)
    {
        return this->interpolate(x);
    }


    T xi(int i)
    {
        T h=this->h();
        return x0+i*h;
    }

    std::vector<T> x(void)
    {
        int n=this->size();
        std::vector<T> x;

        int i;
        for(i=0;i<n;i++)
        {
            x.push_back(this->xi(i));
        }
        return x;
    }


    int imin_first(void)
    {
        std::vector<T>::iterator result=std::min_element(y.begin(),y.end());
        int i=(int) std::distance(y.begin(),result);

        return i;
    }

    int imax_first(void)
    {
        std::vector<T>::iterator result=std::max_element(y.begin(),y.end());
        int i=(int) std::distance(y.begin(),result);

        return i;
    }

    T xmin_first(void)
    {
        int i=this->imin_first();
        
        return this->xi(i);
    }

    T xmax_first(void)
    {
        int i=this->imax_first();

        return this->xi(i);
    }

    T ymin(void)
    {
        int i=this->imin_first();
        return y[i];
    }

    T ymax(void)
    {
        int i=this->imax_first();
        return y[i];
    }


    std::vector<int> where_i(T yi)
    {
        int n=this->size();
        std::vector<int> Vi;

        T upper=abs(y[0]-y[1])/2;
        if(equals<T>(y[0],yi,upper,upper)){Vi.push_back(0);}
    
        int i;
        for(i=1;i<n-1;i++)
        {
            T lower=abs(y[i]-y[i-1])/2;
            T upper=abs(y[i]-y[i+1])/2;
            if(y[i+1]>y[i-1])
            {
                if(equals<T>(y[i],yi,lower,upper)){Vi.push_back(i);}
            }
            else
            {
                if(equals<T>(y[i],yi,upper,lower)){Vi.push_back(i);}
            }
            
        }

        T lower=abs(y[n-1]-y[n-2])/2;
        if(equals<T>(y[n-1],yi,lower,lower)){Vi.push_back(n-1);}

        return Vi;
    }

    std::vector<T> where(T yi)
    {
        std::vector<int> Vi=this->where_i(yi);
    
        T h=this->h();
        std::vector<T> Vx=itox(Vi,x0,h);

        return Vx;
    }

    std::vector<T> where_ri(T yi)
    {
        T h=this->h();
        int n=this->size();

        std::vector<T> Vx;

        int i;
        for(i=1;i<n;i++)
        {
            T& y_0=y[i-1];
            T& y_1=y[i];

            if(((y_0<yi)&&(y_1>=yi))||(y_1<=yi)&&(y_0>yi))
            {
                T x_0=this->xi(i-1);
                T x_1=this->xi(i);

                T xi=x_0+(yi-y_0)*(x_1-x_0)/(y_1-y_0);

                Vx.push_back(xi);
            }
        }

        return Vx;
    }


    std::vector<int> local_imins(void)
    {
        FUN<T> df=this->diff();
        FUN<T> ddf=df.diff();
        std::vector<int> Vi0=df.where_i(0);
        int n=static_cast<int>(Vi0.size());
        std::vector<int> Vi;

        int i;
        for(i=0;i<n;i++)
        {
            int k=Vi0[i]+2;
            if(ddf.y[k+2]>0){Vi.push_back(k);}
        }
    return Vi;
    }

    std::vector<int> local_imaxs(void)
    {
        FUN<T> df=this->diff();
        FUN<T> ddf=df.diff();
        std::vector<int> Vi0=df.where_i(0);
        int n=static_cast<int>(Vi0.size());
        std::vector<int> Vi;

        int i;
        for(i=0;i<n;i++)
        {
            int k=Vi0[i]+2;
            if(ddf.y[k+2]<0){Vi.push_back(k);}
        }
    return Vi;
    }

    std::vector<T> local_mins(void)
    {
        std::vector<int> Vi=this->local_imins();

        T h=this->h();
        std::vector<T> Vx=itox(Vi,x0,h);

        return Vx;
    }

    std::vector<T> local_maxs(void)
    {
        std::vector<int> Vi=this->local_imaxs();

        T h=this->h();
        std::vector<T> Vx=itox(Vi,x0,h);

        return Vx;
    }


    std::vector<int> mins_i(T d=100)
    {
        int imin=this->imin_first();
        int imax=this->imax_first();

        T& ymin=y[imin];
        T& ymax=y[imax];

        std::vector<int> Vi0=this->local_imins();
        int n=static_cast<int>(Vi0.size());

        T D=abs((ymin-ymax)/d);

        std::vector<int> Vi;

        int i;
        for(i=0;i<n;i++)
        {  
            int k=Vi0[i];
            if(equals(y[k],ymin,D,D)){Vi.push_back(k);}
        }
        return Vi;
    }

    std::vector<int> maxs_i(T d=100)
    {
        int imin=this->imin_first();
        int imax=this->imax_first();

        T& ymin=y[imin];
        T& ymax=y[imax];

        std::vector<int> Vi0=this->local_imaxs();
        int n=static_cast<int>(Vi0.size());

        T D=abs((ymin-ymax)/d);

        std::vector<int> Vi;

        int i;
        for(i=0;i<n;i++)
        {  
            int k=Vi0[i];
            if(equals(y[k],ymax,D,D)){Vi.push_back(k);}
        }
        return Vi;
    }

    std::vector<T> mins(T d=100)
    {
        std::vector<int> Vi=this->mins_i(d);

        T h=this->h();
        std::vector<T> Vx=itox(Vi,x0,h);

        return Vx;
    }

    std::vector<T> maxs(T d=100)
    {
        std::vector<int> Vi=this->maxs_i(d);

        T h=this->h();
        std::vector<T> Vx=itox(Vi,x0,h);

        return Vx;
    }


    FUN<T> diff(void)
    {
        T h=this->h();

        int n=this->size();

        std::vector<T> dy;
        T dx0=x0+2*h;

        int i;
        for(i=2;i<n-2;i++)
        {
            T& y0=y[i-2];
            T& y1=y[i-1];
            T& y2=y[i+1];
            T& y3=y[i+2];

            T dyi=(-y3+8*y2-8*y1+y0)/(12*h);

            dy.push_back(dyi);
        }

        T dx1=x1-2*h;
        FUN<T> df={dx0,dx1,dy};
        return df;
    }

    FUN<T> integral(T C=0.0)
    {
        T h=this->h();

        int n=this->size();

        std::vector<T> Y;

        T Y_i=y[0]*h/3+C;

        Y.push_back(Y_i);

        int i;
        for(i=1;i<n-1;i++)
        {
            if((i%2)==1){Y_i+=4*y[i]*h/3;}
            else{Y_i+=2*y[i]*h/3;}

            Y.push_back(Y_i);
        }

        Y_i+=y[n-1]*h/3;
        Y.push_back(Y_i);

        FUN<T> F={x0,x1,Y};
        return F;
    }

    T integrate(T a,T b)
    {
        T C=0.0;
        FUN<T> F=this->integral(C);

        T A=F.value(a);
        T B=F.value(b);

        T Y=B-A;
        return Y;
    }


    void to_FILE(std::string filename)
    {
        T h=this->h();

        int n=this->size();

        std::ofstream file;
        file.open(filename);

        int i;
        for(i=0;i<n;i++)
        {
            T& y_i=y[i];
            T x=this->xi(i);
            file<<x<<","<<y_i<<"\n";
        }

        file.close();


        return;
    }

    void print(int n=0)
    {
        T h=this->h();

        int N=this->size();
        if(n==0){n=N;}
        else if(n>N){n=N;}

        int i;
        for(i=0;i<n;i++)
        {
            T& y_i=y[i];
            T x=this->xi(i);
            std::cout<<x<<","<<y_i<<"\n";
        }

        return;
    }


};

template<typename T>
std::vector<T> itox(std::vector<int> Vi,T x0, T h)
{
    std::vector<T> Vx;

    int n=static_cast<int>(Vi.size());

    int i;
    for(i=0;i<n;i++)
    {
        int k=Vi[i];
        Vx.push_back(x0+k*h);
    }
    return Vx;
}


template<typename T> 
bool equals(T y1, T y2, T lower,T upper)
{
    if(y1==y2){return true;}
    if(((y1+upper)>=y2)&&((y1-lower)<=y2)){return true;}   
    
    return false;
}

template<typename T, typename F>
FUN<T> make_FUN(T x0, T x1,F f,int n)
{
    std::vector<T> y;
    T h=(x1-x0)/(n-1);

    T x=x0;

    int i;
    for(i=0;i<n;i++)
    {
        x+=h;
        y.push_back(f(x));
    }

    FUN<T> fun={x0,x1,y};
    return fun;
}