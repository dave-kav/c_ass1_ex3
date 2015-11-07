
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "visible.h"

//--------------------------------------------------
// initialise_array
//--------------------------------------------------

void initialise_array(int* a, int size, int num) {
	int rem = num;
	for (int i = size - 1; i >= 0; i--) {
		a[i] = rem % 10;
		rem = rem / 10;
	}
}

//--------------------------------------------------
// is_pal
//--------------------------------------------------

int is_pal(int* a, int size_num) {
	if (size_num == 0)
		return 1;
	if (size_num == 1)
		return 1;
	int* b = a + size_num - 1;
	while (b >= a) {
		if (*a != *b)
			return 0;
		else {
			a++;
			b--;
		}
	}
	return 1;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int* a, int size_num, int** p, int* num_mov, char c) {
	switch (c) {
	case 'a':
		if (*p != a + 0) {
			*num_mov = *num_mov + 1;
			*p = (*p - 1);
		}
		break;

	case 'd':
		if (*p != a + size_num - 1) {
			*num_mov = *num_mov + 1;
			*p = (*p + 1);
		}
		break;
	case 'x':
		if (**p != 0) {
			*num_mov = *num_mov + 1;
			**p = (**p - 1);
		}
		break;
	case 'w':
		if (**p != 9) {
			*num_mov = *num_mov + 1;
			**p = (**p + 1);
		}
		break;
	default:
		break;
	}
}

//--------------------------------------------------
// print_arrow
//--------------------------------------------------

void print_arrow(int* a, int* p) {
	int gap = p - a;
	printf("\n");
	for (int i = 0; i < gap; i++) {
		printf("  ");
	}
	printf("           ^");
}

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int* a, int size_num, int* p, int num_mov) {
	printf("------ Game Status -------\n");
	printf("Number = { ");
	for (int i = 0; i < size_num; i++)
		printf("%d ", a[i]);
	printf("}\n");
	print_arrow(a, p);
	printf("\nNumber of moves = %d", num_mov);
	printf("\n---------------------------\n");
}


//--------------------------------------------------
// get_solving_array
//--------------------------------------------------

