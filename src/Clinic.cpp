#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <limits>

#include "Clinic.h"
#include "AppointmentEnhancer.h"

Clinic* Clinic::instanta = nullptr;

Clinic::Clinic()
{
    std::string line, ClinicName;

    std::vector<Doctor*> Doctors;
    std::vector<Administrator> Administrators;
    std::vector<Appointment> Appointments;
    std::vector<int> Prices, Stocks;
    std::vector<std::string> VaccineNames, Types;
    std::vector<Vaccine> Vaccines;
    std::vector<Vaccine*> Vaccines1;
    std::vector<Room*> Rooms;
    int ok=0;

    std::ifstream file("resources/appointments.in");
    if(!file.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului" << std::endl;
    }
    else
    {
        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            if (!line.empty())
            {
                if (line.rfind("Nume clinica veterinara: ", 0) == 0)
                {
                    ClinicName = line.substr(25);
                }
                else if (line.rfind("Nume vaccinuri: ", 0) == 0)
                {
                    line = line.substr(16);
                    ss.clear();
                    ss.str(line);
                    std::string Name;
                    while (std::getline(ss, Name, ','))
                    {
                        VaccineNames.push_back(Name);
                    }
                }
                else if (line.rfind("Pret vaccinuri: ", 0) == 0)
                {
                    line = line.substr(16);
                    ss.clear();
                    ss.str(line);
                    int Price;
                    while (ss >> Price)
                    {
                        Prices.push_back(Price);
                    }
                }
                else if (line.rfind("Stoc vaccinuri: ", 0) == 0)
                {
                    line = line.substr(16);
                    ss.clear();
                    ss.str(line);
                    int Stock;
                    while (ss >> Stock)
                    {
                        Stocks.push_back(Stock);
                    }
                }
                else if (line.rfind("Mentiuni: ", 0) == 0)
                {
                    line=line.substr(10);
                    ss.clear();
                    ss.str(line);
                    std::string Type;
                    while(std::getline(ss,Type,','))
                    {
                        Types.push_back(Type);
                    }
                }
                else if(line == "SALI DE CONSULTATIE")
                {
                    while(std::getline(file, line))
                    {
                        if(line == "SFARSIT")
                            break;
                        else
                        {
                            std::string Number, Ultrasound;
                            int nr;
                            bool hasUltrasound;
                            std::istringstream ss(line);
                            std::getline(ss, Number, ' ');
                            std::getline(ss, Ultrasound);
                            nr = std::stoi(Number);
                            if(Ultrasound == "ecograf")
                                hasUltrasound = true;
                            else
                                hasUltrasound = false;
                            Rooms.push_back(new ConsultationRoom(nr, nr / 10, hasUltrasound));

                        }
                    }
                }
                else if(line == "SALI DE OPERATIE")
                {
                    while(std::getline(file, line))
                    {
                        if(line == "SFARSIT")
                            break;
                        else
                        {
                            std::string Number, Sterile;
                            int nr;
                            bool isSterile;
                            std::istringstream ss(line);
                            std::getline(ss, Number, ' ');
                            std::getline(ss, Sterile);
                            nr = std::stoi(Number);
                            if(Sterile == "sterilizata")
                                isSterile = true;
                            else
                                isSterile = false;
                            Rooms.push_back(new OperationRoom(nr, nr / 10, isSterile));

                        }
                    }
                }
                else if (line == "DIRECTOR DE DEPARTAMENT")
                {
                    std::string LastName, FirstName, Telephone, Department, Specialization, gender;
                    Gender genderEnum;
                    int Age, yearOfExperience;
                    while(std::getline(file, line))
                    {
                        if(line == "SFARSIT")
                            break;
                        else
                        {
                            std::istringstream ss(line);
                            if(line.rfind("Nume si prenume: ", 0) == 0)
                            {
                                line = line.substr(17);
                                ss.clear();
                                ss.str(line);
                                std::getline(ss, LastName, ' ');
                                std::getline(ss, FirstName);
                            }
                            else if(line.rfind("Telefon: ", 0) == 0)
                            {
                                Telephone = line.substr(9);
                            }
                            else if(line.rfind("Gen: ", 0) == 0)
                            {
                                gender = line.substr(5);
                                if ( gender == "Feminin")
                                {
                                    genderEnum = Gender::Female;
                                }
                                else if (gender == "Masculin")
                                {
                                    genderEnum = Gender::Male;
                                }
                                else
                                {
                                    genderEnum = Gender::Unknown;
                                }
                            }
                            else if(line.rfind("Varsta: ", 0) == 0)
                            {
                                Age = std::stoi(line.substr(8));
                            }
                            else if(line.rfind("Departament: ", 0) == 0)
                            {
                                Department=line.substr(13);
                            }
                            else if(line.rfind("Specializare: ", 0) == 0)
                            {
                                Specialization=line.substr(14);
                            }
                            else if(line.rfind("Ani experienta: ", 0) == 0)
                            {
                                yearOfExperience=std::stoi(line.substr(16));
                            }
                        }
                    }
                    Doctors.push_back(new HeadOfDepartment(LastName, FirstName, Telephone, genderEnum, Age, Specialization, yearOfExperience, Department));

                }
                else if (line == "ADMINISTRATOR")
                {
                    std::string LastName, FirstName, Telephone, Department, gender;
                    Gender genderEnum;
                    int Age;
                    while(std::getline(file, line))
                    {
                        if(line == "SFARSIT")
                            break;
                        else
                        {
                            std::istringstream ss(line);
                            if(line.rfind("Nume si prenume: ", 0) == 0)
                            {
                                line = line.substr(17);
                                ss.clear();
                                ss.str(line);
                                std::getline(ss, LastName, ' ');
                                std::getline(ss, FirstName);
                            }
                            else if(line.rfind("Telefon: ", 0) == 0)
                            {
                                Telephone = line.substr(9);
                            }
                            else if(line.rfind("Gen: ", 0) == 0)
                            {
                                gender = line.substr(5);
                                if ( gender == "Feminin")
                                {
                                    genderEnum = Gender::Female;
                                }
                                else if (gender == "Masculin")
                                {
                                    genderEnum = Gender::Male;
                                }
                                else
                                {
                                    genderEnum = Gender::Unknown;
                                }
                            }
                            else if(line.rfind("Varsta: ", 0) == 0)
                            {
                                Age = std::stoi(line.substr(8));
                            }
                            else if(line.rfind("Departament: ", 0) == 0)
                            {
                                Department=line.substr(13);
                            }
                        }
                    }
                    Administrators.push_back(Administrator(LastName, FirstName, Telephone, genderEnum, Age, Department));
                }
                else if (line == "MEDIC VETERINAR")
                {
                    std::string LastName, FirstName, Telephone, Specialization, gender;
                    Gender genderEnum;
                    int Age, yearOfExperience;
                    while(std::getline(file, line))
                    {
                        if(line == "SFARSIT")
                            break;
                        else
                        {
                            std::istringstream ss(line);
                            if(line.rfind("Nume si prenume: ", 0) == 0)
                            {
                                line = line.substr(17);
                                ss.clear();
                                ss.str(line);
                                std::getline(ss, LastName, ' ');
                                std::getline(ss, FirstName);
                            }
                            else if(line.rfind("Telefon: ", 0) == 0)
                            {
                                Telephone = line.substr(9);
                            }
                            else if(line.rfind("Gen: ", 0) == 0)
                            {
                                gender = line.substr(5);
                                if ( gender == "Feminin")
                                {
                                    genderEnum = Gender::Female;
                                }
                                else if (gender == "Masculin")
                                {
                                    genderEnum = Gender::Male;
                                }
                                else
                                {
                                    genderEnum = Gender::Unknown;
                                }
                            }
                            else if(line.rfind("Varsta: ", 0) == 0)
                            {
                                Age = std::stoi(line.substr(8));
                            }
                            else if(line.rfind("Specializare: ", 0) == 0)
                            {
                                Specialization=line.substr(14);
                            }
                            else if(line.rfind("Ani experienta: ", 0) == 0)
                            {
                                yearOfExperience=std::stoi(line.substr(16));
                            }
                        }
                    }
                    Doctors.push_back(new Doctor(LastName, FirstName, Telephone, genderEnum, Age, Specialization, yearOfExperience));
                }
                else if(line == "INCEPUT PROGRAMARE")
                {
                    std::string Name, Species, gender1, gender2, featherColor, Size, TrainingStatus, furLength, LastName1, FirstName1, LastName2, FirstName2, Telephone, Date;
                    bool isTrained;
                    int Age1, Weight, Age2;
                    Gender genderEnum1, genderEnum2;
                    Pet* pet=nullptr;
                    Doctor* doctor=nullptr;
                    while (std::getline(file, line))
                    {
                        if(line == "SFARSIT PROGRAMARE")
                            break;
                        else
                        {
                            std::istringstream ss(line);
                            if (line.rfind("Nume si prenume: ", 0) == 0)
                            {
                                line = line.substr(17);
                                ss.clear();
                                ss.str(line);
                                std::getline(ss, LastName1, ' ');
                                std::getline(ss, FirstName1);
                            }
                            else if(line.rfind("Telefon: ", 0) == 0)
                            {
                                Telephone = line.substr(9);
                            }
                            else if(line.rfind("Gen: ", 0) == 0)
                            {
                                gender1 = line.substr(5);
                                if ( gender1 == "Feminin")
                                {
                                    genderEnum1 = Gender::Female;
                                }
                                else if (gender1 == "Masculin")
                                {
                                    genderEnum1 = Gender::Male;
                                }
                                else
                                {
                                    genderEnum1 = Gender::Unknown;
                                }
                            }
                            else if(line.rfind("Varsta: ", 0) == 0)
                            {
                                Age1 = std::stoi(line.substr(8));
                            }
                            else if(line.rfind("Medic veterinar: ", 0) == 0)
                            {
                                line = line.substr(17);
                                ss.clear();
                                ss.str(line);
                                std::getline(ss, LastName2, ' ');
                                std::getline(ss, FirstName2);
                            }
                            else if (line.rfind("Nume pacient: ", 0) == 0)
                            {
                                Name = line.substr(14);
                            }
                            else if(line.rfind("Gen pacient: ", 0) == 0)
                            {
                                gender2 = line.substr(13);
                                if ( gender2 == "Femela")
                                {
                                    genderEnum2 = Gender::Female;
                                }
                                else if (gender2 == "Mascul")
                                {
                                    genderEnum2 = Gender::Male;
                                }
                                else
                                {
                                    genderEnum2 = Gender::Unknown;
                                }
                            }
                            else if (line.rfind("Greutate(in gr): ", 0) == 0)
                            {
                                Weight = std::stoi(line.substr(17));
                            }
                            else if (line.rfind("Varsta(in ani): ", 0) == 0)
                            {
                                Age2 = std::stoi(line.substr(16));
                            }
                            else if (line.rfind("Specie: ", 0) == 0)
                            {
                                Species = line.substr(8);
                                if(Species == "Pisica" || Species == "Caine")
                                {
                                    std::getline(file,line);
                                    line = line.substr(21);
                                    ss.clear();
                                    ss.str(line);
                                    int id;
                                    while (ss >> id)
                                    {
                                        for (int i = 0; i < Vaccines.size(); i++)
                                        {
                                            if (id == Vaccines[i].getID())
                                            {
                                                Vaccines1.push_back(&Vaccines[i]);
                                                break;
                                            }
                                        }
                                    }
                                    std::getline(file, line);

                                    if(Species == "Pisica")
                                    {
                                        furLength = line.substr(17);
                                    }

                                    else
                                    {
                                        Size= line.substr(7);

                                        std::getline(file, line);
                                        TrainingStatus = line.substr(8);
                                        isTrained = (TrainingStatus == "Da");
                                    }

                                }
                                else if(Species == "Pasare")
                                {
                                    std::getline(file, line);
                                    featherColor = line.substr(15);
                                }
                            }
                        }
                    }

                    if(Species == "Pisica")
                    {
                        pet = new Cat(Name, Weight, Age2, furLength, genderEnum2, Vaccines1);
                        Vaccines1.clear();
                    }
                    else if(Species == "Caine")
                    {
                        pet = new Dog(Name, Weight, Age2, Size, genderEnum2, isTrained, Vaccines1);
                        Vaccines1.clear();
                    }
                    else if(Species == "Pasare")
                    {
                        pet = new Bird(Name, Weight, Age2, genderEnum2, featherColor);
                    }
                    else
                    {
                        pet = new Pet(Name, Weight, Age2, Species, genderEnum2);
                    }
                    for( Doctor* d : Doctors )
                    {
                        if(d->getFirstName() == FirstName2 && d->getLastName() == LastName2)
                        {
                            doctor = d;
                            break;
                        }
                    }
                    if(doctor)
                    {
                        Appointments.push_back(Appointment(Owner(LastName1, FirstName1, Telephone, genderEnum1, Age1, pet), doctor));

                    }
                }
            }
            if(VaccineNames.size() && Prices.size() && Stocks.size() && Types.size() && !ok)
            {
                for (int i = 0; i < VaccineNames.size(); i++)
                {
                    Vaccines.push_back(Vaccine(VaccineNames[i], Prices[i], i + 1, Stocks[i], Types[i]));
                }
                ok=1;
                VaccineNames.clear();
                Prices.clear();
                Stocks.clear();
                Types.clear();
            }
        }
    }

    file.close();

    this->Name = ClinicName;
    this->Rooms = Rooms;
    this->Doctors = Doctors;
    this->Vaccines = Vaccines;
    this->Administrators = Administrators;
    this->Appointments = Appointments;
}

