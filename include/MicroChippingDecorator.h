#ifndef HELPET_MICROCHIPPINGDECORATOR_H
#define HELPET_MICROCHIPPINGDECORATOR_H

#include "ServiceDecorator.h"

class MicrochippingDecorator : public ServiceDecorator
{
    std::string chipType;

public:
    MicrochippingDecorator(AppointmentService* app, const std::string& petSpecies, const std::string& type = "standard");

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_MICROCHIPPINGDECORATOR_H