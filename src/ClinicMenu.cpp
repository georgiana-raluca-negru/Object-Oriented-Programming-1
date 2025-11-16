#include "Clinic.h"
#include "Exception.h"
#include <iostream>
#include <limits>
#include <stdexcept>

void Clinic::menu()
{
    int choice=1;

    while(choice)
    {
        std::cout<<std::endl;
        std::cout<<"Bun venit la clinica veterinara "<<this->getName()<<". Ce actiuni doresti sa faci?\n";
        std::cout<<"1. Primeste o programare deja inregistrata in sistem\n";
        std::cout<<"2. Inregistreaza o noua programare in sistem\n";
        std::cout<<"3. Detalii administrative\n";
        std::cout<<"0. Exit\n";

        while(true)
        {
            try
            {
                std::cout<<"Optiune: ";
                std::cin>>choice;
                std::cout<<"\n";

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Input invalid! Te rog sa introduci un numar intreg valid intre 0 si 3.\n");
                }

                if(choice < 0 || choice > 3)
                {
                    throw std::invalid_argument("Optiune invalida! Incearca din nou (0-3).\n");
                }
                break;
            }
            catch(const std::exception& e)
            {
                std::cout<<e.what();
            }
            catch(...)
            {
                std::cout<<"Eroare necunoscuta...Incearca din nou.\n";
            }
        }

        if(choice == 0)
        {
            return;
        }

        else if(choice == 1)
        {
            this->receiveAppointment();
        }
        else if(choice == 2)
        {
            this->addNewAppointment();
        }
        else
        {
            this->administrativeDetails();

        }
    }
}
