#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

#define COMPANY_ID "34260311"
#define AI "00"

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"

enum class SSCCError {
	NONE,
    INVALID_LENGTH,
    NON_NUMERIC,
    INVALID_AI,
    INVALID_COMPANY_ID,
    INVALID_CHECK_DIGIT
};

class SSCC {
	private:
		std::string _ai;
		std::string _exDigit;
		std::string _companyId;
		std::string _serial;
		std::string _checkDigit;
		std::string _sscc;
	public:
		// Constructors
		SSCC();
		~SSCC();
		SSCC(SSCC const &copy);
		SSCC operator=(SSCC const &copy);

		// Getters
		std::string getAI() const;
		std::string getExDigit() const;
		std::string getCompanyId() const;
		std::string getSerial() const;
		std::string getCheckDigit() const;
		std::string getSSCC() const;

		// Setters
		void setAI(const std::string &sscc);
		void setExDigit(const std::string &sscc);
		void setCompanyId(const std::string &sscc);
		void setSerial(const std::string &sscc);
		void setCheckDigit(const std::string &sscc);
		void setSSCC(const std::string &sscc);
		void theBigSetter(const std::string &sscc);

		// Methods
		int isValidLuhn(const std::string &code);
		std::string errorHandle(SSCCError &code);
		void printNcheck(const std::string &codes);
		std::vector<SSCCError> process(const std::string &code);
};
