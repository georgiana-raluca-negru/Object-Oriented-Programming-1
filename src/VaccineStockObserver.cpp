#include "VaccineStockObserver.h"
#include "Vaccine.h"
#include <iostream>
#include <algorithm>

void VaccineStockNotifier::onStockChanged(const Vaccine* vaccine, int oldStock, int newStock)
{

    if (newStock == 0 && oldStock > 0)
    {
        std::cout<<"\n\033[31mALERTA CRITICA: Vaccinul "<<vaccine->getName()<<" (ID: " << vaccine->getID()<<") este EPUIZAT!\033[0m\n"<<std::endl;
    }
    else if (newStock > 0 && newStock <= 10 && oldStock >= 10)
    {
        std::cout<<"\n\033[38;5;214mALERTA: Vaccinul "<< vaccine->getName()<<" (ID: "<<vaccine->getID()<<") are doar "<<newStock<<" doze ramase!\033[0m\n"<<std::endl;
    }
    else if (newStock > 10 && newStock <= 25 && oldStock >= 25)
    {
        std::cout<<"\n\033[33mAVERTISMENT: Vaccinul "<<vaccine->getName()<<" (ID: "<<vaccine->getID()<<") are doar " << newStock<<" doze ramase!\033[0m\n"<<std::endl;
    }

    if (oldStock == 0 && newStock > 0)
    {
        std::cout<<"\n\033[92mREAPROVIZIONARE: Vaccinul "<<vaccine->getName()<<" (ID: "<<vaccine->getID()<<") a fost reaprovizionat cu "<<newStock<<" doze!\033[0m\n"<<std::endl;
    }
}

void VaccineSubject::addObserver(VaccineObserver* observer)
{
    if (observer != nullptr)
    {
        observers.push_back(observer);
    }
}

void VaccineSubject::removeObserver(VaccineObserver* observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        observers.erase(it);
    }
}

void VaccineSubject::notifyObservers(const Vaccine* vaccine, int oldStock, int newStock)
{
    for (auto observer : observers)
    {
        observer->onStockChanged(vaccine, oldStock, newStock);
    }
}