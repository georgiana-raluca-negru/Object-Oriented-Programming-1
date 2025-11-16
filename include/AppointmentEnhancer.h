#ifndef HELPET_APPOINTMENTENHANCER_H
#define HELPET_APPOINTMENTENHANCER_H

#include "Appointment.h"
#include "AppointmentService.h"

class BaseAppointment;
class GroomingDecorator;
class ClawTrimmingDecorator;
class DentalCareDecorator;
class MicroChippingDecorator;

class AppointmentEnhancer
{
    Appointment* baseAppointment;
    AppointmentService* enhancedService;
    std::string petSpecies;

public:
    AppointmentEnhancer(Appointment* appointment);
    ~AppointmentEnhancer();

    void addGrooming();
    void addDeclawing();
    void addDentalCare();
    void addMicrochipping(const std::string& type = "standard");

    std::string getPetSpecies() const;
    bool isServiceAvailable(const std::string& serviceName) const;
    bool hasAvailableServices() const;

    std::string getServicesOnlyDescription() const;
    std::string getFullDescription() const;
    int getTotalCost() const;

    void performAllServices() const;
    void displayEnhancedInfo() const;
    void displayAvailableServices() const;
};

#endif //HELPET_APPOINTMENTENHANCER_H