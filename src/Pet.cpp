#include "Pet.h"

const std::string Cat::catSpecies = "Pisica";
const std::string Dog::dogSpecies = "Caine";
const std::string Bird::birdSpecies = "Pasare";


Pet::Pet(const std::string& Name, int Weight, int Age, const std::string& Species, Gender gender)
{
    this->Name = Name;
    this->Species = Species;
    this->Weight = Weight;
    this->Age = Age;
    this->gender = gender;
}

std::string Pet::getGender() const
{
    switch(gender)
    {
    case Gender::Male:
        return "Mascul";
    case Gender::Female:
        return "Femela";
    default:
        return "Necunoscut";
    }
}

std::string Pet::getName() const
{
    return Name;
}

std::string Pet::getSpecies() const
{
    return Species;
}

int Pet::getWeight() const
{
    return Weight;
}

void Pet::setName(const std::string& Name)
{
    this->Name = Name;
}

void Pet::setWeight(int Weight)
{
    this->Weight = Weight;
}

void Pet::displayInfo() const
{
    std::cout << "        Nume: " << Name << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Specie: " << Species << std::endl;
    std::cout << "        Greutate: " << Weight << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
}

void Pet::addVaccine(Vaccine* vaccine) {}


Cat::Cat(const std::string& Name, int Weight, int Age, const std::string& furLength, Gender gender, std::vector<Vaccine*> Vaccines)
    : Pet(Name, Weight, Age, catSpecies, gender), furLength(furLength), Vaccines(Vaccines) {}

void Cat::displayInfo() const
{
    std::cout << "        Nume: " << Name << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Specie: " << Species << std::endl;
    std::cout << "        Greutate: " << Weight << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Lungimea blanii: " << furLength << std::endl;
    std::cout << "        Id-urile vaccinelor: ";
    for(const auto& vaccine : Vaccines)
    {
        std::cout << vaccine->getID() << " ";
    }
    std::cout << std::endl;
}

void Cat::addVaccine(Vaccine* vaccine)
{
    *vaccine -= 1;
    Vaccines.push_back(vaccine);
}


Dog::Dog(const std::string& Name, int Weight, int Age, const std::string& Size, Gender gender, bool isTrained, std::vector<Vaccine*> Vaccines)
    : Pet(Name, Weight, Age, dogSpecies, gender), Size(Size), isTrained(isTrained), Vaccines(Vaccines) {}

void Dog::displayInfo() const
{
    std::cout << "        Nume: " << Name << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Specie: " << Species << std::endl;
    std::cout << "        Greutate: " << Weight << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Talie: " << Size << std::endl;
    std::cout << "        Dresaj: " << (isTrained ? "Da" : "Nu") << std::endl;
    std::cout << "        Id-urile vaccinelor: ";
    for(const auto& vaccine : Vaccines)
    {
        std::cout << vaccine->getID() << " ";
    }
    std::cout << std::endl;
}

void Dog::addVaccine(Vaccine* vaccine)
{
    *vaccine -= 1;
    Vaccines.push_back(vaccine);
}


Bird::Bird(const std::string& Name, int Weight, int Age, Gender gender, const std::string& featherColor)
    : Pet(Name, Weight, Age, birdSpecies, gender), featherColor(featherColor) {}

void Bird::displayInfo() const
{
    std::cout << "        Nume: " << Name << std::endl;
    std::cout << "        Gen: " << getGender() << std::endl;
    std::cout << "        Specie: " << Species << std::endl;
    std::cout << "        Greutate: " << Weight << std::endl;
    std::cout << "        Varsta: " << Age << std::endl;
    std::cout << "        Culoare penaj: " << featherColor << std::endl;
}

void Bird::addVaccine(Vaccine* vaccine) {}