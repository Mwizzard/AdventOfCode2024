#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <cassert>

const std::regex expression("XMAS");

std::string reverseString(std::string s){
    std::reverse(s.begin(), s.end());
    return s;
}
int countXMAS(std::string s){
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), expression);
    auto words_end = std::sregex_iterator();
    return std::distance(words_begin, words_end);

}
/// @brief permet de calculer le nombre de 'XMAS' horizontal (a l'endroit et a l'envers)
/// @param vecteur2d
/// @return nbXmas horizontal
int compteHorizontal(std::vector<std::vector<char>> valeurs) {
    assert(valeurs.size() != 0);
    assert(valeurs[0].size() != 0);

    std::string ligne;
    int nbXMAS = 0;

    for(int i = 0; i < valeurs.size(); i++){
        for(int j = 0; j < valeurs[0].size(); j++){
            ligne+= valeurs[i][j];  //ligne par ligne
        }
        //compte nombre de XMAS
        nbXMAS += countXMAS(ligne);
        ligne = reverseString(ligne);
        nbXMAS += countXMAS(ligne);
        ligne = "";
    }

    return nbXMAS;
}

/// @brief permet de calculer le nombre de 'XMAS' vertical (a l'endroit et a l'envers)
/// @param vecteur2d
/// @return nbXmas Vertical
int compteVertical(std::vector<std::vector<char>> valeurs) {
    std::string colonne;
    int nbXMAS = 0;

    for(int i = 0; i < valeurs[0].size(); i++){
        for(int j = 0; j < valeurs.size(); j++){
            colonne+= valeurs[j][i];
        }

        nbXMAS += countXMAS(colonne);
        colonne = reverseString(colonne);
        nbXMAS += countXMAS(colonne);
        colonne = "";
    }
    return nbXMAS;
}

/// @brief permet de calculer le nombre de 'XMAS' diagonal (a l'endroit et a l'envers)
/// @param vecteur2d
/// @return nbXmas Diagonal
int compteDiagonal(std::vector<std::vector<char>> valeurs) {
    std::string diagonale;
    int nbXMAS = 0;

    int rows = valeurs.size();
    int cols = valeurs[0].size();

    // Parcourir les diagonales commencant en haut de la matrice
    for (int startCol = 0; startCol < cols; startCol++) {
        diagonale = "";
        for (int i = 0, j = startCol; i < rows && j < cols; ++i, ++j) {
            diagonale += valeurs[i][j];
        }
        nbXMAS += countXMAS(diagonale);
        diagonale = reverseString(diagonale);
        nbXMAS += countXMAS(diagonale);
        diagonale = "";
    }

    // Parcourir les diagonales commençant sur la gauche de la matrice (en dessous de la diagonale principale)
    for (int startRow = 1; startRow < rows; startRow++) {
        diagonale = "";
        for (int i = startRow, j = 0; i < rows && j < cols; i++, j++) {
            diagonale += valeurs[i][j];
        }
        nbXMAS += countXMAS(diagonale);
        diagonale = reverseString(diagonale);
        nbXMAS += countXMAS(diagonale);
        diagonale = "";
    }

    for (int startCol = 0; startCol < cols; ++startCol) {
        for (int i = rows - 1, j = startCol; i >= 0 && j < cols; --i, ++j) {
            diagonale += valeurs[i][j];
        }
        nbXMAS += countXMAS(diagonale);
        diagonale = reverseString(diagonale);
        nbXMAS += countXMAS(diagonale);
        diagonale = "";
        }

    for (int startRow = rows - 2; startRow >= 0; --startRow) {
        for (int i = startRow, j = 0; i >= 0 && j < cols; --i, ++j) {
            diagonale += valeurs[i][j];
        }
        nbXMAS += countXMAS(diagonale);
        diagonale = reverseString(diagonale);
        nbXMAS += countXMAS(diagonale);
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

    std::cout << "Nombre de XMAS horizontal : " << compteHorizontal(valeurs) << std::endl;
    std::cout << "Nombre de XMAS vertical : " << compteVertical(valeurs) << std::endl;
    std::cout <<"Nombre de XMAS diagonal : "  << compteDiagonal(valeurs) << std::endl;
    return 0;
}