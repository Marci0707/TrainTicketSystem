#include "database.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include "time.h"

/**
 * Constructs a Database object that stores a binary search tree of Days
 *
 * @param {std::shared_ptr} root - root of the tree
 */
DataBase::DataBase(std::shared_ptr<Day> root) : Root(root)
{
    if(root!= nullptr)
        sumTrains = root->getNumOfTrains();
    else
        sumTrains = 0;
}

/**
 * Deletes the dynamically allocated tree, recursively
 * Is not needed anymore after switching to smart pointers
 * @param {std::shared_ptr} root - node in recursion

void DataBase::free(std::shared_ptr<Day> root)
{
    if(root != nullptr)
    {
        free(root->rightBranch);
        free(root->leftBranch);
        delete root;
    }
}
 */


/**
 * Prints the whole tree to console
 *
 * @param {std::shared_ptr} root - node in recursion
 */
void DataBase::listAll(std::shared_ptr<Day> root)
{
    if(root == nullptr)
        return;


    listAll(root->leftBranch);
    root->listTrainsOnDay();
    listAll(root->rightBranch);


}


/**
 * Sets the root of the binary search tree
 *
 * @param {std::shared_ptr} newRoot - new Root
 */
void DataBase::setRoot(std::shared_ptr<Day> newRoot)
{
    Root = newRoot;
}

/**
 * Returns if a specific day is in the binary search tree
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {int} dateNum - the day in yyyymmdd format, basically the ID of the day
 * @returns {boolean} - returns true if the day is in the tree
 */
bool DataBase::dayInTree(std::shared_ptr<Day> root,int dateNum)
{
    if(root == nullptr)
        return false;

    if(dateNum == root->getDateNum())
        return true;

    else if(dateNum > root->getDateNum())
        return dayInTree(root->rightBranch,dateNum);

    else // if(dateNum < this->dateNum)
        return dayInTree(root->leftBranch,dateNum);
}


/**
 * Prints a specific day from the tree
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {int} wantedDay - the day in yyyymmdd format, basically the ID of the day
 * @returns {boolean} returns true if the searched day is in the tree
 */

bool DataBase::listDay(std::shared_ptr<Day> root, int wantedDay)
{
    if(root == NULL)
        return false;

    if(wantedDay == root->getDateNum())
    {

        root->listTrainsOnDay();
        return true;
    }

    if(wantedDay > root->getDateNum())
    {
        return listDay(root->rightBranch,wantedDay);
    }
    else
        return listDay(root->leftBranch,wantedDay);
}

/**
 * Removes a specific train from the database
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {int} ID - the day in yyyymmdd format, basically the ID of the day
 * @returns {boolean} returns true if the train is found and removed
 */
bool DataBase::removeTrainFromBase(std::shared_ptr<Day> root,int ID)
{
    if(root == NULL)
        return false;

    if(root->trainInDay(ID))
    {
        root->removeTrainFromDay(ID);
        return true;
    }
    if(removeTrainFromBase(root->leftBranch,ID)== false)
        return removeTrainFromBase(root->rightBranch,ID);
    else
        return true;
}


/**
 * Returns if a specific day is in the tree
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {int} id - the day in yyyymmdd format, basically the ID of the day
 * @returns {boolean} - returns true if the day is in the tree
 */
bool DataBase::trainInTree(std::shared_ptr<Day> root,int id)
{
    if(root==nullptr)
        return false;
    if(root->trainInDay(id))
        return true;

    return trainInTree(root->rightBranch,id) || trainInTree(root->leftBranch,id);

}

/**
 * Returns the number of trains stored in the database
 *
 * @returns {int} - number of trains
 */
int DataBase::getSum()
{
    return sumTrains;
}


/**
 * Adds a new Day(leaf) to the Database(tree)
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {std::shared_ptr} newLeaf - new Day to be added
 * @returns {std::shared_ptr} - new root of the (sub)Tree
 */
