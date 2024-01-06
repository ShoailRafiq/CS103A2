/// This module stores global collection stores for the various
/// types of data

#ifndef STORES
#define STORES 1

#include "DataObject.hpp"
#include "User.hpp"

class Stores {
   private:
    static DataObjectCollection users;
    static DataObjectCollection tripTransactions;
    static DataObjectCollection lostItems;
    static DataObjectCollection complaints;

    static User* activeUser;

   public:
    static DataObjectCollection* getUsers();
    static DataObjectCollection* getTripTransactions();
    static DataObjectCollection* getLostItems();
    static DataObjectCollection* getComplaints();

    static void setActiveUser(User* activeUser);
    static User* getActiveUser();
};

#endif
