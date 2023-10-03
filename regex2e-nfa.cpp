#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<int, map<char, vector<int>>> transitionTable;

int cntOfStates = 0;

bool isBracesIn(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
            return true;
    }
    return false;
}

vector<int> convert(string s, char closure)
{
    if (s == "")
        return {-1, -1};
    string tmp;
    int i, open, close, cnt;
    vector<vector<int>> subParts;
    if (isBracesIn(s))
    {
        while (s.length() > 1)
        {
            // cout << s.length() << " " << s << endl;

            i = 0;
            if (s[i] == '+')
                i++;
            if (s[i] == '(')
            {
                open = i;
                i++;
                tmp = "";
                cnt = 1;
                while (true)
                {
                    if (s[i] == '(')
                        cnt++;
                    if (s[i] == ')')
                        cnt--;
                    if (cnt == 0)
                        break;
                    tmp += s[i];
                    i++;
                }
                close = i;
                if (i + 1 < s.length() && (s[i + 1] == '*'))
                {
                    subParts.push_back(convert(tmp, '*'));
                    s = s.substr(0, open) + s.substr(close + 2);
                }
                else
                {
                    subParts.push_back(convert(tmp, '0'));
                    s = s.substr(0, open) + s.substr(close + 1);
                }
            }
        }
    }
    // cout << s << endl;
    int start, end;
    if (s.length() == 0)
    {
        for (i = 0; i < subParts.size() - 1; i++)
        {
            transitionTable[subParts[i][1]]['e'] = {subParts[i + 1][0]};
        }
        start = subParts[0][0];
        end = subParts[subParts.size() - 1][1];
    }
    else if (s[0] == '+')
    {
        cntOfStates++;
        transitionTable[cntOfStates]['e'] = {subParts[0][0], subParts[1][0]};
        cntOfStates++;
        transitionTable[subParts[0][1]]['e'] = {cntOfStates};
        transitionTable[subParts[1][1]]['e'] = {cntOfStates};

        start = cntOfStates - 1;
        end = cntOfStates;
    }
    else // the string contains a single character
    {
        cntOfStates++;
        transitionTable[cntOfStates][s[0]] = {cntOfStates + 1};
        cntOfStates++;
        start = cntOfStates - 1;
        end = cntOfStates;
    }

    if (closure == '*')
    {
        cntOfStates++;
        transitionTable[cntOfStates]['e'] = {start, cntOfStates + 1};
        cntOfStates++;
        transitionTable[end]['e'] = {start, cntOfStates};
        start = cntOfStates - 1;
        end = cntOfStates;
    }
    return {start, end};
}

int main()
{
    int j;
    string s;
    cout << "\n\t********************      REGULAR EXPRESSION TO EPSILON-NFA      ********************\n\n";
    cout << "Enter the regular expression \nThe RE should be given inside paranthesis.\nEach and every part of it should be enclosed in the paranthesis\n";
    cout << "For example (a+b)*a*b*abc should be given as (((a)+(b))*(a)*(b)*(a)(b)(c))\n";
    cout << "The character \"e\" refers to epsilon input. Use any characters other than \"e\" in the input!!!" << endl;
    cout << "Use '+' for union operation, '*' for closure operation.\nDon't use '.' for concatenation operation, just place the expressions next to each other.\n";
    cout << "\tInput here\t:\t";
    cin >> s;

    vector<int> initialAndFinalState;
    initialAndFinalState = convert(s, '0');
    set<char> inputs;

    for (auto &x : transitionTable)
    {
        for (auto &y : x.second)
        {
            inputs.insert(y.first);
        }
    }
    for (auto &x : inputs)
    {
        transitionTable[cntOfStates][x] = {};
    }

    cout << "\n\t--------------------      TRANSITION TABLE OF EQUIVALENT EPSILON-NFA      --------------------\n\n";
    cout << "\t";
    for (auto &x : inputs)
    {
        cout << "\t" << x;
    }
    cout << endl;

    vector<int> transitions;
    for (auto &state : transitionTable)
    {
        if (state.first == initialAndFinalState[0])
        {
            cout << "->";
        }
        if (state.first == initialAndFinalState[1])
        {
            cout << "*";
        }
        cout << "\t" << state.first << "\t";
        for (auto &input : inputs)
        {
            if (state.second[input].size() == 0)
                cout << "-1\t";
            else
            {
                transitions = state.second[input];
                for (j = 0; j < transitions.size(); j++)
                {
                    cout << transitions[j];
                    if (j != transitions.size() - 1)
                        cout << ",";
                }
                cout << "\t";
            }
        }
        cout << endl;
    }

    return 0;
}