#ifndef HELPET_SERVICEDECORATOR_H
#define HELPET_SERVICEDECORATOR_H

#include "AppointmentService.h"

class ServiceDecorator : public AppointmentService
{
protected:
    AppointmentService* appointment;

public:
    ServiceDecorator(AppointmentService* app);
    virtual ~ServiceDecorator();

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_SERVICEDECORATOR_H