
#include "Menus.hpp"
#include "Stores.hpp"

int main() {
    // Load the stored data
    Stores::load();

    // Display the main menu
    displayMainMenu();

    // Save the stored data
    Stores::save();
}
