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

    string getStartLocation() const;
    void setStartLocation(string startLocation);

    string getEndLocation() const;
    void setEndLocation(string endLocation);

    void populateObject(DataObject* object) override;
    void fromObject(DataObject* object) override;
    uint32_t getObjectId() const override;
};

/// <summary>
/// Displays a list of the trips, relevant for the
/// current active user type
/// </summary>
void displayTripsList();

void displayCreateTrip();

void displayEditTrip();

void displayViewTrips();

void displayCancelTrip();

#endif