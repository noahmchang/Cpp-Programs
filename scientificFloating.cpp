#include <iostream>
#include <string>
#include <cmath>
#include <vector>

int main(){
    float myfloat;
    int float_int;
    std::cout << "Please enter a float: ";
    std::cin >> myfloat;
    float_int = *((unsigned int*)&myfloat); //int base 10
    
    int sign = (float_int >> 31) & 1;
    if(sign == 1){
        std::cout << "-";
    }
    int exponent = (float_int >> 23) & 0b11111111;
    if(exponent != 0){
        std::cout << "1.";
    } else{
        std::cout << "0.";
    }
    int mantissa = float_int & 0b11111111111111111111111;
    
    std::vector<int> myvector;
    for(int j=23; j>=0; j--){
        myvector.push_back(((mantissa >> j) & 1));
    }
    int k=myvector.size()-1; //least significant 1 index
    for(; k>0; k--){
        if(myvector[k] == 1){
            break;
        }
    }
    if(mantissa == 0){
        std::cout << "0";
    } else{
        for(int i=22; i>=22-k+1; i--){
            std::cout << ((mantissa >> i) & 1);
        }
    }
    std::cout << "E" << (exponent-127) << std::endl;
}