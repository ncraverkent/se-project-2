#include <iostream>
#include "Business.h"
#include "Defs.h"

using namespace WEP;

int main()
{
    Option<Business> business = Business::promptUserNew();
    if (business.has_value())
    {
        std::cout << "Created a buisness with name: " << business.value().getName() << "; and id: " << business.value().getId();
    }
    else
    {
        std::cout << "Did not make buisness";
    }
}