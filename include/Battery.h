#include <iostream>

#ifndef BATTERY_H
#define BATTERY_H
class Battery
{
private:
    double voltage, capacity, charge;
    static constexpr double DISCHARGE_RATE = 100.0;
    static constexpr double RECHARGE_RATE = 150.0;
    /**
     * @brief the constructer allows us to create a Battery object
     * @param v it shows us the voltage
     * @param c its the Batterys current charge
     * @param initialCharge its the initial charge
     */
public:
    Battery(double v, double c, double initialCharge);
    /**
     * @brief Decreases charge based on a fixed discharge rate.
     * @param hours Number of hours of usage.
     */
    virtual void use(double hours);
    /**
     * @brief Decreases charge based on a fixed recharge rate.
     * @param hours Number of hours of recharge.
     */
    virtual void recharge(double hours);
    /**
     * @brief returns the voltage
     */
    virtual double getVoltage() const;
    /**
     * @brief returns the charge capacity
     */
    virtual double getCapacity() const;
    /**
     * @brief returns amount of charge left
     */
    virtual double getCharge() const;
    /**
     * @brief returns charge/capacity in a percentage
     */
    virtual double getPercent() const;
    virtual ~Battery() {}
};
#endif