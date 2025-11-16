#ifndef HELPET_CLAWTRIMMINGDECORATOR_H
#define HELPET_CLAWTRIMMINGDECORATOR_H

#include "ServiceDecorator.h"

class ClawTrimmingDecorator : public ServiceDecorator
{
public:
    ClawTrimmingDecorator(AppointmentService* app, const std::string& petSpecies);

    std::string getDescription() const override;
    int getCost() const override;
};

#endif //HELPET_CLAWTRIMMINGDECORATOR_H