Clinic::Clinic(const Clinic& other)
{
    Name = other.Name;
    Vaccines = other.Vaccines;
    Administrators = other.Administrators;


    for (auto doctor : other.Doctors)
    {
        if (doctor)
            Doctors.push_back(doctor->clone());
    }

    Appointments = other.Appointments;

    for (size_t i = 0; i < other.Appointments.size(); i++)
    {
        Doctor* oldDoctor = other.Appointments[i].getDoctor();
        if (oldDoctor)
        {
            for (size_t j = 0; j < other.Doctors.size(); j++)
            {
                if (other.Doctors[j]->getFirstName() == oldDoctor->getFirstName() &&
                        other.Doctors[j]->getLastName() == oldDoctor->getLastName())
                {
                    Appointments[i].setDoctor(Doctors[j]);
                    break;
                }
            }
        }
    }

    for (auto room : other.Rooms)
    {
        if (room) Rooms.push_back(room->clone());
    }
}

Clinic& Clinic::operator=(const Clinic& other)
{
    if (this == &other)
        return *this;

    for (auto doctor : Doctors)
        delete doctor;
    Doctors.clear();

    for (auto room : Rooms)
        delete room;
    Rooms.clear();

    Name = other.Name;
    Vaccines = other.Vaccines;
    Administrators = other.Administrators;

    for (auto doctor : other.Doctors)
        if (doctor)
            Doctors.push_back(doctor->clone());

    Appointments = other.Appointments;

    for (size_t i = 0; i < other.Appointments.size(); i++)
    {
        Doctor* oldDoctor = other.Appointments[i].getDoctor();
        if (oldDoctor)
        {
            for (size_t j = 0; j < other.Doctors.size(); j++)
            {
                if (other.Doctors[j]->getFirstName() == oldDoctor->getFirstName() &&
                        other.Doctors[j]->getLastName() == oldDoctor->getLastName())
                {
                    Appointments[i].setDoctor(Doctors[j]);
                    break;
                }
            }
        }
    }

    for (auto room : other.Rooms)
        if (room) Rooms.push_back(room->clone());

    return *this;
}

