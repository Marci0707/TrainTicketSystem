#ifndef DATEBASE_H_INCLUDED
#define DATEBASE_H_INCLUDED
#include "day.h"
#include <fstream>

/**
 * This is the database that all the trains are in. The Database object stores the Root of a binary search tree.
 * The Nodes in the Tree are Day objects that contain all the trains leaving that day.
*/
class DataBase
{
    int sumTrains; /**Number of trains in the database*/
    std::shared_ptr<Day> Root;
public:
    DataBase(std::shared_ptr<Day> root);

    void free(std::shared_ptr<Day> root);
    void listAll(std::shared_ptr<Day> root);
    void setRoot(std::shared_ptr<Day> newRoot);

    bool dayInTree(std::shared_ptr<Day> root,int dateNum);
    bool listDay(std::shared_ptr<Day> root, int wantedDay);
    bool removeTrainFromBase(std::shared_ptr<Day> root,int ID);
    bool trainInTree(std::shared_ptr<Day> root,int id);

    int getSum();

    std::shared_ptr<Day> addLeaf(std::shared_ptr<Day> root, Day newLeaf);
    std::shared_ptr<Day> addTrainToBase(std::shared_ptr<Day> root,Train newTrain,int dateNum);
    std::shared_ptr<Day> getRoot();
    std::shared_ptr<Day> getSchedule(std::istream &file,bool fromConsole);

    Train* getTrainFromBase(std::shared_ptr<Day> Root,int id);
};


#endif // DATEBASE_H_INCLUDED
