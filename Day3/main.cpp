#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

int main() {
    std::string s;
    std::string temp;
    std::regex e("mul\\([0-9]+,[0-9]+\\)");  //expression regex
    
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << inputFile.rdbuf();
    s = oss.str();

    auto words_begin = std::sregex_iterator(s.begin(), s.end(), e);
    auto words_end = std::sregex_iterator();

    int a, b;
    char comma;
    long long sum = 0;

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        
        // Extraire les nombres 
        std::string input = match_str.substr(4, match_str.size() - 5);
        
        std::stringstream ss(input);
        ss >> a >> comma >> b;

        if (ss) {
            std::cout << "a: " << a << " b: " << b << std::endl;
            sum += (a * b);
        }
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}