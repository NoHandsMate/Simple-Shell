#include <iostream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
		
	short i = 0;
	
	fs::path const current_path = argv[0];
	
	for (auto const& file : fs::directory_iterator(current_path)) {

		if (i % 3 == 0) {
			std::cout << '\n';
			i = 0;
		}

		i++;
		std::cout << std::setw(32) << std::left << file.path().filename().string() << " ";
	}

}
