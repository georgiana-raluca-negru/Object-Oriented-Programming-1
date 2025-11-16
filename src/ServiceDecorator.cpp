#include "ServiceDecorator.h"

ServiceDecorator::ServiceDecorator(AppointmentService* app): appointment(app) {}

ServiceDecorator::~ServiceDecorator()
{
    delete appointment;
}

std::string ServiceDecorator::getDescription() const
{
    return appointment->getDescription();
}

int ServiceDecorator::getCost() const
{
    return appointment->getCost();
}
