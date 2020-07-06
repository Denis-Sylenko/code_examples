#include <string>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int _pipe[2];
	pipe(_pipe);

	pid_t pid = fork();

	if (pid == 0)
	{
		std::string first_msg("Hi daddy, I’m your child.");
		write(_pipe[1], first_msg.c_str(), first_msg.length());
		close(_pipe[1]);
	}
	else
	{
		char buffer[BUFSIZ + 1];
		read(_pipe[0], buffer, BUFSIZ);
		std::string second_msg = buffer;
		second_msg += "Hello.";
		std::ofstream outfile("/home/denis/Task_2/result.txt");
		outfile << second_msg;
		outfile.close();
		close(_pipe[0]);

	}

	return 0;
}
