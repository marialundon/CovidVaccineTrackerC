/* Week 8 exam

ID : 14386816

Due Date: 16/01/2022

Module: Fundamentals of Programming

Exam Part A */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Declaring global variables and structure
typedef char String[100];

FILE *recordsFile;

int numRecords = 0;
char str1[5]= "None";

struct Record * Records;

struct Record
{
    String first_name;
    String last_name;
    String vendor;
    String vaccination_date;
    String date_of_birth;
    String underlying_condition;
    int id;
};

// Function prototypes
void load_data();
void display_menu();
void add_new_record();
void view_all_records();
void modify_record();
void sort_vaccinated_by_name();
void sort_unvaccinated_by_name();
void sort_vaccinated_by_date();
void display_percent_unvaccinated();
void display_seniors_with_condition();
void save_data();
void bubble_sort_name(struct Record Records[], int numRecords);
void bubble_sort_vaccination_date(struct Record Records[], int numRecords);
void bubble_sort_date_of_birth(struct Record Records[], int numRecords);
int age(int current_day, int current_month, int current_year, int birth_day, int birth_month, int birth_year);

//Main program - calls functions to load data and display main menu
int main()
{
    load_data();

    while (1)
        display_menu();

    return 0;
}

// Function to load data from records file and store it (creates a records file if none exists)
void load_data()
{
    struct Record record;
    int i;
    
    recordsFile = fopen("records.txt","r+");

    //Creating file if none exists and printing success/error message
    if (recordsFile == NULL)
	{
		FILE * tempFile;
		tempFile = fopen("records.txt", "w");
		fclose(tempFile);
		recordsFile = fopen("records.txt", "r+");
		if (recordsFile == NULL)
			printf("Error creating file!\n");
		else
			printf("File for records successfully created!\n");
	}

    // Counting number of records in file
    while  (!feof(recordsFile))
    {
		fscanf(recordsFile,"%s", record.first_name);
        fscanf(recordsFile,"%s", record.last_name);
		fscanf(recordsFile,"%s", record.vendor);
		fscanf(recordsFile,"%s", record.vaccination_date);
        fscanf(recordsFile,"%s", record.date_of_birth);
        fscanf(recordsFile,"%s", record.underlying_condition);
        fscanf(recordsFile,"%i", &record.id);
        numRecords++;
	}
    numRecords --;

	fseek(recordsFile,0,0); //Finding top of records file

    // Dynamically allocating memory to array of structs based on number of records in file
	Records = (struct Record *) malloc(numRecords*sizeof(struct Record));
	
    // Writing data from file to array of structs
	for (i=0; i < numRecords; i++)
	{
        fgets(Records[i].first_name, MAX_LENGTH, recordsFile);
        fgets(Records[i].last_name, MAX_LENGTH, recordsFile);
        fgets(Records[i].vendor, MAX_LENGTH, recordsFile);
        fgets(Records[i].vaccination_date, MAX_LENGTH, recordsFile);
        fgets(Records[i].date_of_birth, MAX_LENGTH, recordsFile);
        fgets(Records[i].underlying_condition, MAX_LENGTH, recordsFile);
        fscanf(recordsFile,"%i\n", &Records[i].id);
	}

    fclose(recordsFile);
}

