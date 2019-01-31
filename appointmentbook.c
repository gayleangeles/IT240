/************************************
 * PROGRAM:      AngelesFernandez.c *
 * DESCRIPTION:  Appointment Book   *
 * CREATED BY:   Gabrielle Angeles  *
 *               Janelle Fernandez  * 
 * DATE CREATED: 28 January 2019    *
 * DATE MODIFIED:                   *
 ************************************
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

struct apptmnt
{
    char desc[50];
    int apptime_hr, apptime_min, app_day, app_mo, app_yr;
    struct apptmnt *next;
};

struct apptmnt *newapp = NULL, *start = NULL, *end = NULL;

bool checkDate(int d, int m, int y)
{
    if (m < 1 || m > 12) {
        return false;
    }
    if (d < 1) {
        return false;
    }

    int days = 31;
    if (m == 2) {
        days = 28;
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
            days = 29;
        }
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        days = 30;
    }

    if (d > days) {
        return false;
    }

    return true;
}

bool checkTime(int hr, int min) 
{
    if (hr > 23 || hr < 0) 
        return false;

    if (min > 59 || min < 0) 
        return false;

    return true;
}

bool isPastDate(int d, int m, int y) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    struct tm setDate = { .tm_year = y - 1900, .tm_mon = m - 1, .tm_mday = d};
    struct tm pastDate = { .tm_year = tm->tm_year, .tm_mon = tm->tm_mon, .tm_mday = tm->tm_mday};

    time_t date1 = mktime(&setDate);
    time_t date2 = mktime(&pastDate);
    
    double diff = difftime(date1, date2);

    if (diff < 0)
        return false;
    
    return true;   
}

void addAppointment()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    newapp = (struct apptmnt *) malloc(sizeof(struct apptmnt));
    newapp->next = 0;
    printf("\nInput new appointment description: ");
    scanf(" %[^\t\n]s", &newapp->desc);
    printf("Appointment Date:\n");
    printf("\tDay (1-31): ");
    scanf("%d", &newapp->app_day);
    printf("\tMonth (1-12): ");
    scanf("%d", &newapp->app_mo);
    printf("\tYear: ");
    scanf("%d", &newapp->app_yr);

    if (!checkDate(newapp->app_day, newapp->app_mo, newapp->app_yr)) 
    {
        printf("Invalid Date! (%d/%d/%d) Please enter correct date.\n", newapp->app_day, newapp->app_mo, newapp->app_yr);
        free(newapp);
        return;
    }

    if (!isPastDate(newapp->app_day, newapp->app_mo, newapp->app_yr)) 
    {
        printf("Invalid Date! Date should not be before (%d-%d-%d).", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        free(newapp);
        return;
    }    

    printf("Appointment Time:\n");
    printf("\tHour (0-23): ");
    scanf("%d", &newapp->apptime_hr);
    printf("\tMinute (0-59): ");
    scanf("%d", &newapp->apptime_min);

    if (!checkTime(newapp->apptime_hr, newapp->apptime_min)) 
    {
        printf("Invalid Time! (%d:%d) Please enter correct time.\n", newapp->apptime_hr, newapp->apptime_min);
        free(newapp);
        return;
    }

    if (start <= 0)
    {        
        start = end = newapp;
    }
    else 
    {
        end->next = newapp;
        end = end->next;
    }

    printf("Appointment Added!");
}

void getAppointments(){
    int counter = 1;
    bool today = 0, tom = 0, dayafter = 0;
    if (start)
    {
        printf("\nList of Appointments:");

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        struct tm tmtomorrow = { .tm_year = tm->tm_year, .tm_mon = tm->tm_mon, .tm_mday= tm->tm_mday+1 };
        struct tm tmdayafter = { .tm_year = tm->tm_year, .tm_mon = tm->tm_mon, .tm_mday= tm->tm_mday+2 };
        mktime(&tmtomorrow);
        mktime(&tmdayafter);

        struct apptmnt *thisappt = start;

        while (thisappt != NULL)
        {
            if (thisappt->app_day == tm->tm_mday && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900 && today == 0)
            {
                today = 1;
            }
            if (thisappt->app_day == tmtomorrow.tm_mday && thisappt->app_mo == tmtomorrow.tm_mon+1 && thisappt->app_yr == tmtomorrow.tm_year+1900 && tom == 0)
            {
                tom = 1;
            }
            if (thisappt->app_day == tmdayafter.tm_mday && thisappt->app_mo == tmdayafter.tm_mon+1 && thisappt->app_yr == tmdayafter.tm_year+1900 && dayafter == 0)
            {
                dayafter = 1;
            }
            thisappt = thisappt->next;      
        }


        // PRINT APPOINTMENTS FOR TODAY      
        if (today == 1)          
        {
            printf("\n\nAppointments for the day (%d/%d/%d):", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
            thisappt = start;
            while (thisappt != NULL)
            {
                if (thisappt->app_day == tm->tm_mday && thisappt->app_mo == tm->tm_mon+1 && thisappt->app_yr == tm->tm_year+1900)
                {
                    printf("\n\t%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
                }
                thisappt = thisappt->next;      
            }
        }

        // PRINT APPOINTMENTS FOR TOMORROW
        if (tom == 1)
        {
            printf("\n\nTomorrow (%d/%d/%d):", tmtomorrow.tm_mday, tmtomorrow.tm_mon+1, tmtomorrow.tm_year+1900);
            thisappt = start;
            while (thisappt != NULL)
            {
                if (thisappt->app_day == tmtomorrow.tm_mday && thisappt->app_mo == tmtomorrow.tm_mon+1 && thisappt->app_yr == tmtomorrow.tm_year+1900)
                {
                    printf("\n\t%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
                }
                thisappt = thisappt->next;      
            }
        }

        // PRINT APPOINTMENTS FOR THE DAY AFTER TOMORROW
        if (dayafter == 1)
        {
            printf("\n\nIn 2 Days (%d/%d/%d):", tmdayafter.tm_mday, tmdayafter.tm_mon+1, tmdayafter.tm_year+1900);
            thisappt = start;
            while (thisappt != NULL)
            {
                if (thisappt->app_day == tmdayafter.tm_mday && thisappt->app_mo == tmdayafter.tm_mon+1 && thisappt->app_yr == tmdayafter.tm_year+1900)
                {
                    printf("\n\t%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
                }
                thisappt = thisappt->next;      
            }
        }
    }
    else
    {
        printf("\nNo appointments");
    }
}

void removeAppointment()
{
    int counter = 1;
    char choice;
    bool found = 0;
    
    if (start)
    {
        struct apptmnt choiceappt;
        printf("Enter date of the appointment you wish to remove: \n");
        printf("\tDay (1-31): ");
        scanf("%d", &choiceappt.app_day);
        printf("\tMonth (1-12): ");
        scanf("%d", &choiceappt.app_mo);
        printf("\tYear: ");
        scanf("%d", &choiceappt.app_yr);

        if (!checkDate(newapp->app_day, newapp->app_mo, newapp->app_yr)) 
        {
            printf("Invalid Date! (%d/%d/%d) Please enter correct date.\n", newapp->app_day, newapp->app_mo, newapp->app_yr);
            return;
        }

        printf("\n\nAppointments for (%d/%d/%d):", choiceappt.app_day, choiceappt.app_mo, choiceappt.app_yr);
        struct apptmnt *thisappt = start;
        while (thisappt != NULL)
        {
            if (thisappt->app_day == choiceappt.app_day && thisappt->app_mo == choiceappt.app_mo && thisappt->app_yr == choiceappt.app_yr)
            {
                printf("\n%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
            }
            thisappt = thisappt->next;      
        }

        printf("\n\nEnter time of appointment you wish to remove: ");
        printf("\n\tHour (0-23): ");
        scanf("%d", &choiceappt.apptime_hr);
        printf("\tMinute (0-59): ");
        scanf("%d", &choiceappt.apptime_min);

        if (!checkTime(newapp->apptime_hr, newapp->apptime_min)) 
        {
            printf("Invalid Time! (%d:%d) Please enter correct time.\n", newapp->apptime_hr, newapp->apptime_min);
            return;
        }

        struct apptmnt *prevappt = NULL;
        struct apptmnt *next = start;

        while (next != NULL)
        {
            if (next->app_day == choiceappt.app_day && next->app_mo == choiceappt.app_mo && next->app_yr == choiceappt.app_yr 
                && next->apptime_hr == choiceappt.apptime_hr && next->apptime_min == choiceappt.apptime_min)
            {
                found = 1;
                break;
            }
            prevappt = next;   
            next = next->next;       
        }

        if (found)
        {
            printf("\nAre you sure you want to remove appointment \" %s \". (Y/N): ", next->desc);
            scanf(" %c", &choice);
            if(choice == 'Y' || choice == 'y') {
                if (next == start)
                {
                    struct apptmnt *holder = start->next;     
                    free(start);               
                    start = holder;
                }
                else
                {
                    prevappt->next = next->next;
                    free(next);
                }                
                printf("\nAppointment removed.");
            } else if(choice == 'N' || choice == 'n') {
                return;
            } else 
            printf("\nInvalid input. Y / N only.");
        }
        else{
            printf("\nAppointment not found.");
        }
    }
    else
    {
        printf("\nNo Appointments.");
    }
}

void clearAppointments()
{
    int counter = 1;
    char choice;
    bool found = 0;
    
    if (start)
    {
        struct apptmnt choiceappt;
        printf("\nEnter date of the appointments you wish to clear: \n");
        printf("\tDay (1-31): ");
        scanf("%d", &choiceappt.app_day);
        printf("\tMonth (1-12): ");
        scanf("%d", &choiceappt.app_mo);
        printf("\tYear: ");
        scanf("%d", &choiceappt.app_yr);

        if (!checkDate(newapp->app_day, newapp->app_mo, newapp->app_yr)) {
            printf("Invalid Date! (%d/%d/%d) Please enter correct date.\n", newapp->app_day, newapp->app_mo, newapp->app_yr);
            return;
        }

        struct apptmnt *thisappt = start;

        while (thisappt != NULL)
        {
            if (thisappt->app_day == choiceappt.app_day && thisappt->app_mo == choiceappt.app_mo && thisappt->app_yr == choiceappt.app_yr)
            {
                found = 1;
                break;
            }
            thisappt = thisappt->next;       
        }

        if (found) 
        {
            printf("\nAppointments for (%d/%d/%d):", choiceappt.app_day, choiceappt.app_mo, choiceappt.app_yr);
            struct apptmnt *thisappt = start;
            while (thisappt != NULL)
            {
                if (thisappt->app_day == choiceappt.app_day && thisappt->app_mo == choiceappt.app_mo && thisappt->app_yr == choiceappt.app_yr)
                {
                    printf("\n\t%d. %s  (%d:%d)", counter++, thisappt->desc, thisappt->apptime_hr, thisappt->apptime_min);
                }
                thisappt = thisappt->next;      
            }

            printf("\n\nAre you sure you want to clear appointments on (%d/%d/%d). (Y/N): ", choiceappt.app_day, choiceappt.app_mo, choiceappt.app_yr);
            scanf("%s", &choice);
            
            if (choice == 'Y' || choice == 'y') 
            {
                struct apptmnt *prevappt = NULL;
                struct apptmnt *holder = NULL;
                struct apptmnt *next = start;
                
                while (next != NULL)
                {
                    if(next->app_day == choiceappt.app_day && next->app_mo == choiceappt.app_mo && next->app_yr == choiceappt.app_yr)
                    {
                        if (next == start)
                        {
                            holder = start;   
                            start = start->next;  
                            free(holder);      
                            next = start;         
                            prevappt = next;   
                        }
                        else
                        {
                            prevappt->next = next->next;
                            holder = next;   
                            next = next->next;   
                            free(holder); 
                        }                       
                    }
                    else
                    {
                        prevappt = next;   
                        next = next->next;   
                    }                   
                }
                printf("\nAppointments cleared.");
            } 
            else if(choice == 'N' || choice == 'n') 
            {
                return;
            } else 
            printf("\nInvalid input. Y / N only.");

        }
        else 
        {
            printf("\nAppointment not found.");
        }
    }
    else 
    {
        printf("\nNo Appointments.");
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
                removeAppointment();
                break;
            case 4:
                clearAppointments();
                break;
            case 5: break;
            default: 
                printf("Invalid Input");
                printf("\nPress any key to continue...");
                getch();
                break;
        }
    }
}