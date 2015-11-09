
#include "pal.h"

int main(int argc, char* argv[]) {
	int pal_num = atoi(argv[1]);
	int num_size = atoi(argv[2]);

	char commands[] = { 'a','d','w','x' };
	int commands_size = 4;

	machine_game_palindrome(pal_num, num_size, commands, commands_size);

	return 0;
}