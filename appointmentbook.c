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
#include <string.h>

// time_t now = time(NULL);
// struct tm *t = localtime(&now);
// printf( "%d\n", t->tm_mon+1 );
// printf( "%d\n", t->tm_mday );
// printf( "%d\n", t->tm_year+1900 );
// printf( "%d\n", t->tm_hour );
// printf( "%d\n", t->tm_min );
// printf( "%d\n", t->tm_sec );

struct apptmnt
{
    char desc[50];
    int apptime_hr, apptime_min, app_day, app_mo, app_yr;
    struct apptmnt *next;
};

struct apptmnt *newapp = NULL, *start = NULL, *end = NULL;

void addAppointment()
{
    //TODO: Scanf not terminating on whitespace input
    newapp = (struct apptmnt *) malloc(sizeof(struct apptmnt));
    // printf("%d\n", newapp);
    printf("\nInput new appointment description: ");
    scanf("%s", &newapp->desc);
    printf("Appointment Date:\n");
    printf("Day (1-31): ");
    scanf("%d", &newapp->app_day);
    printf("Month (1-12): ");
    scanf("%d", &newapp->app_mo);
    printf("Year: ");
    scanf("%d", &newapp->app_yr);
    printf("\nDescription: %s Day: %d  Month: %d  Year: %d", newapp->desc, newapp->app_day, newapp->app_mo, newapp->app_yr);
    if (start == NULL)
    {
        start = end = newapp;
        printf("star == 0");
        // printf("\n%d AND %d", start, start->next);
        // newapp->next = 0;
    }
    else 
    {
        printf("else");
        end->next = newapp;
        end = end->next;
    }
}

void getAppointments(){
   
    if (start)
    {
        // printf("%d AND %d", start, start->next);
        printf("\n\nAppointments for the day:");
        struct apptmnt *thisappt = start;
        // printf("%d AND %d", app, app->next);
        while (thisappt != NULL){
            printf("\nDescription: %s Day: %d  Month: %d  Year: %d", thisappt->desc, thisappt->app_day, thisappt->app_mo, thisappt->app_yr);
            thisappt = thisappt->next;      
        }
    }
    else
    {
        printf("\nNo appointments\n");
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
    printf("5. Exit the program\n");
    while (choice != 5)
    {
        printf("\nEnter: ");
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