#pragma once

#include <exception>

/**
 * a class of exceptions so the program can return the exception if there is an error.
 */
class MessageException : public std::exception {
public:
    /**
    * @brief constractor- get an array of chars ("string").
    */
    MessageException(const char*);

    /**
     * @brief override- print the message of the exception to the screen.
     */
    const char* what() const noexcept override;

private:
    /**
     * error message.
     */
    const char* errorMessage;
    
};