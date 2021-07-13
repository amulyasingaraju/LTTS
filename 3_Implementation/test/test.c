#include "unity.h"
#include "unity_internals.h"
#include "lib.h"

/* Modify these two lines according to the project */
#define PROJECT_NAME    "SongBook_Management"

/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}


/* Write all the test functions */ 
void printMessageCenter(const char* message) {
  TEST_ASSERT_EQUAL(pass,printMessageCenter(const char* message)));
}

void headMessage(const char *message) {
  TEST_ASSERT_EQUAL(pass,headMessage(const char *message));
}
  

void addSongInDataBase() {
  TEST_ASSERT_EQUAL(pass,addSongInDataBase());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,addSongInDataBase());
}

void welcomeMessage() {
  TEST_ASSERT_EQUAL(pass,welcomeMessage());
}
void searchSongs(){
  TEST_ASSERT_EQUAL(pass,searchSongs());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,searchSongs());

}
void viewSongs(){
  TEST_ASSERT_EQUAL(pass,viewSongs());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,viewSongs());

}
void updateCredential(void){
  TEST_ASSERT_EQUAL(pass,updateCredential(void));
}

void deleteSongs(){
  TEST_ASSERT_EQUAL(pass,deleteSongs());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,deleteSongs());

}

void menu(){
  TEST_ASSERT_EQUAL(pass,menu());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,menu());

}

void login(){
  TEST_ASSERT_EQUAL(pass,login());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,login());

}

void init(){
  TEST_ASSERT_EQUAL(pass,init());
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,init());

}

int isValidDate(Date *validDate){
  TEST_ASSERT_EQUAL(pass,isValidDate(Date *validDate));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(fail,isValidDate(Date *validDate));

}


/* Start of the application test */
int main()
{
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();

/* Run Test functions */
  RUN_TEST(test_printMessageCenter);
  RUN_TEST(test_headMessage);
  RUN_TEST(test_addSongInDataBase);
  RUN_TEST(test_welcomeMessage);
  RUN_TEST(test_searchSongs);
  RUN_TEST(test_viewSongs);
  RUN_TEST(test_updateCredential);
  RUN_TEST(test_deleteSongs);
  RUN_TEST(test_menu);
  RUN_TEST(test_login);
  RUN_TEST(test_init);
  RUN_TEST(test_isValidDate);

  /* Close the Unity Test Framework */
  return UNITY_END();
}
