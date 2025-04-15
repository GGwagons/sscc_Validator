#include "../include/SSCC.hpp"
#include <thread>
#include <chrono>
#include <csignal>


volatile std::sig_atomic_t g_signalStatus;

void signal_handler(int signum) {
    std::cout << "Caught signal " << signum << ", cleaning up...\n";
    g_signalStatus = signum;
}

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
		if (file.good()) {
			runFile(file);
			std::cout << std::endl;
		}
		else {
			std::cerr << RED << "Error: file " << tests[i] << WHI << std::endl;
			return ;
		}
	}
}

void runLive() {
    SSCC sscc;
    std::cout << "Input file path: ";
    std::string input;
    std::getline(std::cin, input);

    std::string lastProcessed;
	std::signal(SIGINT, signal_handler);
    while (g_signalStatus == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));		// Short delay to avoid over-checking
        std::ifstream inFile(input);
        if (!inFile.is_open()) {
            std::cerr << "Could not open file.\n";
            return ;
        }
        std::vector<std::string> lines;										// Read all lines into memory
        std::string line;
        while (std::getline(inFile, line)) {
            lines.push_back(line);
        }
        if (inFile.close(), lines.empty()) continue;						// Skip any empty lines or output lines (error messages)
        int lastIdx = lines.size() - 1;
        while (lastIdx >= 0 && (lines[lastIdx].empty() || \
				lines[lastIdx].find("SSCC:") != std::string::npos || \
				lines[lastIdx].find("->") != std::string::npos)) {			// Skip error/output lines that have been appended
        	lastIdx--;
        }
        if (lastIdx < 0) {
			continue;
		}																	// If no valid input to process, continue
        std::string toProcess = lines[lastIdx];
        if (toProcess.empty() || toProcess == lastProcessed) {
			continue;														// Check if we have already processed this line
		}
        lastProcessed = toProcess;
        lines.erase(lines.begin() + lastIdx);								// Remove the line from its current position
        std::ofstream outFile(input, std::ios::trunc);						// Reopen the file for writing (overwrite all content)
        if (!outFile.is_open()) {
        	std::cerr << "Could not write to file.\n";
        	return ;
        }
        for (const auto& l : lines) {										// Write all remaining lines back (original input section)
            outFile << l << "\n";
        }
        outFile << "\n";
        sscc.printNcheckLive(toProcess, outFile);
        outFile << toProcess << "\n";        
    }
}

int main(int ac, char *av[]) {
	if (ac >= 2) {
		std::string fileName = av[1];
		if (fileName == "--test") {
			runTest();
		}
		else if (fileName == "--live") {
			runLive();
		}
		else {
			std::fstream file(fileName.c_str());
			if (file.good()) {
				runFile(file);
			}
			else if (!file.good() && fileName.find(".txt") == std::string::npos) {
				runArg(ac, av);
			}
			else {
				return (std::cerr << RED << "Error: file " << fileName << WHI << std::endl, 1);
			}
		}
		return (0);
	}
	std::cout << "[ Supply a file or arguments ]" << std::endl;
	std::cerr << "Usage: ./sscc [...] \n";
	std::cout << "Usage: ./sscc [...] [...] \n";
	std::cout << "Usage: ./sscc [file path] \n";
	std::cerr << "Usage: ./sscc --test" << std::endl;
	std::cerr << "Usage: ./sscc --live" << std::endl;
	return (1);
}
