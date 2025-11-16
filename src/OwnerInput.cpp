#include "Person.h"
#include "Clinic.h"
#include "Exception.h"
#include <iostream>
#include <sstream>
#include <limits>

std::istream &operator>>(std::istream &is, Owner &owner)
{
    Clinic* clinic = Clinic::getInstanta();
    std::cout<<"Introduceti, va rog, numele si prenumele dumneavoastra.\nOptiune: ";
    is>>owner.LastName>>owner.FirstName;
    std::cout<<std::endl;
    std::cout<<"Acum, introduceti un numar de telefon valid.\n";
    std::string Telephone;
    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            is>>Telephone;

            if(!clinic->validTelephone(Telephone))
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
    owner.setTelephone(Telephone);
    std::cout<<std::endl;
    std::cout<<"Introduceti genul (feminin/masculin).\n";
    std::string gender1;
    Gender genderEnum1;
    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            is>>gender1;
            if(gender1 != "feminin" && gender1 != "masculin")
            {
                throw "\nStringul introdus nu este recunoscut. Incearca din nou ('feminin' sau 'masculin').\n";
            }
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
    if(gender1 == "feminin")
    {
        genderEnum1 = Gender::Female;
    }
    else
    {
        genderEnum1 = Gender::Male;
    }

    owner.setGender(genderEnum1);
    std::cout<<std::endl;
    std::cout<<"Introduceti varsta dumneavoastra.\n";
    int Age1;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            is>>Age1;
            if (is.fail())
            {
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid. Incearca din nou, introducand un numar natural valid.\n");
            }
            if(Age1 < 0)
            {
                throw std::logic_error("\nVarsta nu poate fi negativa. Incearca din nou.\n");
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
    owner.setAge(Age1);
    std::cout<<"\nCare este numele animalutului de companie?\n";
    std::string petName;


    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            is>>petName;

            if(!clinic->validName(petName))
            {

                throw std::invalid_argument("\nNumele animalului este invalid. Incearca din nou.\n");
            }
            break;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what();
        }
    }

    std::cout<<"\nIntrodu genul animalutului de companie.\n";
    std::string gender2;
    Gender genderEnum2;

    while(true)
    {
        try
        {
            std::cout<<"Optiune: ";
            is>>gender2;

            if(gender2 != "feminin" && gender2 != "masculin")
                throw std::invalid_argument("\nGenul nu este recunoscut. Incearca din nou, introducand una dintre valorile 'feminin' sau 'masculin'.\n");
            break;
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"\nEroare necunoscuta...Incearca din nou.\n";
        }
    }
    if(gender2 == "feminin")
    {
        genderEnum2 = Gender::Female;
    }
    else
    {
        genderEnum2 = Gender::Male;
    }
    std::cout<<"\nIntroduceti, acum, varsta si greutatea acestuia (in ani si gr).\nOptiune: ";
    int Age2, Weight;
    is>>Age2>>Weight;

    while(true)
    {
        try
        {
            if (is.fail())
            {
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("\nInput invalid! Te rog sa introduci numere intregi valide.\n");
            }
            if(Age2 < 0 )
            {
                if(Weight < 0)
                    throw 10;
                else
                    throw 'a';
            }
            else
            {
                if(Weight < 0)
                    throw "abc";
            }

            break;
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<e.what();
            is>>Age2>>Weight;
        }
        catch(int x)
        {
            std::cout<<"Varsta si greutatea nu pot fi negative. Incearca sa introduci, din nou, ambele valori.\n";
            is>>Age2>>Weight;
        }
        catch(const char c)
        {
            std::cout<<"Varsta nu poate fi negativa. Introdu din nou varsta.\n";
            is>>Age2;
        }
        catch(const char* c)
        {
            std::cout<<"Greutatea nu poate fi negativa. Introdu din nou greutatea.\n";
            is>>Weight;
        }
        catch(...)
        {
            std::cout<<"Eroare necunoscuta...Incearca sa introduci, din nou, ambele valori.\n";
            is>>Age2>>Weight;
        }
    }
    std::cout<<"\nCe specie este animalutul de companie? (una dintre variantele 'Pisica', 'Caine', 'Pasare' sau orice alta specie, cu mentiunea sa inceapa cu litera majuscula).\nOptiune: ";
    std::string Species;
    Pet* pet;
    std::vector<Vaccine*> Vaccines;
    is>>Species;

    if(Species == "Pisica" || Species == "Caine")
    {
        Vaccines.clear();
        std::cout<<"Introdu numarul de vaccinuri ale animalului: ";
        int number;

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                is>>number;
                if(is.fail())
                {
                    is.clear();
                    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("\nInput invalid. Incearca sa introduci un numar natural valid.\n");
                }
                if(number < 0)
                {
                    throw std::logic_error("\nNumarul de vaccinuri nu poate fi negativ. Incearca din nou.\n");
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
        std::cout<<"\nIntroduceti, pe rand, ID-urile vaccinelor (apasa Enter dupa fiecare ID introdus): ";
        int ID;
        for(int i = 0; i < number; i++)
        {
            while(true)
            {
                try
                {
                    std::cout<<"Vaccinul Nr. "<<i+1<<": ";
                    is>>ID;

                    if(is.fail())
                    {
                        is.clear();
                        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::invalid_argument("\nInput invalid. Incearca sa introduci un numar intreg valid.\n");
                    }

                    if(!clinic->isVaccine(ID))
                    {
                        throw std::logic_error("\nVaccinul de acest ID nu exista. Incearca din nou.\n");
                    }

                    if((clinic->getVaccineID(ID).getType() == "caini"  && Species == "Pisica") || (clinic->getVaccineID(ID).getType() == "pisici"  && Species == "Caine"))
                    {
                        throw std::logic_error("\nVaccinul nu este potrivit pentru specia animalului. Incearca din nou.\n");
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
            Vaccines.push_back(&clinic->getVaccineID(ID));

        }
        if(Species == "Pisica")
        {
            std::cout<<"\nIntrodu lungimea blanii pisicii (Scurta/Medie/Mare).\n";
            std::string furLength;
            while(true)
            {
                try
                {
                    std::cout<<"Optiune: ";
                    is>>furLength;
                    if( furLength != "Scurta" && furLength != "Medie" && furLength != "Mare")
                    {
                        throw std::invalid_argument("\nInputul trebuie sa fie unul dintre specificatiile Scurta, Medie sau Mare. Incearca din nou.\n");
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
            pet = new Cat(petName, Weight, Age2, furLength, genderEnum2, Vaccines);
        }
        else
        {
            std::cout<<"\nIntrodu talia catelului (Mica/Medie/Mare).\n";
            std::string Size;
            while(true)
            {
                try
                {
                    std::cout<<"Optiune: ";
                    is>>Size;
                    if( Size != "Mica" && Size != "Medie" && Size != "Mare")
                    {
                        throw std::invalid_argument("\nInputul trebuie sa fie unul dintre specificatiile Mica, Medie sau Mare. Incearca din nou.\n");
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
            std::cout<<"\nEste cainele dresat? [Da/Nu]: ";
            std::string TrainingStatus;
            bool isTrained;
            while(true)
            {
                try
                {
                    is>>TrainingStatus;
                    if(TrainingStatus != "Da" && TrainingStatus != "NU")
                    {
                        throw std::invalid_argument("\nInputul trebuie sa fie unul dintre specificatiile Da sau Nu. Incearca din nou.\n");
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
            isTrained = (TrainingStatus == "Da");
            pet = new Dog(petName, Weight, Age2, Size, genderEnum2, isTrained, Vaccines);
        }
    }
    else if(Species == "Pasare")
    {
        std::cout<<"\nIntrodu culoarea penajului (albastru, rosu, galben, multicolor etc.).\n";
        std::string featherColor;

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                is>>featherColor;
                if(!clinic->validName(featherColor))
                {
                    throw std::invalid_argument("\nStringul introdus nu poate reprezenta o culoare. Incearca din nou (albastru, rosu, galben, multicolor etc.).\n");
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
        pet = new Bird(petName, Weight, Age2, genderEnum2, featherColor);
    }
    else
    {
        pet = new Pet(petName, Weight, Age2, Species, genderEnum2);
    }
    owner.setPet(pet);

    return is;
}