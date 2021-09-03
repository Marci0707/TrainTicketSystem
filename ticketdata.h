#ifndef TICKETDATA_H_INCLUDED
#define TICKETDATA_H_INCLUDED
#include "train.h"
#include <memory>
/**Contains all the data that a ticket needs*/
class TicketData
{
    static int dataID;
    std::string firstName;
    std::string lastName;
    int quantity;
    int id;
    std::shared_ptr<Train> train;
public:

    TicketData();
    TicketData( std::string fName, std::string lName,int quantity,Train* train);
    ~TicketData();

    int getID();
    int getQuantity();

    std::string getFirstName();
    std::string getLastName();

    std::shared_ptr<Train> getTrain();


};


#endif // TICKETDATA_H_INCLUDED
