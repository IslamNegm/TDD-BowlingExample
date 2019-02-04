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
			thisBall += 2;
		}
		else if (rolls[thisBall] == 10)					// Strike 
		{
			total+= 10 + rolls[thisBall+1] + rolls[thisBall+2];
			thisBall += 1;
		}
		else
		{
			total+=	rolls[thisBall] + rolls[thisBall+1];
			thisBall += 2;
		}
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

void strike_adds_next_two_rolls(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(2);
	roll(7);	// 9 
	
	roll(10);	// 9+10+4+5 = 28
	
	roll(4);	 
	roll(5);	// 38+9 = 37
	
	//Then
	TEST_ASSERT_EQUAL_INT(37, getScore());
}

void zero_then_spare_in_frame_behaves_as_a_spare_frame(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(2);
	roll(7);	// 9 
	
	// Spare
	roll(0);	
	roll(10);	// 9+10 = 19 >> 19 + 5 = 24
	
	roll(5);	 
	roll(3);	// 24+8 = 32
	
	//Then
	TEST_ASSERT_EQUAL_INT(32, getScore());
}


void bouns_for_spare_adds_one_extra_roll(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	// 0
	roll(0);
	roll(0);	// 0 
	// 1
	roll(0);
	roll(0);	// 0 
	// 2 
	roll(0);
	roll(0);	// 0 
	// 3
	roll(0);
	roll(0);	// 0 
	// 4
	roll(0);
	roll(0);	// 0 
	// 5
	roll(0);
	roll(0);	// 0 
	// 6
	roll(0);
	roll(0);	// 0 
	// 7
	roll(0);
	roll(0);	// 0 
	// 8
	roll(0);
	roll(0);	// 0 
	// 9
	roll(5);
	roll(5);	// 10 + 2 = 12   
	
	// Extra roll
	roll(2);	// 12 
	
	//Then
	TEST_ASSERT_EQUAL_INT(12, getScore());
}

void perfect_game_score_300(void)
{
	//Given new game
	initGame();

	//When I hit no pins
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	roll(10); 
	
	// Extra roll
	roll(10);
	roll(10);
	
	
	//Then
	TEST_ASSERT_EQUAL_INT(300, getScore());
}

/* ----- test runner ------ */
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(gutter_score_is_0);
	RUN_TEST(open_frame_score_is_sum_of_rolls);
	RUN_TEST(spare_score_adds_one_extra_roll);
	RUN_TEST(ten_in_two_frames_is_not_spare);
	RUN_TEST(strike_adds_next_two_rolls);
	RUN_TEST(zero_then_spare_in_frame_behaves_as_a_spare_frame);
	RUN_TEST(bouns_for_spare_adds_one_extra_roll);
	RUN_TEST(perfect_game_score_300);

    return UNITY_END();
}
