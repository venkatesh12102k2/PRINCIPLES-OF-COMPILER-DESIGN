#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

vector<vector<int>> vectorOfSet(set<set<int>> s)
{
    vector<vector<int>> v;
    for (auto &x : s)
    {
        vector<int> tmp;
        for (auto &y : x)
        {
            tmp.push_back(y);
        }
        v.push_back(tmp);
    }
    return v;
}

void insertAll(set<int> &s, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        s.insert(v[i]);
    }
}

bool hasCommonStates(set<int> a, vector<int> b)
{
    for (auto &x : a)
    {
        for (int j = 0; j < b.size(); j++)
        {
            if (x == b[j])
                return true;
        }
    }
    return false;
}

int main()
{
    int noOfStates, noOfInputSymbols, noOfFinalStates, initialState, tmp;
    int i, j, k;
    cout << "\n\t********************      MINIMIZATION OF DFA      ********************\n\n";
    cout << "Enter the no of states : ";
    cin >> noOfStates;
    cout << "Enter the no of input symbols : ";
    cin >> noOfInputSymbols;

    cout << "(Note: If number of states are 4 then the states are taken as 0, 1, 2, 3.\nSimilarly if number of inputs are 4 then the inputs are taken as 0, 1, 2, 3.)\n";
    cout << "If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.\n";
    cout << "Similarly if the inputs are a,b,c then map the characters to integers as a->0, b->1, c->2\n";
    cout << "Using the above mapping give the following inputs as integer only!!!" << endl;
    cout << "Enter the initial state : ";
    cin >> initialState;
    cout << "Enter no of final states : ";
    cin >> noOfFinalStates;
    vector<bool> isFinalState(noOfStates, false);
    cout << "Enter " << noOfFinalStates << " final states : \n";

    for (int i = 0; i < noOfFinalStates; i++)
    {
        cout << "Final State " << i + 1 << " : ";
        cin >> tmp;
        isFinalState[tmp] = true;
    }

    vector<vector<int>> tt(noOfStates, vector<int>(noOfInputSymbols));
    // tt = {{1, 2}, {2, 4}, {3, 2}, {2, 4}, {1, 4}};
    cout << endl;
    for (int i = 0; i < noOfStates; i++)
    {
        cout << "Enter transitions for the state " << i << " : \n";
        for (int j = 0; j < noOfInputSymbols; j++)
        {
            cout << "State " << i << " on input " << j << " takes transition to ";
            cin >> tt[i][j];
        }
        cout << endl;
    }

    vector<vector<bool>> distinguishableTable(noOfStates, vector<bool>(noOfStates, true));
    int noOfDistinguishableStates = 0;

    for (i = 1; i < noOfStates; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (isFinalState[i] && !isFinalState[j])
            {
                distinguishableTable[i][j] = false;
                distinguishableTable[j][i] = false;
                noOfDistinguishableStates++;
            }
            if (isFinalState[j] && !isFinalState[i])
            {
                distinguishableTable[i][j] = false;
                distinguishableTable[j][i] = false;
                noOfDistinguishableStates++;
            }
        }
    }

    while (true)
    {
        tmp = noOfDistinguishableStates;
        for (i = 1; i < noOfStates; i++)
        {
            for (j = 0; j < i; j++)
            {
                if (distinguishableTable[i][j] == false)
                    continue;
                for (k = 0; k < noOfInputSymbols; k++)
                {
                    if (distinguishableTable[tt[i][k]][tt[j][k]] == false)
                    {
                        distinguishableTable[i][j] = false;
                        distinguishableTable[j][i] = false;
                        noOfDistinguishableStates++;
                        break;
                    }
                }
            }
        }
        if (tmp == noOfDistinguishableStates)
        {
            break;
        }
    }

    cout << endl;
    cout << "\n\t--------------------      DISTINGUISHABLE TABLE      --------------------\n\n";
    for (i = 1; i < noOfStates; i++)
    {
        cout << i;
        for (j = 0; j < i; j++)
        {
            cout << "\t";
            if (distinguishableTable[i][j] == true)
                cout << i << j;
            else
                cout << "X";
        }
        cout << endl;
    }
    cout << endl;
    for (i = 0; i < noOfStates - 1; i++)
    {
        cout << "\t" << i;
    }
    cout << endl;
    vector<vector<int>> minDfaStates;
    vector<int> isCombined(noOfStates, false);
    map<int, vector<int>> dfaStatesToCombinedStates;

    for (i = 1; i < noOfStates; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (distinguishableTable[i][j] == true)
            {
                isCombined[i] = true;
                isCombined[j] = true;
                minDfaStates.push_back({i, j});
            }
        }
    }

    for (i = 0; i < isCombined.size(); i++)
    {
        if (isCombined[i] == false)
        {
            minDfaStates.push_back({i});
        }
    }

    set<set<int>> finalCombinedStates;
    // If 23 and 34 are two combined states we have to make it as a single state as 234.This is done below
    for (i = 0; i < minDfaStates.size(); i++)
    {
        set<int> s;
        for (j = 0; j < minDfaStates[i].size(); j++)
        {
            s.insert(minDfaStates[i][j]);
        }
        for (j = 0; j < minDfaStates.size(); j++)
        {
            if (i == j)
                continue;
            if (hasCommonStates(s, minDfaStates[j]))
            {
                insertAll(s, minDfaStates[j]);
            }
        }
        finalCombinedStates.insert(s);
    }

    // the set "finalCombinedStates" is converted to vector for further processing
    minDfaStates = vectorOfSet(finalCombinedStates);

    for (i = 0; i < minDfaStates.size(); i++)
    {
        for (j = 0; j < minDfaStates[i].size(); j++)
        {
            dfaStatesToCombinedStates[minDfaStates[i][j]] = minDfaStates[i];
        }
    }

    cout << "\n\n\t--------------------      TRANSITION TABLE OF MINIMIZED DFA      ---------------------\n\n";
    vector<int> transitions;
    cout << "\t";
    for (i = 0; i < noOfInputSymbols; i++)
    {
        cout << "\t" << i;
    }
    cout << endl;
    for (i = 0; i < minDfaStates.size(); i++)
    {
        bool starPrinted = false;
        for (j = 0; j < minDfaStates[i].size(); j++)
        {
            if (minDfaStates[i][j] == initialState)
                cout << "->";
            if (!starPrinted && isFinalState[minDfaStates[i][j]])
            {
                cout << "*";
                starPrinted = true;
            }
        }
        cout << "\t";
        for (j = 0; j < minDfaStates[i].size(); j++)
        {
            cout << minDfaStates[i][j];
        }
        for (j = 0; j < noOfInputSymbols; j++)
        {
            transitions = dfaStatesToCombinedStates[tt[minDfaStates[i][0]][j]];
            cout << "\t";
            for (k = 0; k < transitions.size(); k++)
            {
                cout << transitions[k];
            }
        }
        cout << endl;
    }
    return 0;
}