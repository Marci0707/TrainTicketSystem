#include <iostream>
#include <fstream>
#include <string>
#include "day.h"
#include "database.h"
#include "menu.h"
#include "cart.h"
#include "ctype.h"

int main()
{
    Cart cart;
    std::shared_ptr<Day> root = nullptr;
    DataBase database = DataBase(root);
    Menu menu;


/**
    An option menu to the user
 */
    menu.waitChoice();
    bool inMenu = true;
    while(inMenu)
    {

        switch(menu.getChoice())
        {
        case(1):
        {
            menu.listTrainsAll(database);
            menu.waitChoice();
            break;
        }
        case(2):
        {
            menu.listTrainsDay(database);
            menu.waitChoice();
            break;
        }
        case(3):
        {
            menu.addTrainConsole(database);
            menu.waitChoice();
            break;
        }
        case(4):
        {
            menu.addTrainFile(database);
            menu.waitChoice();
            break;
        }
        case(5):
        {
            menu.ticketToCart(cart,database);
            menu.waitChoice();
            break;
        }
        case(6):
        {
            menu.cartList(cart);
            menu.waitChoice();
            break;
        }
        case(7):
        {
            menu.clearCart(cart);
            menu.waitChoice();
            break;
        }
        case(8):
        {
            menu.payCart(cart);
            menu.waitChoice();
            break;
        }
        case(9):
        {
            menu.removeTrain(database,cart);
            menu.waitChoice();
            break;
        }
        case(10):
        {
            menu.removeCartItem(cart,database);
            menu.waitChoice();
            break;
        }
        case(11):
        {
            inMenu = false;
            break;
        }
        default:
            std::cout<<"\n-----Invalid option-----\n"<<std::endl;
            menu.waitChoice();
        }
    }

    std::cout<<"dsa";
    return 0;
}

