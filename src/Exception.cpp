#include "Exception.h"

const char* failException::what() const noexcept
{
    return "Input invalid! Te rog sa introduci un numar intreg valid.";
}