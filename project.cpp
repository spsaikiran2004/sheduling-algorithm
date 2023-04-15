#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
    int q;
    int rbt;
};

int n;
struct process p[10];

void getdata()
{
    int i;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the arrival time of process %d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter the burst time of process %d:",i+1);
        scanf("%d",&p[i].bt);
        printf("Enter the priority of process %d:",i+1);
        scanf("%d",&p[i].priority);
        p[i].pid=i+1;
        p[i].rbt=p[i].bt;
    }
}

void display()
{
	int i;
   printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time \n");
    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d \n",p[i].pid,p[i].at,p[i].bt,p[i].priority,p[i].ct,p[i].tat,p[i].wt);

}
}

void sort()
{
    int i,j;
    struct process temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].at>p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void roundrobin()
{
    int i,t=0,tq=3,flag=0;
    while(1)
    {
        flag=0;
        for(i=0;i<n;i++)
        {
            if(p[i].rbt==0)
            {
                continue;
            }
            if(p[i].rbt>tq)
            {
                t=t+tq;
                p[i].rbt=p[i].rbt-tq;
            }
            else
            {
                if(p[i].rbt>=0)
                {
                    t=t+p[i].rbt;
                    p[i].rbt=0;
                    p[i].ct=t;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    p[i].q=1;
                }
            }
            if(p[i].rbt>0)
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            break;
        }
    }
}

void priority()
{
    int i,j,t=0;
    struct process temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].priority>p[j+1].priority)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(p[i].q==1)
        {
            continue;
        }
        else
        {
            t=t+p[i].bt;
            p[i].ct=t;
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
            p[i].q=2;
        }
    }
}

void sjf()
{
    int i,j,t=0;
    struct process temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].bt>p[j+1].bt)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(p[i].q==1||p[i].q==2)
        {
            continue;
        }
        else
        {
            t=t+p[i].bt;
            p[i].ct=t;
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
            p[i].q=3;
        }
    }
}

int main()
{

    getdata();
    sort();
    roundrobin();
    priority();
    sjf();
    display();
    return 0;
}
