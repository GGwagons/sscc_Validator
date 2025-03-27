# sscc_Validator

sscc_Validator is a C++ project designed to validate and process SSCC (Serial Shipping Container Code) numbers. It provides functionality to check the validity of SSCC codes based on their length, numeric content, Application Identifier (AI), company prefix, and check digit.

## Features

- **Validation**: Validate SSCC codes using the Luhn algorithm.
- **Error Identification**: Detect specific errors such as:
  - Invalid length
  - Non-numeric characters
  - Invalid Application Identifier (AI)
  - Invalid company prefix
  - Invalid check digit
- **Input Flexibility**: Process SSCC codes from files or command-line arguments.
- **Testing**: Run predefined tests using test datasets.

## Quick Start

1. Clone the repository:
   ```sh
   git clone <repository-url>
   cd <repository-directory>
   ```
2. Build the project:
   ```sh
   make
   ```
3. Validate an SSCC code:
   ```sh
   ./sscc 00034260311130776599
   ```

## Project Structure

### Key Components

- **`main.cpp`**: Entry point of the program. Handles command-line arguments, file processing, and test execution.
- **`include/SSCC.hpp`**: Header file defining the `SSCC` class and its methods.
- **`src/SSCC.cpp`**: Implementation of the `SSCC` class, including validation logic and error handling.
- **`tests/`**: Directory containing test datasets for validating SSCC codes.

## Installation

### Prerequisites
- A C++17-compatible compiler (e.g., `g++` or `clang`).
- `make` build system.

### Build Instructions
1. Clone the repository.
2. Run the following command to build the project:
   ```sh
   make
   ```
3. The executable `sscc` will be created in the project root directory.

### Clean Build
To remove all compiled files and rebuild the project:
1. Clean the build:
   ```sh
   make clean
   ```
   This removes object files and intermediate build artifacts.
2. Perform a full clean:
   ```sh
   make fclean
   ```
   This removes all build artifacts, including the executable.
3. Rebuild the project:
   ```sh
   make re
   ```

## Usage

### Command-Line Usage
The program can be used in the following ways:

1. Validate one or more SSCC codes passed as command-line arguments:
   ```sh
   ./sscc [SSCC_CODE]
   ./sscc 00034260311130776599
   ```
   or
   ```sh
   ./sscc [SSCC_CODE] [SSCC_CODE] [...]
   ./sscc "00034260311130776599" "00034260311130776144"
   ```

2. Validate SSCC codes from a file:
   ```sh
   ./sscc [example.txt]
   ./sscc tests/EXAMPLES.txt
   ```

3. Run predefined tests using the files in the **`tests`** directory:
   ```sh
   ./sscc --test
   ```

### Output

- Valid SSCC codes are displayed in green.
- Invalid SSCC codes are displayed in red, with specific error messages in yellow.

### Testing

#### Test Files
The `tests` directory contains various test datasets:

- **`AI.txt`**: Tests for invalid Application Identifiers.
- **`CHECK_DIGIT.txt`**: Tests for invalid check digits.
- **`COMPANY_ID.txt`**: Tests for invalid company prefixes.
- **`EXAMPLES.txt`**: General examples of SSCC codes.
- **`INVALID_LENGTH.txt`**: Tests for SSCC codes with incorrect lengths.
- **`NON_NUMERIC.txt`**: Tests for SSCC codes with non-numeric characters.
- **`NONE.txt`**: Valid SSCC codes.

#### Running Tests
To run all tests:
```sh
./sscc --test
```

To run a specific test:
```sh
./sscc tests/example.txt
```
