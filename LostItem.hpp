#ifndef LOST_ITEM
#define LOST_ITEM 1

#include "DataObject.hpp"
#include "TripTransaction.hpp"
#include "User.hpp";
#include <stdint.h>

using std::int32_t;

class LostItem : public DataObjectStructure {
   private:
    uint32_t id;
    uint32_t trip;
    uint32_t reporter;
    string description;

   public:
    LostItem();

    uint32_t getId() const;

    uint32_t getTrip() const;

    void setTrip(TripTransaction const& trip);

    uint32_t getReporter() const;

    void setReporter(User const& reporter);

    string getDescription() const;

    void setDescription(string description);

    void populateObject(DataObject* object) override;
    void fromObject(DataObject* object) override;
    uint32_t getObjectId() const override;
};

void lostItemMenu(User const& user, DataObjectCollection& lostItems);

#endif