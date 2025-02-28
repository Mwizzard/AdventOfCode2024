#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main() {
    std::ifstream fichierEntree("input.txt");
    if (!fichierEntree) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> rapports;
    std::string s;

    while (fichierEntree >> s) {
        std::vector<int> rapport;
        do {
            rapport.push_back(std::stoi(s));
        } while (fichierEntree.peek() != '\n' && fichierEntree >> s); // Lire jusqu'a la fin de la ligne
        rapports.push_back(rapport);
    }

    int rapportsSurs = 0;

    for (const auto& rapport : rapports) {
        bool estSur = true;
        bool estCroissant = rapport[1] > rapport[0];  // Verifier si la sequence est initialement croissante
        bool estDecroissant = rapport[1] < rapport[0];  // Verifier si la sequence est initialement decroissante
        
        for (size_t i = 1; i < rapport.size(); ++i) {
            int diff = std::abs(rapport[i] - rapport[i-1]);
            
            if (diff < 1 || diff > 3) {
                estSur = false;
                break;
            }

            // Vérifier la sequence croissante ou decroissante
            if (estCroissant && rapport[i] < rapport[i-1]) {
                estSur = false;
                break;
            }
            if (estDecroissant && rapport[i] > rapport[i-1]) {
                estSur = false;
                break;
            }

            if (rapport[i] > rapport[i-1]) {
                estCroissant = true;
                estDecroissant = false;
            } else if (rapport[i] < rapport[i-1]) {
                estDecroissant = true;
                estCroissant = false;
            }
        }

        if (estSur) {
            rapportsSurs++;
        }
    }
    std::cout << "Nombre de rapports securitaires : " << rapportsSurs << std::endl;

    return 0;
}