// Function to display menu, prompt user for input and call relevant function based on input given
void display_menu()
{
    int choice, status = 0;
    char temp;
    
    printf("\nMAIN MENU\n");
    printf("1. Add a new person\n");
    printf("2. View vaccination status for all students and staff\n");
    printf("3. Modify existing record\n");
    printf("4. Sort vaccinated people by name\n");
    printf("5. Sort unvaccinated people by name\n");
    printf("6. Sort vaccinated people by date\n");
    printf("7. Display percentage of unvaccinated people\n");
    printf("8. Display a list of people with an underlying condition older than 65\n");
    printf("9. Exit\n");
    printf("\nPlease enter the number of the option you require from the above menu: ");
    status = scanf("%i", &choice);

    temp = getchar(); 
    
    // Checking for invalid characters in user input
    while (temp != '\n') 
	{
		if (temp != ' ')
		{
			status = 0;
			break;
		}

		temp = getchar();
	}

    if (status != 1) 
    {
        while ((temp=getchar()) != EOF && temp != '\n') 
        {};

        printf ("Invalid input - please enter an integer between 1 and 9\n");
    }             

    // Calling functions based on input
	else if (choice == 1)
		add_new_record();

	else if (choice == 2)
        view_all_records();

	else if (choice == 3)
		modify_record();

    else if (choice == 4)
        sort_vaccinated_by_name();
            
    else if (choice == 5)
        sort_unvaccinated_by_name();
            
    else if (choice == 6)
        sort_vaccinated_by_date();
            
    else if (choice == 7)
        display_percent_unvaccinated();
            
    else if (choice == 8)
        display_seniors_with_condition();
            
    else if (choice == 9)
    {
        save_data();
        printf("\nEnd of program - records written to data file\n");
        free(Records);
        exit(0);
    }
    
    else 
        printf("\nInvalid input - please enter an integer between 1 and 9");

	printf("\n");
}

// Function to display all records in array of structs on the screen
void view_all_records()
{
    int i;
	printf("\nLIST OF ALL RECORDS\n\n");
    
    for (i=0; i < numRecords; i++)
    {
        printf("First name: %s", Records[i].first_name);
        printf("Last name: %s", Records[i].last_name);
        printf("Vendor: %s", Records[i].vendor);
        printf("Vaccination date: %s", Records[i].vaccination_date);
        printf("Date of birth: %s", Records[i].date_of_birth);
        printf("Underlying condition: %s", Records[i].underlying_condition);
        printf("ID: %d", Records[i].id);
        printf("\n\n");
    }
}

// Function to add new record to array of structs based on user input
void add_new_record()
{
	int i;
    char c;
	struct Record * temp;
	struct Record new;

    printf("ADDING NEW RECORD\n\n");
    printf("Enter first name: ");  
    fgets(new.first_name, MAX_LENGTH, stdin);
    printf("Enter last name: ");
    fgets(new.last_name, MAX_LENGTH, stdin);
    printf("Enter vendor (Enter 'None' if no vendor): ");
    fgets(new.vendor, MAX_LENGTH, stdin);
    printf("Enter vaccination date in form dd/mm/yyyy (Enter 'None' if no vaccination date): ");
    fgets(new.vaccination_date, MAX_LENGTH, stdin);
    printf("Enter DOB in form dd/mm/yyyy: ");
    fgets(new.date_of_birth, MAX_LENGTH, stdin);
    printf("Enter underlying condition (Enter 'None' if no underlying condition): ");
    fgets(new.underlying_condition, MAX_LENGTH, stdin);
    printf("Enter id: ");
    scanf("%i", &new.id);


    numRecords++;
	temp = (struct Record *) malloc(numRecords * sizeof(struct Record));
    for (i=0; i < numRecords-1; i++)
    {
		temp[i] = Records[i];
    }
    free(Records);
	temp[numRecords - 1] = new;
	Records = temp;

    printf("\nRECORD ADDED SUCCESSFULLY");
}

// Function to modify existing record based on an ID provided by user
void modify_record()
{
	int i, id_entered, num = 0;
    char c;
	struct Record * temp;
	struct Record new;

    printf("Enter the id of record to be updated? ");
    scanf("%i", &id_entered);
    getchar();

    // Stores number of record to be updated 
    for (i=0; i < numRecords; i++)
    {
        if (Records[i].id == id_entered)
        {
            num = i+1;
        }
    }

    // Writes updated info to the record based on user input
    if (num > 0)
    {
        printf("RECORD WITH THIS ID FOUND\n\n");
        printf("MODIFYING RECORD\n\n");
        printf("Enter updated first name: ");  
        fgets(Records[num-1].first_name, MAX_LENGTH, stdin);
        printf("Enter updated last name: ");
        fgets(Records[num-1].last_name, MAX_LENGTH, stdin);
        printf("Enter updated vendor (Enter 'None' if no vendor): ");
        fgets(Records[num-1].vendor, MAX_LENGTH, stdin);
        printf("Enter updated vaccination date in form dd/mm/yyyy (Enter 'None' if no vaccination date): ");
        fgets(Records[num-1].vaccination_date, MAX_LENGTH, stdin);
        printf("Enter DOB in form dd/mm/yyyy: ");
        fgets(Records[num-1].date_of_birth, MAX_LENGTH, stdin);
        printf("Enter underlying condition(s): ");
        fgets(Records[num-1].underlying_condition, MAX_LENGTH, stdin);
    
        printf("\nRECORD MODIFIED SUCCESSFULLY\n");

    }

    else
        printf("\nNO RECORD WITH THIS ID FOUND");

}

