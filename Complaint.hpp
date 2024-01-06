#ifndef COMPLAINT
#define COMPLAINT 1

#include "DataObject.hpp"
#include "TripTransaction.hpp"
#include "User.hpp";
#include <stdint.h>

using std::int32_t;

/// <summary>
/// Represents a complaint filed
/// </summary>
class Complaint : public DataObjectStructure {
   private:
    /// <summary>
    /// The unique ID for this complaint
    /// </summary>
    uint32_t id;
    /// <summary>
    /// The ID of the user who created the complaint
    /// </summary>
    uint32_t author;
    /// <summary>
    /// The complaint message
    /// </summary>
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

/// <summary>
/// Displays a list of the complaints, relevant for the
/// current active user type
/// </summary>
void displayComplaintsList();

/// <summary>
/// Displays the create complaint menu
/// </summary>
void displayCreateComplaint();

/// <summary>
/// Displays the edit complaint menu
/// </summary>
void displayEditComplaint();

/// <summary>
/// Displays the view complaints menu
/// </summary>
void displayViewComplaints();

/// <summary>
/// Displays the delete complaint menu
/// </summary>
void displayDeleteComplaint();

#endif