   #include <bits/stdc++.h>
#define MAX 999
using namespace std;

class Job
{
    int id;
    int arrival;
    int burst;
    int cp;
    int ta;
    int waiting;
    int pr;

public:
    Job()
    {
        id = 0;
        arrival = 0;
        burst = 0;
        ta = 0;
        cp = 0;
        waiting = 0;
        pr=0;
    }

    void accept(){
        cout << "Enter Process Id: ";
        cin >> id;
        cout << "Enter Arrival time: ";
        cin >> arrival;
        cout << "Enter Burst time: ";
        cin >> burst;
    }

    void accept2()
    {
        cout << "Enter Process Id: ";
        cin >> id;
        cout << "Enter Arrival time: ";
        cin >> arrival;
        cout << "Enter Burst time: ";
        cin >> burst;
        cout<< "Enter Priority; ";
        cin>>pr;
    }

    /*
    void display()
    {
        cout << id << "\t" << arrival << "\t" << arrival << "\t" << burst << "\t" << ta << "\t" << waiting << endl;
    }*/
    friend class Scheduler;
};

class Scheduler
{
    vector<Job> jobs;
    int n;
    int *remainingTime;

public:
    Scheduler()
    {
        cout << "Enter no. of processes: ";
        cin >> n;
    }

    void get(){
        for (int i = 0; i < n; i++)
        {
            Job j;
            cout<<"\n\n";
            j.accept();
            jobs.push_back(j);
        }
    }

    void get1(){
        for (int i = 0; i < n; i++)
        {
            Job j;
            cout<<"\n\n";
            j.accept2();
            jobs.push_back(j);
        }
    }

