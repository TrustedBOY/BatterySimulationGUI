#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include <vector>
#include "Battery.h"

class BatteryPack : public Battery
{

public:
    enum ConnectionType
    {
        SERIES,
        PARALLEL
    };

protected:
    ConnectionType type;
    std::vector<Battery *> cells;

public:
    BatteryPack(ConnectionType t);
    /**
     * @brief adds a battery to the cells
     * @param b the battery thats being added to the cells
     */
    void add(Battery *b);
    /**
     * @brief Decreases charge of all batteries in the cell based on the specific discharge rate of every single battery.
     * @param hours Number of hours of usage.
     */
    void use(double hours) override;
    /**
     * @brief increases charge of all batteries in the cell based on the specific recharge rate of every single battery.
     * @param hours Number of hours of recharge.
     */
    void recharge(double hours) override;
    /**
     * @brief deletes a battery from the cells
     */
    void deleteBattery(int index);
    /**
     *@brief returns the sum of all voltages
     */
    
    double getVoltage() const override;
    /**
     *@brief returns the capacity of the batterypack
     */
    double getCapacity() const override;
    /**
     *@brief returns the charge of the batterypack
     */
    double getCharge() const override;

    /**
     * @brief returns cells
     */
    std::vector<Battery *> &getCells() const;

    /**
     * @brief returns connection type
     */
    ConnectionType getConnectionType() const;


};

#endif // BATTERYPACK_H