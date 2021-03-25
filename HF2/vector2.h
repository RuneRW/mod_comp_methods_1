#include<cmath>
#include<iostream>

template<typename T>

struct Vector2d
{
    T x,y;

    Vector2d<T>& operator+=(Vector2d<T> const& v)
    {
        x+=v.x;
        y+=v.y;
        return *this;
    }

    Vector2d<T>& operator-=(Vector2d<T> const& v)
    {
        x-=v.x;
        y-=v.y;
        return *this;
    }

    Vector2d<T>& operator*=(T const& a)
    {
        x*=a;
        y*=a;
        return *this;
    }

    Vector2d<T>& operator/=(T const& a)
    {
        x/=a;
        y/=a;
        return *this;
    }
};

template<typename T>
Vector2d<T> operator+(Vector2d<T> const& a, Vector2d<T> const& b)
{
    return Vector2d<T>{a.x+b.x,a.y+b.y};
}

template<typename T>
Vector2d<T> operator-(Vector2d<T> const& a, Vector2d<T> const& b)
{
    return Vector2d<T>{a.x-b.x,a.y-b.y};
}

template<typename T>
Vector2d<T> operator*(Vector2d<T> const& a,T b)
{
    return Vector2d<T>{b*a.x,b*a.y};
}

template<typename T>
Vector2d<T> operator*(T a, Vector2d<T> b)
{
    return Vector2d<T>{a*b.x,a*b.y};
}

template<typename T>
Vector2d<T> operator/(Vector2d<T> a,T b)
{
    return Vector2d<T>{a.x/b,a.y/b};
}

template<typename T>
T dot(Vector2d<T> const& a,Vector2d<T> const& b)
{
    return a.x*b.x+a.y*b.y;
}

template<typename T>
T sqlength(Vector2d<T> const&a)
{
    T c;
    c=dot(a,a);
    return c;
}

template<typename T>
T length(Vector2d<T> const& a)
{
    T c;
    c=std::sqrt(sqlength(a));
    return c;
}

template<typename T>
Vector2d<T> normalize(Vector2d<T> const& a)
{
    return a/length(a);
}


template<typename T>
std::ostream& operator<<(std::ostream& o, Vector2d<T> const& v)
{
    o << v.x << " " << v.y;
    return o;
}

template<typename T>
std::istream& operator>>(std::istream& i, Vector2d<T>& v)
{
    i >> v.x;
    i >> v.y;
    return i;
}