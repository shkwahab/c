#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <unordered_set>
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

bool checkValidSentence(string s)
{
    // check if first character is uppercase
    if (!isupper(s[0]))
    {
        return false;
    }
    // check if last character is a period
    if (s[s.size() - 1] != '.')
    {
        return false;
    }
    // check if there are no double spaces
    for (int i = 0; i < s.size() - 1; i++)
    {
        if (s[i] == ' ' && s[i + 1] == ' ')
        {
            return false;
        }
    }
    return true;
}

// Function to check if input string contains only valid characters
bool checkValidChars(string s, unordered_set<char> &validChars)
{
    for (auto c : s)
    {
        if (validChars.find(c) == validChars.end())
        {
            return false;
        }
    }
    return true;
}

bool wordBreak(string s, unordered_set<string> &wordDict);
bool checkGrammar(string s, unordered_set<string> &wordDict)
{
    return wordBreak(s, wordDict) && checkValidSentence(s);
}
bool wordBreak(string s, unordered_set<string> &wordDict)
{
    int n = s.size();
    bool dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end())
            {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int main()
{

    cout << "--------------------------------------------------------------------"
         << endl;
    cout << "\t\t\t"
         << "Grammar Checker\n"
         << "---------------------------------------------------------------------"
         << "\n\n";
    Sleep(2000);
    system("cls");

    unordered_set<string> wordDict = {"life", "is", "amazing"};
    unordered_set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '.'};
    string w, c, s;
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
                    cout << "\nPress 1 to Enter the word\n";
                    cout << "\nPress 2 to Enter the character\n";
                    cout << "\nPress 3 to Enter the sentence\n";
                    cout << "\nPress 4 to check the word is valid word or not\n";
                    cout << "\nPress 5 to check the character is valid character or not\n";
                    cout << "\nPress 6 to check the sentence is valid sentence or not\n";
                    cout << "\nEnter your choice: ";
                    cin >> ch;
                    if (ch == 0)
                    {
                        break;
                    }
                    switch (ch)
                    {
                    case 1:

                        cout << "Enter the Word:";
                        cin >> w;
                        break;
                    case 2:
                        cout << "Enter the Character:";
                        cin >> c;
                        break;
                    case 3:
                        cin.ignore();
                        cout << "Enter the Sentence:";
                        getline(cin, s);
                        break;
                    case 4:;
                        if (checkGrammar(w, wordDict))
                        {
                            cout << "Valid Word" << endl;
                        }
                        else
                        {
                            cout << "Invalid Word" << endl;
                        }
                        break;
                    case 5:

                        if (checkValidChars(c, validChars))
                        {
                            cout << "Valid Character" << endl;
                        }
                        else
                        {
                            cout << "Invalid Character" << endl;
                        }
                        break;
                    case 6:

                        if (checkValidSentence(s))
                        {
                            cout << "Valid Sentence" << endl;
                        }
                        else
                        {
                            cout << "Invalid Sentence" << endl;
                        }
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