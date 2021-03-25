#include"vector2.h"
#include<iostream>

int main() 
{
    Vector2d<double> v1{}, v2{};
    double x;
    std::cout << "Enter vector 1:\n";
    std::cin >> v1;
    std::cout << "Enter vector 2:\n";
    std::cin >> v2;
    std::cout << "Enter number x:\n";
    std::cin >> x;
    std::cout << "The sum of the two vectors is:\n" << v1+v2 <<"\n\n";
    std::cout << "The difference the two vectors is:\n" << v1-v2 <<"\n\n";
    std::cout << "The dot product of the two vectors is:\n" << dot(v1,v2) <<"\n\n";
    std::cout << "The length of vector 1 is:\n" << length(v1) <<"\n\n";
    std::cout << "The square of the length of vector 2 is:\n"<< sqlength(v2) <<"\n\n";
    std::cout << "If we normalize v2, we get:\n" << normalize(v2) <<"\n\n";
    std::cout << "v1 times x is:\n" << v1*x <<"\n\n";
    std::cout << "x times v1 is:\n" << x*v1 <<"\n\n";
    std::cout << "v2 divided by x is:\n" << v2/x << "\n\n";
    v1+=v2;
    std::cout << "If we add v2 to v1, the resulting vector is:\n" << v1 <<"\n\n";
    v1-=v2;
    std::cout << "If we subtract v2 from the resulting vector, the new resulting vector is:\n" << v1 <<"\n\n";
    v2*=x;
    std::cout << "If we multiply v2 by x, the resulting vector is:\n" << v2 << "\n\n";
    v2/=x;
    std::cout << "If we divide the resulting vector by x, the new resulting vector is:\n" << v2 << "\n\n";


    return 0;
}