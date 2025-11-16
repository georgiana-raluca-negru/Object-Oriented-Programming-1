
#include "Clinic.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(0));

    Clinic *clinic=Clinic::getInstanta();
    clinic->menu();
    Clinic::deleteInstanta();
    return 0;
}