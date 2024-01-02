// Made By    - Akshar Chanchlani
// Student-ID - M00896814


#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> safeSequence;

const int process = 5;
const int resources = 3;

int allocation[process][resources];
int maxNeed[process][resources];
int available[resources];
int need[process][resources];
int newRequests[process][resources];
bool finished[resources];

int n, m; // Number of processes and resources

// Function to check if the system is in a safe state
bool isSafe()
{
    int work[resources];
    for (int j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    bool finish[process];
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }

    int count = 0;

    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);  // Record the process number
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Input for the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the number of resources: ";
    cin >> m;

    // Input the allocation resources
    cout << "Enter the allocation resources:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    // Input the max-need & calculate the need-resources
    cout << "Enter the max-need resources:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maxNeed[i][j];
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    // Input available resources
    cout << "Enter the available resources:" << endl;
    for (int j = 0; j < m; j++)
    {
        cin >> available[j];
    }

    // Check if the system is in a safe state
    if (isSafe())
{
    cout << "System is in a safe state." << endl;
    cout << "Safe Sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSequence[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;
}
else
{
    cout << "System is in an unsafe state." << endl;
}

    // Handle new requests from the system
    cout << "Enter the new request: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> newRequests[i][j];
        }
    }

    // Update allocation resources
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            allocation[i][j] += newRequests[i][j];
        }
    }

    // Update available resources
    for (int j = 0; j < m; j++)
    {
        available[j] -= newRequests[0][j];
    }

    // Check if the system remains in a safe state after processing new requests
    if (isSafe())
    {
        cout << "Request granted. System is still in a safe state." << endl;
    }
    else
    {
        cout << "Request denied. System is no longer in a safe state." << endl;
    }

    return 0;
}