// Function to sort vaccinated people by last name
void sort_vaccinated_by_name()
{
    int i;
    char* result;

    // Performing bubble sort on array of structs based on last name
    bubble_sort_name(Records,numRecords);

    printf("\nLIST OF VACCINATED PEOPLE SORTED BY LAST NAME:\n");

    for (i=0; i < numRecords; i++)
    {
        result = strstr(Records[i].vendor, str1); //Checking if vendor is 'None'

        if (result == NULL)
        {
            printf("\nFirst name: %sLast name: %s", Records[i].first_name, Records[i].last_name);
        }
    }

}

// Function to sort unvaccinated people by last name
void sort_unvaccinated_by_name()
{
    int i;
    char* result;

    // Performing bubble sort on array of structs based on last name
    bubble_sort_name(Records,numRecords);

    printf("\nLIST OF UNVACCINATED PEOPLE SORTED BY LAST NAME:\n");

    for (i=0; i < numRecords; i++)
    {
        result = strstr(Records[i].vendor, str1); //Checking if vendor is 'None'

        if (result != NULL)
        {
            printf("\nFirst name: %sLast name: %s", Records[i].first_name, Records[i].last_name);
        }
    }

}

// Function to sort vaccinated people by date of vaccine
void sort_vaccinated_by_date()
{
    int i;
    char* result;
    char day[3];
	char mon[3]; 
	char year[5]; 

    printf("\nLIST OF VACCINATED PEOPLE SORTED BY VACCINATION DATE (MOST TO LEAST RECENT):");

    // Changing format of date to yyyy/mm/dd
    for (i=0; i < numRecords; i++)
    {
        result = strstr(Records[i].vendor, str1); //Checking if vendor is 'None'

        if (result == NULL)
        {
            sscanf(Records[i].vaccination_date, "%2s/%2s/%4s", day, mon, year);
            sprintf(Records[i].vaccination_date, "%4s/%2s/%2s", year, mon, day);
        }
    }
    // Performing bubble sort on array of structs based on vaccination date
    bubble_sort_vaccination_date(Records,numRecords);

    for (i=0; i < numRecords; i++)

    {
        result = strstr(Records[i].vendor, str1); //Checking if vendor is 'None'

        if (result == NULL)
        {
            printf("\n\nFirst Name: %sLast name: %sVaccination date: %s", Records[i].first_name, Records[i].last_name, Records[i].vaccination_date);
            // Changing format of date to dd/mm/yyyy
            sscanf(Records[i].vaccination_date, "%4s/%2s/%2s", year, mon, day);
            sprintf(Records[i].vaccination_date, "%2s/%2s/%4s\n", day, mon, year);
        }
    
    }
}

// Function to display the percentage of people that are unvaccinated
void display_percent_unvaccinated()
{
    int i;
    float numUnvaccinatedRecords = 0;
    float percentage_unvaccinated;
    char* result;

    //Counting number of unvaccinated records
    for (i=0; i < numRecords; i++)
    {
        result = strstr(Records[i].vendor, str1); //Checking if vendor is 'None'

        if (result != NULL)
        {
            numUnvaccinatedRecords++;
        }
    }

    percentage_unvaccinated = numUnvaccinatedRecords/numRecords; //Calculation of percentage

    printf("\n%.2f percent of people are unvaccinated",  (numUnvaccinatedRecords/numRecords)*100);

}

