#ifndef HELPET_VACCINE_H
#define HELPET_VACCINE_H

#include <string>
#include <iostream>
#include "VaccineStockObserver.h"

class Vaccine
{
    static int numberVaccines;
    static VaccineSubject stockSubject;
    static bool observerInitialized;

    std::string Name;
    int Price;
    int ID;
    int Stock;
    std::string typeOfPet;

    void notifyStockChange(int oldStock, int newStock);

public:
    Vaccine(const std::string& Name = "", int Price = 0, int ID = 0, int Stock = 0, const std::string& typeOfPet = "");

    std::string getName() const;
    int getPrice() const;
    int getID() const;
    int getStock() const;
    std::string getType() const;
    void setPrice(int Price);

    Vaccine& operator+=(int number);
    Vaccine& operator-=(int number);
    Vaccine& operator*=(int number);
    Vaccine& operator/=(int number);
    bool operator<(const Vaccine& vaccine) const;

    static int getNumberVaccines();
    static void decreaseNumberVaccines();
    static void initializeStockObserver();
    void displayInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Vaccine& vaccine);
};

#endif //HELPET_VACCINE_H