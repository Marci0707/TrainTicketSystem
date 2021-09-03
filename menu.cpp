#include "menu.h"
#include <iostream>

/**
 * A menu object that handles the choices of the user
 */
Menu::Menu() {}

/**
 * Menu option: Handles the input of a new Train from console
 *
 * @param {DataBase&} database - the database that the trains are stored in
 */
void Menu::addTrainConsole(DataBase &database)
{
    std::cout<<"\nAdding new train ;\n";
    std::cout<<"Format : \n";
    std::cout<<"From To DEPy DEPmo DEPd DEPh DEPmi ARRy ARRmo ARRd ARRh ARRmi SeatNUM Price\n";
    std::cout<<"where DEP = departure, ARR = arrival, y = year, mo = month..... mi = minute!\n";
    std::cout<<"after input press enter , ctrl+Z and then double enter !"<<std::endl;

    database.setRoot(database.getSchedule(std::cin,true));
}


/**
 * Menu option: Handles the input of new Trains from file
 *
 * @param {DataBase&} database - the database that the trains are stored in
 */
void Menu::addTrainFile(DataBase &database)
{
    std::string fileName;
    std::cout<<"\nEnter filename!"<<std::endl;
    std::cin>>fileName;
    std::ifstream file (fileName.c_str());
    database.getSchedule(file,false);

}

/**
 * Menu option: Lists cart
 *
 * @param {Cart} cart - cart to be listed
 */
void Menu::cartList(Cart cart)
{
    cart.listCart();
}

/**
 * Menu option: Clears and deletes the dynamically allocated tickets from the Cart and from memory
 *
 * @param {Cart&} cart - cart to be cleared
 */
void Menu::clearCart(Cart &cart)
{

    cart.emptyCart(cart.first);
    cart.first = nullptr;

    std::cout<<"\n-----Cart is now empty-----\n";

}

/**
 * Menu option: Listing all Trains from the database
 *
 * @param {Database&} db - the database that the trains are stored in
 */
void Menu::listTrainsAll(DataBase& db)
{
    if(db.getRoot() == NULL)
    {
        std::cout<<"-----Database is empty!-----"<<std::endl;
        return;
    }

    db.listAll(db.getRoot());
}


/**
 * Menu option: Listing all Trains on a specific day
 *
 * @param {Database&} db - the database that the trains are stored in
 */
void Menu::listTrainsDay(DataBase &database)
{
    int day;
    std::cout<<"\nWhich day would u like to list? Format: YYYYMMDD";
    std::cin>>day;

    if(day>=10000101 && day<=99991231)
    {
        bool success = database.listDay(database.getRoot(),day);
        if(!success)
            std::cout<<"\n-----There is not such date-----\n";
    }
    else
        std::cout<<"\n-----Incorrect format!-----\n";
}


/**
 * Printing menu options
 */
void Menu::options()
{

    std::cout<<"List all trains                1"<<std::endl;
    std::cout<<"List trains on a specific day  2"<<std::endl;
    std::cout<<"Add trains from console        3"<<std::endl;
    std::cout<<"Add trains from file           4"<<std::endl;
    std::cout<<"Add Ticket to Cart             5"<<std::endl;
    std::cout<<"List Cart                      6"<<std::endl;
    std::cout<<"Clear Cart                     7"<<std::endl;
    std::cout<<"Pay items in Cart              8"<<std::endl;
    std::cout<<"Remove Train from Database     9"<<std::endl;
    std::cout<<"Remove Train from Cart         10"<<std::endl;
    std::cout<<"Exit                           11"<<std::endl;
}

/**
 * Menu option: Payment of the tickets
 *
 * @param {Cart&} cart - cart where the tickets are stored
 */

void Menu::payCart(Cart &cart)
{
    if(cart.first != nullptr)
    {

        cart.pay();
        cart.emptyCart(cart.first);
        cart.first = nullptr;
        std::cout<< "SUM:"<< cart.sumCart()<<std::endl;

    }
    else
    {
        std::cout<< "\n-----There are no items to purchase!-----"<<std::endl;
    }
}


