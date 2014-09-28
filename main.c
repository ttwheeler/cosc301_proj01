/*
 *
 * author name(s), date, and other info here
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"
#include <sys/resource.h>
#include <sys/time.h>

void process_data(FILE *input_file)
{
	char filestream[2000000]; 
	struct node *new_node = NULL; 
	if (input_file == stdin)
	{
	   printf("Type input: "); 
	   int number;
	   fflush(stdout);
	   while(fgets(filestream, 2000000,stdin)!= NULL)
	   { 	
	        int slen = strlen(filestream);
		filestream[slen-1] = '\0';  
 
	        if(strlen(filestream) >= 1)
	        {
		    char *token = strtok(filestream, " \t\n");
		    while(token != NULL)
		    {
		        int counter= 0; 
		        for(int i=0; i<strlen(token); i++)
    		        {
    			    if(i == 0 && (isdigit(token[i]) || token[i]=='-'))
    			    {
    			    	counter++; 
    			    }	 
    			    else if(isdigit(token[i]))
    			    {
    				counter++; 
	    		    }
       		        }
	    		if (counter == strlen(token))
	    		{
	    			number = atoi(token); 
	    			list_append(&number, &new_node); 
	    		}
                        if(token[0]=='#')
                        {
                            token=strtok(NULL,"\n");
                        }
                        else
                        {
                            token = strtok(NULL, " \t\n");
                        }
		    }
		    printf("add next item, or ctrl+d to exit: ");
		    fflush(stdout);
	        }
   	   }
	}
	else
	{
		int number; 
		while(fgets(filestream, 2000000,input_file) != NULL)
		{
			int slen = strlen(filestream);
			filestream[slen-1] = '\0';   
	
			char *token = strtok(filestream, " \t\n"); 

			while(token != NULL)
			{
			    int counter= 0; 
	        	    for(int i=0; i<strlen(token); i++)
			    {
			        if(i == 0 && (isdigit(token[i]) || token[i]=='-'))
				{
				    counter++; 
				}	 
				else if(isdigit(token[i]))
				{
				    counter++; 
				}
			    }
			    if (counter == strlen(token))
			    {
			        number = atoi(token); 
				list_append(&number, &new_node); 
			    }
                            if(token[0]=='#')
                            {
                                token=strtok(NULL,"\n");
                            }
                            else
                            {
                                token=strtok(NULL, " \t\n");
                            }
			}
		}
	}
        if(ferror input_file!=0)
        {
            printf("\nError reading file\n");
            return;
        }
	list_print(new_node);
        list_clear(new_node);
        struct rusage use;
        getrusage(RUSAGE_SELF,&use);
        printf("\nUser time: %ld.%06lds\n",use.ru_utime.tv_sec,use.ru_utime.tv_usec);
        printf("System time: %ld.%06lds\n",use.ru_stime.tv_sec,use.ru_stime.tv_usec);
}
void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
