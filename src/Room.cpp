#include "Room.h"
#include <iostream>
#include <string>

int Room::numberRooms = 0;

Room::Room(int Number, int Floor, bool Occupied)
{
    this->Number = Number;
    this->Floor = Floor;
    this->Occupied = Occupied;
    numberRooms++;
}

int Room::getNumber() const
{
    return Number;
}

int Room::getFloor() const
{
    return Floor;
}

bool Room::getOccupied() const
{
    return Occupied;
}

void Room::setIndex(int Index)
{
    this->Index = Index;
}

int Room::getIndex() const
{
    return Index;
}

int Room::getNumberRooms()
{
    return numberRooms;
}

void Room::useRoom()
{
    Occupied = true;
}

void Room::exitRoom()
{
    Occupied = false;
}

bool Room::operator<(const Room& room) const
{
    return this->Number < room.Number;
}


ConsultationRoom::ConsultationRoom(int Number, int Floor, bool hasUltrasound, bool Occupied)
    : Room(Number, Floor, Occupied), hasUltrasound(hasUltrasound) {}

bool ConsultationRoom::getUltrasound() const
{
    return hasUltrasound;
}

void ConsultationRoom::displayInfo() const
{
    std::cout << "        Numarul salii: " << Number << std::endl;
    std::cout << "        Etajul: " << (Floor ? std::to_string(Floor) : "parter") << std::endl;
    std::cout << "        Status: " << (Occupied ? "ocupata" : "libera") << std::endl;
    std::cout << "        Ecograf: " << (hasUltrasound ? "Da" : "Nu") << std::endl;
}

ConsultationRoom* ConsultationRoom::clone() const
{
    return new ConsultationRoom(*this);
}


OperationRoom::OperationRoom(int Number, int Floor, bool isSterile, bool Occupied)
    : Room(Number, Floor, Occupied), isSterile(isSterile) {}

bool OperationRoom::getSterile() const
{
    return isSterile;
}

void OperationRoom::cleanRoom()
{
    isSterile = true;
}

void OperationRoom::afterOperation()
{
    isSterile = false;
}

bool OperationRoom::State() const
{
    return isSterile;
}

void OperationRoom::displayInfo() const
{
    std::cout << "        Numarul salii: " << Number << std::endl;
    std::cout << "        Etajul: " << (Floor ? std::to_string(Floor) : "parter") << std::endl;
    std::cout << "        Status: " << (Occupied ? "ocupata" : "libera") << std::endl;
    std::cout << "        Sterilizare: " << (isSterile ? "Da" : "Nu") << std::endl;
}

OperationRoom* OperationRoom::clone() const
{
    return new OperationRoom(*this);
}