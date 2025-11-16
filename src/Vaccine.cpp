#include "Vaccine.h"

int Vaccine::numberVaccines = 0;
VaccineSubject Vaccine::stockSubject;
bool Vaccine::observerInitialized = false;

Vaccine::Vaccine(const std::string& Name, int Price, int ID, int Stock, const std::string& typeOfPet)
{
    this->Name = Name;
    this->Price = Price;
    this->ID = ID;
    this->Stock = Stock;
    this->typeOfPet = typeOfPet;
    numberVaccines++;


    if (!observerInitialized) {
        initializeStockObserver();
        observerInitialized = true;
    }
}

void Vaccine::initializeStockObserver() {
    static VaccineStockNotifier notifier;
    stockSubject.addObserver(&notifier);
}

void Vaccine::notifyStockChange(int oldStock, int newStock) {
    stockSubject.notifyObservers(this, oldStock, newStock);
}

std::string Vaccine::getName() const
{
    return Name;
}

int Vaccine::getPrice() const
{
    return Price;
}

int Vaccine::getID() const
{
    return ID;
}

int Vaccine::getStock() const
{
    return Stock;
}

std::string Vaccine::getType() const
{
    return typeOfPet;
}

void Vaccine::setPrice(int Price)
{
    this->Price = Price;
}

Vaccine& Vaccine::operator+=(int number)
{
    int oldStock = Stock;
    Stock += number;
    notifyStockChange(oldStock, Stock);
    return *this;
}

Vaccine& Vaccine::operator-=(int number)
{
    int oldStock = Stock;
    Stock -= number;
    if (Stock < 0) Stock = 0;
    notifyStockChange(oldStock, Stock);
    return *this;
}

Vaccine& Vaccine::operator*=(int number)
{
    int oldStock = Stock;
    Stock *= number;
    notifyStockChange(oldStock, Stock);
    return *this;
}

Vaccine& Vaccine::operator/=(int number)
{
    if (number == 0)
    {
        throw std::invalid_argument("Nu se poate imparti la 0.");
    }
    int oldStock = Stock;
    Stock /= number;
    notifyStockChange(oldStock, Stock);
    return *this;
}

bool Vaccine::operator<(const Vaccine& vaccine) const
{
    if(this->Price < vaccine.Price)
        return true;
    else if(this->Price == vaccine.Price)
        if(this->Stock < vaccine.Stock)
        return true;
    return false;
}

int Vaccine::getNumberVaccines()
{
    return numberVaccines;
}

void Vaccine::decreaseNumberVaccines()
{
    numberVaccines--;
}

void Vaccine::displayInfo() const
{
    std::cout << "        Name Vaccine: " << Name << std::endl;
    std::cout << "        ID vaccin: " << ID << std::endl;
    std::cout << "        Pret Vaccine: " << Price << " lei" << std::endl;
    std::cout << "        Stoc disponibil: " << Stock << " doze" << std::endl;
    std::cout << "        Tipul: " << typeOfPet << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Vaccine& vaccine)
{
    os << "        Name Vaccine: " << vaccine.Name << std::endl;
    os << "        ID vaccin: " << vaccine.ID << std::endl;
    os << "        Pret Vaccine: " << vaccine.Price << " lei" << std::endl;
    os << "        Stoc disponibil: " << vaccine.Stock << " doze" << std::endl;
    os << "        Tipul: " << vaccine.typeOfPet << std::endl;
    return os;
}