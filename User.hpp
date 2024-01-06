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

/// <summary>
/// Finds the admin user from the users data collection if one exists,
/// if none exists a nullptr is returned instead
/// </summary>
/// <returns>The admin user or a nullptr</returns>
User* getAdminUser();

bool isAdminUserSet();

User* getUserByName(string const& name);

/// <summary>
/// Display a menu showing the login and registration options
/// </summary>
void displayAuthMenu();

/// <summary>
/// Displays the login menu
/// </summary>
void displayLoginMenu();

/// <summary>
/// Displays the registration menu
/// </summary>
void displayRegisterMenu();

void displayInitAdminMenu();

#endif