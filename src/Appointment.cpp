#include "Appointment.h"

int Appointment::numberAppointments = 0;

Appointment::Appointment(Owner owner, Doctor* doctor)
    : owner(owner), doctor(doctor), room(nullptr), isTaken(false)
{
    numberAppointments++;
}

Doctor* Appointment::getDoctor() const
{
    return doctor;
}

Owner& Appointment::getOwner()
{
    return owner;
}

int Appointment::getAppointmentNumber()
{
    return numberAppointments;
}

void Appointment::decreaseNumberAppointments()
{
    numberAppointments--;
}

bool Appointment::Status() const
{
    return isTaken;
}

void Appointment::setTaken(Room* room)
{
    isTaken = true;
    this->room = room;
}

Room* Appointment::getRoom() const
{
    return room;
}

void Appointment::setDoctor(Doctor* doctor)
{
    this->doctor = doctor;
}

void Appointment::displayInfo() const
{
    owner.displayInfo();
    std::cout << std::endl;
    owner.getPet()->displayInfo();
    std::cout << std::endl;
    doctor->displayInfo();
    std::cout << std::endl;
    std::cout << "        Status programare: " << (isTaken ? "preluata" : "nepreluata") << std::endl;
    std::cout << std::endl;
    if (isTaken)
    {
        std::cout << "        Sala: " << room->getNumber() << std::endl;
    }
    std::cout << std::endl;
}