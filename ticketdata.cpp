#include "ticketdata.h"
#include <string.h>

int TicketData::dataID = 1;


/**
 * In this object we store all the data that describes a Train Ticket
 */
TicketData::TicketData() {};

/**
 * In this object we store all the data that describes a TrainTicket
 *
 * @param {const char*} fName - firs name of the customer
 * @param {const char*} lName - last name of the customer
 * @param {int} quantity - number of seats on the ticket
 * @param {Train*} train - train to which the ticket is purchased to
 */
TicketData::TicketData(const std::string fName,const std::string lName, int quantity, Train* train) : quantity(quantity),train(train)
{
    firstName = fName;
    lastName = lName;
    id = dataID++;
}

TicketData::~TicketData()
{

}
int TicketData::getID()
{
    return id;
}
int TicketData::getQuantity()
{
    return quantity;
}

std::string TicketData::getFirstName()
{
    return firstName;
}
std::string TicketData::getLastName()
{
    return lastName;
}

std::shared_ptr<Train> TicketData::getTrain()
{
    return train;
}
