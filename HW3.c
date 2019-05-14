#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//int pt_isFull(struct page_content pt[], int size);
bool in_array(int list[], int key);
void append_array(int list[], int key);

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
	int page;

	//create variables to store parsed data into
	int id_arr[100];
	char action_arr[100];
	int page_arr[100];
		
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
			if(!(sscanf(line, "%d %c %d", &id, &action, &page) == 3) ){
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
		printf("%d %c %d\n", id_arr[x], action_arr[x], page_arr[x]);
        }
	
	struct page_content{
		bool access;
	       	bool dirty;
		int process;
		int virtual_address; 	
	};
	
	int pt_size = 20;
	struct page_content pt_fifo[pt_size]; 
		
	for(int x = 0; x < pt_size; x++){
		pt_fifo[pt_size].access = false;
		pt_fifo[pt_size].dirty = false;
		pt_fifo[pt_size].process = -1;
		pt_fifo[pt_size].virtual_address = -1;
	}
	//int innn = pt_isFull(pt_fifo, pt_size);

	//printf("%s", innn  ? "true" : "false");

//FIFO Swap Policy - Ismael will implement
	int created_list[150];
	for(int x = 0; x < 150; x++){
		created_list[x] = -1;
	}

	/* This is to test auxilary functions
	append_array(created_list, 35);
        append_array(created_list, 45);
        append_array(created_list, 55);
        for(int x = 0; x < 150; x++){
               printf("%d",created_list[x]);
        }

	if(in_array(created_list, 35)){
		printf("Yes it is\n");
	} */

	for(int x = 0; x < i; x ++){ //Overall loop for each line entry
		if(action_arr[x] == "C"){ //Create action
			if(!in_array(created_list, pt_fifo.process)){ //If process is not in created list, add to list
				append_array(created_list, pt_fifo.process); //
			else{ //do nothing
				continue;
			}
		}
		else if(action_arr[x] == "A"){ //Allocate action
			if(in_array(created_list, pt_fifo.process)){ //if proccess has been created	
				if(!pt_isFull(pt_fifo, pt_size)){ //if there is unmodified pages in the table
					for(int q; q < pt_size; q++){
						if(pt_fifo[q].virtual_address != -1 && pt_fifo[q].process != -1){ //Allocate the memory to empty page entry
							pt_fifo[q].virtual_address = page_arr[x];
							pt_fifo[q].process = id_arr[x];
							break;
						}
					}
				}

				else{ //Do fifo swap policy

				}
			}
			else{
				//TODO: Kill 
			}
		}
		else if(action_arr[x] == "R"){
			if(in_array(created_list, pt_fifo.process)){
				//Access  bool is true
			}
			else{
				//TODO: Kill
			}
		}
		else if(action_arr[x] == "W"){
			if(in_array(created_list, pt_fifo.process)){
				//Dirty bool is true
			}
			else{
				//KILL
			}
		}
		else if (action_arr[x] == "F"){ 
			//Access bool is false
		
		}
		else{ // Terminated action
			//Clear spot in PT
			//Clear spot in Created List
		}
	}
	/*
	for(int x = 0; x < i; x++){ //Overall loop for each line entry
		if(action_arr[x] == "C" || action_arr[x] == "A" || action_arr[x] == "W"){ //If process is attempting to create
			bool pt_modified = true;
			for(int a = 0; a < pt_size; a++){ //Check if there is an umodifired page in page table exist
				if(page_table[a].dirty == false){
					pt_modified = false; //page table has an unmodified page
				}
			}
	
			for(int a = 0; a < pt_size; a++){
				if(pt_modified == false){ //if unmodified pages exist
					if(page_table[ind].dirty == false){ //look for first page that is unmodified 
					


						break;
					}	
				}
		
	*/
//Random Swap Policy - Andy will implement




//LRU Swap Policy - 3rd teammate will implement



	fclose(fp); //close file
   	return 0;
}

bool in_array(int list[], int key){
	for(int x = 0; x < 150; x++){
		if(key == list[x]){
			return true;
		}
	}
	return false;
}

void append_array(int list[], int key){
	for(int x = 0; x < 150; x++){
		if(list[x] == -1){
			list[x] = key;
			break;
		}
	}
}
/*
int pt_isFull(struct page_content pt[], int size){
	for(int x = 0; x < size; x++){
		if(pt[x].process == -1 && pt[x].virtual_address == -1){
			return 0;
		}
	}
	return 1;
}*/
