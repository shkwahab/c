#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

int main()
{
    vector<string> text = {"foo", "bar", "baz", "qux"};
    vector<string> pattern = {"b*r", "f*"};
    vector<pair<string, int>> result = search(pattern, text);
    for (pair<string, int> s : result)
    {
        cout << s.first << " found at index " << s.second << endl;
    }
    return 0;
}
