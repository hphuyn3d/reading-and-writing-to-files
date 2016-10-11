/**
 * Hung Huynh
 * 3/29/16
 * ASSIGNMENT 4
 * Program which reads from two files: person.txt and dob.txt.
 * There are two structs: a Person struct and a Date_of_Birth struct.
 * It will then populate these structs with values from the file and add
 * them into an array. It will then, sort the array according to the
 * name field using bubble sort. Once the array has been sorted, it will
 * write it out to an output file called output.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*----------------------------------------------------------------------*/
// structure for date of birth
typedef struct {
	int day;
	int month;
	int year;
} DATE;

/*----------------------------------------------------------------------*/
// structure for person
typedef struct {
	char *last_name;
	DATE *dob;
	int ssn;
	char *street_address;
	char *city;
	int age;
} PERSON;

/*----------------------------------------------------------------------*/
//stores array of records from dob.txt and person.txt
PERSON *person;
//number of lines in a file
int c = 0; // keeps a count

/*----------------------------------------------------------------------*/
//function prototypes
void sort();
void loadFile(FILE*, FILE*);
void printToFile();
void freeMemory();
void numberOfLine(FILE*, FILE*);

/*----------------------------------------------------------------------*/
int main(){

	FILE *fptr1, *fptr2;
	// opens file for reading
	fptr1 = fopen("person.txt","r");
	fptr2 = fopen("dob.txt", "r");

	// calling the functions
	numberOfLine(fptr1, fptr2);
	loadFile(fptr1, fptr2);
	sort();
	printToFile();

	// frees the allocated memory
	freeMemory();

	// closes the files 
	fclose(fptr1);
	fclose(fptr2);

	return 0;
}

/*----------------------------------------------------------------------*/
//Function that loads the data
void loadFile(FILE *fptr1, FILE *fptr2){

	char str[2000];
	char *token;
	int i;
	//creating person array
	person = (PERSON*) malloc((c)*sizeof(PERSON));

	for(i = 0; i < c; i++) {
		//populating structs
		person[i].last_name = (char*) malloc(100);
		person[i].street_address = (char*)malloc(100);
		person[i].city = (char*)malloc(100);
		person[i].dob = (DATE*) malloc(100);


		fgets(str, sizeof(str), fptr1);

		token = strtok(str,",");			
		strcpy(person[i].last_name,token);

		token = strtok(NULL, ",");
		person[i].ssn = atoi(token);

		token = strtok(NULL, ",");
		strcpy(person[i].street_address,token);


		token = strtok(NULL, ",");
		strcpy(person[i].city,token);

		token = strtok(NULL,"\n");
		person[i].age = atoi(token);


		fgets(str, sizeof(str), fptr2);			

		token = strtok(str,",");
		person[i].dob->month = atoi(token);

		token = strtok(NULL,",");
		person[i].dob->day = atoi(token);

		token = strtok(NULL,"\n");
		person[i].dob->year = atoi(token);
	}
}

/*---------------------------------------------------------------------*/
// Function that uses bubble sort algorithm to sort data by last name. 
void sort(){
	int j = 0;
	PERSON temp;

	for (int i = 0; i < c; i++) {
		for (j = (i + 1); j < c; j++) {
			if (strcmp(person[i].last_name,person[j].last_name) > 0) {
				temp = person[i];
				person[i] = person[j];
				person[j] = temp;
			}
		}
	}
}


/*---------------------------------------------------------------------*/
// Function for printing data into output.txt file
void printToFile(){

	int i;
	//creates a file called "output.txt"
	FILE *fptr = fopen("output.txt", "w");

	for (i = 0; i < c; i++) {
		fprintf(fptr,"\n %s      %d %s    %s %d\n", 
				person[i].last_name, person[i].ssn, person[i].street_address, person[i].city, person[i].age);

		fprintf(fptr,"Date of Birth: %d/%d/%d \n", person[i].dob->month, person[i].dob->day, person[i].dob->year);
	}
	//closes file
	fclose(fptr);
}

/*---------------------------------------------------------------------*/
// Function for freeing the memory
void freeMemory(){
	free(person->last_name);
	free(person->street_address);
	free(person->city);
	free(person->dob);
	free(person);
}
/*---------------------------------------------------------------------*/
//Function for checking the number of lines in a file
void numberOfLine(FILE *fptr1, FILE *fptr2){
	char ch;
	// Checks to see if the file was opened or not.
	if(fptr1 == NULL || fptr2 == NULL) {
		puts("File did not open! \n");
	} else {
		while (!feof(fptr1)) {
			ch = fgetc(fptr1);
			if(ch == '\n') 
				c++;
		}
		rewind(fptr1); // sets file position to the beginning of the file
	}
}










