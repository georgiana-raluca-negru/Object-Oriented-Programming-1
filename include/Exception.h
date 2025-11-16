#ifndef HELPET_EXCEPTION_H
#define HELPET_EXCEPTION_H

#include <exception>

class failException : public std::exception
{
public:
    const char* what() const noexcept override;
};

#endif //HELPET_EXCEPTION_H