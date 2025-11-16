#ifndef HELPET_UTILITY_H
#define HELPET_UTILITY_H

#include <vector>
#include <cstdlib>

template<class T>
T minElement(std::vector<T> &array)
{
    if(array.size() <= 0)
        throw std::invalid_argument("Lista data nu are cel putin un element.\n");
    T min = array[0];
    for(int i = 1; i < array.size(); i++)
    {
        if(array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

#endif //HELPET_UTILITY_H