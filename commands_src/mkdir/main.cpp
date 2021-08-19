#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, const char* argv[]) {
	std::string arg = argv[0];

	if(arg.empty()) {
		
		std::cout << "No dir name specified " << '\n';
		return -1;
		
	}

	fs::create_directory(arg);
	return 0;
}
