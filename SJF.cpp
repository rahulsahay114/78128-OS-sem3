#include <iostream>
using namespace std;

int size;
int t=0;

class process {

public:

    string name;
    int tt; //turnaround time
    int bt; //burst time
    int wt; //waiting time

};

template <class t>
void swapp(t &t1, t &t2) //t1 is the smaller item from the bubble sort comparison
{
    t temp = t1;
    t1 = t2;
    t2 = temp;
}

void sort_by_bursttime(process p[])
{
    for(int i=0; i<size-1; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if(p[j].bt > p[j+1].bt) //if previous item greater than the next one
            { //if yes, then swap.

                //sorting by burst times
                int temp = p[j+1].bt;
                p[j+1].bt = p[j].bt;
                p[j].bt = temp;

                //accordingly sorting other properties of the process as well
                //swapp<int>(p[j].at, p[j+1].at);
                swapp<int>(p[j].wt, p[j+1].wt);
                swapp<string>(p[j].name, p[j+1].name);

            }
        }
    }
}

int main() {

    cout<<"\nEnter size: ";
    cin>>size;

    /*int* at = new int[size]; //new array for holding the arrival time
    string* process = new string[size]; //array for holding each process' name
    int* bt = new int[size]; //array for holding burst times of each process.*/

    process p[size];

    for(int i=0; i<size; i++)
    {
        cout<<"\nProcess' Name: ";
        cin>>p[i].name;

        cout<<"Burst time of process (ms): ";
        cin>>p[i].bt;
    }

    sort_by_bursttime(p); //sort the input by burst time.

    float tot_wt = 0; //total waiting time
    float avg_wt = 0; //average waiting time
    float tot_tt = 0; //total turnaround time
    float avg_tt = 0; //average turnaround time

    //calculating waiting time for each process.
    p[0].wt = 0; p[0].tt = 0;

    for(int i=1; i<size; i++)
    {
        p[i].wt =0;
        p[i].wt = p[i-1].wt + p[i-1].bt;
        tot_wt += p[i].wt; //total waiting time

        p[i].tt = p[i].bt + p[i].wt;
        tot_tt += p[i].tt; //total turnaround time
    }

    //calculating average waiting and turnaround times
    avg_wt = tot_wt/size;
    avg_tt = tot_tt/size;

    //output and display
    for(int i=0; i<size; i++)
    {
        cout<<"\nName: "<<p[i].name<<"; "<<"Burst Time: "<<p[i].bt<<"; Waiting Time: "<<p[i].wt<<"; Turnaround Time: "<<p[i].tt;
    }

    cout<<"\n\nAverage Wait Time: "<<avg_wt;
    cout<<"\nAverage Turnaround Time: "<<avg_tt;

    return 0;
}
