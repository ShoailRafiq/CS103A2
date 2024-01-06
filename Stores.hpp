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

    /// <summary>
    /// Loads all the data object collections that
    /// this store contains
    /// </summary>
    static void load();

    /// <summary>
    /// Saves all the data object collections that
    /// this store contains
    /// </summary>
    static void save();
};

#endif
