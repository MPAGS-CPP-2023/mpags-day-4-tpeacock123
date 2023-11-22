#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>

PlayfairCipher::PlayfairCipher(const std::string& key) 
{
    this -> setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{

    key_ = key;
    key_ += "abcdefghijklmnopqrstuvwxyz";
    
    std::transform(key_.begin(),key_.end(),key_.begin(),::toupper);

    auto iter = std::remove_if(key_.begin(),key_.end(), 
    [](char c){return !isalpha(c);});
    key_.erase(iter, key_.end());

    std::transform(key_.begin(),key_.end(),key_.begin(),
    [](char c){ return (c == 'J') ? 'I': c;});
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
    std::map< std::pair<int, int>, char> keyMap;
    
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 5; col++){

            std::pair<int, int> p0{col, row};

            keyMap[p0] = key_[row+ 5*col];
        };
    };
    std::map<char, std::pair<int, int>> coordMap;
        
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 5; col++){

            std::pair<int, int> p1{col, row};
            char x = key_[row+5*col];
            coordMap[x] = p1;
        };
    };
    coordMap_ = coordMap;    
    keyMap_ = keyMap;   
}


std::string PlayfairCipher::applyCipher(const std::string& inputText_,
                                      const CipherMode cipherMode) const
{
    std::string inputText{inputText_};
    std::transform(inputText.begin(),inputText.end(),inputText.begin(),::toupper);

    auto iter3 = std::remove_if(inputText.begin(),inputText.end(), 
    [](char c){return !isalpha(c);});
    inputText.erase(iter3, inputText.end());


    std::transform(inputText.begin(),inputText.end(),inputText.begin(),
    [](char c){ return (c == 'J') ? 'I': c;});

    for(int i = 1; i < int(inputText.length()); i++){
        if ((inputText[i] == 'X') and (inputText[i-1] == 'X')){
            inputText.insert(i,1,'Q');
            ++i;
        }
        else if (inputText[i] == inputText[i-1] and !(inputText[i-1] == 'X') ){
            
            inputText.insert(i,1,'X');
            ++i;
        }

    };

    if(inputText.size()%2 != 0){
        inputText += 'Z';
    };
     
    
    std::map<char, std::pair<int, int>> coordMap = coordMap_;
    std::map<std::pair<int, int>, char> keyMap = keyMap_;

    std::string  outputText{""};
    switch (cipherMode){
        case CipherMode::Encrypt:
            for (int i = 0; i < int(inputText.length()); i += 2) {
                char ch1 = inputText[i];
                char ch2 = inputText[i + 1];

                int x{0}, y{0};
                
                std::pair<int, int> d1 = coordMap[ch1];
                std::pair<int, int> d2 = coordMap[ch2];

                std::pair<int, int> d1_new, d2_new;

                
                if (d1.first == d2.first) {
                    y = 1;
                } else if (d1.second == d2.second) {
                    x = 1;
                }
                d1_new = {d1.first + x, d1.second + y};
                d2_new = {d2.first + x, d2.second + y};
                
                if (x == 0 and y == 0) {
                    d1_new = {d2.first, d1.second};
                    d2_new = {d1.first, d2.second};
                }
            
                outputText += keyMap[d1_new];
                outputText += keyMap[d2_new];
            }
            break;
        case CipherMode::Decrypt:
            for (int i = 0; i < int(inputText.length()); i += 2) {
                char ch1 = inputText[i];
                char ch2 = inputText[i + 1];

                int x{0},y{0};
                
                std::pair<int, int> d1 = coordMap[ch1];
                std::pair<int, int> d2 = coordMap[ch2];

                std::pair<int, int> d1_new, d2_new;

                
                if (d1.first == d2.first) {
                    y = 1;
                } else if (d1.second == d2.second) {
                    x = 1;
                }
                d1_new = {d1.first - x, d1.second - y};
                d2_new = {d2.first - x, d2.second - y};
                
                if (x == 0 and y == 0) {
                    d1_new = {d2.first, d1.second};
                    d2_new = {d1.first, d2.second};
                }
            
                outputText += keyMap[d1_new];
                outputText += keyMap[d2_new];
            }
            break;
    }
    return outputText;
}