// Function to display people aged 65 and over with any underlying condition
void display_seniors_with_condition()
{
    int i, birth_day, birth_month, birth_year, ret;
    int current_day = 16;
    int current_month = 1;
    int current_year = 2022;
    char* check;
    char day[3];
	char mon[3]; 
	char year[5]; 

    printf("\nLIST OF PEOPLE OVER THE AGE OF 65 WITH UNDERLYING CONDITIONS:\n\n");

    //Getting date in the format yyyy/mm/dd
    for (i=0; i < numRecords; i++)
    {
        sscanf(Records[i].date_of_birth, "%2s/%2s/%4s", day, mon, year);
        sprintf(Records[i].date_of_birth, "%4s/%2s/%2s", year, mon, day);
    
    }
    //Performing bubble sort on array of structs based on date of birth
    bubble_sort_date_of_birth(Records,numRecords);

    for (i=0; i < numRecords; i++)
    {
        check = strstr(Records[i].underlying_condition, str1); // Checking if underlying condition is 'None'

        // Calculating age of person by calling age function
        sscanf(Records[i].date_of_birth, "%4s/%2s/%2s", year, mon, day);
        birth_day = atoi(day);
        birth_month = atoi(mon);
        birth_year = atoi(year);
        ret = age(current_day, current_month, current_year, birth_day, birth_month, birth_year);

        // Printing record if person is 65 and over and has underlying condition
        if (check == NULL && ret > 64)
        {
            printf("First Name: %sLast name: %sDate of birth: %s\nUnderlying Condition: %s\n", Records[i].first_name, Records[i].last_name, Records[i].date_of_birth, Records[i].underlying_condition);
        }

        // Returning date of birth to format dd/mm/yyyy
        sscanf(Records[i].date_of_birth, "%4s/%2s/%2s", year, mon, day);
        sprintf(Records[i].date_of_birth, "%2s/%2s/%4s\n", day, mon, year);
    }
}

// Function to write records held in array of structs to data file
void save_data()
{
    int i;

    recordsFile = fopen("records.txt", "w");

    for (i=0; i < numRecords; i++)
    {
        fprintf(recordsFile,"First name: %s", Records[i].first_name);
        fprintf(recordsFile,"Last name: %s", Records[i].last_name);
        fprintf(recordsFile,"Vendor: %s", Records[i].vendor);
        fprintf(recordsFile,"Vaccination date: %s", Records[i].vaccination_date);
        fprintf(recordsFile,"Date of birth: %s", Records[i].date_of_birth);
        fprintf(recordsFile,"Underlying condition: %s", Records[i].underlying_condition);
        fprintf(recordsFile,"ID: %d", Records[i].id);
        fprintf(recordsFile,"\n\n");
    }

    fclose(recordsFile);

}

// Function to perform bubble sort based on last name
void bubble_sort_name(struct Record Records[], int numRecords)
{
	int i, j;
    struct Record temp;

	for (i=0; i < numRecords; i++)
    {
		for (j=i; j < numRecords; j++)

		    if (strcmp(Records[i].last_name, Records[j].last_name) > 0)
            {
                strcpy(temp.first_name, Records[i].first_name);
                strcpy(temp.last_name, Records[i].last_name);
                strcpy(temp.vendor, Records[i].vendor);
                strcpy(temp.vaccination_date, Records[i].vaccination_date);
                strcpy(temp.date_of_birth, Records[i].date_of_birth);
                strcpy(temp.underlying_condition, Records[i].underlying_condition);
                temp.id = Records[i].id;

                strcpy(Records[i].first_name, Records[j].first_name);
                strcpy(Records[i].last_name, Records[j].last_name);
                strcpy(Records[i].vendor, Records[j].vendor);
                strcpy(Records[i].vaccination_date, Records[j].vaccination_date);
                strcpy(Records[i].date_of_birth, Records[j].date_of_birth);
                strcpy(Records[i].underlying_condition, Records[j].underlying_condition);
                Records[i].id = Records[j].id;

                strcpy(Records[j].first_name, temp.first_name);
                strcpy(Records[j].last_name, temp.last_name);
                strcpy(Records[j].vendor, temp.vendor);
                strcpy(Records[j].vaccination_date, temp.vaccination_date);
                strcpy(Records[j].date_of_birth, temp.date_of_birth);
                strcpy(Records[j].underlying_condition, temp.underlying_condition);
                Records[j].id = temp.id;
        
            }   
        }      
    }

