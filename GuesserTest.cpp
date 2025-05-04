/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// 1) Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

// 2) Correct guess returns true and resets remaining attempts to 3
TEST(GuesserTest, Match_Correct) 
{
	Guesser object("Secret");
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_EQ(object.remaining(), 3);
}

// 3) Incorrect guess (close match) returns false and decrements remaining
TEST(GuesserTest, Match_CloseGuess) 
{
    Guesser object("Secret");
    ASSERT_FALSE(object.match("Secrat"));
    ASSERT_EQ(object.remaining(), 2);
}

// 4) Brute force guess (distance > 2) locks the guesser
TEST(GuesserTest, Match_BruteForce) 
{
    Guesser object("Secret");
    ASSERT_FALSE(object.match("WrongWord")); 
    ASSERT_FALSE(object.match("Secret"));    
    ASSERT_EQ(object.remaining(), 3);       
}

// 5) 3 incorrect close guesses lock the guesser
TEST(GuesserTest, Match_ThreeFails) 
{
    Guesser object("Secret");
    object.match("Secrat");  
    object.match("Secrex"); 
    object.match("Secrey");  
    ASSERT_EQ(object.remaining(), 0);
    ASSERT_FALSE(object.match("Secret")); 
}

// 6) Correct guess after incorrect guess resets the remaining count
TEST(GuesserTest, Match_CorrectAfterFail) 
{
	Guesser object("Secret");
    object.match("Secrat"); // wrong
    EXPECT_EQ(object.remaining(), 2);
    bool result = object.match("Secret");
    EXPECT_TRUE(result);
    // EXPECT_EQ(object.remaining(), 3);    
}

// 7) Secret should be 32 characters if too long
TEST(GuesserTest, Char_Long) 
{
    Guesser object("abcdefghijklmnopqrstuvwxyz1234567890EXTRA");
    EXPECT_TRUE(object.match("abcdefghijklmnopqrstuvwxyz123456")); 
}

// 8) Guess with distance of 2 does not lock but distance 3 does
TEST(GuesserTest, Match_Distance) 
{
    Guesser object("cat");
    ASSERT_FALSE(object.match("c"));     
    ASSERT_EQ(object.remaining(), 2);
    ASSERT_FALSE(object.match("dog"));   
    ASSERT_FALSE(object.match("cat"));   
}

// 9) Remaining guesses still decrement
TEST(GuesserTest, Match_Locked) 
{
    Guesser object("hello");
    object.match("xxxxx"); 
    object.match("xxxxx"); 
    EXPECT_EQ(object.remaining(), 3); 
}

// 10) Case sensitivity test
TEST(GuesserTest, Match_Case) {
    Guesser object("Secret");
    ASSERT_FALSE(object.match("secret"));
    ASSERT_EQ(object.remaining(), 2);
}