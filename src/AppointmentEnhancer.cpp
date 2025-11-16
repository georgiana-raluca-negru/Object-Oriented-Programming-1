#include "AppointmentEnhancer.h"
#include "BaseAppointment.h"
#include "GroomingDecorator.h"
#include "ClawTrimmingDecorator.h"
#include "DentalCareDecorator.h"
#include "MicrochippingDecorator.h"
#include <iostream>

AppointmentEnhancer::AppointmentEnhancer(Appointment* appointment): baseAppointment(appointment)
{
    enhancedService = new BaseAppointment();

    petSpecies = baseAppointment->getOwner().getPet()->getSpecies();
}

AppointmentEnhancer::~AppointmentEnhancer()
{
    delete enhancedService;
}

void AppointmentEnhancer::addGrooming()
{
    AppointmentService* oldService = enhancedService;
    enhancedService = new GroomingDecorator(oldService, petSpecies);
}

void AppointmentEnhancer::addDeclawing()
{
    AppointmentService* oldService = enhancedService;
    enhancedService = new ClawTrimmingDecorator(oldService, petSpecies);
}

void AppointmentEnhancer::addDentalCare()
{
    AppointmentService* oldService = enhancedService;
    enhancedService = new DentalCareDecorator(oldService, petSpecies);
}

void AppointmentEnhancer::addMicrochipping(const std::string& type)
{
    AppointmentService* oldService = enhancedService;
    enhancedService = new MicrochippingDecorator(oldService, petSpecies, type);
}

std::string AppointmentEnhancer::getPetSpecies() const
{
    return petSpecies;
}

bool AppointmentEnhancer::isServiceAvailable(const std::string& serviceName) const
{
    if (petSpecies != "Pisica" && petSpecies != "Caine")
    {
        return false;
    }

    if (serviceName == "declawing")
    {
        return petSpecies == "Pisica";
    }

    return true;
}


std::string AppointmentEnhancer::getServicesOnlyDescription() const
{
    std::string fullDesc = enhancedService->getDescription();
    std::string baseDesc = "Servicii";

    if (fullDesc.find(baseDesc) == 0)
    {
        if (fullDesc.length() > baseDesc.length())
        {
            return fullDesc.substr(baseDesc.length() + 3);
        }
        else
        {
            return "";
        }
    }
    return fullDesc;
}

std::string AppointmentEnhancer::getFullDescription() const
{
    return enhancedService->getDescription();
}

int AppointmentEnhancer::getTotalCost() const
{
    return enhancedService->getCost();
}

void AppointmentEnhancer::displayEnhancedInfo() const
{
    baseAppointment->displayInfo();
    std::cout << "        Servicii suplimentare: " << getFullDescription() <<"\n";
    std::cout << "        Cost total: " << getTotalCost() << " lei\n";
}

void AppointmentEnhancer::displayAvailableServices() const
{

    std::cout << "Servicii speciale disponibile pentru " << petSpecies << ":\n";
    std::cout << "1. Ingrijire dentara\n";
    std::cout << "2. Microcipare\n";
    std::cout << "3. Ingrijire corporala\n";

    if (petSpecies == "Pisica") {
        std::cout << "4. Taiere gheare\n";
    }
    std::cout<<"0. Exit\n";
}