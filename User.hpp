#ifndef USER
#define USER 1

#include "DataObject.hpp"
#include <stdint.h>

using std::int32_t;

enum UserType : int32_t {
    CUSTOMER = 0x0,
    DRIVER = 0x1,
    ADMIN = 0x2,
};

class User : public DataObjectStructure {
   private:
    uint32_t id;
    UserType type;
    string name;
    string password;

   public:
    User();

    uint32_t getId() const;

    UserType getType() const;

    void setType(UserType type);

    string getName() const;

    void setName(string name);

    void setPassword(string password);

    bool isMatchingPassword(string password) const;

    void populateObject(DataObject* object) override;
    void fromObject(DataObject* object) override;
    uint32_t getObjectId() const override;
};

#endif