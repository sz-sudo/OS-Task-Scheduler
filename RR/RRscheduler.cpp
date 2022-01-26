#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <unistd.h>
#include <vector>
#include <ctime>


using std::vector;
using std::cout;
using std::cin;
using std::thread;
using std::string;
using std::queue;
using std::endl;

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
        this->state= State::Ready;
    }

    string getTaskName() const {return this->taskName; }
    string getTaskType() const {return this-> taskType; }
    void setTaskDuration(int x){this->taskDuration = x ; }
    int getTaskDuration() const {return this-> taskDuration; }

        string taskName;
        string taskType;
        int taskDuration;
        State state;
};


int r1, r2, r3, tasksNum;
queue <Task> ready;
vector <Task> ready0;
vector <Task> waiting;
queue <Task> temp;
bool busy[4] = {false, false, false, false};





void RR(int index){

     for (int i = 0; i < waiting.size(); i++)
    {
        
        Task t = waiting.at(i);
        if (t.getTaskType() == "X")
        {
            cout<<"X1\n";
           if (r1 > 0 && r2 > 0)
           {
                 t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if(ready.size()==0){
                    ready.push(t);
                }
                else{
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
            cout<<"Y1\n";
            if (r3 > 0 && r2 > 0)
            {
               
                  t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if(ready.size()==0){
                    ready.push(t);
                }
                else{
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
            cout<<"Z1\n";
            if (r1 > 0 && r3 > 0)
            {
                  t.state = State::Ready;
                waiting.erase(waiting.begin() + (i));
                temp.push(t);
                if(ready.size()==0){
                    ready.push(t);
                }
                else{
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

    
    if(ready.size()>0){

    Task task = ready.front();
    ready.pop();


    cout << "Task type: " << task.getTaskType() << endl;
    if (task.getTaskType() == "X")
    {
        cout<<"X2\n";
        if (r1 > 0 && r2 > 0)
        {
            
            r1--;
            r2--;
            cout<<"CPU "<<index<<" : "<<task.getTaskName()<<endl;
              task.state = State::Running;
            if(task.getTaskDuration() >=2){
            usleep(2*1000000);
            task.setTaskDuration(task.getTaskDuration() -2);
            }else{
                usleep(1000000);
                task.setTaskDuration(task.getTaskDuration() - 1);
            }
            if(task.getTaskDuration()>0){
                ready.push(task);
            }

            cout<<"duraton : " <<task.getTaskDuration()<<endl;
            r1++;
            r2++;
            busy[index] = false;
            
        }
        else 
        {
            task.state = State::Waiting;
            cout << "in cindition\n";
            waiting.push_back(task);
            busy[index] = false;
            
            return;
        }

    }
    
    else if (task.getTaskType() == "Y")
    {
            cout<<"Y2\n";
        if (r3 > 0 && r2 > 0)
        {
            
            r3--;
            r2--;
            task.state = State::Running;
            cout<<"CPU "<<index<<" : "<<task.getTaskName()<<endl;
            if(task.getTaskDuration()>=2){
            usleep(2*1000000);
            task.setTaskDuration(task.getTaskDuration()-2);
            }else{
                usleep(1000000);
                task.setTaskDuration(task.getTaskDuration() - 1);
            }
            if(task.getTaskDuration()>0){
                ready.push(task);
            }

            cout<<"duraton : " <<task.getTaskDuration()<<endl;
            r3++;
            r2++;
            busy[index] = false;
    
        }
        else 
        {
          task.state = State::Waiting;
            waiting.push_back(task);
            busy[index] = false;
   
            return;
            
        }
    }
    
    else if (task.getTaskType() == "Z")
    {
        cout<<"Z2\n";
        if (r3 > 0 && r1 > 0)
        {
            cout << "ma umadam\n";
      
            r3--;
            r1--;
             task.state = State::Running;
             cout<<"CPU "<<index<<" : "<<task.getTaskName()<<endl;
            if(task.getTaskDuration()>=2){
            usleep(2*1000000);
            task.setTaskDuration(task.getTaskDuration()-2);
            }else{
                usleep(1000000);
                task.setTaskDuration(task.getTaskDuration() - 1);
            }
            if(task.getTaskDuration()>0){
                ready.push(task);
            }

         
            cout<<"duraton : " <<task.getTaskDuration()<<endl;
            r3++;
            r1++;
            busy[index] = false;
     
        }
        else 
        {
            task.state = State::Waiting;
            waiting.push_back(task);
            busy[index] = false; 
    
            return;
        }
    }
    }
    busy[index]= false;
    return;
}



void print()
{

    for(int i=0; i<4 ; i++){
        if(busy[i]==false){
            cout<<"CPU "<<i <<" : Idle"<<endl;
        }
    }


    cout << r1 << " " << r2 << " " << r3 << endl;
    int p =  waiting.size();
    cout << "Waiting:\n";
    for (int l = 0; l < p; l++)
    {
        cout << waiting.at(l).getTaskName() <<" ";
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

int main()
{

    int counter = 0;
    cin >> r1 >> r2 >> r3 >> tasksNum;
    int source1 =r1;
    int source2 =r2;
    int source3 =r3;
    
    Task tasks[tasksNum];

    string temp1, temp2;
    int temp3;

    for (int i = 0; i < tasksNum; i++)
    {
        cin >> temp1 >> temp2 >> temp3;
        tasks[i] = Task(temp1, temp2, temp3);
        ready0.push_back(tasks[i]);
    }

    for(int i=0;i<tasksNum ;i++){
        if(ready0.at(i).getTaskType()=="Z"){
            ready.push(ready0.at(i));
        }
    }
    
    for(int i=0;i<tasksNum ;i++){
        if(ready0.at(i).getTaskType()=="Y"){
            ready.push(ready0.at(i));
        }
    }

    for(int i=0;i<tasksNum ;i++){
        if(ready0.at(i).getTaskType()=="X"){
            ready.push(ready0.at(i));
        }
    }



    thread th[5];

    print();
    
     for (int i = 0; i < 5; i++){
         if(busy[i]==false){
           th[i] = thread(RR, i);
           th[i].detach();
           busy[i] = true;
           
         }
         usleep(1*1000000);
           if(i==4){
               i=0;
           }
     
        th[4] = thread(print);
        th[4].join();
        cout<<endl;
       
        if(ready.size()==0 && waiting.size()==0){
            if(r1==source1 && r2 == source2 && r3 == source3){
                print();
                break;
            }
        }
     }
    

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


