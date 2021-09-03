#ifndef TICKET_H_INCLUDED
#define TICKET_H_INCLUDED
#include "train.h"
#include "ticketdata.h"
#include <memory>
/**This object is a linked list node that describes a ticket to a Train*/
class Ticket
{
    std::shared_ptr<Ticket> next;
    std::shared_ptr<TicketData> data; /**All the data of a ticket*/

public:
    Ticket();

    void setData(std::shared_ptr<TicketData> data);
    void setNext(std::shared_ptr<Ticket> newNext);

    std::shared_ptr<Ticket> getNext();

    std::shared_ptr<TicketData> getData();
};

#endif // TICKET_H_INCLUDED