// Function to perform bubble sort based on vaccination date
void bubble_sort_vaccination_date(struct Record Records[], int numRecords)
{
	int i, j;
    struct Record temp;

	for (i=0; i < numRecords; i++)
    {
		for (j=i; j < numRecords; j++)

		    if (strcmp(Records[i].vaccination_date, Records[j].vaccination_date) < 0)
            {
                strcpy(temp.first_name, Records[i].first_name);
                strcpy(temp.last_name, Records[i].last_name);
                strcpy(temp.vendor, Records[i].vendor);
                strcpy(temp.vaccination_date, Records[i].vaccination_date);
                strcpy(temp.date_of_birth, Records[i].date_of_birth);
                strcpy(temp.underlying_condition, Records[i].underlying_condition);
                temp.id = Records[i].id;

                strcpy(Records[i].first_name, Records[j].first_name);
                strcpy(Records[i].last_name, Records[j].last_name);
                strcpy(Records[i].vendor, Records[j].vendor);
                strcpy(Records[i].vaccination_date, Records[j].vaccination_date);
                strcpy(Records[i].date_of_birth, Records[j].date_of_birth);
                strcpy(Records[i].underlying_condition, Records[j].underlying_condition);
                Records[i].id = Records[j].id;

                strcpy(Records[j].first_name, temp.first_name);
                strcpy(Records[j].last_name, temp.last_name);
                strcpy(Records[j].vendor, temp.vendor);
                strcpy(Records[j].vaccination_date, temp.vaccination_date);
                strcpy(Records[j].date_of_birth, temp.date_of_birth);
                strcpy(Records[j].underlying_condition, temp.underlying_condition);
                Records[j].id = temp.id;
        
            }   
        }      
    }

// Function to perform bubble sort based on date of birth
void bubble_sort_date_of_birth(struct Record Records[], int numRecords)
{
	int i, j;
    struct Record temp;

	for (i=0; i < numRecords; i++)
    {
		for (j=i; j < numRecords; j++)

		    if (strcmp(Records[i].date_of_birth, Records[j].date_of_birth) > 0)
            {
                strcpy(temp.first_name, Records[i].first_name);
                strcpy(temp.last_name, Records[i].last_name);
                strcpy(temp.vendor, Records[i].vendor);
                strcpy(temp.vaccination_date, Records[i].vaccination_date);
                strcpy(temp.date_of_birth, Records[i].date_of_birth);
                strcpy(temp.underlying_condition, Records[i].underlying_condition);
                temp.id = Records[i].id;

                strcpy(Records[i].first_name, Records[j].first_name);
                strcpy(Records[i].last_name, Records[j].last_name);
                strcpy(Records[i].vendor, Records[j].vendor);
                strcpy(Records[i].vaccination_date, Records[j].vaccination_date);
                strcpy(Records[i].date_of_birth, Records[j].date_of_birth);
                strcpy(Records[i].underlying_condition, Records[j].underlying_condition);
                Records[i].id = Records[j].id;

                strcpy(Records[j].first_name, temp.first_name);
                strcpy(Records[j].last_name, temp.last_name);
                strcpy(Records[j].vendor, temp.vendor);
                strcpy(Records[j].vaccination_date, temp.vaccination_date);
                strcpy(Records[j].date_of_birth, temp.date_of_birth);
                strcpy(Records[j].underlying_condition, temp.underlying_condition);
                Records[j].id = temp.id;
        
            }   
        }      
    }

// Function to return age in years based on date of birth and current date - based on logic and code found at https://www.geeksforgeeks.org/program-calculate-age
int age(int current_day, int current_month, int current_year, int birth_day, int birth_month, int birth_year)
{
    int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (birth_day > current_day) 
    {
        current_day = current_day + month[birth_month - 1];
        current_month = current_month - 1;
    }

    if (birth_month > current_month) 
    {
        current_year = current_year - 1;
        current_month = current_month + 12;
    }

    int difference_day = current_day - birth_day;
    int difference_month = current_month - birth_month;
    int difference_year = current_year - birth_year;

    return difference_year;
}
