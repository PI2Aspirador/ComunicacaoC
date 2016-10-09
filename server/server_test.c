#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_control.h"

int test_verify_distance(){
	int distance = 14;
	char response = verify_distance(distance);
	if (response == 'R'){
		printf(".");
		return 1;
	}
	else{
		return 0;
	}
}

int test_hash_data(){
	char *text = "blabla";
	char *hashed_text = hash_data(text);
	if (strcmp(hashed_text, "abE745FOPspe2") == 0){
		printf(".");
		return 1;
	}
	else{
		return 0;
	}
}

void run_test_suite(){
	int test = test_verify_distance();
	if (!test){
		printf("Test verify_distance failed.\n");
		exit(1);
	}

	int test2 = test_hash_data();
	if (!test2){
		printf("Test hash_data failed.\n");
		exit(1);
	}
}

int main(){
	printf("\nStarting tests...\n");
	run_test_suite();
	printf("\nTests finished.\n");
	return 0;
}