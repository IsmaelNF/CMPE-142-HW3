#include <stdio.h>
#include <stdlib.h>

int main(){

	char ch, file_name[30];
   	printf("Enter name of a file:\n");
   	gets(file_name);

   	FILE *fp = fopen(file_name, "r"); // open file in read mode

   	if (fp == NULL) //throw handler in case file is empty
   	{
      		perror("Error opening the file.\n");
      		exit(EXIT_FAILURE);
   	}

	printf("The contents of %s file are:\n", file_name);

	//create variables to temporarily parse data into
	char line[2048];
	int id;
	char action;
	char page;

	//create variables to store parsed data into
	int id_arr[100];
	char action_arr[100];
	char page_arr[100];
	for(int l = 0; l < 100; l++){
		page_arr[l] = 0;
	}

	int i = 0; //counter for array
	while(fgets(line, sizeof(line), fp) != NULL) //while fgets does not fail to scan a line
	{
    		if(!(sscanf(line, "%d %c", &id, &action) == 2) ) //If sscanf failed to scan everything from the scanned line
      		{
         		printf("Bad line detected\n");
         		exit(-1);
    		}

		//Saved parsed data to arrays
		id_arr[i] = id;
		action_arr[i] = action;
		
		if(action_arr[i] != 'C' && action_arr[i] != 'T'){ 
			if(!(sscanf(line, "%d %c %c", &id, &action, &page) == 3) ){
				printf("Bad line detected\n");
	 			exit(-1);
               		 }
		}
		else{
			page = '\0';
		}
		page_arr[i] = page;

		i++;
	}

	//Below are test prints to check if file is being properly parsed
	for(int x = 0; x < i; x++){
		printf("%d %c %c\n", id_arr[x], action_arr[x], page_arr[x]);
        }
	
	fclose(fp); //close file
   	return 0;
}
