#ifndef HELPET_BASEAPPOINTMENT_H
#define HELPET_BASEAPPOINTMENT_H

#include "AppointmentService.h"

class BaseAppointment : public AppointmentService
{
    std::string type;

public:
    BaseAppointment(const std::string& appointmentType = "Servicii");

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_BASEAPPOINTMENT_H