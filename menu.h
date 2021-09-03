#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "cart.h"
#include "day.h"
#include "database.h"
#include <string.h>


/**This object is responsible for handling user input*/
class Menu
{
    int menuChoice; /**Currently chosen menu option*/
public:

    Menu();

    void addTrainConsole(DataBase &db);
    void addTrainFile(DataBase &db);
    void cartList(Cart cart);
    void clearCart(Cart &cart);
    void listTrainsAll(DataBase& db);
    void listTrainsDay(DataBase &db);
    void options();
    void payCart(Cart &cart);
    void removeTrain(DataBase& db,Cart &cart);
    void removeCartItem(Cart &cart,DataBase & db);
    void ticketToCart(Cart &cart,DataBase db);
    void waitChoice();

    int getChoice();
    //std::ostream& getOutput();
};


#endif // MENU_H_INCLUDED
