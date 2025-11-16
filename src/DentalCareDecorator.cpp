#include "DentalCareDecorator.h"
#include <stdexcept>
#include <iostream>

DentalCareDecorator::DentalCareDecorator(AppointmentService* app, const std::string& petSpecies): ServiceDecorator(app)
{

    if (petSpecies != "Pisica" && petSpecies != "Caine")
    {
        throw std::invalid_argument("Ingrijirea dentara este un serviciu strict pentru caini si pisici.");
    }
}

std::string DentalCareDecorator::getDescription() const
{
    return ServiceDecorator::getDescription() + " + Ingrijire dentara";
}

int DentalCareDecorator::getCost() const
{
    return ServiceDecorator::getCost() + 150;
}