    static bool compareAT(Job x, Job y)
    {
        return x.arrival < y.arrival;
    }

    
    void display()
    {
        cout << "\n-----------------------------------------------------------------------------------------------";
        cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn-Around Time | Wait Time ";
        cout << "\n-----------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < n; i++)
        {
            cout << "    " << jobs[i].id << "\t\t" << jobs[i].arrival << "\t\t" << jobs[i].burst << "\t\t" << jobs[i].cp << "\t\t" << jobs[i].ta << "\t\t" << jobs[i].waiting<<endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }
    

    void display1()
    {
        cout << "\n-------------------------------------------------------------------------------------------------------";
        cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn-Around Time | Wait Time | Priority";
        cout << "\n-------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < n; i++)
        {
            cout << "    " << jobs[i].id << "\t\t" << jobs[i].arrival << "\t\t" << jobs[i].burst << "\t\t" << jobs[i].cp << "\t\t" << jobs[i].ta << "\t\t" << jobs[i].waiting <<"\t\t"<<jobs[i].pr<<endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }

    void FCFS()
    {
        sort(jobs.begin(), jobs.end(), compareAT);

        float avg_w = 0, avg_ta = 0;
        jobs[0].cp = jobs[0].burst;
        jobs[0].ta = jobs[0].burst;
        jobs[0].waiting = 0;

        int temp = jobs[0].burst;

        for (int i = 1; i < n; i++)
        {
            temp += jobs[i].burst;
            jobs[i].cp = temp;
        }

        for (int i = 1; i < n; i++)
        {
            jobs[i].ta = jobs[i].cp - jobs[i].arrival;
            jobs[i].waiting = jobs[i].ta - jobs[i].burst;
        }

        for (int i = 0; i < n; i++)
        {
            avg_w += jobs[i].waiting;
            avg_ta += jobs[i].ta;
        }

        avg_ta /= n;
        avg_w /= n;

        cout << "Average waiting time: " << avg_w << endl;
        cout << "Average turn around time: " << avg_ta;
    }

    void SJF()
    {
        remainingTime = new int[n];

        for (int i = 0; i < n; i++)
        {
            remainingTime[i] = jobs[i].burst;
        }

        int currentTime = 0;
        int completedTasks = 0;
        int shortestTask = 0;
        int minBurst = MAX;
        bool active = false;

        while (completedTasks != n)
        {
            for (int j = 0; j < n; j++)
            {
                if (jobs[j].arrival <= currentTime && jobs[j].burst < minBurst && remainingTime[j] > 0)
                {
                    shortestTask = j;
                    minBurst = jobs[j].burst;
                    active = true;
                }
            }

            if (active == false)
            {
                currentTime++;
                continue;
            }

            minBurst = --remainingTime[shortestTask];
            if (minBurst == 0)
            {
                minBurst = MAX;
            }

            if (remainingTime[shortestTask] == 0)
            {
                completedTasks++;
                active = false;
                jobs[shortestTask].cp = currentTime + 1;
                jobs[shortestTask].ta = jobs[shortestTask].cp - jobs[shortestTask].arrival;
                jobs[shortestTask].waiting = jobs[shortestTask].ta - jobs[shortestTask].burst;

                if (jobs[shortestTask].waiting < 0)
                {
                    jobs[shortestTask].waiting = 0;
                }
            }
            currentTime++;
        }
        float avg_w = 0, avg_ta = 0;

        for (int i = 0; i < n; i++)
        {
            avg_w += jobs[i].waiting;
            avg_ta += jobs[i].ta;
        }

        avg_ta /= n;
        avg_w /= n;

        cout << "Average waiting time: " << avg_w << endl;
        cout << "Average turn around time: " << avg_ta;
    }

    void roundRobin(int tq)
    {
        queue<int> readyQ;

        int currentTime = 0;
        int completedTasks = 0;
        int curr;

        remainingTime = new int[n];
        for (int i = 0; i < n; i++)
        {
            remainingTime[i] = jobs[i].burst;
        }

        for (int j = 0; j < n; j++)
        {
            if (jobs[j].arrival <= currentTime)
            {
                readyQ.push(j);
            }
        }

        while (completedTasks != n)
        {
            curr = readyQ.front();
            readyQ.pop();

            int counter = 0;

            while (counter != tq && counter != remainingTime[curr])
            {
                currentTime++;
                counter++;

                for (int j = 0; j < n; j++)
                {
                    if (jobs[j].arrival == currentTime)
                    {
                        readyQ.push(j);
                    }
                }
            }

            remainingTime[curr] -= counter;

            if (remainingTime[curr] == 0)
            {
                jobs[curr].cp = currentTime;
                jobs[curr].ta = jobs[curr].cp - jobs[curr].arrival;
                jobs[curr].waiting = jobs[curr].ta - jobs[curr].burst;
                completedTasks++;
            }
            else
            {
                readyQ.push(curr);
            }
        }
        float avg_w = 0, avg_ta = 0;

        for (int i = 0; i < n; i++)
        {
            avg_w += jobs[i].waiting;
            avg_ta += jobs[i].ta;
        }

        avg_ta /= n;
        avg_w /= n;

        cout << "Average waiting time: " << avg_w << endl;
        cout << "Average turn around time: " << avg_ta;
    }

void priority()
{
    remainingTime = new int[n];

    for (int i=0; i<n; i++)
        remainingTime[i] = jobs[i].burst;

    int currentTime = 0;
    int completedTasks = 0;
    int completionTime = 0;
    int higherPriority = 0;
    int remBurst = 0;
    int maxPriority = MAX;
    bool taskActive = false;

    while (completedTasks != n)
    {
        for (int j=0; j<n; j++)
        {
            if(jobs[j].arrival <= currentTime && remainingTime[j] > 0 && jobs[j].pr < maxPriority)
            {
                higherPriority = j;
                maxPriority = jobs[j].pr;
                taskActive = true;
            }
        }

        if(!taskActive)
        {
            currentTime++;
            continue;
        }

        currentTime += jobs[higherPriority].burst;
        remainingTime[higherPriority] = 0;
        maxPriority = MAX;
        taskActive = false;
        completedTasks++;
           
        jobs[higherPriority].cp = currentTime;
        jobs[higherPriority].ta =  jobs[higherPriority].cp -  jobs[higherPriority].arrival;
        jobs[higherPriority].waiting =  jobs[higherPriority].ta -  jobs[higherPriority].burst;
    }

    float avg_w = 0, avg_ta = 0;

        for (int i = 0; i < n; i++)
        {
            avg_w += jobs[i].waiting;
            avg_ta += jobs[i].ta;
        }

        avg_ta /= n;
        avg_w /= n;

        cout << "Average waiting time: " << avg_w << endl;
        cout << "Average turn around time: " << avg_ta;
}

};

int main()
{
    Scheduler obj;
    int ch, quantum;
    char ans = 'y';

    do
    {
        cout<<"\nChoose algorithm: \n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            obj.get();
            obj.FCFS();
            obj.display();
            break;

            case 2:
            obj.get();
            obj.SJF();
            obj.display();
            break;

            case 3:
            obj.get1();
            obj.priority();
            obj.display1();
            break;

            case 4:
            cout<<"\nEnter time quantum: ";
            cin>>quantum;
            obj.get();
            obj.roundRobin(quantum);
            obj.display();
            break;            

            default:
            cout<<"\nInvalid choice!";
            break;
        } 
        
        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
}