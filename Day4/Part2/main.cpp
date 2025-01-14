#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <cassert>

const std::regex expression("MAS|SAM");

/// @brief permet de calculer le nombre de 'XMAS' diagonal (a l'endroit et a l'envers)
/// @param vecteur2d
/// @return nbXmas Diagonal
int compteDiagonal(std::vector<std::vector<char>> valeurs) {
    std::string diagonale;
    int nbXMAS = 0;

    int rows = valeurs.size();
    int cols = valeurs[0].size();
    std::string diagonale2;
    // Parcourir les diagonales commencant en haut de la matrice
    for (int startCol = 0; startCol < cols; startCol++) {
        diagonale = "";
        for (int i = 0, j = startCol; i < rows && j < cols; ++i, ++j) {
            diagonale += valeurs[i][j];
            if(diagonale == "SAM" || diagonale == "MAS"){
                for(int k = i-2; k <= i; k++){
                    for(int l = j; j > l-2; j--){
                        diagonale2 += valeurs[i][j];
                        if(diagonale2 == "SAM" || diagonale2 == "MAS")
                            nbXMAS++;
                    }
                }
                diagonale2 = "";
            }
        }
        std::cout << diagonale << std::endl;
        diagonale = "";
    }

    // Parcourir les diagonales commençant sur la gauche de la matrice (en dessous de la diagonale principale)
    for (int startRow = 1; startRow < rows; startRow++) {
        diagonale = "";
        for (int i = startRow, j = 0; i < rows && j < cols; i++, j++) {
            diagonale += valeurs[i][j];
            if(diagonale == "SAM" || diagonale == "MAS"){
                for(int k = i-2; k <= i; k++){
                    for(int l = j; j > l-2; j--){
                        diagonale2 += valeurs[i][j];
                        if(diagonale2 == "SAM" || diagonale2 == "MAS")
                            nbXMAS++;
                    }
                }
                diagonale2 = "";
            }
        }
        std::cout << diagonale << std::endl;
        diagonale = "";
    }
    return nbXMAS;
}

int main() {
    std::vector<std::vector<char>> valeurs;

    //lecture du fichier
    std::ifstream fichierEntree("input.txt");

    if (!fichierEntree) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    //mettre dans le vecteur
    std::string ligne;
    while (std::getline(fichierEntree, ligne)) {
        std::vector<char> ligneVec(ligne.begin(), ligne.end());
        valeurs.push_back(ligneVec);
    }

    fichierEntree.close();

    //Afficher le contenu
    for (const auto& ligne : valeurs) {
        for (const auto& caractere : ligne) {
            std::cout << caractere;
        }
        std::cout << std::endl;
    }
    std::cout <<"Nombre de XMAS diagonal : "  << compteDiagonal(valeurs) << std::endl;
    return 0;
}