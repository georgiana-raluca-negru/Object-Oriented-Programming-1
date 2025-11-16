#include "GroomingDecorator.h"
#include <stdexcept>
#include <iostream>

GroomingDecorator::GroomingDecorator(AppointmentService* app, const std::string& species): ServiceDecorator(app), petSpecies(species)
{

    if (petSpecies != "Pisica" && petSpecies != "Caine")
    {
        throw std::invalid_argument("");
    }
}

std::string GroomingDecorator::getDescription() const
{
    return ServiceDecorator::getDescription() + " + Ingrijire corporala";
}

int GroomingDecorator::getCost() const
{
    int cost = ServiceDecorator::getCost();

    if (petSpecies == "Pisica")
    {
        cost += 60;
    }
    else if (petSpecies == "Caine")
    {
        cost += 80;
    }

    return cost;
}
