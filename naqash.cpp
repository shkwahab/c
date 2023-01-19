#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <unordered_set>

using namespace std;

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
    string s = "Life is amazing.";
    unordered_set<string> wordDict = {"life", "is", "amazing"};
    unordered_set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '.'};
    
    if ( checkValidSentence(s) )
    {
        cout << "this is a valid sentence." << endl;
    }
    else
    {
        cout << "this is not a valid sentence." << endl;
    }
}
