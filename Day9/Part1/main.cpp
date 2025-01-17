#include <iostream>
#include <vector>
#include <string>
#include <fstream>


int main() {
    
    std::vector<int> memory;
    int idNumber = 0;
    bool freeMemory = false;    //flag to know if we are in a free memory spot

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }
    char c;

    //we fill the vector with the raw memory
    while(inputFile >> c){
        if(freeMemory){
            for(int i= 0; i < (c-'0'); i++){
                memory.push_back(-1);
            }
            freeMemory = false;
        }
        else{
            for(int i= 0; i < (c-'0'); i++){
                memory.push_back(idNumber);
            }
            freeMemory = true;
            idNumber++;
        }
    }
    /*for(const int i : memory){
            std::cout << i;
        }*/
    //clean the memory
    int start = 0;
    int end = memory.size();
    while(start < end){
        if(memory[start] != -1){
            start++;
        }else{
            while(memory[end] == -1){
                end--;
            }
            memory[start] = memory[end];
            memory[end] = -1;
        }
    }
    memory[end] = memory[start];
    for(const int i : memory){
            std::cout << i;
        }
    //CheckSum
    long long int sum =0;
    int i = 0;
    while(memory[i] != -1){
        sum += i * memory[i];
        i++;
    }
    std::cout << "Sum = " << sum << std::endl;
}