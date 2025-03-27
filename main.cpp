#include "include/SSCC.hpp"

int runArg(int argc, char *argv[]) {
	SSCC sscc;
	for (int i = 1; i < argc; i++) {
		std::string call = argv[i];
		sscc.printNcheck(call);
		std::cout << std::endl;
	}
	return (0);
}

int runFile(std::fstream &file) {
	SSCC sscc;
	std::string line;
	while (std::getline(file, line)) {
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		if (line.empty()) {continue;}
		if (line[0] == '[') {std::cout << BLU << "\t" << line << WHI << "\n\n"; continue;}
		std::istringstream iss(line);
		std::string token;
		while (iss >> token) {
			sscc.printNcheck(token);
			std::cout << std::endl;
		}
	}
	return (0);
}

void runTest() {
	std::vector<std::string> tests = {"EXAMPLES.txt", 
									"AI.txt",
									"COMPANY_ID.txt", 
									"CHECK_DIGIT.txt", 
									"INVALID_LENGTH.txt", 
									"NON_NUMERIC.txt", 
									"NONE.txt"};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::fstream file("tests/" + tests[i]);
		runFile(file);
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "[ Supply a file or arguments ]" << std::endl;
		std::cerr << "Usage: ./sscc [...] \n";
		std::cout << "Usage: ./sscc [...] [...] \n";
		std::cout << "Usage: ./sscc [file] \n";
		std::cerr << "Usage: ./sscc --test" << std::endl;
		return (1);
	}
	std::string fileName = argv[1];
	if (fileName == "--test") {
		runTest();
		return (0);
	}
	std::fstream file(fileName.c_str());
	if (file.good()) {
		runFile(file);
	}
	else {
		runArg(argc, argv);
	}
	return (0);
}