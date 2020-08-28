#include <exception>

#include "MessageException.hpp"

MessageException::MessageException (const char* message) : std::exception() {
       this->errorMessage = message;
}
    
const char* MessageException::what() const noexcept {
       return this->errorMessage;
}
