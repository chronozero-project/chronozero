#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chronos <file.crn>\n";
        return 1;
    }

    const std::string filename = argv[1];
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Chronos: Can't open " << filename << "\n";
        return 1;
    }

    std::string source(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
        );

    std::cout << "Chronos source loaded.\n";
    std::cout << "File: " << filename << "\n";
    std::cout << "Size: " << source.size() << " bytes\n";

    return 0;
}