Clinic* Clinic::getInstanta()
{
    if(instanta == nullptr)
        instanta = new Clinic();
    return instanta;
}

void Clinic::deleteInstanta()
{
    if(instanta != nullptr)
        delete instanta;
    instanta = nullptr;
}

Clinic::~Clinic()
{
    for(const auto& doctor : Doctors)
    {
        delete doctor;
    }
    for(const auto& room: Rooms)
    {
        delete room;
    }
    Vaccines.clear();
    Administrators.clear();
    Appointments.clear();
    Doctors.clear();
    Rooms.clear();
}

std::string Clinic::getName() const
{
    return Name;
}

void Clinic::receiveAppointment()
{
    std::cout<<"Ai ales sa primesti o programare deja inregistrata. Introdu indexul unei programari pe care doresti sa o preiei (0-"<<Appointment::getAppointmentNumber() - 1<<").\n";
    int index;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>index;
            std::cout<<std::endl;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Input invalid! Te rog sa introduci un numar intreg valid intre 0 si " + std::to_string(Appointment::getAppointmentNumber() - 1)+ ".\n");
            }

            if(index < 0 || index > Appointment::getAppointmentNumber() - 1)
            {
                throw std::out_of_range("Optiune invalida! Incearca din nou (0-" + std::to_string(Appointment::getAppointmentNumber() - 1) + ").\n");
            }

            if(this->getElement(Appointments, index).Status())
            {
                throw std::logic_error("Programarea aceasta este in curs de desfasurare. Incearca din nou.\n");
            }

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"Eroare necunoscuta...Incearca din nou."<<std::endl;
        }
    }

    std::cout<<"Programarea cautata a fost gasita, iata detalii despre aceasta :\n\n";
    this->getElement(Appointments, index).displayInfo();
    std::cout<<"\nPentru ce ati venit astazi cu animalutul de companie?\n";
    std::cout<<"1. Control periodic\n";
    std::cout<<"2. Modificarea datelor referitoare la programare\n";
    std::cout<<"3. Deparazitari interne/externe\n";
    std::cout<<"4. Operatie\n";
    std::cout<<"5. Ecografie\n";

    bool ceva = false;
    int choice;

    if (dynamic_cast<Cat*>(this->getElement(Appointments,index).getOwner().getPet()) || dynamic_cast<Dog*>(this->getElement(Appointments,index).getOwner().getPet()))
    {
        std::cout<<"6. Servicii speciale\n";
        std::cout<<"7. Efectuarea unui vaccin\n";
        ceva = true;
    }

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;
            std::cout<<std::endl;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Input invalid! Te rog sa introduci un numar intreg valid intre 1 si " + std::string(ceva ? "7" : "5") + ".\n");
            }

            if(choice < 1 || choice > (ceva ? 7 : 5))
            {
                throw std::out_of_range("Optiune invalida! Incearca din nou (1-" + std::string(ceva ? "7" : "5") + ").\n");
            }

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"Eroare necunoscuta...Incearca din nou."<<std::endl;
        }
    }

    if(choice == 1 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
    {
        int nr = 0;
        if(!this->getElement(Appointments,index).getDoctor()->Availability())
        {
            std::cout<<"Medicul veterinar "<<this->getElement(Appointments, index).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index).getDoctor()->getLastName()<<" se afla in cadrul unei alte programari. Va rugam sa asteptati.\n";
            std::cout<<"Apasa tasta Enter pentru a astepta...\n";
            std::cin.ignore();
            std::cin.get();
            std::cout<<"\n";
            Doctor doctor1 = *(this->getElement(Appointments, index).getDoctor());
            Doctor doctor2 = Doctor();
            Doctor::decreaseNumberDoctors();
            for(int i = 0; i< Appointment::getAppointmentNumber(); i++)
            {
                doctor2 = *(this->getElement(Appointments, i).getDoctor());
                if( doctor1 == doctor2 && this->getElement(Appointments, i).Status())
                {
                    this->getElement(Appointments, i).getDoctor()->freeDoctor();
                    this->getElement(Appointments, i).getRoom()->exitRoom();
                    if(i < index)
                        nr++;
                    this->cancelAppointment(i);
                    Appointment::decreaseNumberAppointments();
                    break;
                }
            }
        }

        Room* room= nullptr;
        if(choice == 1 || choice == 3 || choice == 6 || choice == 7)
        {

            std::cout<<"Vom cauta o sala de consultatie in care sa va repartizam. Asteptati un moment.\n";
            std::cout<<"Apasa tasta Enter pentru a continua...\n";
            std::cin.ignore();
            std::cin.get();
            std::cout<<"\n";
            room = this->randomAvailableConsultationRoom();
            if(!room)
            {
                std::cout<<"Nu este disponibila nicio sala de consultatie momentan. Asteptati un moment.\n";
                std::cout<<"Apasa tasta Enter pentru a astepta...\n";
                std::cin.get();
                std::cout<<"\n";
                room = this->randomConsultationRoom();
                room->exitRoom();
                this->getElement(Appointments,room->getIndex()-nr).getDoctor()->freeDoctor();
                if(room->getIndex() < index)
                    nr++;
                this->cancelAppointment(room->getIndex()-nr);
                Appointment::decreaseNumberAppointments();
            }
        }
        else if(choice == 5)
        {
            std::cout<<"Vom cauta o sala de consultatie cu ecograf in care sa va repartizam. Asteptati un moment.\n";
            std::cout<<"Apasa tasta Enter pentru a continua...\n";
            std::cin.get();
            std::cout<<"\n";
            room = this->randomAvailableConsultationRoomUltrasounnd();
            if(!room)
            {
                std::cout<<"Nu este disponibila nicio sala de consultatie cu ecograf momentan. Asteptati un moment.\n";
                std::cout<<"Apasa tasta Enter pentru a astepta...\n";
                std::cin.get();
                std::cout<<"\n";
                room = this->randomConsultationRoomUltrasound();
                room->exitRoom();
                this->getElement(Appointments,room->getIndex()-nr).getDoctor()->freeDoctor();
                if(room->getIndex() < index)
                    nr++;
                this->cancelAppointment(room->getIndex()-nr);
                Appointment::decreaseNumberAppointments();
            }
        }
        else if(choice == 4)
        {
            std::cout<<"Vom cauta o sala de operatie in care sa va repartizam. Asteptati un moment.\n";
            std::cout<<"Apasa tasta Enter pentru a continua...\n";
            std::cin.ignore();
            std::cin.get();
            std::cout<<"\n";
            room = this->randomAvailableOperationRoom();
            if(!room)
            {
                std::cout<<"Nu este disponibila nicio sala de operatie momentan. Asteptati un moment.\n";
                std::cout<<"Apasa tasta Enter pentru a astepta...\n";
                std::cin.get();
                std::cout<<"\n";
                room = this->randomOperationRoom();
                room->exitRoom();
                this->getElement(Appointments, room->getIndex()-nr).getDoctor()->freeDoctor();
                if(room->getIndex() < index)
                    nr++;
                this->cancelAppointment(room->getIndex()-nr);
                Appointment::decreaseNumberAppointments();
            }

            OperationRoom* opRoom = dynamic_cast<OperationRoom*>(room);
            if(!opRoom->State())
            {
                std::cout<<"Camera de operatie nu este sterilizata. Acorda-ne un moment pentru a o curata.\n";
                std::cout<<"Apasa tasta Enter pentru a astepta...\n";
                std::cin.ignore();
                std::cin.get();
                std::cout<<"\n";
                opRoom->cleanRoom();
            }
            opRoom->afterOperation();
        }
        std::cout<<"Medicul veterinar "<<this->getElement(Appointments,index-nr).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index-nr).getDoctor()->getLastName()<<" va asteapta la sala numarul "<<room->getNumber()<<"\n";
        std::cout<<"Apasa tasta Enter pentru a intra in sala...\n";
        std::cin.get();
        std::cout<<"\n";
        room->useRoom();
        room->setIndex(index-nr);
        this->getElement(Appointments, index-nr).getDoctor()->inConsultation();
        this->getElement(Appointments, index-nr).setTaken(room);

        if(choice == 1)
        {
            std::cout<<"                        DETALIILE PACIENTULUI\n\n";
            this->getElement(Appointments, index-nr).getOwner().getPet()->displayInfo();
        }
        else if(choice == 3)
        {
            this->Deworming(index-nr);
        }
        else if(choice == 4)
        {
            std::cout<<"Actiune finalizata! Medicul veterinar "<<this->getElement(Appointments, index-nr).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index-nr).getDoctor()->getLastName()<<" a realizat cu succes operatia pacientului "<<this->getElement(Appointments, index-nr).getOwner().getPet()->getName()<<".\n";
        }
        else if(choice == 5)
        {
            std::cout<<"Actiune finalizata! Medicul veterinar "<<this->getElement(Appointments, index-nr).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index-nr).getDoctor()->getLastName()<<" a realizat o ecografie pacientului "<<this->getElement(Appointments, index-nr).getOwner().getPet()->getName()<<"."<<std::endl;
        }
        else if(choice == 6)
        {
            this->handleSpecialServices(index-nr);
        }
        else if(choice == 7)
        {
            this->Vaccination(index-nr);
        }
    }
    else if(choice == 2)
    {
        this->changeDetails(index);
    }
}

