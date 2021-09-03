#include "ticket.h"
#include <iostream>
#include "ticketdata.h"

/**
 * Creates a Ticket object that are stored in the Cart as a linked list node
 */
Ticket::Ticket()
{
    data = nullptr;
    next = nullptr;
}

void Ticket::setData(std::shared_ptr<TicketData> newData)
{
    data = newData;
}
void Ticket::setNext(std::shared_ptr<Ticket> newNext)
{
    next = newNext;
}

std::shared_ptr<Ticket> Ticket::getNext()
{
    return next;
}

std::shared_ptr<TicketData> Ticket::getData()
{
    return data;
}

