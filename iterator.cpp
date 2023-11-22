#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include <map>
int main()
{
    std::string key_ = "PLAYFAIREXAMPLE";
    key_ += "abcdefghijklmnopqrstuvwxyz";
    
    std::transform(key_.begin(),key_.end(),key_.begin(),::toupper);

    auto iter = std::remove_if(key_.begin(),key_.end(), 
    [](char c){return !isalpha(c);});
    key_.erase(iter, key_.end());

    std::transform(key_.begin(),key_.end(),key_.begin(),
    [](char c){ return (c == 'J') ? 'I': c;});

    std::cout << key_ << "\n";

    std::string s1{""}; 
    auto duplicate = [&](char c){
        if (s1.find(c) == std::string::npos){
            s1 += c;
            return false;  
        }
        else {
            return true;
        } 
    };

    auto iter2 = std::remove_if(key_.begin(),key_.end(),duplicate);
    key_.erase(iter2, key_.end());

    std::cout << key_ << "\n";


    std::map< std::pair<int, int>, char> keyMap;
    
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 5; col++){

            std::pair<int, int> p0{col, row};

            keyMap[p0] = key_[row+ 5*col];
        };
    };

    int i{0};
    for( auto p : keyMap)
    {
        std::cout << p.second;
        i += 1;
        if (i%5== 0){
            std::cout << "\n";
        };
    }


    std::map<char, std::pair<int, int>> coordMap;
        
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 5; col++){

            std::pair<int, int> p1{col, row};
            char x = key_[row+5*col];
            coordMap[x] = p1;
        };
    };

     for( auto p : coordMap)
    {
        std::cout << p.first << (p.second).first << (p.second).second << "\n";
    }

   
// Store the coords of each letter
// Store the playfair cihper key map
}
