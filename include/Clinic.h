#ifndef HELPET_CLINIC_H
#define HELPET_CLINIC_H

#include <string>
#include <vector>
#include <iostream>
#include "Room.h"
#include "Appointment.h"
#include "Vaccine.h"

class Clinic
{
    std::string Name;
    std::vector<Room*> Rooms;
    std::vector<Appointment> Appointments;
    std::vector<Doctor*> Doctors;
    std::vector<Administrator> Administrators;
    std::vector<Vaccine> Vaccines;

    static Clinic* instanta;

    Clinic();
    Clinic(const Clinic& other);
    Clinic& operator=(const Clinic& other);

public:

    static Clinic* getInstanta();
    static void deleteInstanta();
    ~Clinic();
    std::string getName() const;
    Appointment& getAppointment(int index);
    template<class T> T& getElement(std::vector<T>& array, int index);
    template<class T> T* getElement(std::vector<T*>& array, int index);
    template<class T> void displayList(std::vector<T>& array, const std::string& title);
    template<class T> void displayList(std::vector<T*>& array, const std::string& title);
    template<class T> T getRandomElement(std::vector<T>& array);
    bool isVaccine(int ID) const;
    Doctor* getDoctor(int index) const;
    int nextHOD() const;
    Administrator& getAdministrator(int index);
    Room* getRoom(int index);
    void deleteDoctor(int index);
    void deleteVaccine(int index);
    void cancelAppointment(int index);
    bool isDepartment(std::string& Department);
    void addRoom(Room* room);
    bool isRoom(int number);
    void addVaccine(const Vaccine& vaccine);
    void addDoctor(Doctor* doctor);
    void addAppointment(const Appointment& appointment);
    Vaccine& getVaccine(int index);
    Vaccine& getVaccineID(int ID);
    Room* randomAvailableConsultationRoom();
    ConsultationRoom* randomAvailableConsultationRoomUltrasounnd();
    Room* randomAvailableOperationRoom();
    Room* randomConsultationRoom();
    ConsultationRoom* randomConsultationRoomUltrasound();
    Room* randomOperationRoom();
    Doctor* randomDoctor();
    void menu();
    void receiveAppointment();
    void administrativeDetails();
    void changeDetails(int index);
    void changeTelephone(int index);
    void changePetName(int index);
    void changePetWeight(int index);
    void changeDoctor(int index);
    void Deworming(int index);
    void Vaccination(int index);
    void addNewAppointment();
    void fireDoctor();
    void addNewRoom();
    void addNewDoctor();
    void changeVaccinePrice();
    void changeVaccineStock();
    void deleteVaccineFromList();
    void cancelAppointmentFromList();
    bool validTelephone(const std::string& Telephone);
    void handleSpecialServices(int appointmentIndex);
    bool validName(const std::string& Name);
};

template<class T>
T& Clinic::getElement(std::vector<T>& array, int index)
{
    return array.at(index);
}

template<class T>
T* Clinic::getElement(std::vector<T*>& array, int index)
{
    return array.at(index);
}

template<class T>
void Clinic::displayList(std::vector<T>& array, const std::string& title)
{
    std::cout<<"----------------"<<title<<"-------------------"<<std::endl<<std::endl;
    for(const auto& element : array)
    {
        element.displayInfo();
        std::cout<<std::endl;
    }
    std::cout<<"------------------------------------------------"<<std::endl;
}

template<class T>
void Clinic::displayList(std::vector<T*>& array, const std::string& title)
{
    std::cout<<"----------------"<<title<<"-------------------"<<std::endl<<std::endl;
    for(const auto& element : array)
    {
        element->displayInfo();
        std::cout<<std::endl;
    }
    std::cout<<"------------------------------------------------"<<std::endl;
}

template<class T>
T Clinic::getRandomElement(std::vector<T> &array)
{
    int random_index = rand() % array.size();
    return array[random_index];
}

#endif //HELPET_CLINIC_H