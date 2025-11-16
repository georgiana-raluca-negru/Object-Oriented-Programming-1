#ifndef HELPET_VACCINESTOCKOBSERVER_H
#define HELPET_VACCINESTOCKOBSERVER_H

#include <string>
#include <vector>
#include <iostream>

class Vaccine;

class VaccineObserver
{
public:
    virtual ~VaccineObserver() = default;
    virtual void onStockChanged(const Vaccine* vaccine, int oldStock, int newStock) = 0;
};

class VaccineStockNotifier : public VaccineObserver
{
    void notifyLowStock(const Vaccine* vaccine, int stock);
    void notifyStockChange(const Vaccine* vaccine, int oldStock, int newStock);

public:
    void onStockChanged(const Vaccine* vaccine, int oldStock, int newStock) override;
};


class VaccineSubject
{
    std::vector<VaccineObserver*> observers;

public:
    void addObserver(VaccineObserver* observer);
    void removeObserver(VaccineObserver* observer);
    void notifyObservers(const Vaccine* vaccine, int oldStock, int newStock);
};

#endif //HELPET_VACCINESTOCKOBSERVER_H