#include <iostream>
#include "BatteryPack.h"

BatteryPack::BatteryPack(ConnectionType t)
    : Battery(0, 0, 0), type(t) {}

/**
 * @brief adds a battery to the cells
 * @param b the battery thats being added to the cells
 */
void BatteryPack::add(Battery *b)
{
    cells.push_back(b);
}

/**
 * @brief deletes a battery from the cells
 * @param index the index of the battery to delete
 */
void BatteryPack::deleteBattery(int index)
{
    if (index >= 0 && index < cells.size())
    {
        cells.erase(cells.begin() + index);
    }
}

/**
 * @brief Decreases charge of all batteries in the cell based on the specific discharge rate of every single battery.
 * @param hours Number of hours of usage.
 */
void BatteryPack::use(double hours)
{
    for (Battery *b : cells)
        b->use(hours);
}

/**
 * @brief increases charge of all batteries in the cell based on the specific recharge rate of every single battery.
 * @param hours Number of hours of recharge.
 */
void BatteryPack::recharge(double hours)
{
    for (Battery *b : cells)
        b->recharge(hours);
}

// Getters //

double BatteryPack::getVoltage() const
{
    double voltage = 0;
    if (type == SERIES)
    {

        for (Battery *b : cells)
        {
            voltage += b->getVoltage();
        }
        return voltage;
    }

    return cells[0]->getVoltage();
}
double BatteryPack::getCapacity() const
{
    if (type == ConnectionType::SERIES)
    {
        double minCapacity = cells.empty() ? 0 : cells[0]->getCapacity();
        for (Battery *b : cells)
        {
            if (b->getCapacity() < minCapacity)
            {
                minCapacity = b->getCapacity();
            }
        }
        return minCapacity;
    }
    else if (type == ConnectionType::PARALLEL)
    {
        double totalCapacity = 0;
        for (Battery *b : cells)
        {
            totalCapacity += b->getCapacity();
        }
        return totalCapacity;
    }
    return 0;
}
double BatteryPack::getCharge() const
{
    if (type == ConnectionType::SERIES)
    {
        double minCharge = cells.empty() ? 0 : cells[0]->getCharge();
        for (Battery *b : cells)
        {
            if (b->getCharge() < minCharge)
            {
                minCharge = b->getCharge();
            }
        }
        return minCharge;
    }
    else if (type == ConnectionType::PARALLEL)
    {
        double totalCharge = 0;
        for (Battery *b : cells)
        {
            totalCharge += b->getCharge();
        }
        return totalCharge;
    }
    return 0;
}
std::vector<Battery *> &BatteryPack::getCells() const
{
    return const_cast<std::vector<Battery *> &>(cells);
}
BatteryPack::ConnectionType BatteryPack::getConnectionType() const
{
    return type;
}