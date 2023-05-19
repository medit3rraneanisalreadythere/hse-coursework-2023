#include "Controller.hpp"

void Controller::read()
{
    std::string s;
    int x = 0;

    std::cin >> s; //supposed to be command

    if (s == "insert")
    {
        std::cin >> s;

        try
        {
            x = std::stoi(s);
            if (newModel.insert(x))
            {
                std::cout << "Node (" << x << ") was added successfully.\n\n";
                getter = newModel.data;
                updated = true;
            }
            else
            {
                std::cout << "Node (" << x << ") was already added.\n\n";
            }
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "\nThe number you've written is out of range. Try again:\n";
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "\nYou didn't typed a number. Try again:\n";
        }
    }

    else if (s == "remove")
    {
        std::cin >> s;
        
        try
        {
            x = std::stoi(s);
            if (newModel.remove(x))
            {
                std::cout << "Node (" << x << ") was deleted successfully.\n\n";
                getter = newModel.data;
                updated = true;
            }
            else
            {
                std::cout << "Node (" << x << ") is not in the tree.\n\n";
            }
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "\nThe number you've written is out of range. Try again:\n";
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "\nYou didn't typed a number. Try again:\n";
        }
    }
    
    else if (s == "clear")
    {
        newModel.clear();
        getter = newModel.data;
        updated = true;
        // std::cout << "end=" << end << std::endl;
        // std::cout << std::get<0>(getter[0]) << " " << std::get<1>(getter[0]) << " " << std::get<2>(getter[0]) << " " << std::get<3>(getter[0]) << " ";
        std::cout << "The tree was cut down.\n\n";
    }

    else if (s == "debug")
    {
        newModel.print();
        // for (auto r: newModel.data)
        // {
        //     std::cout << std::endl << r.first << " " << r.second;
        // }
    }

    else if (s == "close")
    {
        newModel.clear();
        end = true;
        std::cout << "Bye-bye!\n";
    }

    else
    {
        std::cout << "You didn't typed correct command. Try again:\n";
    }
}