void Clinic::changeDetails(int index)
{
    std::cout<<"Ce modificare doresti sa faci?\n";
    std::cout<<"1. Schimba numarul de telefon (al proprietarului)\n";
    std::cout<<"2. Schimba numele animalutului de companie\n";
    std::cout<<"3. Inregistreaza o alta greutate a animalului\n";
    std::cout<<"4. Solicita schimbarea medicului veterinar\n";

    int choice;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;
            std::cout<<std::endl;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Input invalid! Te rog sa introduci un numar intreg valid intre 1 si 4.\n");
            }

            if(choice < 1 || choice > 4)
            {
                throw std::out_of_range("Optiune invalida! Incearca din nou (1-4).\n");
            }

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"Eroare necunoscuta...Incearca din nou."<<std::endl;
        }
    }

    if(choice == 1)
    {
        this->changeTelephone(index);
    }
    else if(choice == 2)
    {
        this->changePetName(index);
    }
    else if(choice == 3)
    {
        this->changePetWeight(index);
    }
    else if(choice == 4)
    {
        this->changeDoctor(index);
    }
}

void Clinic::changeTelephone(int index)
{
    std::string Telephone;
    std::cout<<std::endl<<"Introdu noul numar de telefon.\n";

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>Telephone;

            if(!validTelephone(Telephone))
            {
                throw std::invalid_argument("\nNumar de telefon invalid. Incearca sa respecti tiparul (sa aiba 10 cifre, dintre care primele 2 sa fie 07).\n");
            }

            if( this->getElement(Appointments, index).getOwner().getTelephone() == Telephone)
            {
                throw std::logic_error("\nNumarul introdus coincide cu cel vechi, incearca din nou.\n");
            }
            break;
        }

        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou: ";
        }
    }
    std::cout<<"\nActiune finalizata. Numarul de telefon a fost modificat din "+ this->getElement(Appointments, index).getOwner().getTelephone()+ " in "+ Telephone + "/n";
    this->getElement(Appointments, index).getOwner().setTelephone(Telephone);
}

void Clinic::changePetName(int index)
{
    std::string Name;
    std::cout<<"Introdu noul nume al animalutului de companie.\n";

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>Name;

            if(!validName(Name))
            {
                throw std::invalid_argument("\nNumele nu poate fi inregistrat, trebuie sa contina doar litere. Incearca din nou.\n");
            }

            if( this->getElement(Appointments, index).getOwner().getPet()->getName() == Name)
            {
                throw std::logic_error("Numele introdus coincide cu cel vechi, incearca din nou.\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\nActiune finalizata. Numele animalutului de companie a fost schimbat din "+this->getElement(Appointments, index).getOwner().getPet()->getName() + " in " + Name + ".\n";
    this->getElement(Appointments, index).getOwner().getPet()->setName(Name);
}

void Clinic::changePetWeight(int index)
{
    int Weight;
    std::cout<<"Introdu greutatea animalului de companie (verificata de medicii veterinari).\n";

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>Weight;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid. Introdu un numar intreg.\n");
            }
            if(this->getElement(Appointments, index).getOwner().getPet()->getWeight() == Weight)
            {
                throw std::logic_error("\nGreutatea introdusa este aceeasi. Incearca din nou.\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\nActiune finalizata. Greutatea animalutului de companie a fost schimbata din "<<this->getElement(Appointments, index).getOwner().getPet()->getWeight()<<" in "<<Weight<<".\n";
    this->getElement(Appointments, index).getOwner().getPet()->setWeight(Weight);
}

void Clinic::changeDoctor(int index)
{
    int choice;
    std::cout<<"Introdu indexul noului medic veterinar care doresti sa iti preia programarea (0-"<<Doctor::getNumberDoctors() - 1<<").\n";
    Doctor doctor1 = Doctor();
    Doctor doctor2 = *(this->getElement(Appointments, index).getDoctor());
    Doctor::decreaseNumberDoctors();

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid. Introdu un numar intreg cuprins intre 0 si "+ std::to_string(Doctor::getNumberDoctors() - 1) + ".\n");
            }
            if(choice < 0 || choice > Doctor::getNumberDoctors() - 1)
            {
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (0-" + std::to_string(Doctor::getNumberDoctors() -1 ) + ").\n");
            }
            doctor1 = *(this->getElement(Doctors, choice));
            if( doctor1 == doctor2 )
            {
                throw std::logic_error("\nMedicul solicitat este acelasi. Incearca din nou.\n");
            }

            if( !doctor1.Availability())
            {
                throw std::logic_error("\nMedicul solicitat nu este disponibil momentan. Incearca din nou.\n");
            }

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }

    std::cout<<"\nActiune finalizata. Programarea iti va fi preluata de medicul " + this->getElement(Doctors, choice)->getFirstName() + " " + this->getElement(Doctors, choice)->getLastName() + ".\n";
    this->getElement(Appointments, index).setDoctor(this->getElement(Doctors, choice));
}

void Clinic::Deworming(int index)
{
    std::cout<<"Ce fel de deparazitare doriti sa-i faceti animalului de companie?\n";
    std::cout<<"1. Interna\n";
    std::cout<<"2. Externa\n";
    std::cout<<"3. Interna si externa\n";

    int choice;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 1 si 3.\n");
            }

            if(choice < 1 || choice > 3)
            {
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (1-3).\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }

    if(choice == 1)
    {
        std::cout<<"\nMedicul veterinar "<<this->getElement(Appointments, index).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index).getDoctor()->getLastName()<<" i-a facut pacientului "<<this->getElement(Appointments, index).getOwner().getPet()->getName()<<" deparazitare interna\n";;
    }
    else if(choice == 2)
    {
        std::cout<<"\nMedicul veterinar "<<this->getElement(Appointments, index).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index).getDoctor()->getLastName()<<" i-a facut pacientului "<<this->getElement(Appointments, index).getOwner().getPet()->getName()<<" deparazitare externa\n";
    }
    else
    {
        std::cout<<"\nMedicul veterinar "<<this->getElement(Appointments, index).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index).getDoctor()->getLastName()<<" i-a facut pacientului "<<this->getElement(Appointments, index).getOwner().getPet()->getName()<<" deparazitare interna si externa\n";
    }
}

