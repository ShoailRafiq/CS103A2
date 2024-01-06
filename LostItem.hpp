#ifndef LOST_ITEM
#define LOST_ITEM 1

#include "DataObject.hpp"
#include "TripTransaction.hpp"
#include "User.hpp";
#include <stdint.h>

/// <summary>
/// Represents a lost item
/// </summary>
class LostItem : public DataObjectStructure {
   private:
    /// <summary>
    /// The unique ID for the lost item
    /// </summary>
    uint32_t id;
    /// <summary>
    /// The ID of the trip transcation that the item was found/lost on
    /// </summary>
    uint32_t trip;
    /// <summary>
    /// The ID of the user that reported the lost item
    /// </summary>
    uint32_t reporter;
    /// <summary>
    /// The description of the lost item
    /// </summary>
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

/// <summary>
/// Displays a list of the lost items, relevant for the
/// current active user type
/// </summary>
void displayLostItemsList();

/// <summary>
/// Prompts the user to select a lost item from a list of
/// lost items
/// </summary>
/// <returns>The selected lost item or nullptr if no lost item was
/// selected</returns>
LostItem* promptSelectLostItem();

/// <summary>
/// Displays the create lost item menu
/// </summary>
void displayCreateLostItem();

/// <summary>
/// Displays the edit lost item menu
/// </summary>
void displayEditLostItem();

/// <summary>
/// Displays the view lost items menu
/// </summary>
void displayViewLostItems();

/// <summary>
/// Displays the delete lost item menu
/// </summary>
void displayDeleteLostItem();

#endif