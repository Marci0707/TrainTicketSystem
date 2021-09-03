#include "cart.h"
#include <iostream>
/**
 * The Cart stores a linked list of tickets
 */
Cart::Cart()
{
    last = nullptr;
    first = nullptr;

}


/**
 * Adds a new item to the linked list in Cart
 *
 * @param {std::shared_ptr} newTicket - The pointer to be added
 */
void Cart::addToCart(std::shared_ptr<Ticket> newTicket)
{
    if(first == nullptr)
    {
        first = newTicket;
        last = newTicket;
        return;
    }
    std::shared_ptr<Ticket> tmp = last;
    last = newTicket;
    tmp->setNext(last);

}



/**
 * Prints out the bought tickets to console
 */
void Cart::displayTickets()
{
    std::cout<<"\n Your Tickets so far:\n";

    std::shared_ptr<Ticket> current = first;
    while(current != NULL)
    {
        std::shared_ptr<Train> train = current->getData()->getTrain(); // current Train;
        std::shared_ptr<TicketData> data = current->getData();
        Time depTime = train->getDep();
        Time arrTime = train->getArr();
        std::cout <<"\n#########################################################################################\n"
                  << "From: " << train->getFrom() << " | To: " << train->getTo() << "\n"
                  << "Dep Time: " << depTime.getYear() << "\\" <<depTime.getMonth() << "\\" <<depTime.getDay()
                  << "on " << depTime.getHour() << ":" << depTime.getMinute() << "\n"
                  << "Arr Time: " << arrTime.getYear() << "\\" <<arrTime.getMonth() << "\\" <<arrTime.getDay()
                  << "on " << arrTime.getHour() << ":" << arrTime.getMinute() << "\n"
                  << "Name: " << data->getFirstName()<<" "<<data->getLastName() << " | Number of seats :" << data->getQuantity() << "\n"
                  <<"#########################################################################################\n";
        current=current->getNext();
    }
}



/**
 * Recursive function to delete the elements of the linked list
 *
 * @param {std::shared_ptr} current - current item in the recursion
 */
void Cart::emptyCart(std::shared_ptr<Ticket> current)
{
    if(current == nullptr)
        return;

    emptyCart(current->getNext());
    current->setNext(nullptr);
}




/**
 * Lists tickets which are in the cart but not yet bought
 */
void Cart::listCart()
{
    if(first == nullptr)
    {
        std::cout<<"\n------Your cart is empty! :( ------\n"<<std::endl;
        return;

    }
    std::cout<<"\n------Your Cart so far:-----\n";

    std::shared_ptr<Ticket> current;

    for(current = first; current != NULL; current = current->getNext())
    {
        std::cout<<"ticketID : "<<current->getData()->getID()<<" | "<<current->getData()->getQuantity()<<" seat(s) | "<<*(current->getData()->getTrain());
    }
}


/**
 * Display all tickets as bought
 */
void Cart::pay()
{
    if(first != nullptr)
        displayTickets();
}



/**
 * Remove a specific item from the Cart.Returns the value of success
 *
 * @param {int} ID - ID of the ticket which is being removed
 * @param {DataBase&} db - The database where the trains are stored
 * @return {boolean} successfully removed
 */

bool Cart::removeFromCart(int ID,DataBase &db)
{
    std::shared_ptr<Ticket> behind = nullptr;
    std::shared_ptr<Ticket> current = first;
    while (current != nullptr && current->getData()->getID() !=  ID)
    {
        behind = current;
        current = current->getNext();
    }

    if (current == nullptr)
    {
        return false;
    }
    else if (behind == nullptr)
    {
        Train* train =  db.getTrainFromBase(db.getRoot(),current->getData()->getTrain()->getID()); //get train pointer from database to freeSeats
        train->freeSeat(current->getData()->getQuantity());
        first = current->getNext();
        return true;
    }
    else
    {
        behind->setNext(current->getNext());
        Train* train =  db.getTrainFromBase(db.getRoot(),current->getData()->getTrain()->getID()); //get train pointer from database to freeSeats
        train->freeSeat(current->getData()->getQuantity());
        return true;
    }
}

/**
 * Sum the prices of the tickets that are in the Cart
 * @return {int} sum
 */


int Cart::sumCart()
{
    int sum;
    std::shared_ptr<Ticket> current;
    for(current = first; current != NULL; current = current->getNext())
    {
        sum+= current->getData()->getTrain()->getPrice()  *   current->getData()->getQuantity();
    }
    return sum;
}
