#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED
#include "time.h"
#include <memory>
/**
 *This class models a train that the whole program revolves around.
 *They are stored in a binary search tree grouped by departure date.
 */

class Train
{
    int trainID;
    int maxSeats;
    int soldSeats;
    Time arrival;
    Time departure;
    std::string from;
    std::string to;
    int price;
public:
    static int trainNum;

    Train();
    Train(int maxSeats,Time arrival, Time departure, const std::string From,const std::string To,int price);
    Train(const Train& oldTrain);
    ~Train();

    void reserveSeat(int quantity);
    void freeSeat(int quanity);

    int getID();
    int getMaxSeats();
    int getPrice();
    int getSoldSeats();

    std::string getFrom() const;
    std::string getTo() const;

    Time getDep();
    Time getArr();
};
std::ostream & operator<<(std::ostream&os,Train train);



#endif // TRAIN_H_INCLUDED