/**
 * Menu option: Removing the tickets from the Cart
 *
 * @param {Cart&} cart - cart where the tickets are stored
 * @param {Database&} db - the database that the trains are stored in
 */
void Menu::removeCartItem(Cart &cart,DataBase& db)
{
    std::cout<<"Enter cart item ID"<<std::endl;
    int id;
    std::cin>>id;

    bool success = cart.removeFromCart(id,db);
    if(success)
    {
        std::cout<<"\n------Item successfully removed from cart!------"<<std::endl;
    }
    else
        std::cout<<"\n------There is no item with such ID!------"<<std::endl;
}

/**
 * Menu option: Removing the Trains from the DataBase
 *
 * @param {Database&} db - the database that the trains are stored in
 * @param {Cart&} cart - cart where the tickets are stored
 */
void Menu::removeTrain(DataBase &database,Cart &cart)
{

    std::cout<<"Enter train ID to be removed!"<<std::endl;
    int id;
    std::cin>>id;
    bool success = database.removeTrainFromBase(database.getRoot(),id);
    if(success)
    {
        bool cartSuccess = cart.removeFromCart(id,database);
        if(cartSuccess)
            std::cout<<"\n-----Successfully removed from database and from cart!-----"<<std::endl;
        else
            std::cout<<"\n-----Successfully removed from database!------"<<std::endl;
    }
    else
    {
        std::cout<<"\n------There is no train with this ID-----"<<std::endl;
    }

}

/**
 * Menu option: Removing a specific Train from the DataBase
 *
 * @param {Database&} db - database where the trains are stored in
 * @param {Cart&} cart - cart where the tickets are stored
 */
void Menu::ticketToCart(Cart &cart,DataBase database)
{
    int id;
    std::cout<<"Enter Train ID in order to make a ticket!"<<std::endl;
    std::cin>>id;
    if(id > Train::trainNum  || id<1 || (database.trainInTree(database.getRoot(),id)== false))
    {
        std::cout<< "\n-----Incorrect ID-----"<<std::endl;
        return;
    }

    Train* wantedTrain;
    if(database.trainInTree(database.getRoot(),id)== false)
    {
        std::cout<<"\n------There is not train with such ID!-----"<<std::endl;
        return;
    }


    wantedTrain = database.getTrainFromBase(database.getRoot(),id);

    std::cout<<"Your Name\n";
    std::string firstName;
    std::cin>>firstName;
    std::string lastName;
    std::cin>>lastName;
    std::cout<<"How many tickets?\n";
    int quantity;
    std::cin>>quantity;


    if(wantedTrain->getMaxSeats()-wantedTrain->getSoldSeats() < quantity)
    {
        std::cout<<"There are not enough seats"<<std::endl;
        return;
    }
    else
    {

        database.getTrainFromBase(database.getRoot(),wantedTrain->getID())->reserveSeat(quantity);
        std::shared_ptr<TicketData> newData = std::make_shared<TicketData>(firstName.c_str(),lastName.c_str(),quantity,wantedTrain);
        std::shared_ptr<Ticket> newTicket = std::make_shared<Ticket>();


        newTicket->setData(newData);
        cart.addToCart(newTicket);

        std::cout<<"\n------Successfully addded!------"<<std::endl;
    }
}

/**
 * Gets a menu choice and stores it in Menu::MenuChoice
 */
void Menu::waitChoice()
{

    std::cout<<"\n-----Enter menu option!-----\n"<<std::endl;
    options();


    std::cin>>menuChoice;
    std::cin.clear(); // if some error occured, it resets streamstate to defaults, followed by
    int bigNumber = 2147483647;
    std::cin.ignore(bigNumber, '\n'); //jporta nem akarta értelmezni az INT_maxot 2 headerből sem amit találtam, hogy megoldhatja , bezzeg a codeblocks vmiért megérti
}

/**
 * Returns the stored choice
 *
 * @return {int} - currently chosen menu option
 */
int Menu::getChoice()
{
    return menuChoice;
}