char* get_solving_array(int* a, int size_num, int* p, int* total_movs) {
	int index = p - a;
	int* i_ptr =&a[index];
	int left = 0;
	char* moves = malloc(50 * sizeof(char));
	for (int i = 0; i < 20; i++) {
		moves[i] = 'b';
	}
	int* ptrA = a + 0;
	int* ptrB = a + size_num;
	int move_index = 0;

	//if odd number and index in the middle, move into the left
	if ((index % 2) == 1)
		if (index == (size_num / 2)) {
			index = index - 1;
			i_ptr = i_ptr - 1;
		}

	// if index is less than/equal to half the size, pointer is in left side
	if (index <= size_num / 2)
		left = 1;

	//define inner bounds
	int inside_left = (size_num / 2) - 1;
	int inside_right = 0;
	if ((size_num % 2) == 1)
		inside_left = (size_num / 2) + 1;
	else
		inside_right = (size_num / 2);

	//if left
	if (left == 1) {
		//if not at right hand inner boundary of left side
		if (index != inside_right) {
			//if not at left most position
			if (i_ptr != (a + 0)) {
				//move to left most position
				while (i_ptr != (a + 0)) {
					index = index - 1;
					i_ptr = i_ptr - 1;
					moves[move_index] = 'a';
					total_movs = total_movs + 1;
				}
				ptrA = (a + index);
				ptrB = (a + size_num - index - 1);
			}
			//if at left most position, set pointers
			else {
				ptrA = a + index;
				ptrB = a + (size_num - index - 1);
				//compare and change 
				while (ptrA != a + inside_left) {	//pointer loop
					while (*ptrA != *ptrB) {		//value loop
						if (*ptrA > *ptrB) {
							while (*ptrA != *ptrB) {
								*ptrA = *ptrA - 1;
								total_movs = total_movs + 1;
								moves[move_index] = 'x';
								move_index = move_index + 1;
							}
						}
						else {
							while (*ptrA != *ptrB) {
								*ptrA = *ptrA + 1;
								total_movs = total_movs + 1;
								moves[move_index] = 'w';
								move_index = move_index + 1;
							}
						}
					}	//end value loop
					ptrA = ptrA - 1;
					moves[move_index] = 'd';
					move_index = move_index + 1;
					total_movs = total_movs + 1;
					ptrB = ptrB + 1;
				}	//end pointer loop
			}
		}
		//if at inside right, set pointers
		else {
			ptrA = a + index;
			ptrB = a + (size_num - index - 1);
			//compare and change 
			while (ptrA != a + 0) {	//pointer loop
				while (*ptrA != *ptrB) {	//value loop
					if (*ptrA > *ptrB) {
						while (*ptrA != *ptrB) {
							*ptrA = *ptrA - 1;
							total_movs = total_movs + 1;
							moves[move_index] = 'x';
							move_index = move_index + 1;
						}
					}
					else {
						while (*ptrA != *ptrB) {
							*ptrA = *ptrA + 1;
							total_movs = total_movs + 1;
							moves[move_index] = 'w';
							move_index = move_index + 1;
						}
					}
				}	//end value loop
				ptrA = ptrA - 1;
				moves[move_index] = 'a';
				move_index = move_index + 1;
				total_movs = total_movs + 1;
				ptrB = ptrB + 1;
			}	//end pointer loop
		} //end of right most side of left
	}//end of left side
	else { //if at right side
		//if not at left hand inner boundary of right side
		if (index != inside_left) {
			//if not at right most position
			if (i_ptr != (a + (size_num - 1))) {
				//move to right most position
				while (i_ptr != (a + (size_num - 1))) {
					index = index + 1;
					i_ptr = i_ptr + 1;
					total_movs = total_movs + 1;
					moves[move_index] = 'd';
				}
				ptrA = (a + index - 1);
				ptrB = (a + size_num - index - 1);
			}
			//if at right most position, set pointers
			else {
				ptrA = a + index;
				ptrB = a + (size_num - index - 1);
				//compare and change 
				while (ptrA != a + inside_left) {	//pointer loop
					while (*ptrA != *ptrB) {		//value loop
						if (*ptrA > *ptrB) {
							while (*ptrA != *ptrB) {
								*ptrA = *ptrA - 1;
								total_movs = total_movs + 1;
								moves[move_index] = 'x';
								move_index = move_index + 1;
							}
						}
						else {
							while (*ptrA != *ptrB) {
								*ptrA = *ptrA + 1;
								total_movs = total_movs + 1;
								moves[move_index] = 'w';
								move_index = move_index + 1;
							}
						}
					}	//end value loop
					ptrA = ptrA - 1;
					moves[move_index] = 'a';
					move_index = move_index + 1;
					total_movs = total_movs + 1;
					ptrB = ptrB + 1;
				}	//end pointer loop
			}
		}
		//if at inside left, set pointers
		else {
			ptrA = a + index;
			ptrB = a + (size_num - index - 1);
			//compare and change 
			while (ptrA != a + 0) {	//pointer loop
				while (*ptrA != *ptrB) {	//value loop
					if (*ptrA > *ptrB) {
						while (*ptrA != *ptrB) {
							*ptrA = *ptrA - 1;
							total_movs = total_movs + 1;
							moves[move_index] = 'x';
							move_index = move_index + 1;
						}
					}
					else {
						while (*ptrA != *ptrB) {
							*ptrA = *ptrA + 1;
							total_movs = total_movs + 1;
							moves[move_index] = 'w';
							move_index = move_index + 1;
						}
					}
				}	//end value loop
				ptrA = ptrA - 1;
				moves[move_index] = 'd';
				move_index = move_index + 1;
				total_movs = total_movs + 1;
				ptrB = ptrB + 1;
			}	//end pointer loop
		} //end of right most side of left
	}
	printf("index %d", index);
	printf("i_ptr %a", i_ptr);
	printf("inside left %d", inside_left);
	printf("inside right %d", inside_right);
	moves = (char*)realloc(moves, total_movs);
	return moves;
}

//--------------------------------------------------
// machine_game_palindrome
//--------------------------------------------------

void machine_game_palindrome(int pal_num, int num_size, char commands[], int command_size) {
	srand(time(NULL));
	int* a = malloc(num_size*sizeof(int));
	initialise_array(a, num_size, pal_num);
	int num_moves = 0;
	int index = gen_num(0, num_size);
	int* index_ptr = &a[index];
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	print_status(a, num_size, index_ptr, num_moves);
	
	char* moves = get_solving_array(a, num_size, index_ptr, &num_moves);
	int bool = 0;

	printf("------------------------------------------------------\n");
	printf("---------- Solved optimally in %d movements ----------\n", num_moves);
	printf("------------------------------------------------------\n\n");
	printf("Press any key to see the solved movements one by one:\n");
	my_get_char();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	while (bool != 1) {
		int i = 0;
		bool = is_pal(a, num_size);
		print_status(a, num_size, index_ptr, num_moves);
		if (bool == 1) {
			printf("----------SOLVED!----------\n");
			printf("---------------------------\n");
		}
		else {
			printf("Press any key to see the solved movements one by one:\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			my_get_char(); 
			//process_movement(a, num_size, &index_ptr, &num_moves, moves + i);
			i = i + 1;
		}
	}
}