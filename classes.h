#ifndef CLASSES_H
#define CLASSES_H

#include "libraries.h"

class User
{
public:
    std::string password;
    std::string login;
    int user_id;
    float money;
    int debt = 0;
    std::vector<std::string> transaction_history; 

    User() : user_id(0), money(0.0f) {}

    void display_info(std::vector<User>& users)   //method to choose what to do on this acc
    {
        int n;
        std::cout << "\n";
        std::cout << "Hello " << login << std::endl;
        std::cout << "Nice to see You again!\n";
        std::cout << "Your user id is " << user_id << " and You have " << money << " $\n";

        if(debt != 0)
        {
            std::cout << "You have " << debt << " $ debt!!!\n";
        }

        std::cout << "\n";

        do
        {
            std::cout << "\n";
            std::cout << "To transfer money press 1\n";
            std::cout << "To return debt press 2\n";
            std::cout << "To take a loan press 3\n";
            std::cout << "To view transaction history press 4\n";
            std::cout << "To log off press 5\n";
            std::cout << "\n";
            
            std::cin >> n;

            switch(n)
            {
                case 1:
                    transfer(users);
                    break;

                case 2:
                    return_debt();
                    break;

                case 3:
                    getting_debt();
                    break;

                case 4:
                    view_transaction_history();
                    break;

                case 5:
                    std::cout << "Logging off...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while(n != 5);
    }



    void transfer(std::vector<User>& users) //method to transfer money 
    {
        std::string login_of_user;
        int index_of_user;
    
        while(true)
        {   
            std::cout << "Provide index and login of account you want to send money to\n";
        
            while (!(std::cin >> index_of_user))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input for index. Please enter a valid number.\n";
            }

            std::cin >> login_of_user;

        if(index_of_user >= 0 && index_of_user < users.size() && login_of_user == users[index_of_user].login)
        {
            break;
        }

            std::cout << "Wrong index or login, try again\n";
        }

        double amount;

        while(true)
        {
            std::cout << "How much money you want to transfer\n";
        
            if (!(std::cin >> amount) || amount <= 0 || amount > money)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid amount, try again\n";
                continue;
            }
        
            break;
    }

    money -= amount;
    users[index_of_user].money += amount;  
    
    std::cout << "Transfer completed successfully!\n";

    transaction_history.push_back("Transferred " + std::to_string(amount) + " $ to " + users[index_of_user].login);
    users[index_of_user].transaction_history.push_back("Received " + std::to_string(amount) + " $ from " + login);
}


    void getting_debt() //method to take a loan
    {
        int borrow_amount;
        std::cout << "How much money You want to borrow?\n";
        std::cin >> borrow_amount;

        if(borrow_amount > 0)
        {
            debt += borrow_amount * 2; 
            money += borrow_amount;
            std::cout << "You have borrowed " << borrow_amount << " $. You owe " << debt << " $ now.\n";

            transaction_history.push_back("Borrowed " + std::to_string(borrow_amount) + " $");
        }
        else
        {
            std::cout << "Invalid amount. Please enter a positive value.\n";
        }
    }

    void return_debt() //method to return a loan
    {
        if(debt == 0)
        {
            std::cout << "You do not have a debt\n";
            return;
        }
        
        int return_amount;
        
        while(true)
        {
            std::cout << "How much money You want to return?\n";
            std::cin >> return_amount;

            if(std::cin.fail() || return_amount <= 0 || return_amount > money)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You do not have enough money or entered an invalid amount. Try again.\n";
                continue;
            }
            break;
        }

        money -= return_amount;

        if(return_amount >= debt)
        {
            std::cout << "Your debt is cleared! You have " << (return_amount - debt) << " $ extra.\n";
            money += (return_amount - debt); 
            debt = 0;

            transaction_history.push_back("Returned " + std::to_string(return_amount - (return_amount - debt)) + " $, Debt cleared.");
        }
        else
        {
            debt -= return_amount;
            std::cout << "You still owe " << debt << " $.\n";

            transaction_history.push_back("Returned " + std::to_string(return_amount) + " $");
        }
    }

    void view_transaction_history() const  //method to display history 
    {
        std::cout << "Transaction History for " << login << ":\n";
        if(transaction_history.empty())
        {
            std::cout << "No transactions found.\n";
        }
        else
        {
            for(const auto& transaction : transaction_history)
            {
                std::cout << transaction << "\n";
            }
        }
    }
};

#endif
