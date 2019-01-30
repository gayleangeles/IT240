/***********************************
 *PROGRAM: appointmentbook.c
 *DESCRIPTION: Initial program...
 *CREATED BY: Gayle Angeles
 *DATE CREATED: 29 January 2019
 *DATE MODIFIED: 
 ***********************************
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct apptmnt
{
    char desc[50];
    int apptime_hr, apptime_min, app_day, app_mo, app_yr;
    struct apptmnt *next;
};

struct apptmnt *newapp = NULL, *start = NULL, *end = NULL;

void addAppointment()
{
    newapp = (struct apptmnt *) malloc(sizeof(struct apptmnt));
    printf("\nInput new appointment description: ");
    scanf("%s", &newapp->desc);
    printf("Appointment Date:\n");
    printf("Day (1-31): ");
    scanf("%d", &newapp->app_day);
    printf("Month (1-12): ");
    scanf("%d", &newapp->app_mo);
    printf("Year: ");
    scanf("%d", &newapp->app_yr);
    printf("Appointment Added!");
    printf("Appointment Time:\n");
    printf("Hour (0-23): ");
    scanf("%d", &newapp->apptime_hr);
    printf("Minute (0-59): ");
    scanf("%d", &newapp->apptime_min);
    printf("Appointment Added!");
    if (start == NULL)
    {
        start = end = newapp;
    }
    else 
    {
        end->next = newapp;
        end = end->next;
    }
}

void getAppointments(){
    int counter = 1;
    if (start)
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("\nAppointments for (%d/%d/%d):", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        struct apptmnt *thisappt = start;
        while (thisappt != NULL){
            if (thisappt->app_day == tm->tm_mday && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900)
            {
                printf("\n%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
            }
            thisappt = thisappt->next;      
        }
    }
    else
    {
        printf("\nNo appointments");
    }
}


int main()
{  
    int choice = 0;

    printf("\n\n*******************************\n");
    printf("*                             *\n");
    printf("*  MY APPOINTMENT BOOK v.1.0  *\n");
    printf("*                             *\n");
    printf("*******************************\n\n");
    printf("Menu:\n");
    printf("1. Display all appointments\n");
    printf("2. Create a new appointment\n");
    printf("3. Remove a specific appointment\n");
    printf("4. Clear all appointments for a given day\n");
    printf("5. Exit the program");
    while (choice != 5)
    {
        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1 :
                getAppointments();
                break;    
            case 2:
                addAppointment();
                break;
            case 3:
                printf("3. Remove a specific appointment\n");
                break;
            case 4:
                printf("4. Clear all appointments for a given day\n");
                break;
            case 5: break;
            default: printf("Invalid Input");
        }
    }
     printf("%c", newapp->desc);


}