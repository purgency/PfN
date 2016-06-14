#include "company.h"
#include <string>

using namespace std;

Task::Task()
{
    _completed = false;
}

Task::Task(const Task& task)
{
    _description = "Copy " + task.getDescription();
    _hours_required = task.getHours_required();
    _completed = task.getCompleted();
}

Task::Task(string description, unsigned int hours_required,
           bool completed = false)
{
    _description = description;
    _hours_required = hours_required;
    _completed = completed;
}

bool Task::getCompleted(void) const
{
    return _completed;
}

string Task::getDescription(void) const
{
    return _description;
}

unsigned int Task::getHours_required(void) const
{
    return _hours_required;
}

void Task::setCompleted(bool completed)
{
    _completed = completed;
}

void Task::setDescription(string description)
{
    _description = description;
}

void Task::setHours_required(unsigned int hours_required)
{
    _hours_required = hours_required;
}


Employee::Employee(void){}

Employee::Employee(string name, unsigned int hourly_wage,
         string task_desc, unsigned int hours_required, bool completed)
{
    _name = name;
    _hourly_wage = hourly_wage;
    _task = Task(task_desc, hours_required, completed);
}

unsigned int Employee::getHourly_wage(void) const
{
    return _hourly_wage;
}

string Employee::getName(void) const
{
    return _name;
}

Task &Employee::getTask(void)
{
    return _task;
}

void Employee::setHourly_wage(unsigned int hourly_wage)
{
    _hourly_wage = hourly_wage;
}

void Employee::setName(string name)
{
    _name = name;
}

void Employee::setTask(Task task)
{
    _task = task;
}


Company::Company(string name, Employee *employees, unsigned int num_employees)
{
    _name = name;
    _num_employees = num_employees;
    _employees = employees;
}

Company::Company(string name, unsigned int num_employees)
{
    _name = name;
    _num_employees = num_employees;
    _employees = new Employee[num_employees];
}

Company::Company(const Company &other)
{
    _name = other.getName();
    _num_employees = other.getNum_employees();
    _employees = other.getEmployees();
}

Company::~Company(void)
{
    delete [] _employees;
}

string Company::getName(void) const
{
    return _name;
}

void Company::setName(string name)
{
    _name = name;
}

unsigned int Company::getNum_employees(void) const
{
     return _num_employees;
}

void Company::setNum_employees(unsigned int num_employees)
{
    _num_employees = num_employees;
}

Employee* Company::getEmployees(void) const
{
    return _employees;
}

void Company::setEmployees(Employee *employees)
{
    _employees = employees;
}

unsigned int Company::totalCosts(bool future)
{
    unsigned int sum = 0;

    for(unsigned int i = 0; i < _num_employees; i++)
    {
        if(future && !_employees[i].getTask().getCompleted())
        {
            sum += _employees[i].getHourly_wage() *
            _employees[i].getTask().getHours_required();
        }
        else if(!future && _employees[i].getTask().getCompleted())
        {
            sum += _employees[i].getHourly_wage() *
            _employees[i].getTask().getHours_required();
        }
    }

    return sum;
}
