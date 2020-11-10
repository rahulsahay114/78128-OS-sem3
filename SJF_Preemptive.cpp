#include <iostream>
using namespace std;

int size;

class process {

public:

    string name;
    int at; //arrival time
    int bt; //burst time

    int tt; //turnaround time
    int rem_bt; //remaining burst time
    int wt; //waiting time

    bool valid;

    process()
    {
        at = tt = bt = wt = rem_bt = 0;
        valid = false;
    }

};

void sjf(process* p)
{
    int totBurst = 0;
    int numOfValidProcesses = size;

    for(int i=0; i<size; i++)
    {
        totBurst += p[i].bt; //calculating total burst time
    }

    for(int i=0; i<totBurst; i+0)
    {
        for(int j=0; j<size; j++)
        {
            if(p[j].at <= i && !p[j].valid && p[j].rem_bt != 0)
            {
                p[j].valid = true;

                /* processes that were previously not valid i.e 'valid == false',
                 * haven't finished running i.e remaining burst time ('rem_bt') != 0, and
                 * whose arrival time ('at') matches with the current time ('i') will be marked valid ('valid' = true).
                 * Only valid processes are given CPU burst. */
            }
        }

        //Give CPU to process with shortest remaining time.

        int minIdx = 0;
        //minIdx will store the index of the process that is valid, i.e has arrived, and has the shortest
        //remaining burst time; the index of the shortest remaining job.

        for(int k=0; k<size; k++)
        {
            if(p[minIdx].rem_bt >= p[k].rem_bt && p[k].valid)
            {
                minIdx = k;
            }
        }

        /* If only one valid process left, i.e all processes have finished executing
         * and only one remains, then 'minIdx' will store the position of that process only.
         * otherwise it always pointed to the position = 0 and it was never able to acquire
         * the index of the last valid process due the if condition being always false when only one valid process
         * was left. */

        if(numOfValidProcesses == 1)
        {
           for(int k=0; k<size; k++)
           {
               if(p[k].valid)
                   minIdx = k;
           }
        }

        p[minIdx].rem_bt = p[minIdx].rem_bt - 1;

        if(p[minIdx].rem_bt == 0)
        {
            p[minIdx].valid = false;
            numOfValidProcesses--; //number of valid processes decremented as processes finish executing.
        }

        for(int k=0; k<size; k++)
        {
            if(k != minIdx && p[k].valid)
            {
                p[k].wt = p[k].wt+1;
            }
        }

        i++;
    }
}


int main() {

    cout<<"\nEnter Number of Processes: ";
    cin>>::size;

    process *p = new process[size];
    for(int i=0; i<size; i++)
    {
        cout<<"\nEnter Process Name: ";
        cin>>p[i].name;

        cout<<"Enter Arrival Time: ";
        cin>>p[i].at;

        cout<<"Enter Burst Time: ";
        cin>>p[i].bt;
        p[i].rem_bt = p[i].bt;
    }

    sjf(p);

    double tot_wt = 0;

    for(int i=0; i<size; i++)
    {
        cout<<"\nName: "<<p[i].name<<"; Burst Time: "<<p[i].bt<<"; Arrival Time: "<<p[i].at<<"; Waiting Time: "<<p[i].wt;
        tot_wt += p[i].wt;
    }

    return 0;
}
