#ifndef CART_H_INCLUDED
#define CART_H_INCLUDED
#include "ticket.h"
#include "database.h"

/**
 *This object stores the Tickets in a linked list that the user wants to purchase
*/
class Cart
{
public:
    std::shared_ptr<Ticket> last; /**Last Node in the linked list*/
    std::shared_ptr<Ticket> first;/**First Node in the linked list*/

    Cart();
    void addToCart(std::shared_ptr<Ticket> ticket);
    void displayTickets();
    void emptyCart(std::shared_ptr<Ticket> current);
    void listCart();
    void pay();
    bool removeFromCart(int ID,DataBase& db);
    int sumCart();
};


#endif // CART_H_INCLUDED
