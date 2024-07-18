#include <iostream>

class OpeException : public std::exception {
public:
    OpeException(const std::string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};