#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(){

    std::vector<int> priorities;
    char a;
    char b;
    std::ifstream fichierEntree("input.txt");

    while (fichierEntree >> a) {
        if(a == '|');
        else{
            priorities.push_back(a - '0');
        }
    }
    for(auto& i : priorities){
        std::cout << i << std::endl;
    }
    return 0;
}