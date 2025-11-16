#ifndef HELPET_GROOMINGDECORATOR_H
#define HELPET_GROOMINGDECORATOR_H

#include "ServiceDecorator.h"

class GroomingDecorator : public ServiceDecorator
{
    std::string petSpecies;

public:
    GroomingDecorator(AppointmentService* app, const std::string& species);

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_GROOMINGDECORATOR_H