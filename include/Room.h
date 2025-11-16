#ifndef HELPET_ROOM_H
#define HELPET_ROOM_H

class Room
{
protected:
    static int numberRooms;
    int Number;
    int Floor;
    int Index;
    bool Occupied;

public:
    Room(int Number = 0, int Floor = 0, bool Occupied = false);
    virtual ~Room() = default;

    int getNumber() const;
    int getFloor() const;
    bool getOccupied() const;
    void setIndex(int Index);
    int getIndex() const;
    static int getNumberRooms();
    void useRoom();
    void exitRoom();

    virtual Room* clone() const = 0;
    virtual void displayInfo() const = 0;

    bool operator<(const Room& room) const;
};

class ConsultationRoom : public Room
{
    bool hasUltrasound;
public:
    ConsultationRoom(int Number = 0, int Floor = 0, bool hasUltrasound = false, bool Occupied = false);
    bool getUltrasound() const;
    void displayInfo() const override;
    ConsultationRoom* clone() const override;
};

class OperationRoom : public Room
{
    bool isSterile;
public:
    OperationRoom(int Number = 0, int Floor = 0, bool isSterile = false, bool Occupied = false);
    bool getSterile() const;
    void cleanRoom();
    void afterOperation();
    bool State() const;
    void displayInfo() const override;
    OperationRoom* clone() const override;
};

#endif //HELPET_ROOM_H