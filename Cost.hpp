
#ifndef COST
#define COST 1

#include <stdint.h>

class Cost {
   private:
    int32_t dollars;
    int32_t cents;

   public:
    Cost(int32_t dollars, int32_t cents);
    Cost();

    int32_t getDollars() const;
    int32_t getCents() const;

    void setDollars(int32_t dollars);
    void setCents(int32_t cents);

    int32_t getTotalCents() const;
};

#endif