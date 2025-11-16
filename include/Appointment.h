#ifndef HELPET_APPOINTMENT_H
#define HELPET_APPOINTMENT_H

#include "Person.h"
#include "Room.h"

class Appointment
{
    static int numberAppointments;
    Owner owner;
    Doctor* doctor;
    Room* room;
    bool isTaken;

public:
    Appointment(Owner owner = Owner(), Doctor* doctor = nullptr);

    Doctor* getDoctor() const;
    Owner& getOwner();
    static int getAppointmentNumber();
    static void decreaseNumberAppointments();
    bool Status() const;
    void setTaken(Room* room);
    Room* getRoom() const;
    void setDoctor(Doctor* doctor);
    void displayInfo() const;
};

#endif //HELPET_APPOINTMENT_H