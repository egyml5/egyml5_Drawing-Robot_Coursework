// C program to demonstrate the array within structures

#include <string.h>
#include <stdio.h>

// Defining array within structure
struct Employee {

    // character array to store name of the employee
    char Name[20];
    int employeeID;
    // integer array to maintain the record of attendanc eof
    // the employee
    int WeekAttendence[7];
};

int main()
{
    // defining structure of type Employee
    struct Employee emp;

    emp.employeeID = 1;
    strcpy(emp.Name, "Rohit");
    emp.WeekAttendence[0] = 1;
    emp.WeekAttendence[1] = 2;
    emp.WeekAttendence[2] = 3;
    emp.WeekAttendence[3] = 4;
    emp.WeekAttendence[4] = 5;
    emp.WeekAttendence[5] = 6;
    emp.WeekAttendence[6] = 7;

    printf("\n");

    // printing the data
    printf("Emplyee ID: %d - Employee Name: %s\n",
           emp.employeeID, emp.Name);
    printf("Attendence\n");
    int week;
    for (week = 0; week < 7; week++) {
        printf("%d ", emp.WeekAttendence[week]);
    }
    printf("\n");

    return 0;
}