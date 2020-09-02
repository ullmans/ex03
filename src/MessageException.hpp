#ifndef MESSAGE_EXCEPTION_H
#define MESSAGE_EXCEPTION_H

#include <exception>
#include <string>

/**
 * a class of exceptions so the program can return the exception if there is an error.
 */
class MessageException : public std::exception {
public:
    /**
    * @brief constractor- get an array of chars ("string").
    */
    MessageException(const char* message);

    /**
    * @brief constractor- get an std::string.
    */
    MessageException(const std::string& message);

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

#endif