#ifndef TRIP_TRANSACTION
#define TRIP_TRANSACTION 1

#include "Cost.hpp"
#include "DataObject.hpp"
#include "User.hpp";
#include <stdint.h>

using std::uint32_t;

class TripTransaction : public DataObjectStructure {
   private:
    uint32_t id;
    uint32_t driver;
    uint32_t customer;
    Cost cost;
    string startLocation;
    string endLocation;

   public:
    TripTransaction();

    uint32_t getId() const;

    uint32_t getDriver() const;
    void setDriver(User const& driver);

    uint32_t getCustomer() const;
    void setCustomer(User const& customer);

    Cost getCost() const;
    void setCost(Cost cost);
};

#endif