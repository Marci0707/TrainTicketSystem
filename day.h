#ifndef DAY_H_INCLUDED
#define DAY_H_INCLUDED
#include "train.h"
#include <vector>
#include <iostream>
#include <memory>
/**
 * This object is a node of the binary search tree. All the trains that are leaving this day
 * are stored in here in {std::vector} trains
 */
class Day
{
    /**Describing the day*/
    int year;
    int month;
    int day;
    int dateNum;

    std::vector<Train> trains; /**Trains on this day*/

public:
    int numOfTrains;
    std::shared_ptr<Day> leftBranch;
    std::shared_ptr<Day> rightBranch;


    Day();
    Day(int year,int month, int day,int dateNum);

    void addTrainToDay(Train newTrain);
    void listTrainsOnDay();
    void removeTrainFromDay(int ID);
    void setLeft(std::shared_ptr<Day> newLeft);
    void setRight(std::shared_ptr<Day> newRight);

    bool trainInDay(int ID);

    int getDateNum();
    int getNumOfTrains();

    Train* getTrainFromDay(int id);
};




#endif // DAY_H_INCLUDED
