#include <iostream>
#include "Battery.h"
Battery::Battery(double v, double c, double initialCharge)
{
   voltage = v;
   capacity = c;
   charge = initialCharge;
   if (charge > capacity)
   {
      charge = capacity;
   }
   if (charge < 0)
   {
      charge = 0;
   }
}

/**
 * @brief Decreases charge based on a fixed discharge rate.
 * @param hours Number of hours of usage.
 */
void Battery::use(double hours)
{
   double usableTime = charge / DISCHARGE_RATE;
   charge = charge - hours * DISCHARGE_RATE;
   if (charge < 0)
   {
      charge = 0;
      std::cout << "The battery can't be used this long, it was used for " << usableTime << std::endl;
   }
}

/**
 * @brief Decreases charge based on a fixed recharge rate.
 * @param hours Number of hours of recharge.
 */
void Battery::recharge(double hours)
{
   double chargeableTime = (capacity - charge) / RECHARGE_RATE;
   charge = charge + hours * RECHARGE_RATE;
   if (charge > capacity)
   {
      charge = capacity;
      std::cout << "The battery has been overcharged,its been charging for an extra" << hours - chargeableTime << std::endl;
   }
}


// Getters //

double Battery::getVoltage() const
{
   return voltage;
}
double Battery::getCharge() const
{
   return charge;
}
double Battery::getCapacity() const
{
   return capacity;
}
double Battery::getPercent() const
{
   return (charge / capacity) * 100;
}