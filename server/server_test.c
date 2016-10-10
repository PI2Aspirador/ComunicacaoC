#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_control.h"

int test_verify_small_distance(){
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

int test_verify_big_distance(){
	int distance = 16;
	char response = verify_distance(distance);
	if (response == 'G'){
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

int test_get_data(){
	char *text = "server/test_text.txt";
	char *full_text = get_data(text);
	if (strcmp(full_text, "testing") == 0){
		printf(".");
		return 1;
	}
	else{
		return 0;
	}
}

void run_test_suite(){
	int failed = 0;

	int test = test_verify_small_distance();
	if (!test){
		printf("\nTest test_verify_small_distance failed.\n");
		failed++;
	}

	int test2 = test_verify_big_distance();
	if (!test2){
		printf("\nTest test_verify_big_distance failed.\n");
		failed++;
	}

	int test3 = test_hash_data();
	if (!test3){
		printf("\nTest hash_data failed.\n");
		failed++;
	}	

	int test4 = test_get_data();
	if (!test4){
		printf("\nTest get_data failed.\n");
		failed++;
	}

	if (failed > 0)
	{
		exit(1);
	}
}

int main(){
	printf("Starting tests\n");
	run_test_suite();
	printf("\nTests finished.\n");
	return 0;
}