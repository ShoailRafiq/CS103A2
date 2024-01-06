#ifndef STORES
#define STORES 1

#include "DataObject.hpp"
#include "User.hpp"

/// <summary>
/// Global store the stores data collections and the active user,
/// allows more easy loading of different data
/// </summary>
class Stores {
   private:
    /// <summary>
    /// Data object collection for users
    /// </summary>
    static DataObjectCollection users;
    /// <summary>
    /// Data object collection for trip transactions
    /// </summary>
    static DataObjectCollection tripTransactions;
    /// <summary>
    /// Data object collection for lost items
    /// </summary>
    static DataObjectCollection lostItems;
    /// <summary>
    /// Data object collection for complaints
    /// </summary>
    static DataObjectCollection complaints;

    /// <summary>
    /// The currently authenticated user
    /// </summary>
    static User* activeUser;

   public:
    /// <summary>
    /// Provides the data object collection for users
    /// </summary>
    /// <returns>Pointer to the data object collection</returns>
    static DataObjectCollection* getUsers();

    /// <summary>
    /// Provides the data object collection for trip transactions
    /// </summary>
    /// <returns>Pointer to the data object collection</returns>
    static DataObjectCollection* getTripTransactions();

    /// <summary>
    /// Provides the data object collection for lost items
    /// </summary>
    /// <returns>Pointer to the data object collection</returns>
    static DataObjectCollection* getLostItems();

    /// <summary>
    /// Provides the data object collection for complaints
    /// </summary>
    /// <returns>Pointer to the data object collection</returns>
    static DataObjectCollection* getComplaints();

    /// <summary>
    /// Sets the currently active user, stores is now considered the
    /// owner of the provided User pointer.
    ///
    /// Will free the memory of existing active users if a new one is set.
    ///
    /// Can be set to a nullptr to represent no active user
    /// </summary>
    /// <param name="activeUser">The pointer to the new active user</param>
    static void setActiveUser(User* activeUser);

    /// <summary>
    /// Provides a pointer to the active user or a nullptr if
    /// there is no active user
    /// </summary>
    /// <returns>The pointer to the active user or nullptr</returns>
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
