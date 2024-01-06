#ifndef TRIP_TRANSACTION
#define TRIP_TRANSACTION 1

#include "Cost.hpp"
#include "DataObject.hpp"
#include "User.hpp";
#include <stdint.h>

using std::uint32_t;

/// <summary>
/// Represents a trip transaction, contains the details for a created trip
/// </summary>
class TripTransaction : public DataObjectStructure {
   private:
    /// <summary>
    /// The unique ID for the trip
    /// </summary>
    uint32_t id;
    /// <summary>
    /// The ID of the User who represents the driver of this trip
    /// </summary>
    uint32_t driver;
    /// <summary>
    /// The ID of the User who represents the customer that payed for the trip
    /// </summary>
    uint32_t customer;
    /// <summary>
    /// The cost of the trip
    /// </summary>
    Cost cost;
    /// <summary>
    /// The trip starting location
    /// </summary>
    string startLocation;
    /// <summary>
    /// The trip end location
    /// </summary>
    string endLocation;

   public:
    TripTransaction();

    uint32_t getId() const;

    uint32_t getDriver() const;
    void setDriver(User* driver);

    uint32_t getCustomer() const;
    void setCustomer(User* customer);

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

User* promptSelectCustomer(vector<User*> const& customers);

TripTransaction* promptSelectTrip();

/// <summary>
/// Displays a list of the trips, relevant for the
/// current active user type
/// </summary>
void displayTripsList();

/// <summary>
/// Displays the create trips menu
/// </summary>
void displayCreateTrip();

/// <summary>
/// Displays the edit trip menu
/// </summary>
void displayEditTrip();

/// <summary>
/// Displays the view trips menu
/// </summary>
void displayViewTrips();

/// <summary>
/// Displays the cancel trip menu
/// </summary>
void displayCancelTrip();

#endif