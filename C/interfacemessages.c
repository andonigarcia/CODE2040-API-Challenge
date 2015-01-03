// Andoni Garcia. 2015.
// Messages for my terminal interface

#include "CODE2040.h"

/* =====================================================================
 * =====================================================================
 * ===========================  Messages ===============================
 * =====================================================================
 * =====================================================================
 */

void err_multArgs1(char *argv)
{
  fprintf(stderr, "Please execute this without any additional arguments."
         " The program will walk you through everything. Please re-run"
         " with:\n%s\n", argv);
  exit(0);
}

void msg_welcome()
{
  system("clear");
  printf("Welcome to Andoni's solution to the CODE2040 API Challenge.\n\nIf"
         " you have any comments or questions, feel free to email me at: "
         "andoni@uchicago.edu.\nYou can check out the source code: "
         "https://github.com/andonigarcia/CODE2040-API-Challenge/C.\nEnjoy!\n");
  return;
}

void msg_register()
{
  printf("\nFirst thing's first. You have to register!\n");
  return;
}

void msg_registerEmail()
{
  printf("\nWhat is your email address that you used to apply for CODE2040? ");
  return;
}

void msg_registerGithub()
{
  printf("\nWhat is your github repository that you linked to CODE2040? ");
  return;
}

void msg_token(char *token)
{
  printf("\nCongrats! Your token ID is: %s\n"
         "Now let's start completing the stages!\n", token);
  return;
}

void msg_success()
{
  printf("\nThats it. You solved the CODE2040-API-Challenge!\n");
  return;
}

void msg_failure()
{
  printf("\nGo through and manually check the answers. Most likely your "
         "compiler or localtime settings did something wonky. Most of these"
         " functions are very thoroughly tested. If you aren't sure though,"
         " send your logs to: andoni@uchicago.edu and I'll get back to you ASAP.\n");
  return;
}

void msg_pass(char *stage)
{
  printf("CONGRATS! You passed %s!\n", stage);
  return;
}

void msg_notPass(char *msg)
{
  printf("For some reason you did not pass. Here's the server's response: %s.\n", msg);
  return;
}

void msg_stageIWelcome()
{
  printf("\n~~~~~~~~~~~~~~~~Welcome to Stage I: Reverse a String~~~~~~~~~~~~~~~~"
         "\n\nHere you will be given a random string. Our program will then "
         "reverse the string and submit the answer to the server.\n");
  return;
}

void msg_stageIIWelcome()
{
  printf("\n~~~~~~~~~~~~~~Next up is Stage II: Needle in a Haystack.~~~~~~~~~~~~~~"
        "\n\nHere you will be given an array of random words (the haystack) and"
        " a word that matches only one of the words in the array (the needle). "
        "Our program will then find the index of that word in the array!\n");
  return;
}

void msg_stageIIIWelcome()
{
  printf("\n~~~~~~~~~~~~~~Wow great work! Here is Stage III: Prefix.~~~~~~~~~~~~~~"
        "\n\nIn this stage, you will get an array of words and a prefix. Then, "
        "our program will go through and filter out any of the words in the "
        "array that start with the prefix!\n");
  return;
}

void msg_stageIVWelcome()
{
  printf("\n~~~~~~~~~~~~~~The final stage! Stage IV: The Dating Game.~~~~~~~~~~~~~~"
        "\n\nThis stage will give you a datestamp and an interval. The program "
        "will then convert the datestamp to Unix time, add the interval to it, "
        "and then re-convert it back to an ISO 8601 datestamp. Be careful, there "
        "is a cygwin bug such that GCC messes up Daylights Savings when you "
        "straight add time together like this. It works on almost all other "
        "compilers though. Sorry for the bug.\n");
  return;
}