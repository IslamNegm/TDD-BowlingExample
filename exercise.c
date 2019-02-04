#include <stdio.h>
#include <string.h>
#include "unity.h"

/* ----- production code ------ */
#define FRAMES_PER_GAME 10
/* /! brief : This will hold the current score */
static int gameScore = -1; 
/* rolls array */
static int rolls[21]; 
static int next_index; 

void initGame (void){
	gameScore = 0;
	next_index = 0;
	/* Init the rolls array */
	memset(rolls, 0, sizeof(rolls));
}

void roll(int pins)
{
	rolls[next_index] = pins;
	next_index++;
}

int getScore(void)
{
	int i, thisBall = 0, total = 0;
	for(i=0; thisBall < FRAMES_PER_GAME; i++)	// iterate over the tests
	{
		if(rolls[thisBall] + rolls[thisBall+1] == 10) //Spare
		{
			total+= 10 + rolls[thisBall+2];	
		}
		else
		{
			total+=	rolls[thisBall] + rolls[thisBall+1];
		}
		thisBall += 2;
	}
	return total;
}

/* ----- test code ------ */
void gutter_score_is_0(void) {
	//Given new game
	initGame();

	//When I hit no pins
	roll(0);

	//Then
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, getScore(), "In gutter, score should be Zero");
}

void open_frame_score_is_sum_of_rolls(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(3);
	roll(4);

	//Then
	TEST_ASSERT_EQUAL_INT(7, getScore());
}

void spare_score_adds_one_extra_roll(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(7);
	roll(3);
	roll(4);
	
	//Then
	TEST_ASSERT_EQUAL_INT(18, getScore());
}

void ten_in_two_frames_is_not_spare(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(2);
	roll(7);
	roll(3);
	roll(4);
	
	//Then
	TEST_ASSERT_EQUAL_INT(16, getScore());
}




/* ----- test runner ------ */
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(gutter_score_is_0);
	RUN_TEST(open_frame_score_is_sum_of_rolls);
	RUN_TEST(spare_score_adds_one_extra_roll);
	RUN_TEST(ten_in_two_frames_is_not_spare);

    return UNITY_END();
}