std::shared_ptr<Day> DataBase::addLeaf(std::shared_ptr<Day> root, Day newLeaf)
{
    if(root == NULL)
    {
        root = std::make_shared<Day>();
        *root = newLeaf;
        return root;
    }

    else if(newLeaf.getDateNum() > root->getDateNum())
    {

        root->rightBranch = addLeaf(root->rightBranch,newLeaf);
    }
    else if(newLeaf.getDateNum() < root->getDateNum())
    {
        //std::cout<<"Gg"<<std::endl;
        root->leftBranch = addLeaf(root->leftBranch,newLeaf);
    }
    return root;
}


/**
 * Adds a new train to the database
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {Train} newTrain - new Train to be added
 * @param {int} dateNum - the day in yyyymmdd format, basically the ID of the day
 * @returns {std::shared_ptr} - returns the new root of the (sub)Tree
 */
std::shared_ptr<Day> DataBase::addTrainToBase(std::shared_ptr<Day> root,Train newTrain,int dateNum)
{

    if(dateNum == root->getDateNum())
    {
        root->addTrainToDay(newTrain);
    }
    else if(dateNum > root->getDateNum())
    {
        root->rightBranch = addTrainToBase(root->rightBranch,newTrain,dateNum);
    }
    else //if(dateNum < root->getDateNum())
    {
        root->leftBranch = addTrainToBase(root->leftBranch,newTrain,dateNum);
    }

    return root;

}

/**
 * Reads a train schedule from a file or from the console and makes a tree out of it
 *
 * @param {std::istream&} is - istream
 * @param {boolean} fromConsole - true if the istream is std::cin
 * @returns {std::shared_ptr} - returns the root the of read tree
 */
std::shared_ptr<Day> DataBase::getSchedule(std::istream &is,bool fromConsole)
{

    int maxSeats;
    int price;
    int depY,depMo,depD,depH,depMi;
    int arrY,arrMo,arrD,arrH,arrMi;
    std::string from;
    std::string to;


    if(!fromConsole && !is)
    {
        std::cout<<"\n-----Incorrect filename!-----\n"<<std::endl;
        return Root;
    }



    std::string line;
    while(std::getline(is,line))
    {

        std::istringstream iss (line);
        iss>>to>>from>>depY>>depMo>>depD>>depH>>depMi>>arrY>>arrMo>>arrD>>arrH>>arrMi >> maxSeats>>price;
        Time dep = Time(depH,depMi,depY,depMo,depD);
        Time arr = Time(arrH,arrMi,arrY,arrMo,arrD);
        Train newTrain = Train(maxSeats,arr,dep,from.c_str(),to.c_str(),price);

        int dateNum = depY*10000+depMo*100+depD; //2000 jul 31 --> 20000731 alapján fafelépítés
        if(dayInTree(Root,dateNum))
        {

            Root = addTrainToBase(Root,newTrain,dateNum);

        }
        else
        {
            Day newDay = Day(depY,depMo,depD,dateNum);
            Root = addLeaf(Root,newDay);
            Root = addTrainToBase(Root,newTrain,dateNum);


        }

    }
    std::cin.clear(); // if some error occured, it resets streamstate to defaults, followed by
    int bigNumber = 2147483647;
    std::cin.ignore(bigNumber, '\n'); //jporta nem akarta értelmezni az INT_maxot 2 headerből sem amit találtam, hogy megoldhatja , bezzeg a codeblocks vmiért megérti
    std::cout<<"\n------Trains successfully added!------\n"<<std::endl;

    return Root;
}

/**
 * Returns the root the the tree
 *
 * @returns {std::shared_ptr} - root the the tree
 */
std::shared_ptr<Day> DataBase::getRoot()
{
    return Root;
}

/**
 * Returns a specific Train from the database
 *
 * @param {std::shared_ptr} root - node in recursion
 * @param {int} ID - ID of the wanted Train
 * @returns {std::shared_ptr} - pointer to the train
 */
Train* DataBase::getTrainFromBase(std::shared_ptr<Day> root,int ID)
{

    if(root == nullptr)
        return nullptr;
    if(root->trainInDay(ID))
        return root->getTrainFromDay(ID);

    if(trainInTree(root->leftBranch,ID))
        return getTrainFromBase(root->leftBranch,ID);
    else
        return getTrainFromBase(root->rightBranch,ID);

}
