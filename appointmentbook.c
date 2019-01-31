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
#include <conio.h>

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
    printf("\tDay (1-31): ");
    scanf("%d", &newapp->app_day);
    printf("\tMonth (1-12): ");
    scanf("%d", &newapp->app_mo);
    printf("\tYear: ");
    scanf("%d", &newapp->app_yr);
    printf("Appointment Time:\n");
    printf("\tHour (0-23): ");
    scanf("%d", &newapp->apptime_hr);
    printf("\tMinute (0-59): ");
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
        printf("\n\nAppointments for the day (%d/%d/%d):", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        struct apptmnt *thisappt = start;
        while (thisappt != NULL){
            if (thisappt->app_day == tm->tm_mday && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900)
            {
                printf("\n%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
            }
            thisappt = thisappt->next;      
        }

        printf("\n\nTomorrow (%d/%d/%d):", tm->tm_mday+1, tm->tm_mon+1, tm->tm_year+1900);
        thisappt = start;
        while (thisappt != NULL){
            if (thisappt->app_day == tm->tm_mday+1 && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900)
            {
                printf("\n%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
            }
            thisappt = thisappt->next;      
        }

        printf("\n\nIn 2 Days (%d/%d/%d):", tm->tm_mday+2, tm->tm_mon+1, tm->tm_year+1900);
        thisappt = start;
        while (thisappt != NULL){
            if (thisappt->app_day == tm->tm_mday+2 && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900)
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

void deleteAppointment(int hr, int min)
{
    typedef struct apptmnt *thisappt;
    thisappt appt = start, end;

    if (appt != NULL
        && appt->apptime_hr == hr
        && appt->apptime_min == min)
    {
        start = appt->next;
        free(appt);
        return;
    }

    while (appt != NULL
        && appt->apptime_hr != hr
        && appt->apptime_min != min)
    {
        end = appt;
        appt = appt->next;
    }

    if (appt == NULL) return;

    end->next = appt->next;

    free(appt);
}

void removeAppointments()
{
    int counter = 1;
    char choice;
    if (start)
    {

        struct apptmnt *choiceappt = start;
        printf("Enter date of the appointment you wish to remove: \n");
        printf("\tDay (1-31): ");
        scanf("%d", &choiceappt->app_day);
        printf("\tMonth (1-12): ");
        scanf("%d", &choiceappt->app_mo);
        printf("\tYear: ");
        scanf("%d", &choiceappt->app_yr);

        printf("\n\nAppointments for (%d/%d/%d):", choiceappt->app_day, choiceappt->app_mo, choiceappt->app_yr);
        struct apptmnt *thisappt = start;
        while (thisappt != NULL){
            if (thisappt->app_day == choiceappt->app_day && thisappt->app_mo == choiceappt->app_mo && thisappt->app_yr == choiceappt->app_yr)
            {
                printf("\n%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
            }
            thisappt = thisappt->next;      
        }

        printf("\n\nEnter time of appointment you wish to remove: ");
        printf("\n\tHour (0-23): ");
        scanf("%d", &choiceappt->apptime_hr);
        printf("\tMinute (0-59): ");
        scanf("%d", &choiceappt->apptime_min);

        while (thisappt != NULL){
            if (thisappt->app_day == choiceappt->app_day && thisappt->app_mo == choiceappt->app_mo && thisappt->app_yr == choiceappt->app_yr 
                && thisappt->apptime_hr == choiceappt->apptime_hr && thisappt->apptime_min == choiceappt->apptime_min)
            {
                printf("\nAre you sure you want to remove appointment \" %s \". (Y/N): ", thisappt->desc);
                scanf("%s", choice);
            }
            thisappt = thisappt->next;      
        }

        if(choice == 'Y' || choice == 'y') {
            deleteAppointment(thisappt->apptime_hr, thisappt->apptime_min);
            printf("\n\nAppointment removed.");
        } else if(choice == 'N' || choice == 'n') {
            //return to menu??
        } else 
        printf("Invalid input. Y / N only.");
    }
    else
    {
        printf("\nAppointment not found.");
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
                removeAppointments();
                break;
            case 4:
                printf("4. Clear all appointments for a given day\n");
                break;
            case 5: break;
            default: 
                printf("Invalid Input");
                printf("\nPress any key to continue...");
                getch();
                break;
        }
    }
     printf("%c", newapp->desc);


}