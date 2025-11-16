#ifndef HELPET_APPOINTMENTSERVICE_H
#define HELPET_APPOINTMENTSERVICE_H

#include <string>

class AppointmentService
{
public:
    virtual ~AppointmentService() = default;
    virtual std::string getDescription() const = 0;
    virtual int getCost() const = 0;
};

#endif //HELPET_APPOINTMENTSERVICE_H