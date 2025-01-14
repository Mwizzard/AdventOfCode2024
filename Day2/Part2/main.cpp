#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

int main() {
    std::ifstream fichierEntree("input.txt");
    if (!fichierEntree) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> rapports;
    std::string ligne;

    // Lecture ligne par ligne
    while (std::getline(fichierEntree, ligne)) {
        std::istringstream streamLigne(ligne);
        std::vector<int> rapport;
        int nombre;

        while (streamLigne >> nombre) {
            rapport.push_back(nombre);
        }

        if (!rapport.empty()) {
            rapports.push_back(rapport);
        }
    }

    int rapportsSurs = 0;

    // Analyse des rapports
    for (const auto& rapport : rapports) {

        int nberreurs = 0;
        bool estSur = true;

        // Déterminer si la sequence est initialement croissante ou decroissante
        bool estCroissant = rapport[1] > rapport[0];
        bool estDecroissant = rapport[1] < rapport[0];

        for (size_t i = 1; i < rapport.size(); ++i) {
            int diff = std::abs(rapport[i] - rapport[i - 1]);

            if (diff < 1 || diff > 3) {
                nberreurs++;
            }

            if ((estCroissant && rapport[i] < rapport[i - 1]) ||
                (estDecroissant && rapport[i] > rapport[i - 1])) {
                nberreurs++;
            }

            if (nberreurs > 1) {
                estSur = false;
                break;
            }
        }

        if (estSur) {
            rapportsSurs++;
        }
    }

    std::cout << "Nombre de rapports securitaires : " << rapportsSurs << std::endl;

    return 0;
}
