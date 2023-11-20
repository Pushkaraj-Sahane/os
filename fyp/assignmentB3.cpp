#include <iostream>
using namespace std;

// we store the index of best fit block for process i in the allocation array

class MemoryManagement
{

    int n, m;
    int *block_size;
    int *process_size;
    int *allocation;

public:
    MemoryManagement()
    {
    }

    void best_fit();
    void worst_fit();
    void first_fit();
    void next_fit();
    void display();
    void accept();
};

void MemoryManagement::best_fit()
{
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;

        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                if (bestIdx == -1)
                {
                    bestIdx = j;
                }
                else if (block_size[bestIdx] > block_size[j])
                {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            block_size[bestIdx] -= process_size[i];
        }
    }
}

void MemoryManagement::worst_fit()
{

    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int wstIdx = -1;

        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                if (wstIdx == -1)
                {
                    wstIdx = j;
                }
                else if (block_size[wstIdx] < block_size[j])
                {
                    wstIdx = j;
                }
            }
        }

        if (wstIdx != -1)
        {
            allocation[i] = wstIdx;
            block_size[wstIdx] -= process_size[i];
        }
    }
}

void MemoryManagement::first_fit()
{
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                allocation[i] = j;
                block_size[j] -= process_size[i];
                break;
            }
        }
    }
}

void MemoryManagement::next_fit()
{
    int j = 0, t = m - 1;
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        // Do not start from beginning
        while (j < m)
        {
            if (block_size[j] >= process_size[i])
            {

                // allocate block j to p[i] process
                allocation[i] = j;

                // Reduce available memory in this block.
                block_size[j] -= process_size[i];

                // sets a new end point
                if(j == 0){
                    t = m-1;
                    break;
                }
                t = (j - 1) % m;

                break;
            }
            if (t == j)
            {
                // sets a new end point
                t = (j - 1) % m;
                // breaks the loop after going through all memory block
                break;
            }
            cout<<j<<" "<<t<<endl;
            // mod m will help in traversing the
            // blocks from starting block after
            // we reach the end.
            j = (j + 1) % m;
        }
    }
}

void MemoryManagement::accept()
{
    cout << "\nEnter the number of processes: ";
    cin >> n;
    cout << "\nEnter the number of blocks: ";
    cin >> m;
    block_size = new int[m];
    process_size = new int[n];
    allocation = new int[n];
    for (int i = 0; i < n; i++)
    {
        int temp;
        cout << "\nEnter process size " << i + 1 << " : ";
        cin >> temp;
        process_size[i] = temp;
    }

    for (int j = 0; j < m; j++)
    {
        int temp;
        cout << "\nEnter block size " << j + 1 << " : ";
        cin >> temp;
        block_size[j] = temp;
    }
}

void MemoryManagement::display()
{

    cout << "\nProcess\tProcessSize\tBlock No." << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << process_size[i] << "\t\t";

        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1;
        }

        else
        {
            cout << "Not allocated";
        }
        cout << endl;
    }
}

int main()
{
    int ch;
    MemoryManagement obj;
    while (true)
    {
        cout << "Menu" << endl;
        cout << "1. To enter the information of block and processes" << endl;
        cout << "2. To perform memory placment with firstfit" << endl;
        cout << "3. To perfrom memory placement with bestfit" << endl;
        cout << "4. To perform memory placment with worstfit" << endl;
        cout << "5. To perform memory placment with nextfit" << endl;
        cout << "0. To exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            obj.accept();
            break;
        case 2:
            obj.first_fit();
            obj.display();
            break;
        case 3:
            obj.best_fit();
            obj.display();
            break;
        case 4:
            obj.worst_fit();
            obj.display();
            break;
        case 5:
            obj.next_fit();
            obj.display();
            break;
        case 0:
            return 0;
            break;
        }
    }
    return 0;
}