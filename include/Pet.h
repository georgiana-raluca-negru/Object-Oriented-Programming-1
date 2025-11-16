#ifndef HELPET_PET_H
#define HELPET_PET_H

#include <string>
#include <vector>
#include "Gender.h"
#include "Vaccine.h"


class Pet {
protected:
    Gender gender;
    std::string Name;
    std::string Species;
    int Weight;
    int Age;

public:
    Pet(const std::string &Name = "", int Weight = 0, int Age = 0, const std::string &Species = "",
        Gender gender = Gender::Unknown);

    virtual ~Pet() = default;

    std::string getGender() const;

    std::string getName() const;

    std::string getSpecies() const;

    int getWeight() const;

    void setName(const std::string &Name);

    void setWeight(int Weight);

    virtual void displayInfo() const;

    virtual void addVaccine(Vaccine *vaccine);
};

class Cat : public Pet {
    static const std::string catSpecies;
    std::string furLength;
    std::vector<Vaccine *> Vaccines;

public:
    Cat(const std::string &Name = "", int Weight = 0, int Age = 0, const std::string &furLength = "Scurta",
        Gender gender = Gender::Unknown, std::vector<Vaccine *> Vaccines = {});

    void displayInfo() const override;

    void addVaccine(Vaccine *vaccine) override;
};

class Dog : public Pet {
    static const std::string dogSpecies;
    bool isTrained;
    std::string Size;
    std::vector<Vaccine *> Vaccines;

public:
    Dog(const std::string &Name = "", int Weight = 0, int Age = 0, const std::string &Size = "Medie",
        Gender gender = Gender::Unknown, bool isTrained = false, std::vector<Vaccine *> Vaccines = {});

    void displayInfo() const override;

    void addVaccine(Vaccine *vaccine) override;
};

class Bird : public Pet {
    static const std::string birdSpecies;
    std::string featherColor;

public:
    Bird(const std::string &Name = "", int Weight = 0, int Age = 0, Gender gender = Gender::Unknown,
         const std::string &featherColor = "");

    void displayInfo() const override;

    void addVaccine(Vaccine *vaccine) override;
};


#endif //HELPET_PET_H
