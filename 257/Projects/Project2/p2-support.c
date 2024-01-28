///////////////////////////////////////////////////////////////////////
// File          : p2-support.c
// Description   : Contains the method declarations for the functions 
//                 used in cmsc257-s22-p2 used to access an interactive
//                 email menu 
// Author        : Krish Patel
// Last Modified : 11/04/2022
///////////////////////////////////////////////////////////////////////

//Add necessary include statements (I added for you!)
#include "p2-support.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////

void initialize(struct Mailbox *ib)
{
  //allocate memory for 2000 emails
  ib->emails = malloc(sizeof(struct Email) * MAILBOX_SIZE);
  ib->size = 0;

  create_email("asonmez@mail.com", user_email, "Welcome to your inbox.",
    "Welcome to your inbox, just wanted to say hi. Here's hoping you get all your code done.",
    11, 20, 2020, ib);
  create_email("mmartinez@mail.com", user_email, "Padding out your inbox.",
    "Yet another email just to pad out your inbox, have fun!",
    11, 30, 2020, ib);
  create_email("dboyle@mail.com", user_email, "3rd email!",
    "Alright, time for another email for your inbox. Not going too lie, it's a bit of a pain coming up with stuff for these strings. Anyways, have fun with your code!",
    12, 2, 2020, ib);
  create_email("cbluer@mail.com", user_email, "4th email!",
    "Content of fourth email. More coding, more fun!",
    12, 8, 2020, ib);
  create_email("cboyle@mail.com", user_email, "5th email!",
    "Content of fifth email. Coding is fun-tastic!",
    12, 18, 2020, ib);
  create_email("sblack@mail.com", user_email, "6th email!",
    "Content of sixth email. Coding is fun-tastic!",
    1, 1, 2021, ib);
  create_email("sblack@mail.com", user_email, "7th email!",
    "Body of seventh email. Coding is fun-tastic!",
    1, 5, 2021, ib);
  create_email("sblack@mail.com", user_email, "8th email!",
    "Body of eighth email. Coding is fun-tastic!",
    2, 15, 2021, ib);
  create_email("sblack@mail.com", user_email, "9th email!",
    "Body of ninth email. Coding is fun-tastic!",
    2, 25, 2021, ib);
  create_email("dboyle@mail.com", user_email, "Last email!",
    "Body of tenth email. Coding is fun-tastic!",
    3, 15, 2021, ib);
}

void display_inbox_menu(struct Mailbox *ib){
  int option, ID = 0;
  char keyword[10];
  
  do{
    printf("\n***************     %s %s     ***************\n", "PATELKP7", "INBOX"); 
    printf("***************   Total Emails: %04i   ***************\n\n", ib->size); 

    printf("1. Show Inbox\n");
    printf("2. Show Email by ID\n");
    printf("3. Sort Inbox by Sender\n");
    printf("4. Sort Inbox by ID\n");
    printf("5. Search Inbox by Keyword\n");
    printf("6. Delete\n");
    printf("7. Exit Inbox\n\n"); 

    scanf("%d", &option);

    switch(option){
      case 1: // Show inbox
        show_inbox(ib);
        break;

      case 2: // Show email by ID
        show_email_by_ID(ib); 
        break;

      case 3: // Sort inbox by sender
        sort_by_sender(ib);
        break;

      case 4: // Sort inbox by ID
        sort_by_ID(ib);
        break;

      case 5: // Search inbox by keyword
        search_by_keyword(ib); 
        break;

      case 6: // Delete an email
        delete_email(ib); 
        break; 

      case 7: // Exit the inbox
        exit_email(ib);
        return 0;  

      default: printf("Invalid option\n"); 
    }
  } while(option != 7);
}

void create_email(char* sender, char* receiver, char* subject, char* body, int month, int day, int year, struct Mailbox* ib){
  // increment size of mailbox (ib) whenever this function is called (new email is created)
  ib -> size++; 

  // copy the string from the given parameters into the email struct within the inbox 
  strcpy(ib -> emails[ib->size].sender, sender);
  strcpy(ib -> emails[ib->size].receiver, receiver);
  strcpy(ib -> emails[ib->size].subject, subject);
  strcpy(ib -> emails[ib->size].body, body);

  // set the month of the email within the inbox equal to the given parameters
  ib -> emails[ib->size].sent_date.month = month;
  ib -> emails[ib->size].sent_date.day = day;
  ib -> emails[ib->size].sent_date.year = year; 

  // set ID equal to the current size of inbox 
  ib -> emails[ib->size].ID = ib -> size; 
}

void show_inbox(struct Mailbox *ib){
  int i;
  printf("\nID   SENDER--------------   MM/DD/YYYY   SUBJECT--------\n");
  printf("--   --------------------   --/--/----   ---------------\n");
  for(i = 1; i <= ib->size; i++){
    printf("%02i - ", ib->emails[i].ID); 
    printf("%-20s - ", ib->emails[i].sender);
    printf("%02i/%02i/%04i - ", ib->emails[i].sent_date.month, ib->emails[i].sent_date.day, ib->emails[i].sent_date.year);
    printf("%-15s\n", ib->emails[i].subject);
  }
}

void show_email_by_ID(struct Mailbox *ib){
  int i, num; 
  printf("\nEnter the ID of the email you want to read: "); 
  scanf("%d", &num); 
  for(i = 1; i < ib->size; i++){
    if(ib->emails[i].ID == num){
      printf("\n%s - %s\n", ib->emails[i].sender, ib->emails[i].subject);
      printf("Email Received on: %02i/%02i/%04i\n\n", ib->emails[i].sent_date.month, ib->emails[i].sent_date.day, ib->emails[i].sent_date.year);
      printf("%s\n", ib->emails[i].body); 
    }
  }
}

void sort_by_sender(struct Mailbox *ib){
  qsort(ib->emails[1].sender, ib->size, sizeof(struct Email), strcmp);
}

void sort_by_ID(struct Mailbox *ib){
  int i, j;
  struct Email *temp;
  temp = (struct Email*) malloc(sizeof(struct Email));
  for(i = 0; i <= ib->size; i++){
    for(j = i+1; j <= ib->size; j++){
      if(ib->emails[i].ID > ib->emails[j].ID){
        *temp = ib->emails[i];
        ib->emails[i] = ib->emails[j];
        ib->emails[j] = *temp; 
      }
    }
  }
  free(temp);
}

void search_by_keyword(struct Mailbox *ib){
  int i;
  char keyword[10]; 
  printf("\nEnter the keyword you wish to read: ");
  scanf("%10s", &keyword);
 
  for(i = 0; i <= ib->size; i++){
    if(strcasestr(ib->emails[i].sender, keyword) != NULL || strcasestr(ib->emails[i].subject, keyword) != NULL ||strcasestr(ib->emails[i].body, keyword) != NULL){
      printf("%02i - ", ib->emails[i].ID); 
      printf("%-20s - ", ib->emails[i].sender);
      printf("%02i/%02i/%04i - ", ib->emails[i].sent_date.month, ib->emails[i].sent_date.day, ib->emails[i].sent_date.year);
      printf("%-15s\n", ib->emails[i].subject);
    }
  }
}

void delete_email(struct Mailbox *ib){
  int ID;
  printf("\nEnter the ID of the email you wish to delete: ");
  scanf("%d", &ID);
  while(ib->size != ID){
    ib->emails[ID] = ib->emails[ID+1];
    ID++;
  }
  ib->size--;
  printf("Email deleted successfully"); 
}

void exit_email(struct Mailbox *ib){
  // free pointers to Email structs
  free(ib -> emails); 
  printf("Exiting mailbox\n\n"); 
}
