#include <iostream>
#include <iomanip>
using namespace std;


int main() {

    int size;

    cout<<"Number of processes: ";
    cin>>size;

    string* process = new string[size]; //array for holding each process' name

    int* bt = new int[size]; //array for holding burst times of each process.

    for(int i=0; i<size; i++)
    {
        cout<<"\nProcess' Name: ";
        cin>>process[i];

        cout<<"Burst time of process (ms): ";
        cin>>bt[i];

    }

    //waiting time calculations

    int *wt = new int[size];
    //waiting time array, indices should be corresponding to the process array so as to indicate
    //the correct waiting to the correct process and avoid mixing them.

    wt[0] = 0; //waiting time of the first process always zero.

    for(int i=0; i<size; i++)
    {
        wt[i+1] = wt[i] + bt[i];
    }

    //turnaround time
    int* tt = new int[size];

    for(int i=0; i<size; i++)
    {
        tt[i] = bt[i] + wt[i];
    }

    //average waiting time
    double awt=0;
    for(int i=0; i<size; i++)
    {
        awt = awt + wt[i];
    }

    awt = awt/size;

    //average turnaround
    double att=0;
    for(int i=0; i<size; i++)
    {
        att = att + tt[i];
    }

    att = att/size;

    //output
    cout<<"\n";
    cout<<"Process Name"<<setw(20)<<" Burst Time"<<setw(20)<<" Waiting Time"<<setw(30)<<" Turnaround Time"<<endl;
    cout<<"------------"<<setw(20)<<" ----------"<<setw(20)<<" ------------"<<setw(30)<<" ------------"<<endl;
    for(int i=0; i<size; i++)
    {
        cout<<process[i]<<setw(25)<<bt[i]<<setw(22)<<wt[i]<<setw(25)<<tt[i]<<endl;
    }

    cout<<"\nAverage Waiting Time: "<<awt;
    cout<<"\nAverage Turnaround Time: "<<att;

    return 0;
}
