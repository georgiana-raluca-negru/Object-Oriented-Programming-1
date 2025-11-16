#include "BaseAppointment.h"
#include <iostream>

BaseAppointment::BaseAppointment(const std::string& appointmentType): type(appointmentType) {}

std::string BaseAppointment::getDescription() const
{
    return type;
}

int BaseAppointment::getCost() const
{
    return 0;
}