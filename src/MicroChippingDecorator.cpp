#include "MicroChippingDecorator.h"
#include <stdexcept>
#include <iostream>

MicrochippingDecorator::MicrochippingDecorator(AppointmentService* app,const std::string& petSpecies,const std::string& type): ServiceDecorator(app), chipType(type)
{

    if (petSpecies != "Pisica" && petSpecies != "Caine")
    {
        throw std::invalid_argument("Microciparea este strict pentru caini si pisici.\n");
    }
}

std::string MicrochippingDecorator::getDescription() const
{
    return ServiceDecorator::getDescription() + " + Microcipare " + chipType;
}

int MicrochippingDecorator::getCost() const
{
    int cost = ServiceDecorator::getCost();

    if (chipType == "standard")
    {
        cost += 80;
    }
    else if (chipType == "premium")
    {
        cost += 120;
    }

    return cost;
}