void Clinic::Vaccination(int index)
{
    std::cout<<"Ce vaccin doresti sa ii administrezi animalutului de companie? Introdu un ID valid dintre cele marcate cu verde de mai jos.\n\n";
    for(int i =0; i<Vaccine::getNumberVaccines(); i++)
    {
        if((dynamic_cast<Cat*>(this->getElement(Appointments, index).getOwner().getPet()) && this->getElement(Vaccines, i).getType() != "caini") || ((dynamic_cast<Dog*>(this->getElement(Appointments, index).getOwner().getPet()) && this->getElement(Vaccines, i).getType() != "pisici")))
        {
            std::cout<<"\033[32mNume vaccin: "<<this->getElement(Vaccines, i).getName()<<"\n";
            std::cout<<"ID vaccin: "<<this->getElement(Vaccines, i).getID()<<"\033[0m"<<"\n";
        }
        else
        {
            std::cout<<"Nume vaccin: "<<this->getElement(Vaccines,i).getName()<<"\n";
            std::cout<<"ID vaccin: "<<this->getElement(Vaccines, i).getID()<<"\n";
        }
        std::cout<<"\n";
    }
    int choice;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
            }

            if(!this->isVaccine(choice))
            {
                throw std::logic_error("\nVaccinul de ID " +std::to_string(choice) + " nu exista. Incearca din nou.\n");
            }

            if((dynamic_cast<Cat*>(this->getElement(Appointments, index).getOwner().getPet()) && this->getVaccineID(choice).getType() == "caini") || ((dynamic_cast<Dog*>(this->getElement(Appointments, index).getOwner().getPet()) && this->getVaccineID(choice).getType() == "pisici")))
            {
                throw std::logic_error("\nAcest tip de vaccin nu este potrivit pentru animalul de companie. Incearca din nou.\n");
            }

            if(this->getVaccineID(choice).getStock() == 0)
            {
                throw std::invalid_argument("\nDin pacate, vaccinul " + this->getVaccineID(choice).getName() + " nu mai este disponibil in stoc. Incearca din nou.\n");
            }

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }

    }

    std::cout<<"\nActiune finalizata! Medicul "<<this->getElement(Appointments, index).getDoctor()->getFirstName()<<" "<<this->getElement(Appointments, index).getDoctor()->getLastName()<<" i-a administrat pacientului "<<this->getElement(Appointments, index).getOwner().getPet()->getName()<<" vaccinul "<<this->getVaccineID(choice).getName()<<".\n";
    this->getElement(Appointments, index).getOwner().getPet()->addVaccine(&this->getVaccineID(choice));
}

void Clinic::addNewAppointment()
{
    std::cout<<"Ai ales sa inregistrezi o noua programare in sistem."<<std::endl;
    Owner owner;
    std::cin>>owner;
    std::cout<<"\nIntroduceti indexul medicului veterinar care doriti sa va preia programarea (0-"<<Doctor::getNumberDoctors() -1 <<").\n";
    int index;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>index;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 0 si "+ std::to_string(Doctor::getNumberDoctors() -1)+".\n");
            }
            if(index < 0 || index > Doctor::getNumberDoctors() - 1)
            {
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (0-"+std::to_string(Doctor::getNumberDoctors() - 1)+").\n");
            }
            break;

        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
        }
    }
    this->addAppointment(Appointment(owner, this->getElement(Doctors, index)));
}
void Clinic::administrativeDetails()
{
    int choice =1;
    while(choice)
    {
        std::cout<< "\nCe actiune doresti sa faci mai departe?\n";
        std::cout << "1.  Adauga o noua sala\n";
        std::cout << "2.  Angajeaza un medic veterinar\n";
        std::cout << "3.  Sterge un medic veterinar din lista\n";
        std::cout << "4.  Modifica pretul unui vaccin deja existent\n";
        std::cout << "5.  Updateaza stocul unui vaccin existent\n";
        std::cout << "6.  Sterge un vaccin existent\n";
        std::cout << "7.  Anuleaza o programare\n";
        std::cout << "8.  Afiseaza lista vaccinelor\n";
        std::cout << "9.  Afiseaza lista medicilor veterinari\n";
        std::cout << "10. Afiseaza lista salilor\n";
        std::cout << "11. Afiseaza lista programarilor\n";
        std::cout << "12. Afiseaza lista administratorilor\n";
        std::cout << "0.  Inapoi" << std::endl;

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin>>choice;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 0 si 12.\n");
                }

                if(choice < 0 || choice > 12)
                {
                    throw std::out_of_range("\nOptiune invalida! Incearca din nou (0-12).\n");
                }
                break;
            }
            catch(const std::exception& e)
            {
                std::cout<<e.what();
            }
            catch(...)
            {
                std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
            }
        }
        std::cout<<"\n";

        if(choice == 0)
            break;
        else if(choice == 1)
        {
            this->addNewRoom();
        }
        else if(choice == 2)
        {
            this->addNewDoctor();
        }
        else if(choice == 3)
        {
            this->fireDoctor();
        }
        else if(choice == 4)
        {
            this->changeVaccinePrice();
        }
        else if(choice == 5)
        {
            this->changeVaccineStock();
        }
        else if(choice == 6)
        {
            this->deleteVaccineFromList();
        }
        else if(choice == 7)
        {
            this->cancelAppointmentFromList();
        }
        else if(choice == 8)
        {
            this->displayList(Vaccines, "LISTA VACCINELOR");
        }
        else if(choice == 9)
        {
            this->displayList(Doctors, "LISTA MEDICILOR VETERINARI");
        }
        else if(choice == 10)
        {
            this->displayList(Rooms, "LISTA SALILOR");
        }
        else if(choice == 11)
        {
            this->displayList(Appointments, "LISTA PROGRAMARILOR");
        }
        else
        {
            this->displayList(Administrators, "LISTA ADMINISTRATORILOR");
        }
    }
}
void Clinic::addNewRoom()
{
    std::cout<<"Ce fel de sala doresti sa adaugi?\n";
    std::cout<<"1. Sala de consultatie\n";
    std::cout<<"2. Sala de operatie\n";

    int choice, roomNumber;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid dintre 1 si 2.\n");
            }

            if(choice != 1 && choice !=2)
            {
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (1 sau 2).\n");
            }

            break;

        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    if(choice == 1)
    {
        std::cout<<"\nIntrodu numarul salii si daca aceasta are, sau nu, ecograf (ex: 12 ecograf, 13 fara ecograf).\n";
        std::string Ultrasound;

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin>>roomNumber;
                std::getline(std::cin >> std::ws, Ultrasound);

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInputuri invalide! Incearca din nou.\n");
                }

                if(Ultrasound != "ecograf" && Ultrasound != "fara ecograf")
                {
                    throw std::invalid_argument("\nInput invalid. Incearca din nou (inputurile acceptate sunt ecograf si fara ecograf).\n");
                }
                if(this->isRoom(roomNumber))
                {
                    throw std::logic_error("\nExista deja o sala cu numarul " + std::to_string(roomNumber) +". Incearca din nou (amandoua valorile).\n");
                }

                break;
            }
            catch(std::exception& e)
            {
                std::cout<<e.what();
            }
            catch(...)
            {
                std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
            }
        }

        if(Ultrasound == "ecograf")
        {
            this->addRoom(new ConsultationRoom(roomNumber, roomNumber/10,true));
        }
        else
        {
            this->addRoom(new ConsultationRoom(roomNumber, roomNumber/10, false));
        }

    }
    else
    {
        std::cout<<"\nIntrodu numarul salii de operatie pe care doresti sa o adaugi (ex 12, 13).\n";

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin>>roomNumber;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
                }
                if(this->isRoom(roomNumber))
                {
                    throw std::logic_error("\nExista deja o sala cu numarul " + std::to_string(roomNumber) +". Incearca din nou.\n");
                }
                break;
            }
            catch(std::exception& e)
            {
                std::cout<<e.what();
            }
            catch(...)
            {
                std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
            }
        }
        try
        {
            this->addRoom(new OperationRoom(roomNumber, roomNumber/10, true));

        }
        catch(std::bad_alloc& e)
        {
            std::cout<<"\nNu s-a putut aloca memorie.\n";
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\nActiune finalizata! Sala cu numarul "<<roomNumber<<" a fost adaugata la etajul "<<roomNumber/10<<".\n";
}

