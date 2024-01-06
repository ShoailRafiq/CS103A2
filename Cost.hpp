
#ifndef COST
#define COST 1

#include <stdint.h>

/// <summary>
/// Represents a cost in dollars and cents
/// </summary>
class Cost {
   private:
    /// <summary>
    /// The number of dollars
    /// </summary>
    int32_t dollars;
    /// <summary>
    /// The number of cents
    /// </summary>
    int32_t cents;

   public:
    /// <summary>
    /// Creates a new cost from the provided dollars
    /// and cents.
    ///
    /// Cents should not be greater than 99
    /// </summary>
    /// <param name="dollars">The number of dollars</param>
    /// <param name="cents">The number of cents</param>
    Cost(int32_t dollars, int32_t cents);

    /// <summary>
    /// Creates a new cost from just the total cents amount.
    /// Any amount of cents greater than 99 will be converted
    /// to dollars
    /// </summary>
    /// <param name="cents">The total number of cents</param>
    Cost(int32_t cents);

    /// <summary>
    /// Creates a default cost of zero dollars and zero cents
    /// </summary>
    Cost();

    /// <summary>
    /// Provides the dollar amount for this cost
    /// </summary>
    /// <returns>The dollar amount</returns>
    int32_t getDollars() const;

    /// <summary>
    /// Provides the cents amount for this cost
    /// </summary>
    /// <returns>The cents amount</returns>
    int32_t getCents() const;

    /// <summary>
    /// Sets the dollar amount for this cost
    /// </summary>
    /// <param name="dollars">The cost dollar value</param>
    void setDollars(int32_t dollars);

    /// <summary>
    /// Sets the cents amount for this cost
    /// </summary>
    /// <param name="cents">The cents value</param>
    void setCents(int32_t cents);

    /// <summary>
    /// Provides the cost in cents, will convert dollars into
    /// cents and sum the total
    /// </summary>
    /// <returns></returns>
    int32_t getTotalCents() const;

    /// <summary>
    /// Displays the formatted cost
    /// </summary>
    void display() const;
};

#endif