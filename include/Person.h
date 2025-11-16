#ifndef HELPET_PERSON_H
#define HELPET_PERSON_H

#include <string>
#include <iostream>
#include "Gender.h"
#include "Pet.h"

class Person {
protected:
    std::string LastName;
    std::string FirstName;
    std::string Telephone;
    Gender gender;
    int Age;

public:
    Person(const std::string &LastName = "", const std::string &FirstName = "", const std::string &Telephone = "",
           Gender gender = Gender::Unknown, int Age = 0);

    virtual ~Person() = default;

    std::string getGender() const;

    Gender GetGender() const;

    std::string getLastName() const;

    std::string getFirstName() const;

    int getAge() const;

    std::string getTelephone() const;

    void setTelephone(const std::string &Telephone);

    void setAge(const int Age);

    void setGender(Gender gender);

    virtual void displayInfo() const = 0;
};

class Owner : public Person {
    Pet *pet;

public:
    Owner(const std::string &LastName = "", const std::string &FirstName = "", const std::string &Telephone = "",
          Gender gender = Gender::Unknown, int Age = 0, Pet *pet = nullptr);

    ~Owner();

    Owner(const Owner &other);

    Owner &operator=(const Owner &other);

    Pet *getPet() const;

    void setPet(Pet *pet);

    void displayInfo() const override;

    friend std::istream &operator>>(std::istream &is, Owner &owner);
};

class Doctor : virtual public Person {
protected:
    static int numberDoctors;
    std::string Specialization;
    int yearsOfExperience;
    bool isAvailable;

public:
    Doctor(const std::string &LastName = "", const std::string &FirstName = "", const std::string &Telephone = "",
           Gender gender = Gender::Unknown, int Age = 0, const std::string &Specialization = "",
           int yearsOfExperience = 0);

    void displayInfo() const;

    static int getNumberDoctors();

    static void decreaseNumberDoctors();

    void freeDoctor();

    void inConsultation();

    int getYears() const;

    std::string getSpecialization() const;

    bool Availability() const;

    bool operator==(const Doctor &doctor);

    bool operator<(const Doctor &doctor) const;

    virtual Doctor *clone() const;
};

class Administrator : virtual public Person {
protected:
    std::string Department;

public:
    Administrator(const std::string &LastName = "", const std::string &FirstName = "",
                  const std::string &Telephone = "", Gender gender = Gender::Unknown, int Age = 0,
                  const std::string &Department = "");

    void displayInfo() const;

    std::string getDepartment() const;

    bool operator<(const Administrator &administrator) const;
};

class HeadOfDepartment : public Doctor, public Administrator {
public:
    HeadOfDepartment(const std::string &LastName = "", const std::string &FirstName = "",
                     const std::string &Telephone = "", Gender gender = Gender::Unknown, int Age = 0,
                     const std::string &Specialization = "", int yearsOfExperience = 0,
                     const std::string &Department = "");

    void displayInfo() const;

    HeadOfDepartment *clone() const override;
};


#endif //HELPET_PERSON_H