void Clinic::addNewDoctor()
{
    std::cout<<"Ce medic doresti sa adaugi?\n";
    std::cout<<"1. Medic veterinar simplu\n";
    std::cout<<"2. Director de departament\n";

    int choice;
    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid dintre 1 si 2.\n");
            }
            if(choice != 1 && choice != 2)
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (1 sau 2).\n");

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    std::cout<<"\nIntrodu numele si prenumele medicului pe care doresti sa il adaugi: ";
    std::string LastName, FirstName;
    std::cin>>LastName>>FirstName;
    std::cout<<"\n\nIntrodu un numar de telefon al medicului.\n";
    std::string Telephone;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>Telephone;
            if(!this->validTelephone(Telephone))
                throw std::invalid_argument("\nNumarul de telefon nu este valid. Incearca din nou (trebuie sa inceapa cu 07 si sa aiba un total de 10 cifre).\n");
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\n\nIntroduceti genul medicului veterinar(feminin/masculin).\n";
    std::string gender;
    Gender genderEnum;
    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>gender;
            if(gender != "feminin" && gender != "masculin")
                throw "\nStringul introdus nu este recunoscut. Incearca din nou ('feminin' sau 'masculin').\n";

            break;
        }
        catch(const char* errMsg)
        {
            std::cout<<errMsg;
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    if(gender == "feminin")
    {
        genderEnum = Gender::Female;
    }
    else
    {
        genderEnum = Gender::Male;
    }
    std::cout<<"\n\nIntroduceti varsta medicului.\n";
    int Age;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>Age;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid. Incearca din nou.\n");
            }
            if(Age < 0)
                throw std::logic_error("\nVarsta nu poate fi negativa. Incearca din nou.\n");

            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\n\nIntrodu numarul anilor de experienta in domeniu.\n";
    int yearsofExp;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>yearsofExp;
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid. Incearca din nou.\n");
            }
            if(yearsofExp < 0)
                throw std::out_of_range("\nNumarul anilor de experienta nu poate fi negativ. Incearca din nou.\n");
            if(yearsofExp > Age)
                throw std::logic_error("\nNumarul anilor de experienta nu poate fi mai mare decat varsta medicului veterinar. Incearca din nou.\n");
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\n\nIntrodu specializarea medicului veterinar.\n";
    std::string Specialization;
    std::cin.ignore();

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::getline(std::cin, Specialization);
            if(!this->validName(Specialization))
                throw std::invalid_argument("\nSpecializarea nu este valida, denumirea nu poate contine cifre. Incearca din nou.\n");
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    if(choice == 2)
    {
        std::cout<<"\n\nIntrodu departamentul de care este responsabil medicul veterinar.\n";
        std::string Department;

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::getline(std::cin, Department);
                if(!this->validName(Department))
                    throw std::invalid_argument("\nDepartamentul nu este valid, denumirea nu poate contine cifre. Incearca din nou.\n");
                if(this->isDepartment(Department))
                    throw std::logic_error("\nExista deja un director pentru acest departament. Incearca din nou.\n");
                break;
            }
            catch(std::exception& e)
            {
                std::cout<<e.what();
            }
            catch(...)
            {
                std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
            }
        }
        this->addDoctor(new HeadOfDepartment(LastName, FirstName, Telephone, genderEnum, Age, Specialization, yearsofExp, Department));
    }
    else
        this->addDoctor(new Doctor(LastName, FirstName, Telephone, genderEnum, Age, Specialization, yearsofExp));
    std::cout<<"\nActiune finalizata! Medicul veterinar "<<LastName<<" "<<FirstName<<" a fost adaugat in lista medicilor clinicii\n/";
}

bool Clinic::isVaccine(int ID) const
{
    for (int i = 0; i < Vaccines.size(); i++)
    {
        if (Vaccines[i].getID() == ID)
            return true;
    }
    return false;
}

void Clinic::fireDoctor()
{
    std::cout<<"Introdu indexul medicului veterinar pe care doresti sa-l stergi (0-"<<Doctor::getNumberDoctors()-1<<").\n";;
    int index;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>index;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 0 si " + std::to_string(Doctor::getNumberDoctors()-1) + ".\n");
            }
            if(index < 0 || index > Doctor::getNumberDoctors() - 1)
            {
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (0-" + std::to_string(Doctor::getNumberDoctors() -1 ) + ").\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    std::cout<<"\nActiune finalizata! Medicul veterinar "<<this->getElement(Doctors, index)->getFirstName()<<" "<<this->getElement(Doctors, index)->getLastName()<<" a fost sters din lista medicilor.\n";

    int index1;
    if(dynamic_cast<HeadOfDepartment*>(this->getElement(Doctors, index)))
    {
        HeadOfDepartment* HoD = dynamic_cast<HeadOfDepartment*>(this->getElement(Doctors, index));
        std::string Department = HoD->getDepartment();
        index1 = this->nextHOD();
        Doctor* doctor = this->getElement(Doctors, index1);
        std::cout<<"In plus, acesta era director de departament. Noul director al departamentului "<<Department<<" a fost ales "<<doctor->getFirstName()<<" "<<doctor->getLastName()<<" avand "<<doctor->getYears()<<" ani de experienta in domeniu.\n";
        this->addDoctor(new HeadOfDepartment(doctor->getFirstName(), doctor->getLastName(), doctor->getTelephone(), doctor->GetGender(), doctor->getAge(), doctor->getSpecialization(), doctor->getYears(), Department));
        this->deleteDoctor(index1);
        if(index1 < index)
            index ++;
    }
    for(int i = 0; i < Appointment::getAppointmentNumber(); i++)
    {
        if (*(this->getElement(Doctors, index)) == *(this->getElement(Appointments, i).getDoctor()))
        {
            Doctor* doctor = this->randomDoctor();
            while(*(doctor) == *(this->getElement(Doctors, index)))
            {
                doctor = this->randomDoctor();
            }
            this->getElement(Appointments, i).setDoctor(doctor);
        }
    }
    this->deleteDoctor(index);
}

