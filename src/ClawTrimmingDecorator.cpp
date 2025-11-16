#include "ClawTrimmingDecorator.h"
#include <stdexcept>
#include <iostream>

ClawTrimmingDecorator::ClawTrimmingDecorator(AppointmentService* app, const std::string& petSpecies): ServiceDecorator(app)
{

    if (petSpecies != "Pisica")
    {
        throw std::invalid_argument("Taierea gherutelor este un serviciu strict pentru pisici.");
    }
}

std::string ClawTrimmingDecorator::getDescription() const
{
    return ServiceDecorator::getDescription() + " + Taiere gherute";
}

int ClawTrimmingDecorator::getCost() const
{
    return ServiceDecorator::getCost() + 400;
}
