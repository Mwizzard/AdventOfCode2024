#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class garde {
    int posX = 0;
    int posY = 0;
    char direction = '^';

public:
    // Constructeur
    garde(int x, int y){
        posX = x, posY = y;
    }

    // Getters
    int getPosX(){ 
        return posX; 
    }
    int getPosY(){
        return posY;
    }
    char getDirection(){
    return direction; 
    }

    // Setters
    void setPosX(int x){
        posX = x; 
    }
    void setPosY(int y){
        posY = y;
    }
    void setDirection(char dir){
        direction = dir;
    }
};

int main() {
    std::vector<std::vector<char>> map;

    // Lecture du fichier
    std::ifstream fichierEntree("input.txt");

    if (!fichierEntree){
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    // Remplir le vecteur
    std::string ligne;
    while (std::getline(fichierEntree, ligne)){
        std::vector<char> ligneVec(ligne.begin(), ligne.end());
        map.push_back(ligneVec);
    }

    // Garder la position actuelle en mémoire
    int posX = 0, posY = 0;

    // Parcourir la carte pour trouver la position initiale du garde
    for (int y = 0; y < map.size(); y++){
        for (int x = 0; x < map[y].size(); x++){
            if (map[y][x] == '^') {
                posX = x;
                posY = y;
            }
            std::cout << map[y][x];
        }
        std::cout << std::endl;
    }


    garde monGarde(posX, posY);
    int memePos;
    int nbParadox = 0;
    for (int y = 0; y < map.size(); y++){
        for (int x = 0; x < map[y].size(); x++){
            std::cout << "Iteration :" << y << ", " << x << std::endl;
            memePos = 0;
            map[y][x] = '#'; // on pose un obstacle a chaque position possible
            monGarde.setPosX(posX), monGarde.setPosY(posY); // on replace le garde a la position initiale

            while (monGarde.getPosX() > 0 && monGarde.getPosX() < map[0].size() - 1 &&
                    monGarde.getPosY() > 0 && monGarde.getPosY() < map.size() - 1){
                    /*std::cout << "Position X : " << monGarde.getPosX() 
                            << " Position Y : " << monGarde.getPosY() 
                            << " Direction : " << monGarde.getDirection() << std::endl;*/
                    if(memePos > 130){//max possible combinations
                        nbParadox +=1; 
                        break;
                    }
                    switch (monGarde.getDirection()){
                        case '^': // Monter
                            if (map[monGarde.getPosY() - 1][monGarde.getPosX()] != '#'){
                                monGarde.setPosY(monGarde.getPosY() - 1);
                                if(map[monGarde.getPosY()][monGarde.getPosX()] == 'X'){
                                    memePos +=1;
                                }else{
                                    memePos = 0;
                                    map[monGarde.getPosY()][monGarde.getPosX()] = 'X';
                                }
                                
                            }else{
                                monGarde.setDirection('>');
                            }
                            break;

                        case '>': // Droite
                            if (map[monGarde.getPosY()][monGarde.getPosX() + 1] != '#'){
                                monGarde.setPosX(monGarde.getPosX() + 1);
                                if(map[monGarde.getPosY()][monGarde.getPosX()] == 'X'){
                                    memePos +=1;
                                }else{
                                    memePos = 0;
                                    map[monGarde.getPosY()][monGarde.getPosX()] = 'X';
                                }
                                
                            }else{
                                monGarde.setDirection('v');
                            }
                            break;

                        case 'v': // Descendre
                            if(map[monGarde.getPosY() + 1][monGarde.getPosX()] != '#'){
                                monGarde.setPosY(monGarde.getPosY() + 1);
                                if(map[monGarde.getPosY()][monGarde.getPosX()] == 'X'){
                                    memePos +=1;
                                }else{
                                    memePos = 0;
                                    map[monGarde.getPosY()][monGarde.getPosX()] = 'X';
                                }
                            }else{
                                monGarde.setDirection('<');
                            }
                            break;

                        case '<': // Gauche
                            if(map[monGarde.getPosY()][monGarde.getPosX() - 1] != '#'){
                                monGarde.setPosX(monGarde.getPosX() - 1);
                                if(map[monGarde.getPosY()][monGarde.getPosX()] == 'X'){
                                    memePos +=1;
                                }else{
                                    memePos = 0;
                                    map[monGarde.getPosY()][monGarde.getPosX()] = 'X';
                                }
                            }else{
                                monGarde.setDirection('^');
                            }
                            break;

                        default:
                            std::cerr << "Erreur : direction inconnue." << std::endl;
                            return 1;
                    }
                }
                //On regenere la map
                // Remplir le vecteur
                map.clear();
                std::ifstream fichierEntree("input.txt");
                std::string ligne;
                while (std::getline(fichierEntree, ligne)){
                    std::vector<char> ligneVec(ligne.begin(), ligne.end());
                    map.push_back(ligneVec);
                }
        }
    }
    fichierEntree.close();
    

    // Écriture dans le fichier de sortie
    std::fstream fichierSortie("output.txt");
    int nbX = 0;

    for(const auto& ligne : map){
        for(const auto& caractere : ligne){
            if(caractere == 'X'){
                nbX++;
            }
            fichierSortie << caractere;
        }
        fichierSortie << '\n';
    }
    fichierSortie.close();
    
    nbX+=1; // On ajoute 1 pour prendre en compte la position initiale du garde.

    std::cout << "Nombre de paradox: " << nbParadox << std::endl;

    return 0;
}
