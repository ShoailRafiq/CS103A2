#ifndef COMPLAINT
#define COMPLAINT 1

#include "DataObject.hpp"
#include "TripTransaction.hpp"
#include "User.hpp";
#include <stdint.h>

using std::int32_t;

class Complaint : public DataObjectStructure {
   private:
    uint32_t id;
    uint32_t author;
    string message;

   public:
    Complaint();

    uint32_t getId() const;

    uint32_t getAuthor() const;

    void setAuthor(User const& user);

    string getMessage() const;

    void setMessage(string message);

    void populateObject(DataObject* object) override;
    void fromObject(DataObject* object) override;
    uint32_t getObjectId() const override;
};

#endif