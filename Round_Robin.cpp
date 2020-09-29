#include <iostream>
using namespace std;

float tq; //time quantum (amount of time for which a process gets the CPU in RR) aka time slice.
int size;

class process
{
public:
    string name;
    float bt=0; //burst time
    float rem_bt=0; //remaining burst time
    float wt=0; //waiting time
};

void waitingtime(process p[])
{
    float total_bt = 0;

    for(int i=0; i<size; i++)
    {
        total_bt += p[i].bt; //total time for which RR will run
    }

    //Below the increment is not 'i++' but 'i+0' as we increment 'i' according to the time for which the CPU has
    //been allotted to a process. This has been defined below.

    for(int i=0; i<total_bt; i+0) //i, in essence, is keeping track of the time.
    {
        for(int j=0; j<size; j++)
        {
            //if remaining burst-time of process is not 0 and greater than time quantum allotted
            if(p[j].rem_bt != 0 && p[j].rem_bt >= tq)
            {
                p[j].rem_bt = p[j].rem_bt - tq;
                /* Give CPU for given time-quantum/time-slice defined by the user,
                 * thus reducing the burst time by 'tq' (time-quantum).
                 * The remaining burst time (rem_bt) will keep track of these subsequent reduced burst times
                 * as CPU is periodically allotted to each process.*/

                for(int k=0; k<size; k++)
                {
                    /* Waiting time of all the other processes (k) except for the one allotted to the CPU
                     * will increase by the amount of time the CPU was allotted to the current process (j),
                     * which in this case is equal to the time-quantum defined by the user. */

                    if(k != j && p[k].rem_bt != 0)
                    {
                        /*'if' condition is making sure that
                         * 'k' only defines process at indices other than the current i.e 'j'.
                         * and simultaneously checking if the process at 'k' has any remaining burst time (rem_bt) or not,
                         * if 'rem_bt' is zero then that process is no longer waiting for CPU allocation. */

                        p[k].wt += tq; //increasing waiting time by the time for which CPU was allotted to current process.
                    }
                }

                i = i + int(tq); //using typecasting to suppress int + float warning
                //moving 'i' ahead in steps of time quantum allotted.
            }

            //if the process' remaining burst time is less than the time-quantum selected by the user.
            else if(p[j].rem_bt < tq)
            {
                i = i + int(p[j].rem_bt); //using typecasting to suppress int + float warning

                /* Moving 'i' ahead in step of the remaining burst time (rem_bt).
                 * Here the required CPU burst is less than the time-quantum, therefore
                 * CPU will only be allotted for that shorter remaining time and not the longer time-quantum.*/

                for(int k=0; k<size; k++)
                {
                    //increasing waiting time of all the other processes, except the current,
                    //by the amount of CPU burst time taken by it.
                    if(k!=j && p[k].rem_bt != 0)
                    {
                        p[k].wt += p[j].rem_bt;
                    }
                }

                p[j].rem_bt = 0; //setting remaining burst time to zero, to indicate that the process has now finished.

                /*remaining burst time (rem_bt) is only lesser than the allotted time quantum when it is nearing its end.
                This process will now end after being allotted CPU for something less than the allotted time quantum (tq)*/
            }

            //if the process has completed execution and has zero remaining burst time left.
            else if(p[j].rem_bt == 0)
            {
                continue; //skip to next process.
            }
        }
    }
}

int main() {

    cout<<"Enter Time Quantum for Round Robin Algorithm: ";
    cin>>tq;

    cout<<"\nNumber of Processes: ";
    cin>>::size;

    process p[size];

    for(int i=0; i<size; i++)
    {
        cout<<"\nProcess Name: ";
        cin>>p[i].name;

        cout<<"Burst Time: ";
        cin>>p[i].bt;
        p[i].rem_bt = p[i].bt;
    }

    waitingtime(p);

    for(int i=0; i<size; i++)
    {
        cout<<"\nName: "<<p[i].name<<"; "<<"Burst Time: "<<p[i].bt<<"; Waiting Time: "<<p[i].wt;
    }

    return 0;
}
