#include "train.h"
#include <string.h>
#include <iomanip>
#include "time.h"
#include <iostream>
int Train::trainNum = 1;

/**
 * In this object we store all the data that describes a TrainTicket
 *
 * @param {int} maxSeats - number of seats on the Train
 * @param {Time} arrival - ETA
 * @param {Time} departure - time of departure
 * @param {std::string} From - city
 * @param {std::string} To - city
 * @param {int} price - price of a single ticket to this train
 */
Train::Train(int maxSeats,Time arrival, Time departure, std::string From,std::string To,int price)
    :maxSeats(maxSeats), arrival(arrival), departure(departure),price(price)
{
    trainID = trainNum++;
    from = From;
    to = To;

    soldSeats = 0;
};

Train::Train()
{
    from = "-";
    to= "-";
}

Train::Train(const Train & oldTrain)
{
    trainID = oldTrain.trainID;
    maxSeats = oldTrain.maxSeats;
    soldSeats = oldTrain.soldSeats;
    arrival = oldTrain.arrival;
    departure = oldTrain.departure;
    price = oldTrain.price;

    from = oldTrain.getFrom();
    to = oldTrain.getTo();
}

Train::~Train()
{
}

void Train::reserveSeat(int quantity)
{
    soldSeats+= quantity;
}
void Train::freeSeat(int quantity)
{
    soldSeats-= quantity;
}

int Train::getID()
{
    return trainID;
}
int Train::getMaxSeats()
{
    return maxSeats;
}
int Train::getPrice()
{
    return price;
}
int Train::getSoldSeats()
{
    return soldSeats;
}

std::string Train::getFrom()const
{
    return from;
}
std::string Train::getTo()const
{
    return to;
}

Time Train::getDep()
{
    return departure;
}
Time Train::getArr()
{
    return arrival;
}

std::ostream& operator<<(std::ostream&os,Train train)
{
    os<<"ID: "<<std::setw(3)<<train.getID()<<" | Leave: "<<train.getDep()<<" | ETA: "<<std::setw(5)<<train.getArr()<<std::left<<" | From: "<<std::setw(15)<<train.getFrom()<<" | To: "<<std::left<<std::setw(15)<<train.getTo()<<" | Available Seats: "<<train.getMaxSeats()-train.getSoldSeats()<<" | Price/seat: "<<train.getPrice()<<"\n";
    return os;
}