void Clinic::changeVaccinePrice()
{
    std::cout<<"Introdu ID-ul vaccinului al carui pret doresti sa-l modifici.\n";
    int ID;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>ID;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
            }

            if(!this->isVaccine(ID))
            {
                throw std::logic_error("\nVaccinul de ID " + std::to_string(ID) + " nu exista. Incearca din nou.\n");
            }
            break;

        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\nIntrodu o suma de lei cu care vrei sa modifici pretul vaccinului "<<this->getVaccineID(ID).getName()<<".\n";
    int price;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>price;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
            }
            if(price < 0)
            {
                throw std::logic_error("\nOptiune invalida. Pretul unui vaccin nu poate fi negativ. Incearca din nou.\n");
            }

            if(price == this->getVaccineID(ID).getPrice())
            {
                throw std::logic_error("\nNoul pret este identic cu cel precedent. Incearca din nou.\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    std::cout<<"\nActiune finalizata! Pretului vaccinului "<<this->getVaccineID(ID).getName()<<" a fost modificat din "<<this->getVaccineID(ID).getPrice()<<" in "<<price<<".\n";
    this->getVaccineID(ID).setPrice(price);
}

void Clinic::changeVaccineStock()
{
    std::cout<<"Introdu ID-ul vaccinului pentru care doresti sa modifici stocul."<<std::endl;
    int ID;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>ID;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
            }
            if(!this->isVaccine(ID))
            {
                throw std::logic_error("\nVaccinul de ID " + std::to_string(ID) + " nu exista. Incearca din nou.\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    std::cout << "\nCum doresti sa modifici stocul vaccinului " << this->getVaccineID(ID).getName() << "?\n";
    std::cout << "1. Adauga un numar de doze de vaccin\n";
    std::cout << "2. Multiplica numarul de doze de vaccin\n";
    std::cout << "3. Scade un numar de doze de vaccin\n";
    std::cout << "4. Micsoreaza de un numar de ori dozele de vaccin\n";
    std::cout << "5. Goleste stocul\n";

    int choice, oldStock = this->getVaccineID(ID).getStock();

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 1 si 5.\n");
            }
            if(choice < 1 || choice > 5)
            {
                throw std::invalid_argument("\nOptiune invalida. Incearca din nou (1-5).\n");
            }
            break;
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    int nr;
    if(choice == 1)
    {
        std::cout << "\nIntrodu numarul de doze pe care doresti sa il adaugi la stoc (numar pozitiv).\n"<<std::endl;

    }
    else if(choice == 2)
    {
        std::cout <<"\nIntrodu numarul cu care vrei sa multiplici stocul deja existent (numar pozitiv).\n"<<std::endl;
    }
    else if(choice == 3)
    {
        std::cout << "\nIntordu numarul de doze pe care doresti sa il scazi din stoc ( numar pozitiv).\n"<<std::endl;
    }
    else if(choice == 4)
    {
        std::cout << "\nIntrodu numarul de ori cu care doresti sa micsorezi stocul ( numar pozitiv).\n"<<std::endl;
    }
    else
    {
        if(this->getVaccineID(ID).getStock() == 0)
        {
            std::cout<<"\nVaccinul "<<this->getVaccineID(ID).getName()<<" nu mai este deja in stoc. Actiunea nu a avut niciun impact.\n";
        }
        else
        {
            this->getVaccineID(ID) -= this->getVaccineID(ID).getStock();
            std::cout << "Actiune finalizata! Vaccinul " << this->getVaccineID(ID).getName() <<" de ID "<<ID<<" nu mai este disponibil in stoc.\n";
        }
    }
    if(choice != 5)
    {
        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin>>nr;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar natural valid.\n");
                }
                if(nr < 0)
                {
                    throw std::logic_error("\nOptiune invalida. Numarul introdus trebuie sa fie intreg pozitiv. Incearca din nou.\n");
                }

                break;
            }
            catch(std::exception& e)
            {
                std::cout<<e.what()<<std::endl;
            }
            catch(...)
            {
                std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
            }
        }
        if(choice == 1)
        {
            this->getVaccineID(ID) += nr;
        }
        else if(choice == 2)
        {
            this->getVaccineID(ID) *= nr;
        }
        else if(choice == 3)
        {
            if(nr > this->getVaccineID(ID).getStock())
            {
                std::cout<<"Nu sunt suficiente doze de vaccin pentru a reduce stocul cu "<<nr<<" doze. Se va reduce stocul cu "<<this->getVaccineID(ID).getStock()<<" iar acesta va ajunge la 0.\n";
                this->getVaccineID(ID) -= this->getVaccineID(ID).getStock();
            }
            else
            {
                this->getVaccineID(ID) -= nr;
            }
        }
        else if(choice == 4)
        {
            this->getVaccineID(ID) /= nr;
        }
        std::cout<<"\nActiune finalizata! Ai modificat stocul vaccinului "<<this->getVaccineID(ID).getName()<<" de ID "<<ID<<" de la "<<oldStock<<" la "<<this->getVaccineID(ID).getStock()<<".\n";
    }
}

void Clinic::deleteVaccineFromList()
{
    std::cout<<"Introdu indexul unui vaccin pe care doresti sa il stergi de pe lista (0-"<<Vaccine::getNumberVaccines() -1<<")."<<std::endl;
    int index;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>index;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg validintre 0 si " + std::to_string(Vaccine::getNumberVaccines() - 1) + ".\n");
            }
            if(index < 0 || index > Vaccine::getNumberVaccines() -1)
            {
                throw std::invalid_argument("\nOptiune invalida. Incearca din nou (0-" + std::to_string(Vaccine::getNumberVaccines()-1)+").\n");
            }
            break;
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n"<<std::endl;
        }
    }
    std::cout<<"\nActiune finalizata! Vaccinul "<<this->getElement(Vaccines, index).getName()<<", de ID "<<this->getElement(Vaccines, index).getID()<<" a fost sters din lista de vaccinuri ale clinicii.\n";
    this->deleteVaccine(index);
    Vaccine::decreaseNumberVaccines();
}

void Clinic::cancelAppointmentFromList()
{
    std::cout<<"Introdu indexul programarii pe care doresti sa o anulezi (0-"<<Appointment::getAppointmentNumber()-1<<").\n";
    int index;
    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            std::cin>>index;
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid intre 0 si "+std::to_string(Appointment::getAppointmentNumber() -1) +".\n");
            }
            if(index < 0 || index > Appointment::getAppointmentNumber() -1)
                throw std::out_of_range("\nOptiune invalida! Incearca din nou (0-" + std::to_string(Appointment::getAppointmentNumber() -1) + ").\n");
            break;
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
        }
        catch(std::out_of_range& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    if(this->getElement(Appointments, index).Status())
    {
        this->getElement(Appointments, index).getDoctor()->freeDoctor();
        this->getElement(Appointments, index).getRoom()->exitRoom();
    }
    this->cancelAppointment(index);
    Appointment::decreaseNumberAppointments();
}

int Clinic::nextHOD() const
{
    int index = 0, maxi = 0;
    for(int i = 0; i < Doctors.size(); i++)
    {
        if(Doctors[i]->getYears() > maxi && !dynamic_cast<HeadOfDepartment*>(Doctors[i]))
        {
            maxi = Doctors[i]->getYears();
            index = i;
        }
    }
    return index;
}

void Clinic::deleteDoctor(int index)
{
    delete Doctors[index];
    Doctors.erase(Doctors.begin() + index);
    Doctor::decreaseNumberDoctors();
}

void Clinic::deleteVaccine(int index)
{
    Vaccines.erase(Vaccines.begin() + index);
}

void Clinic::cancelAppointment(int index)
{
    Appointments.erase(Appointments.begin() + index);
}

void Clinic::addRoom(Room* room)
{
    Rooms.push_back(room);
}

