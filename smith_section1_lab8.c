// Eighth Program: Phonebook 3
// TaiJon Smith
// 03/08/16
// Section 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data structure for the Phonebook User Entries
typedef struct phoneBookOptions {
	char firstName[20]; //expecting max 20 characters from user
	char lastName[20];
	char phoneNumber[20];		
	} record;

//function prototypes
record *addContact(record *contacts, int *total);
record *deleteContact(record *contacts, int *total);
void findRecord(record *contacts, int *total);
int callRandom(record *contacts, int *total);
void sortAlpha(record *contacts, int *total);
int deleteAll(record *contacts, int *total);
void printBook(record *contacts, int total);
void saveBook(record *contacts, int *total);
void loadBook(record *contacts, int *total);
int exitBook();

int main() {
	record *contacts; //pointer for data structure
	contacts = (record *) malloc(sizeof(record)); //allocates bytes of memory based on size of data stucture
	if (contacts == NULL) //memory check
		printf("(Out of Memory)\n\n");
	else
		printf("(Memory Allocation Successful)\n\n");
	
	int menuOption = 0; //for menu options (switch statements)
	int total = 0; //Number of contacts/entries
	srand(time(NULL)); //random number function
	
do {	
	printf("PhoneBook Program\n\n1) Add Contact\n2) Delete Contact\n3) Find Phone Number\n4) Random Call\n5) "
	"Sort Alphabetically (First Name)\n6) Delete All Contacts\n7) Show Phonebook\n8) Save\n9) Load\n0) Exit");
	printf("\n\nPlease select an option: ");
	scanf("%d", &menuOption);
	
	switch(menuOption) {
		case 1: //adds a contact
			contacts = addContact(contacts, &total);
			break;
			
		case 2: //deletes a contact
			contacts = deleteContact(contacts, &total);
			break;
			
		case 3: //search for a specific person's number
			findRecord(contacts, &total);
			break;
			
		case 4: //call a random contact
    		callRandom(contacts, &total);
    		break;
    		
    	case 5: //Sorts contacts in alphabetical order (Note: Will see alphabetical order once user selects menu option 7)
    		sortAlpha(contacts, &total);
    		break;
    		
    	case 6: //deletes all contacts in phonebook
    		deleteAll(contacts, &total);
    		break;
			
		case 7: //see all entries in Phonebook
			printBook(contacts, total);
			break;
			
		case 8: //save Phonebook
			saveBook(contacts, &total);
			break;
			
		case 9: //load Phonebook  
			loadBook(contacts, &total);
			break; 
			    
		case 0: //exit application
			free(contacts); //frees all assigned memory
			exitBook();
			break;
	
		default: //default error option in case user doesn't enter valid number for menu option
			printf("\nThat is not a valid option. Please select a valid operation from the options\nbelow.\n\n");
			break;
	}
	
} while(menuOption!=0); //loops until user selects exit option

return(0);
}

//adds contact
record *addContact(record *contacts, int* total) {
	record *tmp = realloc(contacts, ((*total)+1)*sizeof(record)); //tmp = temporary pointer for memory
	contacts = tmp;
	if(tmp == NULL) {
		printf("Out Of Memory\n");
		return(contacts);
	}
	
	printf("\nPlease enter the first name of your new contact: ");
	scanf("%s", contacts[(*total)].firstName);
	printf("\nPlease enter the last name of your new contact: ");
	scanf("%s", contacts[(*total)].lastName);
	printf("\nPlease enter the phone number of your new contact: ");
	scanf("%s", contacts[(*total)].phoneNumber);
	printf("\n%s %s has been added to your contacts. \n\n", contacts[(*total)].firstName, contacts[(*total)].lastName);
	(*total) = (*total) + 1; //increments total entries
	return(contacts);
}

//deletes contact
record *deleteContact(record *contacts, int* total) {
	char firstEntry[20]; //array reserved for the first name of entry that user wants to delete
	char lastEntry[20];
	
	if((*total)==0) { //no entries available
		printf("\nThere are no contacts available to delete.\n\n");
	}
	else {
		printf("\nSelect who you want to delete from your contacts\n\n");
		printf("Enter the first name of the person you would like to delete: ");
		scanf("%s", firstEntry);
		printf("\nEnter the last name of the person you would like to delete: ");
		scanf("%s", lastEntry);
		int x;
		int y;
		for(x=0; x < *total; x++) {
			if(strcmp(contacts[x].firstName, firstEntry)==0) {
				if(strcmp(contacts[x].lastName, lastEntry)==0) {  //if statement for if first and last name is founded
					for(y = x; y < *total; y++) {
            		strcpy(contacts[y].firstName, contacts[y+1].firstName);
            		strcpy(contacts[y].lastName, contacts[y+1].lastName);
            		strcpy(contacts[y].phoneNumber, contacts[y+1].phoneNumber);
				}
            	printf("\nContact Deleted!\n\n");
        		(*total)--; //decrements total of entries once
        		contacts = (record*)realloc(contacts, (*total)*sizeof(record)); //reallocates memory b/c of deleted contact
        		return(contacts);
				}
			}
		}
		printf("\nContact Not Found!\n\n");
		return(contacts);
	}
}

