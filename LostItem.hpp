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

    uint32_t getReporter();

    void setReporter(User const& reporter);

    string getDescription() const;

    void setDescription(string description);
};

void lostItemMenu(User const& user, DataObjectCollection& lostItems);
