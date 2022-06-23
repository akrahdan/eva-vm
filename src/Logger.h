#ifndef Logger_h
#define Logger_h
#include <sstream>
#include <iostream>
class ErrorLogMessage : public std::basic_ostringstream<char> {
  public:
  ~ErrorLogMessage() {
    fprintf(stderr, "Fatal Error: %s\n", str().c_str());
    exit(EXIT_FAILURE);
  }
};

#define DIE ErrorLogMessage()

#define log(value) std::cout << #value << " = " << (value) << "\n";
#endif