//search for contact
void findRecord(record *contacts, int* total) {
	char entryFirst[20]; //array for the first name of contact that user wants to search for
	char entryLast[20];
	int x;
	if((*total)==0) { //no entries available
		printf("\nThere are no contacts available to find.\n\n");
	}
	else {
		printf("\nEnter the first name of the person you would like to search for: ");
		scanf("%s", entryFirst);
		printf("\nEnter the last name of the person you would like to search for: ");
		scanf("%s", entryLast);
    	for(x = 0; x < *total; x++) {
			if(strcmp(contacts[x].firstName, entryFirst)==0) { //If statement used for searching the first name of the contact
    			if(strcmp(contacts[x].lastName, entryLast)==0) { //If statement used for searching the last name of the contact	
					printf("\n%s %s's number is (%s)\n\n", contacts[x].firstName, contacts[x].lastName, contacts[x].phoneNumber);//Prints out name & number
    				return;
				}
			}
		}
	printf("\nContact Not Found!\n\n");
	return;	
	}
}

//call a random contact
int callRandom(record *contacts, int *total) {
	if(*total==0) {
	printf("\nThere are no contacts available to call.\n\n"); //no contacts available	
	}
	else {
	int random = (rand() % (*total)); //random contact selected within entries to call
	printf("Calling %s %s (%s)... \n\n", contacts[random].firstName, contacts[random].lastName, contacts[random].phoneNumber);
	return;
	}
}

//sort contacts in Phonebook in alphabetical order
void sortAlpha(record *contacts, int *total) {
	int x, swap = 1;
    record sort; //data type is in data structure, "sort" is variable that represents contacts in Phonebook
    if(*total==0) {
		printf("\nThere are no contacts available to sort alphabetically.\n\n");	
	}
	else {
    while((0 < (*total)-1) && (swap==1)) { //allows the contacts to be placed in alphabetical order
    	swap = 0;
		for(x = 0; x < (*total-1); x++) { 
	    	if(strcmp(contacts[x].firstName, contacts[x+1].firstName) > 0 ) {  //for searching through the contact list 
	    	sort = contacts[x+1];
	    	contacts[x+1] = contacts[x];
	    	contacts[x] = sort;
	    	swap = 1;
			}
		//if contacts have same first name, but different last names
	    else if(strcmp(contacts[x].firstName, contacts[x+1].firstName)==0 && strcmp(contacts[x].lastName, contacts[x +1].lastName) > 0) {
	    	sort = contacts[x+1];
	    	contacts[x+1] = contacts[x];
	    	contacts[x] = sort;
	    	swap = 1;
		}
		}
	}
	printf("\nPhonebook sorted alphabetically!\n\n");
	}
}

//delete whole Phonebook
int deleteAll(record *contacts, int *total) {
	int x; //variable for conditional iteration
	if(*total==0) {
		printf("\nThere are no contacts available to delete.\n\n");	
	}
	else {
    	for(x = 0; x < *total; x++) {                 
			strcpy(contacts[x].firstName, "\0");
        	strcpy(contacts[x].lastName, "\0");
        	strcpy(contacts[x].phoneNumber, "\0");
			}
    	*total = 0; //no more entries
    	contacts = (record*)realloc((contacts), sizeof(record)); //frees up memory
    	printf("\nPhonebook Deleted\n\n");
	}
	return(0);
}

//see all contacts
void printBook (record *contacts, int total) {
	if(total==0) {
		printf("\nThere are no contacts to show.\n\n"); //no entries in phonebook
	}
	else {
		int x = 0;
		printf("\nPhonebook Contact Page: \n\n");
		for (x = 0; x < total; x++) {
  			printf("%s %s \n%s \n\n", contacts[x].firstName, contacts[x].lastName, contacts[x].phoneNumber); //print available entries
		}
	}
}

//save Phonebook
void saveBook(record *contacts, int *total) {
	FILE *write;    //File pointer used to save the phonebook
	char file[50]; //array variable used to save the phonebook
	int x;	
	if(*total == 0) {
		printf("No contacts are in Phonebook to save!\n"); //no contacts are in saved phonebook to save
		return;
	}
	
	printf("\nPlease name the file you want to save: "); //file name for phonebook
	scanf("%s", file);
	write = fopen(file, "w"); //open file for writing
	if(write == NULL) { //If statement to make sure the input is a file 
		printf("\nUnable to Save File!\n\n");
	}
	else {
		for(x = 0; x < *total; x++) {
			fprintf(write,"%s %s %s\n", contacts[x].firstName, contacts[x].lastName, contacts[x].phoneNumber); //saving data in phonebook
		}
	printf("\nFile Saved!\n\n");
	}
	fclose(write); //end
}

//load saved Phonebook	
void loadBook(record *contacts, int *total) {
	FILE *read; //File pointer used to load the phonebook
	char file[50];  //array variable used to load the saved phonebook
	printf("\nPlease enter the name of the file you want to open: ");
	scanf("%s", file);  //scanf to look for the saved file
	read = fopen(file, "r");
	if(read == NULL) {  //file isnt found
		printf("\nFile was not found!\n\n");
		return;
	}
	else {
		while(!feof(read)) {   //process of loading saved contacts
			(*total) = (*total) + 1;
			contacts = (record*)realloc(contacts, ((*total))*sizeof(record)); //allocates memory for loaded data
			fscanf(read,"%s %s %s\n", contacts[(*total)-1].firstName, contacts[(*total)-1].lastName, contacts[(*total)-1].phoneNumber);
		}
		printf("\nFile Opened!\n\n");
	}
	fclose(read); //end
}

//exits program
int exitBook () {
	printf("\nExiting...");
	exit(0); //standard exit function	
}