bool Clinic::isDepartment(std::string& Department)
{
    for(auto& doctor : Doctors)
    {
        if(dynamic_cast<HeadOfDepartment*>(doctor))
        {
            HeadOfDepartment* HoD = dynamic_cast<HeadOfDepartment*>(doctor);
            if(HoD->getDepartment() == Department)
                return true;
        }
    }
    return false;
}

bool Clinic::isRoom(int number)
{
    for(int i = 0; i < Rooms.size(); i++)
    {
        if(Rooms[i]->getNumber() == number)
            return true;
    }
    return false;
}

void Clinic::addVaccine(const Vaccine& vaccine)
{
    Vaccines.push_back(vaccine);
}

void Clinic::addDoctor(Doctor* doctor)
{
    Doctors.push_back(doctor);
}

void Clinic::addAppointment(const Appointment& appointment)
{
    Appointments.push_back(appointment);
}

Vaccine& Clinic::getVaccineID(int ID)
{
    for (int i = 0; i < Vaccines.size(); i++)
    {
        if(Vaccines[i].getID() == ID)
            return Vaccines[i];
    }
    return Vaccines[0];
}

Room* Clinic::randomAvailableConsultationRoom()
{
    bool ok = false;
    for (int i = 0; i < Rooms.size(); i++)
    {
        if(dynamic_cast<ConsultationRoom*>(Rooms[i]) && !Rooms[i]->getOccupied())
        {
            ok = true;
            break;
        }
    }

    if(!ok)
    {
        return nullptr;
    }
    Room* room = this->getRandomElement(Rooms);
    while(!dynamic_cast<ConsultationRoom*>(room) || room->getOccupied())
    {
        room = getRandomElement(Rooms);
    }
    return room;
}

ConsultationRoom* Clinic::randomAvailableConsultationRoomUltrasounnd()
{
    bool ok = false;
    ConsultationRoom* room = nullptr;
    for (int i = 0; i < Rooms.size(); i++)
    {
        room = dynamic_cast<ConsultationRoom*>(Rooms[i]);
        if(room && !room->getOccupied() && room->getUltrasound())
        {
            ok = true;
            break;
        }
    }

    if(!ok)
    {
        return nullptr;
    }
    room = dynamic_cast<ConsultationRoom*>(getRandomElement(Rooms));
    while(!room || room->getOccupied() || !room->getUltrasound())
    {
        room = dynamic_cast<ConsultationRoom*>(getRandomElement(Rooms));
    }
    return room;
}

Room* Clinic::randomAvailableOperationRoom()
{
    bool ok = false;
    for (int i = 0; i < Rooms.size(); i++)
    {
        if(dynamic_cast<OperationRoom*>(Rooms[i]) && !Rooms[i]->getOccupied())
        {
            ok = true;
            break;
        }
    }

    if(!ok)
        return nullptr;
    Room* room = getRandomElement(Rooms);
    while(!dynamic_cast<OperationRoom*>(room) || room->getOccupied())
    {
        room = getRandomElement(Rooms);
    }
    return room;
}

Room* Clinic::randomConsultationRoom()
{
    Room* room = getRandomElement(Rooms);
    while(!dynamic_cast<ConsultationRoom*>(room))
    {
        room = getRandomElement(Rooms);
    }
    return room;
}

ConsultationRoom* Clinic::randomConsultationRoomUltrasound()
{
    ConsultationRoom* room = dynamic_cast<ConsultationRoom*>(getRandomElement(Rooms));
    while(!room || !room->getUltrasound())
    {
        room = dynamic_cast<ConsultationRoom*>(getRandomElement(Rooms));
    }
    return room;
}

Room* Clinic::randomOperationRoom()
{
    Room* room = getRandomElement(Rooms);
    while(!dynamic_cast<OperationRoom*>(room))
    {
        room = getRandomElement(Rooms);
    }
    return room;
}

Doctor* Clinic::randomDoctor()
{
    return getRandomElement(Doctors);
}

bool Clinic::validTelephone(const std::string& Telephone)
{
    if (Telephone.size() != 10)
        return false;
    if (Telephone[0] != '0' || Telephone[1] != '7')
        return false;
    for (char c: Telephone)
        if (!isdigit(c))
            return false;
    return true;
}

bool Clinic::validName(const std::string& Name)
{
    for(char c: Name)
        if(isdigit(c))
            return false;
    return true;
}

void Clinic::handleSpecialServices(int appointmentIndex)
{
    std::cout << "----------SERVICII SPECIALE----------\n\n";

    AppointmentEnhancer enhancer(&this->getElement(Appointments, appointmentIndex));

    std::cout << "Pacient: " << this->getElement(Appointments, appointmentIndex).getOwner().getPet()->getName()<<"\n\n";

    enhancer.displayAvailableServices();
    int serviceChoice = 1;

    while (serviceChoice)
    {
        std::cout << "\nSelecteaza un serviciu.\n";

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin >> serviceChoice;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInput invalid! Te rog sa introduci un numar intreg valid.\n");
                }

                int maxChoice = (enhancer.getPetSpecies() == "Pisica") ? 4 : 3;

                if(serviceChoice < 0 || serviceChoice > maxChoice)
                {
                    throw std::out_of_range("\nOptiune invalida! Incearca din nou (1-" + std::to_string(maxChoice) + ").\n");
                }

                break;
            }
            catch(std::exception& e)
            {
                std::cout << e.what();
            }
            catch(...)
            {
                std::cout << "\nEroare necunoscuta...Incearca din nou.\n" << std::endl;
            }
        }
        if(serviceChoice == 0)
        {
            break;
        }
        else if(serviceChoice == 1)
        {
            enhancer.addDentalCare();
            std::cout << "\nIngrijire dentara realizata cu succes!\n";
        }
        else if(serviceChoice == 2)
        {
            std::cout << "Tip microcip:\n";
            std::cout << "1. Standard (80 lei)\n";
            std::cout << "2. Premium (120 lei)\n";

            int chipChoice;
            std::string chipType = "standard";

            while(true)
            {
                try
                {
                    std::cout << "Optiune: ";
                    std::cin >> chipChoice;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::invalid_argument("\nInput invalid! Te rog sa introduci 1 sau 2.\n");
                    }
                    if(chipChoice != 1 && chipChoice != 2)
                    {
                        throw std::out_of_range("\nOptiune invalida! Incearca din nou (1 sau 2).\n");
                    }
                    break;
                }
                catch(std::exception& e)
                {
                    std::cout << e.what();
                }
            }

            enhancer.addMicrochipping(chipType);
            std::cout << "Microcipare " << chipType << " realizata cu succes!\n";
        }
        else if(serviceChoice == 3)
        {
            enhancer.addGrooming();
            std::cout << "Ingrijire corporala realizata cu succes!\n";
        }
        else
        {
            if (enhancer.getPetSpecies() == "Pisica")
            {
                enhancer.addDeclawing();
                std::cout << "Taierea ghearelor realizata cu succes!\n";
            }
            else
            {
                std::cout << "Optiune invalida pentru aceasta specie!\n";
            }
        }

        if (serviceChoice != 0)
        {
            std::cout << "Cost curent: " << enhancer.getTotalCost() << " lei\n";
        }
    }
    if (enhancer.getTotalCost() > 0)
    {
        std::cout << "\nPacient: " << this->getElement(Appointments, appointmentIndex).getOwner().getPet()->getName()<<"\n";

        std::string servicesOnly = enhancer.getServicesOnlyDescription();
        if (!servicesOnly.empty())
        {
            std::cout << "Servicii aplicate: " << servicesOnly <<"\n";
        }

        std::cout << "Cost total: " << enhancer.getTotalCost() << " lei" << std::endl;
    }
    else
    {
        std::cout << std::endl << "Nu au fost adaugate servicii suplimentare.\n";
    }
}
