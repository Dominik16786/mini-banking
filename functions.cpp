#include "classes.h"

void terminal()
{
    std::cout <<"\n";
    std::cout << "Welcome to the banking system.\n";
    std::cout << "Press 1 to log in to an account.\n";
    std::cout << "Press 2 to create a new account.\n";
    std::cout << "Press 3 to view the list of users.\n";
    std::cout << "Press 4 to reset the system to default.\n";
    std::cout << "Press 5 to exit.\n";
    std::cout <<"\n";
}

void add_user(std::vector<User>& users) //function to add new user
{
    User user;

    user.user_id = users.size();
    std::cout <<"\n";
    std::cout << "Provide login\n";
    std::cin >> user.login;

    std::cout << "Provide password\n";
    std::cin >> user.password;

    std::cout << "Provide initial balance\n";
    std::cin >> user.money;

    users.push_back(user);

    std::cout << "User created: " << user.login << " with user id: " << user.user_id << "\n";
    std::cout <<"\n";
}

void users_list(const std::vector<User>& users) // function to display users list
{
    std::cout <<"\n";
    std::cout << "List of users:\n";
    for (const auto& user : users)
    {
        std::cout << "Login: " << user.login << ", User ID: " << user.user_id << ", Money: " << user.money << "\n";
    }
    std::cout <<"\n";
}

void login(std::vector<User>& users)  //function to login 
{
    int i;
    std::string login, password;

    while(true)
    {   
        std::cout <<"\n";
        std::cout << "Provide ID of Your account \n";
        std::cin >> i;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n";
            std::cout << "Invalid input. Please enter a valid ID number.\n";
            std::cout << "\n";
            continue;
        }

        if(i >= 0 && i < users.size())
        {
            break;
        }

        std::cout <<"\n";
        std::cout << "Wrong ID, please try again\n";
        std::cout <<"\n";
    }

    while(true)
    {
        std::cout <<"\n";
        std::cout << "Now please provide login to your account\n";
        std::cin >> login;
        if(login == users[i].login)
        {
            break;
        }
        std::cout <<"\n";
        std::cout << "Wrong login, please try again\n";
        std::cout <<"\n";
    }

    while(true)
    {
        std::cout <<"\n";
        std::cout << "Now please provide password to your account\n";
        std::cin >> password;
        if(password == users[i].password)
        {
            break;
        }
        std::cout <<"\n";
        std::cout << "Wrong password, try again\n";
        std::cout <<"\n";
    }
    
    users[i].display_info(users);
}

void save_users_to_file(const std::vector<User>& users, const std::string& filename) // function to save users from file
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (const auto& user : users)
        {
            file << user.user_id << " "
                 << user.login << " "
                 << user.debt << " "
                 << user.password << " "
                 << user.money << "\n";

            file << user.transaction_history.size() << "\n"; 
            for (const auto& transaction : user.transaction_history)
            {
                file << transaction << "\n";
            }
        }
        file.close();
        std::cout << "Users and their transaction history saved to file successfully.\n";
    }
    else
    {
        std::cerr << "Failed to open file for writing.\n";
    }
}


void load_users_from_file(std::vector<User>& users, const std::string& filename) //function to load users from file 
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        User user;
        users.clear();
        while (file >> user.user_id >> user.login >> user.debt >> user.password >> user.money)
        {
            
            int transaction_count;
            file >> transaction_count;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            user.transaction_history.clear();
            for (int i = 0; i < transaction_count; ++i)
            {
                std::string transaction;
                std::getline(file, transaction);
                user.transaction_history.push_back(transaction);
            }

            users.push_back(user);
        }
        file.close();
        std::cout << "Users and their transaction history loaded from file successfully.\n";
    }
    else
    {
        std::cerr << "Failed to open file for reading.\n";
    }
}


void reset_system(std::vector<User>& users, const std::string& default_filename)  //function to reset system with 3 basic accounts
{
    load_users_from_file(users, default_filename);
    std::cout << "System reset to default state.\n";
}
