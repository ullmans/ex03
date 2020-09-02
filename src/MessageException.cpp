#include <exception>
#include <string>

#include "MessageException.hpp"

MessageException::MessageException (const char* message) : std::exception() {
       this->errorMessage = message;
}

MessageException::MessageException (const std::string& message) : std::exception() {
       this->errorMessage = message.c_str();
}
    
const char* MessageException::what() const noexcept {
       return this->errorMessage;
}
