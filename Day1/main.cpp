//AdventOfCode2024

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 0;
    }

    std::string nombre;
    char digit = '0';
    int i = 0;
    std::vector<int> gauche;
    std::vector<int> droite;

    while(!inputFile.eof()){
        inputFile >> nombre;
        if(i % 2 == 0){
            gauche.push_back(std::stoi(nombre));
        }
        else{
            droite.push_back(std::stoi(nombre));
        }
        i++;
    }
    //For part 1:

    std::sort(gauche.begin(), gauche.end());
    std::sort(droite.begin(), droite.end());

    for(int i : gauche)
        std::cout << "gauche : " << i << "\n";
    for(int i : droite)
        std::cout << "droite : " << i << "\n";
    int distance = 0;

    for(int i = 0; i < gauche.size(); i++){
        distance+= (abs(gauche[i] - droite[i]));
    }
    std::cout << "distance = " << distance;

    //For part 2:

    int similarity = 0;
    int numberOfoccurence = 0;
    for(int i : gauche){
        for(int j : droite){
            if(i == j){
                numberOfoccurence +=1;
            }
        }
        similarity += (numberOfoccurence * i);
        numberOfoccurence = 0;
    }
    std::cout << "similarity = " << similarity;
}