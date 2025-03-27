#include "../include/SSCC.hpp"

SSCC::SSCC() {
	_ai = "00";
    _exDigit = "0";
	_companyId = "0000000";
    _serial = "000000000";
    _checkDigit = "0";
    _sscc = _ai + _exDigit + _companyId + _serial + _checkDigit;
}

SSCC::SSCC(SSCC const &copy) {*this = copy;}

SSCC SSCC::operator=(SSCC const &copy) {
    if (this != &copy) {
        _sscc = copy._sscc;
        _ai = copy._ai;
        _exDigit = copy._exDigit;
        _companyId = copy._companyId;
        _serial = copy._serial;
        _checkDigit = copy._checkDigit;
    }
    return *this;
}

SSCC::~SSCC() {}

std::string SSCC::getSSCC() const {return _sscc;}
std::string SSCC::getAI() const {return _ai;}
std::string SSCC::getExDigit() const {return _exDigit;}
std::string SSCC::getCompanyId() const {return _companyId;}
std::string SSCC::getSerial() const {return _serial;}
std::string SSCC::getCheckDigit() const {return _checkDigit;}

void SSCC::setSSCC(const std::string &sscc) {_sscc = sscc;}
void SSCC::setAI(const std::string &sscc) {_ai = sscc.substr(0, 2);}
void SSCC::setExDigit(const std::string &sscc) {_exDigit = sscc.substr(2, 1);}
void SSCC::setCompanyId(const std::string &sscc) {_companyId = sscc.substr(3, 8);}
void SSCC::setSerial(const std::string &sscc) {_serial = sscc.substr(11, 8);}
void SSCC::setCheckDigit(const std::string &sscc) {_checkDigit = sscc.substr(19, 1);}

void SSCC::theBigSetter(const std::string &sscc) {
    setSSCC(sscc);
    if (sscc.length() != 20) {
        return;
    }
    setAI(sscc);
    setExDigit(sscc);
    setCompanyId(sscc);
    setSerial(sscc);
    setCheckDigit(sscc);
}

// Luhn Algorithm
int SSCC::isValidLuhn(const std::string &code) {
	int len = code.length();
	int parity = len % 2;
	int sum = 0;

	for (int i = len - 2; i >= 0; --i) {
		int d = code[i] - '0';
		if (i % 2 == parity) {
			d *= 2;
		}
		if (d > 9) {
			d -= 9;
		}
		sum += d;
	}
    int check = (10 - (sum % 10)) % 10;
    if (check == (code[len - 1] - '0')) {
        return 0;
    }
	return 1;
}

std::string SSCC::errorHandle(SSCCError &code) {
	switch (code) {
        case SSCCError::INVALID_LENGTH:
			return ("ERROR: SSCC has to be a size of 20");
        case SSCCError::NON_NUMERIC:
			return ("ERROR: SSCC has to contain only digits: invalid at " + std::to_string(getSSCC().find_first_not_of("0123456789")));
        case SSCCError::INVALID_AI:
			return ("ERROR: AI (Application Identifier): [" + getAI() + "] " + getExDigit() + getCompanyId() + getSerial() + getCheckDigit());
        case SSCCError::INVALID_COMPANY_ID:
            return ("ERROR: invalid GS1 Company Prefix: " + getAI() + getExDigit() + " [" + getCompanyId() + "] " + getSerial() + getCheckDigit());
        case SSCCError::INVALID_CHECK_DIGIT:
			return ("ERROR: invalid CHECK DIGIT: " + getAI() + getExDigit() + getCompanyId() + getSerial() + " [" + getCheckDigit() + "]");
        default:
			return ("SSCC is valid!");
    }
}

void SSCC::printNcheck(const std::string &codes) {
    theBigSetter(codes);
    std::vector<SSCCError> errors = proccess(codes);
    std::string print = "SSCC: [ " + codes + " ] ";
    int count = 0;
    for (size_t i = 0; i < errors.size(); ++i) {
        if (errors[i] == SSCCError::NONE) {
            std::cout << GRE << print << errorHandle(errors[i]) << WHI << "\n";
        }
        else {
            if (count == 0) {
                std::cout << RED << print << WHI << "\n";
                count++;
            }
            std::cout << YEL << "\t\t|\n";
            std::cout << "\t\t-> " << errorHandle(errors[i]) << WHI << "\n";
        }
        std::cout << "\n";
    }
}

std::vector<SSCCError> SSCC::proccess(const std::string &code) {
    std::vector<SSCCError> errors;
    if (code.length() != 20) {
        errors.push_back(SSCCError::INVALID_LENGTH);
        return errors;
    }
    if (!std::all_of(code.begin(), code.end(), ::isdigit)) {
        errors.push_back(SSCCError::NON_NUMERIC);
		return errors;
    }
    if (AI != _ai) {
        errors.push_back(SSCCError::INVALID_AI);
    }
    if (COMPANY_ID != _companyId) {
        errors.push_back(SSCCError::INVALID_COMPANY_ID);
    }
	if (isValidLuhn(code) != 0) {
        errors.push_back(SSCCError::INVALID_CHECK_DIGIT);
    }
    if (errors.empty()) {
        errors.push_back(SSCCError::NONE);
    }
    return errors;
}
