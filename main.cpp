#include "libraries.h"
#include "classes.h"
#include "functions.cpp"

int main()
{
    std::vector<User> users;
    int choice;
    std::string filename = "file.txt";
    std::string default_filename = "default.txt"; 

    load_users_from_file(users, filename);

    while (true)
    {
        terminal();

        while (!(std::cin >> choice)) 
        {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a number.\n";
            terminal();
        }
        

        switch (choice)
        {
            case 1:
                login(users);
                break;

            case 2:
                add_user(users);
                break;

            case 3:
                users_list(users);
                break;

            case 4:
                reset_system(users, default_filename);
                break;

            case 5:
                std::cout << "Exiting...\n";
                save_users_to_file(users, filename);
                return 0;
                
            default:
                std::cout << "Invalid choice, please try again.\n";
                break;
        }
    }

    return 0;
}
