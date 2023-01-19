#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

string u_name, u_password, confirm_password;
vector<string> txt;
vector<string> ptrn;
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

class TextSearchEngine
{
private:
public:
    bool match(string pattern, string text)
    {
        int p = 0, t = 0;
        int star = -1, s = 0;
        while (t < text.length())
        {
            if (p < pattern.length() && (pattern[p] == '?' || pattern[p] == text[t]))
            {
                p++;
                t++;
            }
            else if (p < pattern.length() && pattern[p] == '*')
            {
                star = p++;
                s = t;
            }
            else if (star != -1)
            {
                p = star + 1;
                t = ++s;
            }
            else
                return false;
        }
        while (p < pattern.length() && pattern[p] == '*')
            p++;
        return p == pattern.length();
    }

    vector<pair<string, int>> search(vector<string> pattern, vector<string> &text)
    {
        vector<pair<string, int>> result;
        for (int i = 0; i < text.size(); i++)
        {
            for (string p : pattern)
            {
                if (match(p, text[i]))
                {
                    result.push_back(make_pair(text[i], i));
                    break;
                }
            }
        }
        return result;
    }
    void createList()
    {
        int n;
        string s;
        cout << "Enter the number of text which you want to add:";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the text" << i + 1 << ":";
            cin >> s;
            txt.push_back(s);
        }
    }
    void search()
    {
        string t;
        cout << "Enter the title which you want to Search like(a*,*a):";
        cin >> t;
        ptrn.push_back(t);
    }
};

int main()
{
    TextSearchEngine project;
    cout << "--------------------------------------------------------------------"
         << endl;
    cout << "\t\t\t"
         << "Text Search Engine\n"
         << "---------------------------------------------------------------------"
         << "\n\n";
    Sleep(2000);
    system("cls");
   vector<pair<string, int>> result ;
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
                system("cls");
                cout << "\n\t\t\t"
                     << "Welcome to my Project KnapSack Travel BagPack made by Abdul Wahab"
                     << "\n\n";
                int ch;
                while (true)
                {
                    cout << "\nPress 0 to exit\n";
                    cout << "\nPress 1 to add the words of the list\n";
                    cout << "\nPress 2 to search the word by star pattern\n";
                    cout << "\nPress 3 to display the index of the search result in array\n";
                    cout << "\nEnter your choice: ";
                    cin >> ch;
                    if (ch == 0)
                    {
                        break;
                    }
                    switch (ch)
                    {
                    case 1:
                        project.createList();
                        break;
                    case 2:
                        project.search();
                        break;
                    case 3:
                         result = project.search(ptrn, txt);
                        for (pair<string, int> s : result)
                        {
                            cout << s.first << " found at index " << s.second << endl;
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
