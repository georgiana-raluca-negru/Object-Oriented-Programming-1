#include "Person.h"
#include "Exception.h"
#include <sstream>
#include <limits>


class Clinic;
extern Clinic clinic;

int Doctor::numberDoctors = 0;


Person::Person(const std::string& LastName, const std::string& FirstName, const std::string& Telephone, Gender gender, int Age)
{
    this->LastName = LastName;
    this->FirstName = FirstName;
    this->Telephone = Telephone;
    this->gender = gender;
    this->Age = Age;
}

std::string Person::getGender() const
{
    switch(gender)
    {
    case Gender::Male:
        return "Masculin";
    case Gender::Female:
        return "Feminin";
    default:
        return "Necunoscut";
    }
}

Gender Person::GetGender() const
{
    return gender;
}

std::string Person::getLastName() const
{
    return LastName;
}

std::string Person::getFirstName() const
{
    return FirstName;
}

int Person::getAge() const
{
    return Age;
}

std::string Person::getTelephone() const
{
    return Telephone;
}

void Person::setTelephone(const std::string& Telephone)
{
    this->Telephone = Telephone;
}

void Person::setAge(const int Age)
{
    this->Age = Age;
}

void Person::setGender(Gender gender)
{
    this->gender = gender;
}


Owner::Owner(const std::string& LastName, const std::string& FirstName, const std::string& Telephone, Gender gender, int Age, Pet* pet)
    : Person(LastName, FirstName, Telephone, gender, Age), pet(pet) {}

Owner::~Owner()
{
    delete pet;
}

Owner::Owner(const Owner& other) : Person(other)
{
    if (other.pet)
    {
        if (dynamic_cast<Cat*>(other.pet))
        {
            pet = new Cat(*dynamic_cast<Cat*>(other.pet));
        }
        else if (dynamic_cast<Dog*>(other.pet))
        {
            pet = new Dog(*dynamic_cast<Dog*>(other.pet));
        }
        else if (dynamic_cast<Bird*>(other.pet))
        {
            pet = new Bird(*dynamic_cast<Bird*>(other.pet));
        }
        else
        {
            pet = new Pet(*other.pet);
        }
    }
    else
    {
        pet = nullptr;
    }
}

Owner& Owner::operator=(const Owner& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        delete pet;

        if (other.pet)
        {
            if (dynamic_cast<Cat*>(other.pet))
            {
                pet = new Cat(*dynamic_cast<Cat*>(other.pet));
            }
            else if (dynamic_cast<Dog*>(other.pet))
            {
                pet = new Dog(*dynamic_cast<Dog*>(other.pet));
            }
            else if (dynamic_cast<Bird*>(other.pet))
            {
                pet = new Bird(*dynamic_cast<Bird*>(other.pet));
            }
            else
            {
                pet = new Pet(*other.pet);
            }
        }
        else
        {
            pet = nullptr;
        }
    }
    return *this;
}

Pet* Owner::getPet() const
{
    return pet;
}

void Owner::setPet(Pet* pet)
{
    this->pet = pet;
}

void Owner::displayInfo() const
{
    std::cout << "        Nume: " << LastName << std::endl;
    std::cout << "        Prenume: " << FirstName << std::endl;
    std::cout << "        Telefon: " << Telephone << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
}

Doctor::Doctor(const std::string& LastName, const std::string& FirstName, const std::string& Telephone, Gender gender, int Age,
               const std::string& Specialization, int yearsOfExperience)
    : Person(LastName, FirstName, Telephone, gender, Age),
      Specialization(Specialization), yearsOfExperience(yearsOfExperience), isAvailable(true)
{
    numberDoctors++;
}

void Doctor::displayInfo() const
{
    std::cout << "        Nume: " << LastName << std::endl;
    std::cout << "        Prenume: " << FirstName << std::endl;
    std::cout << "        Telefon: " << Telephone << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Specializare: " << Specialization << std::endl;
    std::cout << "        Ani experienta: " << yearsOfExperience << std::endl;
    std::cout << "        Disponibilitate: " << (isAvailable ? "disponibil" : "indisponibil") << std::endl;
}

int Doctor::getNumberDoctors()
{
    return numberDoctors;
}

void Doctor::decreaseNumberDoctors()
{
    numberDoctors--;
}

void Doctor::freeDoctor()
{
    isAvailable = true;
}

void Doctor::inConsultation()
{
    isAvailable = false;
}

int Doctor::getYears() const
{
    return yearsOfExperience;
}

std::string Doctor::getSpecialization() const
{
    return Specialization;
}

bool Doctor::Availability() const
{
    return isAvailable;
}

bool Doctor::operator==(const Doctor& doctor)
{
    return LastName == doctor.LastName && FirstName == doctor.FirstName;
}

bool Doctor::operator<(const Doctor& doctor) const
{
    if(this->yearsOfExperience < doctor.yearsOfExperience)
        return true;
    else if(this->yearsOfExperience == doctor.yearsOfExperience)
        if(this->Age < doctor.Age)
        return true;
    return false;
}

Doctor* Doctor::clone() const
{
    return new Doctor(*this);
}


Administrator::Administrator(const std::string& LastName, const std::string& FirstName, const std::string& Telephone,
                             Gender gender, int Age, const std::string& Department)
    : Person(LastName, FirstName, Telephone, gender, Age), Department(Department) {}

void Administrator::displayInfo() const
{
    std::cout << "        Nume: " << LastName << std::endl;
    std::cout << "        Prenume: " << FirstName << std::endl;
    std::cout << "        Telefon: " << Telephone << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Departament: " << Department << std::endl;
}

std::string Administrator::getDepartment() const
{
    return Department;
}

bool Administrator::operator<(const Administrator& administrator) const
{
    if(this->Department < administrator.Department)
        return true;
    else if(this->Department == administrator.Department)
        if(this->Age < administrator.Age)
        return true;
    return false;
}

HeadOfDepartment::HeadOfDepartment(const std::string& LastName, const std::string& FirstName, const std::string& Telephone,
                                   Gender gender, int Age, const std::string& Specialization,
                                   int yearsOfExperience, const std::string& Department)
    : Person(LastName, FirstName, Telephone, gender, Age),
      Doctor(LastName, FirstName, Telephone, gender, Age, Specialization, yearsOfExperience),
      Administrator(LastName, FirstName, Telephone, gender, Age, Department) {}

void HeadOfDepartment::displayInfo() const
{
    std::cout << "        Nume: " << LastName << std::endl;
    std::cout << "        Prenume: " << FirstName << std::endl;
    std::cout << "        Telefon: " << Telephone << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Departament: " << Department << std::endl;
    std::cout << "        Specializare: " << Specialization << std::endl;
    std::cout << "        Ani experienta: " << yearsOfExperience << std::endl;
    std::cout << "        Disponibilitate: " << (isAvailable ? "disponibil" : "indisponibil") << std::endl;
}

HeadOfDepartment* HeadOfDepartment::clone() const
{
    return new HeadOfDepartment(*this);
}