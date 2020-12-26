// Basil El-Hindi
// CS 4348.HON
// 9/10/2020
// Project 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	// Hold values to error check for successful forking
   pid_t child1, child2;

	// Hold values for file descriptors after creating pipes
	int oneToTwo[2];
	int twoToOne[2]; 
   
	// File pointer for result of popen for ls command
	FILE *fp;
	// File pointer to open file for reading or writing
	FILE *openfile;
	// Values for reading results of popen and file contents
	ssize_t input;
	char *line = NULL;
	size_t len = 0;
	// Buffers to hold I/O for pipes
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];

	// Value to error check for successful reads and writes
	int check;
	// Value to toggle between creating a file and writing to its contents
	int toggle = 0;

	// Values to error check for successful piping
	int pipe1 = pipe(oneToTwo);
	int pipe2 = pipe(twoToOne);

	// Ensure both pipes were successfully created
	if(pipe1 < 0)
	{
		perror("Pipe 1 failed to create\n");
		exit(1);
	}
	if(pipe2 < 0)
	{
		perror("Pipe 2 failed to create\n");
		exit(1);
	}

	// Spawn first child process from parent and error check
   child1 = fork();
   if(child1 < 0)
   {
      perror("Error creating child1\n");
  		exit(1);
   }
	// Child 1
   else if(child1 == 0)
   {
		// Close file descriptors that child 1 will not use.
		// Will write to child 2 and read from child 2
		if(close(oneToTwo[0]) < 0 || close(twoToOne[1]) < 0)
		{
			perror("Failed to close pipe ends\n");
			exit(1);
		}
		// Change directory to dir 1 and ensure it was successful
		if(chdir("./dir1") < 0)
		{
			perror("Failed to change directory\n");
			exit(1);
		}

		// Use popen to run ls command sorted by file size and ensure success
		fp = popen("/bin/ls -Sr /home/osc/Project1/dir1", "r");
		if(fp == NULL)
		{
			perror("Failed to run command\n");
			exit(1);
		}
		// Sleep to synchronize and ensure both children have run ls
		sleep(1);
		// Read each line of the ls result
		while(input = getline(&line, &len, fp) != -1)
		{
			// Remove newline character from end of each file entry
			memmove(&line[strlen(line)-1], &line[strlen(line)], 1);
			if(line == NULL)
			{
				perror("Failed to write file name\n");
				exit(1);
			}
			// Write to child 2
			check = write(oneToTwo[1], line, strlen(line) + 1);
			if(check < 0)
			{
				perror("Error writing to pipe 1\n");
				exit(1);
			}
			// Let child 2 read and create the file before providing contents
			sleep(2);

			// Open the file for reading
			openfile = fopen(line, "rb");
			if(openfile == NULL)
			{
				perror("Failed to open file for reading\n");
				exit(1);
			}
			// Read file content one character at a time until end of file reached
			unsigned count = 0;
			while(!feof(openfile) && count < BUFFER_SIZE)
			{
				buffer1[count++] = fgetc(openfile);
			}
			if(feof(openfile))
			{
				buffer1[--count] = 0;
			}
			else
			{
				buffer1[BUFFER_SIZE - 1] = 0;
			}
			// Write file contents to child 2
			// Entire file contents are sent at once in the buffer
			check = write(oneToTwo[1], buffer1, strlen(buffer1));
			if(check < 0)
			{
				perror("Error writing file content to pipe 1\n");
				exit(1);
			}
			fclose(openfile);
			sleep(2);
		}

		if(pclose(fp) < 0)
		{
			perror("Error closing fp for ls command\n");
			exit(1);
		}
		// Close writing end of pipe and resynchronize with child 2
		if(close(oneToTwo[1]) < 0)
		{
			perror("Failed to close pipe end\n");
			exit(1);
		}
		sleep(4);

		// Read from child 2
		while(check = read(twoToOne[0], buffer2, BUFFER_SIZE) > 0)
		{
			// When toggle is 0, we have receieved a new file to create
			if(toggle == 0)
			{
				openfile = fopen(buffer2, "w");
				toggle = 1;
				continue;
			}
			// When toggle is 1, we are writing file contents
			if(toggle == 1)
			{
				check = fputs(buffer2, openfile);
				fclose(openfile);
				toggle = 0;
				continue;
			}
		}
		if(check < 0)
		{
			perror("Error reading from pipe 1\n");
			exit(1);
		}
		// Close read end of pipe
		if(close(twoToOne[0]) < 0)
		{
			perror("Failed to close pipe end\n");
			exit(1);
		}

		// Safely exit child 1
		exit(0);
	}
      
	// Create child 2 from parent and ensure success
	child2 = fork();
   if(child2 < 0)
   {
      perror("Error creating child2\n");
		exit(1);
	}
	// Child 2
   else if(child2 == 0)
   {
		// Close pipe ends not being used
		// Will read from child 1 and write to child 1
		if(close(oneToTwo[1]) < 0 || close(twoToOne[0]) < 0)
		{
			perror("Failed to close pipe ends\n");
			exit(1);
		}
		// Change directory and ensure success
		if(chdir("./dir2") < 0)
		{
			perror("Failed to change directory\n");
			exit(1);
		}
		// Run ls command
		fp = popen("/bin/ls -Sr /home/osc/Project1/dir2", "r");
		if(fp == NULL)
		{
			perror("Failed to run command\n");
			exit(1);
		}

		// Synchronize processes and begin reading from child 1
		sleep(2);
		while(check = read(oneToTwo[0], buffer2, BUFFER_SIZE) > 0)
		{
			if(toggle == 0)
			{
				openfile = fopen(buffer2, "w");
				toggle = 1;
				continue;
			}
			if(toggle == 1)
			{
				check = fputs(buffer2, openfile);
				fclose(openfile);
				toggle = 0;
				continue;
			}
		}
		if(check < 0)
		{
			perror("Error reading from pipe 1\n");
			exit(1);
		}
		if(close(oneToTwo[0]) < 0)
		{
			perror("Failed to close pipe end\n");
			exit(1);
		}
		// Sleep to synchronize and prepare for writing to child 1
		sleep(2);

		// Read each line of ls
		while(input = getline(&line, &len, fp) != -1)
		{
			// Remove newline character from ls entry
			memmove(&line[strlen(line)-1], &line[strlen(line)], 1);
			if(line == NULL)
			{
				perror("Failed to read file name\n");
				exit(1);
			}
			// Write to child 1
			check = write(twoToOne[1], line, strlen(line) + 1);
			if(check < 0)
			{
				perror("Error writing to pipe 2\n");
				exit(1);
			}
			sleep(2);

			// Open file for reading contents
			openfile = fopen(line, "rb");
			if(openfile == NULL)
			{
				perror("Failed to open file for reading\n");
				exit(1);
			}
			// Read file one character at a time
			unsigned count = 0;
			while(!feof(openfile) && count < BUFFER_SIZE)
			{
				buffer1[count++] = fgetc(openfile);
			}
			if(feof(openfile))
			{
				buffer1[--count] = 0;
			}
			// Write file contents to child 1
			check = write(twoToOne[1], buffer1, strlen(buffer1));
			if(check < 0)
			{
				perror("Error writing file content to pipe 2\n");
				exit(1);
			}
			fclose(openfile);
			sleep(2);
		}
		if(pclose(fp) < 0)
		{
			perror("Failed to close pipe for ls command\n");
			exit(1);
		}

		if(close(twoToOne[1]) < 0)
		{
			perror("Failed to close pipe end\n");
			exit(1);
		}
		
		// Safely exit child 2
		exit(0);
	}

	// Parent
	// Close both ends of both pipes and wait for both children to finish
	if(close(oneToTwo[0]) < 0 ||
	close(oneToTwo[1]) < 0 ||
	close(twoToOne[0]) < 0 ||
	close(twoToOne[1]) < 0)
	{
		perror("Failed to close pipe ends\n");
		exit(1);
	}
  	while(wait(NULL) > 0)
	{
		;
	}
   return 0;
} 
