#include "AtlasPacker.h"

int main(int argc, char* argv[])
{

    std::cout << "Press ENTER to start debugging...";
    std::cin.get();

	sOptions Options;

	Options.InputPath = argv[1];

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--size" && i + 1 < argc) {
            Options.AtlasSize = std::stoi(argv[++i]);
        }
        else if (arg == "--out" && i + 1 < argc) {
            Options.OutputPath = argv[++i];
        }
        else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }

    AtlasPacker AtlasPacker;
    AtlasPacker.Pack(Options);

	return 0;
}
