//Type templating
#include<iostream>
#include<type_traits>








/*
namespace cartoon
{
    //Make a function that can only work if the type is int
template<typename T>
typename  int //std::enable_if<std::is_integral<T>::value>::type
print_after_making_triple(T x){
    std::cout<<3*x<<std::endl;
}
}


int main() {
    double x =5.6;
    //cartoon::print_after_making_triple(x); //This will just give error
    cartoon::print_after_making_triple(5);
    return 0;
}*/