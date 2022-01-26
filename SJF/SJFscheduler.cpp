#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <unistd.h>
#include <vector>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::thread;
using std::vector;

void print();
void SJF(int index);
enum State
    {
        Ready,
        Waiting,
        Running
    };

class Task
{
public:
    Task()
    {
    
    }
    Task(string taskName, string taskType, int taskDuration)
    {
        this->taskName = taskName;
        this->taskType = taskType;
        this->taskDuration = taskDuration;
        this->state = State::Ready;
        
    }

    string getTaskName() const { return this->taskName; }
    string getTaskType() const { return this->taskType; }
    int getTaskDuration() const { return this->taskDuration; }

    string taskName;
    string taskType;
    int taskDuration;
    State state ;

};

int r1, r2, r3, tasksNum;
queue<Task> ready;
vector<Task> waiting;
queue<Task> temp;
bool busy[4] = {false, false, false, false};
vector<Task> shortest;

void bubbleSort(Task tasks[], int tasksNum)
{
    bool swapped;
    for (int i = 0; i < tasksNum - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < tasksNum - i - 1; j++)
        {
            if (tasks[j].getTaskDuration() > tasks[j + 1].getTaskDuration())
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
    }
}



int main()
{

    int counter = 0;
    cin >> r1 >> r2 >> r3 >> tasksNum;
    int source1 = r1;
    int source2 = r2;
    int source3 = r3;

    Task tasks[tasksNum];

    string temp1, temp2;
    int temp3;

    for (int i = 0; i < tasksNum; i++)
    {
        cin >> temp1 >> temp2 >> temp3;
        tasks[i] = Task(temp1, temp2, temp3);
        //ready.push(tasks[i]);
    }
       cout<<tasks[0].state<<endl;

    bubbleSort(tasks, tasksNum);

    for (int i = 0; i < tasksNum; i++)
        ready.push(tasks[i]);

    thread th[5];

    print();

    for (int i = 0; i < 5; i++)
    {
        if(busy[i]==false){
        th[i] = thread(SJF, i);
        th[i].detach();
        busy[i] = true;
        
        }
        usleep(1 * 1000000);
        if (i == 4)
        {
            i = 0;
        }

        th[4] = thread(print);
        th[4].join();
        cout << endl;

        if (ready.size() == 0 && waiting.size() == 0)
        {
            if (r1 == source1 && r2 == source2 && r3 == source3)
            {
                print();
                break;
            }
        }
    }
}

void SJF(int index)
{
    for (int i = 0; i < waiting.size(); i++)
    {

        Task t = waiting.at(i);
        if (t.getTaskType() == "X")
        {
            cout << "X1\n";
            if (r1 > 0 && r2 > 0)
            {
                t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if (ready.size() == 0)
                {
                    ready.push(t);
                }
                else
                {
                    int size = ready.size();
                    for (int j = 0; j < size; j++)
                    {
                        temp.push(ready.front());
                        ready.pop();
                    }

                    size = temp.size();
                    for (int j = 0; j < size; j++)
                    {
                        ready.push(temp.front());
                        temp.pop();
                    }
                }
            }
        }
        else if (t.getTaskType() == "Y")
        {
            cout << "Y1\n";
            if (r3 > 0 && r2 > 0)
            {
                t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if (ready.size() == 0)
                {
                    ready.push(t);
                }
                else
                {
                    int size = ready.size();
                    for (int j = 0; j < size; j++)
                    {
                        temp.push(ready.front());
                        ready.pop();
                    }

                    size = temp.size();
                    for (int j = 0; j < size; j++)
                    {
                        ready.push(temp.front());
                        temp.pop();
                    }
                }
            }
        }
        else if (t.getTaskType() == "Z")
        {
            cout << "Z1\n";
            if (r1 > 0 && r3 > 0)
            {
                t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if (ready.size() == 0)
                {
                    ready.push(t);
                }
                else
                {
                    int size = ready.size();
                    for (int j = 0; j < size; j++)
                    {
                        temp.push(ready.front());
                        ready.pop();
                    }

                    size = temp.size();
                    for (int j = 0; j < size; j++)
                    {
                        ready.push(temp.front());
                        temp.pop();
                    }
                }
            }
        }
    }

    if (ready.size() > 0)
    {
        Task temp = ready.front();
        shortest.push_back(temp);
        ready.pop();

        if (ready.size() > 0)
        {
            while (ready.front().getTaskDuration() == temp.getTaskDuration())
            {
                shortest.push_back(ready.front());
                ready.pop();
            }
        }

        for (int i = 0; i < shortest.size(); i++)
        {
            for (int j = 0; j < shortest.size(); j++)
            {
                if (shortest.at(j).getTaskType() == "Z")
                {
                    cout << "Z\n";
                    Task t = shortest.at(j);
                    shortest.erase(shortest.begin() + j);
                    if (r1 > 0 && r3 > 0)
                    {
                        cout << "Z2\n";
                        r1--;
                        r3--;
                        cout<<"duraton : " <<t.getTaskDuration()<<endl;
                        t.state = State::Running;
                        usleep(t.getTaskDuration() * 1000000);
                        r1++;
                        r3++;
                        busy[index] = false;
                    }
                    else
                    {
                         t.state = State::Waiting;
                        waiting.push_back(t);
                        busy[index] = false;
                        return;
                    }
                }
            }

            for (int j = 0; j < shortest.size(); j++)
            {
                if (shortest.at(j).getTaskType() == "Y")
                {
                    cout << "Y\n";
                    Task t = shortest.at(j);
                    shortest.erase(shortest.begin() + j);
                    if (r2 > 0 && r3 > 0)
                    {
                        cout << "Y2\n";
                        r2--;
                        r3--;
                        cout<<"duraton : " <<t.getTaskDuration()<<endl;
                        t.state = State::Running;

                        usleep(t.getTaskDuration() * 1000000);
                        r2++;
                        r3++;
                        busy[index] = false;
                    }
                    else
                    {
                          t.state = State::Waiting;
                        waiting.push_back(t);
                        busy[index] = false;
                        return;
                    }
                }
            }

            for (int j = 0; j < shortest.size(); j++)
            {
                if (shortest.at(j).getTaskType() == "X")
                {
                    cout << "X\n";
                    Task t = shortest.at(j);
                    shortest.erase(shortest.begin() + j);
                    if (r1 > 0 && r2 > 0)
                    {
                        cout << "X2\n";
                        r1--;
                        r2--;
                        cout<<"duraton : " <<t.getTaskDuration()<<endl;
                        t.state = State::Running;

                        usleep(t.getTaskDuration() * 1000000);
                        r1++;
                        r2++;
                        busy[index] = false;
                    }
                    else
                    {
                        t.state = State::Waiting;
                        waiting.push_back(t);
                        busy[index] = false;
                        return;
                    }
                }
            }
        }
    }
}


void print()
{

    for(int i=0; i<4 ; i++){
        if(busy[i]==false){
            cout<<"CPU "<<i <<" : Idle"<<endl;
        }
    }

    cout << r1 << " " << r2 << " " << r3 << endl;
    int p = waiting.size();
    cout << "Waiting:\n";
    for (int l = 0; l < p; l++)
    {
        cout << waiting.at(l).getTaskName() << " ";
    }
    cout << endl;

    p = ready.size();
    cout << "Ready:\n";
    for (int l = 0; l < p; l++)
    {
        Task t = ready.front();
        cout << t.getTaskName() << " ";
        ready.pop();
        ready.push(t);
    }
    cout << endl;

    return;
}

/*
2                                  
2
2
4
T1 Y 3
T2 X 6
T3 X 5
T4 Z 1
*/