#ifndef HELPET_DENTALCAREDECORATOR_H
#define HELPET_DENTALCAREDECORATOR_H

#include "ServiceDecorator.h"

class DentalCareDecorator : public ServiceDecorator
{
public:
    DentalCareDecorator(AppointmentService* app, const std::string& petSpecies);

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_DENTALCAREDECORATOR_H