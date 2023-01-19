#include <iostream>
#include <vector>
#include <unordered_map>
#include <windows.h>

using namespace std;

string u_name, u_password, confirm_password;

bool login()
{
    string name, password;
    int counter = 0;
    cout << " Enter the username:";
    cin >> name;
    cout << "Enter the password:";
    cin >> password;
    if (u_name == name && u_password == password)
    {
        return true;
    }
    else
    {
        cout << "Wrong Creditionals";
        cout << endl;
        return false;
    }
    return false;
}

void takeSignUp()
{
    cout << "Enter your username:";
    cin >> u_name;
    cout << "Enter your password:";
    cin >> u_password;
    cout << "Enter confirm password:";
    cin >> confirm_password;
}
void signup()
{
    takeSignUp();
    int counter = 0;
    if (u_password != confirm_password)
    {
        cout << "Password and Confirm Password doesn't match!\n";
        cout << "Retry" << endl;
        while (true)
        {
            if (counter == 3)
            {
                break;
            }
            if (counter == 1)
            {
                cout << "You have left one chance to type write password otherwise you will have to wait run the program again\n";
            }
            takeSignUp();
            counter++;
        }
    }
    else
    {
        cout << "Registered Successfully" << endl;
    }
}
//  unordered_map, which is a type of associative container that stores elements in no particular order, and allows for fast access to elements using a key value. In this program, it is used to store the names of items, where the keys are integers and the values are strings.
unordered_map<int, string> item_names;
int n;
int w;
//  vectors, which are dynamic arrays that can grow or shrink in size. They are used to store the weight and value of each item.
vector<int> weight;
vector<int> value;

class KnapSackTravelBagPack
{
public:
    void knapsack(int n, int w, vector<int> weight, vector<int> value)
    {
        // Declare a 2D array dp to store the maximum value that can be achieved for each combination of items and weight
        int dp[n + 1][w + 1];
        // Declare a 2D array included to keep track of which items are included in the optimal solution
        bool included[n + 1][w + 1];
         // Iterate through all the items and all the weights
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= w; j++)
            {
                // If we're at the first row or column, set the value to 0
                if (i == 0 || j == 0)
                {
                    dp[i][j] = 0;
                    included[i][j] = false;
                }
                    // If the weight of the current item is less than or equal to the current weight limit
                else if (weight[i - 1] <= j)
                {
                    // Calculate the maximum value that can be achieved by including the current item
                    int included_val = value[i - 1] + dp[i - 1][j - weight[i - 1]];
                    // Calculate the maximum value that can be achieved by not including the current item
                    int excluded_val = dp[i - 1][j];
                     // Compare the two values and mark the one that is greater as the maximum value for that combination of item and weight in the dp table
                    if (included_val > excluded_val)
                    {
                        dp[i][j] = included_val;
                        included[i][j] = true;
                    }
                    else
                    {
                        dp[i][j] = excluded_val;
                        included[i][j] = false;
                    }
                }
                // If the weight of the current item is greater than the current weight limit
                else
                {
                    dp[i][j] = dp[i - 1][j];
                    included[i][j] = false;
                }
            }
        }

        cout << "Maximum value: " << dp[n][w] << endl;

        cout << "Included items: ";
        int i = n;
        int j = w;
        while (i > 0 && j > 0)
        {
            if (included[i][j])
            {
                cout << item_names[i] << " ";
                j -= weight[i - 1];
            }
            i--;
        }
        cout << endl;
    }

    void myTravelBag()
    {
        cout << "Choose Your Bag from the list\n";
        cout << "Press 1 for Salkan Backpacker \n";
        cout << "Press 2 for The Stubble & Co Adventure \n";
        cout << "Press 3 for Best Weekender: AmazonBasics Slim \n";
        cout << "Press 4 for Budget Carry-On: AmazonBasics Carry-On\n";
        int ch;
        cout <<"Enter Your Choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Your TravelBagPack is Salkan Backpacker and its weight = 30lbs";
            w = 30;
            break;
        case 2:
            cout << "Your TravelBagPack is The Stubble & Co Adventure and its weight = 60lbs";
            w = 60;
            break;
        case 3:
            cout << "Your TravelBagPack is Best Weekender: AmazonBasics Slim and its weight = 90lbs";
            w = 90;
            break;
        case 4:
            cout << "Your TravelBagPack is Budget Carry-On: AmazonBasics Carry-On and its weight = 120lbs";
            w = 120;
            break;

        default:
            break;
        }
    }
    void addItems()
    {

        cout << "Enter the number of the products you want to add:";
        cin >> n;
        int w[n], v[n];
        cout << "Enter the name of the products:";
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the name of item" << i << ":";
            cin >> item_names[i];
        }
        cout << "Enter the weight of the products:";
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the weight of item" << i << ":";
            cin >> w[i];
            weight.push_back(w[i]);
        }
        cout << "Enter the value or priority of the products:";
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the value of item" << i << ":";
            cin >> v[i];
            value.push_back(v[i]);
        }
    }
};

int main()
{
    KnapSackTravelBagPack project;
    cout << "--------------------------------------------------------------------"
         << endl;
    cout << "\t\t\t"
         << "KnapSack Travel BagPack\n"
         << "---------------------------------------------------------------------"
         << "\n\n";
        Sleep(2000);
        system("cls");

    while (true)
    {
        cout << " ----- To Use This Application You mush have to sign in  ---" << endl;
        cout << endl
             << "Press 1 to Sign In" << endl
             << "Press 2 to Sign Up" << endl
             << "Press 3 to Exit" << endl;
        int option;
        cout << "Enter your choice:";
        cin >> option;
        if (option == 3)
        {
            break;
        }
        switch (option)
        {
        case 1:

            if (login() == 1)
            {

                cout << "\n\t\t\t"
                     << "Welcome to my Project KnapSack Travel BagPack made by Abdul Wahab"
                     << "\n\n";
                int ch;
                while (true)
                {
                    cout << "\nPress 0 to exit\n";
                    cout << "\nPress 1 to add your trip items\n";
                    cout << "\nPress 2 to choose your BagPack\n";
                    cout << "\nPress 3 to see what items you can take on the trip\n";
                    cout << "\nEnter your choice: ";
                    cin >> ch;
                    if (ch == 0)
                    {
                        break;
                    }
                    switch (ch)
                    {
                    case 1:
                        project.addItems();
                        break;
                    case 2:
                    project.myTravelBag();
                        break;
                    case 3:
                    project.knapsack(n,w,weight,value);
                        break;
                    default:
                        cout << "Invalid option" << endl;
                        break;
                    }
                }
            }
            break;
        case 2:
            signup();
            break;
        case 3:
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    return 0;
}

