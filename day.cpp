#include "day.h"
#include <iostream>
#include "day.h"
#include "time.h"
#include "train.h"

/**
 * Creates a new Day which is a leaf in the binary search tree
 */
Day::Day()
{

    rightBranch = nullptr;
    leftBranch = nullptr;
    numOfTrains = 0;
}

/**
 * Creates a new Day which is a leaf in the binary search tree
 *
 * @param {int} year - year of the day
 * @param {int} month - month of the day
 * @param {int} day - day of the day
 * @param {int} dateNum - date of the day in yyyymmdd format, basically the ID of the Day
 */
Day::Day(int year,int month, int day,int dateNum) : year(year), month(month), day(day),dateNum(dateNum)
{
    rightBranch = nullptr;
    leftBranch = nullptr;
    numOfTrains = 1;
}

/**
 * Adds a new train to the day
 *
 * @param {Train} newTrain - new train to be added
 */
void Day::addTrainToDay(Train newTrain)
{

    trains.push_back(newTrain);
    numOfTrains++;

}

/**
 * Lists the trains that are stored in this day
 */
void Day::listTrainsOnDay()
{
    for(Train train : trains)
    {
        std::cout<<train;
    }
}

/**
 * Sets the left subtree of the node
 */
void Day::setLeft(std::shared_ptr<Day> newLeft)
{
    leftBranch = newLeft;
}

/**
 * Sets the right subtree of the node
 */
void Day::setRight(std::shared_ptr<Day> newRight)
{
    rightBranch = newRight;
}


/**
 * Removes a specific train from the day
 *
 * @param {int} ID - ID of the train
 */
void Day::removeTrainFromDay(int ID)
{
    for(unsigned int i = 0; i < trains.size(); i++)
    {
        if(trains[i].getID() == ID)
        {
            trains.erase(trains.begin()+i);
        }
    }
    numOfTrains--;
}

/**
 * Returns if a train is stored in this day
 *
 * @param {int} ID - ID of the train
 * @returns {boolean} - returns true if the train is in this day
*/
bool Day::trainInDay(int ID)
{
    for(unsigned int i = 0; i < trains.size(); i++)
    {
        if(trains[i].getID() == ID)
            return true;
    }
    return false;
}

/**
 * Returns the ID of the day
 *
 * @returns {int} - ID of the day in yyyymmdd format
 */
int Day::getDateNum()
{
    return dateNum;
}

/**
 * Returns the number of trains stored in that day
 *
 * @returns {int} - number of trains that day
 */
int Day::getNumOfTrains()
{
    return numOfTrains;
}

/**
 * Returns a wanted Train from this Day
 *
 * @param {int} ID - ID of the train
 * @returns {Train*} - pointer to the wanted train. Nullptr if the train is NOT in this day
 */
Train* Day::getTrainFromDay(int ID)
{
    for(unsigned int i = 0; i < trains.size(); i++)
        if(trains[i].getID() == ID)
        {
            return &trains[i];
        }
    return nullptr;
}
