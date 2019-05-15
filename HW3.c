#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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




//LRU Swap Policy - 3rd teammate will implement

//Random Swap Policy - Andy will implement




//FIFO Swap Policy - LRU Variable used by mistake, but it is FIFO
	struct page_content page_tableLRU[pt_size];
	struct page_content swapLRU[100];


	int createdArray[100];
	bool fullLRU = false;
	for(int k = 0; k < pt_size; k++)
	{
		page_tableLRU[k].access = false;
		page_tableLRU[k].dirty = false;
		page_tableLRU[k].process = -1;
		page_tableLRU[k].virtual_address = -1;
	}
	for(int y = 0; y < 100; y++)
	{
		swapLRU[y].access = false;
		swapLRU[y].dirty = false;
		swapLRU[y].process = -1;
		swapLRU[y].virtual_address = -1;
	}
	
	int find = 0;
	for(int k = 0; k < i; k++)
	{
		for(int pageTableIndex = 0; pageTableIndex < pt_size; pageTableIndex++)
		{
			if(page_tableLRU[pageTableIndex].process == -1)
			{
				fullLRU = false;
				break;
			}
			else
			{
				fullLRU = true;
			}
		}
		if(action_arr[k] == 'C')
		{	if(fullLRU == false){
				printf("");
			}
			else{
				for(int si = 0; si < 100; si++){
					if(swapLRU[si].process == -1){
						swapLRU[si].process = page_tableLRU[find].process;
						swapLRU[si].virtual_address = page_tableLRU[find].virtual_address;
						swapLRU[si].dirty = page_tableLRU[find].dirty;
						swapLRU[si].access = page_tableLRU[find].access;
						
						page_tableLRU[find].process = -1;
						page_tableLRU[find].virtual_address = -1;
						page_tableLRU[find].access = false;
						page_tableLRU[find].dirty = false;
						fullLRU = false;
						if(find == 19){
							find = 0;
						}
						else{
							find++;
						}
						break;
					}
				}
			}
		}
		else if(action_arr[k] == 'A' && fullLRU == false)
		{
			for(int t = 0; t < pt_size; t++)
			{
				if(page_tableLRU[t].process == -1)
				{
					page_tableLRU[t].process = id_arr[k];
					page_tableLRU[t].virtual_address = page_arr[k];
					break;
				}
			}
		}
		else if(action_arr[k] == 'T')
		{
			for(int s = 0; s < pt_size; s++)
			{
				if(page_tableLRU[s].process == id_arr[k])
				{
					page_tableLRU[s].process = -1;
				}
			}
		}
		else if(action_arr[k] == 'W')
		{
			for(int r = 0; r < pt_size; r++)
			{
				if(page_tableLRU[r].process == id_arr[k] && page_tableLRU[r].virtual_address == page_arr[k])
				{
					page_tableLRU[r].dirty = true;
				}
			}
		}
		else if(action_arr[k] == 'R')
                {
                        for(int d = 0; d < pt_size; d++)
                        {
                                if(page_tableLRU[d].process == id_arr[k] && page_tableLRU[d].virtual_address == page_arr[k])
                                {
                                        page_tableLRU[d].access = true;
                                }
                        }
                }

	}
	for(int m = 0; m < pt_size; m++)
	{
		if(page_tableLRU[m].process != -1){
			printf("\nProcess: %d\n", page_tableLRU[m].process);
			printf("Virtual: %d\t Physical: %d\n", page_tableLRU[m].virtual_address, m);
		}
		//printf("%d ", page_tableLRU[m].process);
	}
	printf("\nFIFO Swap:\n");
	for(int m = 0; m < 100; m++){
		 if(swapLRU[m].process != -1){
                        printf("Process: %d\t Virtual: %d\n", swapLRU[m].process, swapLRU[m].virtual_address);
                }
	}
	
	printf("\nPHYSICAL:\n");
	for(int m = 0; m <pt_size; m++){
		if(page_tableLRU[m].process != -1){
			printf("%d\tProcess %d\n", m, page_tableLRU[m].process);
		}
		else{
			printf("%d\tFree\n", m);
		}
	}

	/*
        printf("\n");
        for(int m = 0; m < pt_size; m++)
        {
                printf("%d ", page_tableLRU[m].virtual_address);
        }
        printf("\n");
        for(int m = 0; m < pt_size; m++)
        {
                printf("%d ", page_tableLRU[m].dirty);
        }
        */

	fclose(fp); //close file
   	return 0;
}
