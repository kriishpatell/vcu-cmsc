#ifndef CMSC257_P2SUPPORT_INCLUDED
#define CMSC257_P2SUPPORT_INCLUDED

#define MAILBOX_SIZE 2000
#define ADDRESS_SIZE 50
#define SUBJECT_SIZE 200
#define BODY_SIZE 2000
#define NAME_SIZE 20
//Replace e@mail.com with your VCU email below
#define user_email "patelkp7@vcu.edu"
//add other define Macros as needed
struct Date
{
  int month;
  int day;
  int year;
};

struct Email
{
  char sender[ADDRESS_SIZE];
  char receiver[ADDRESS_SIZE];
  char subject[SUBJECT_SIZE];
  char body[BODY_SIZE];
  struct Date sent_date;
  int ID;
};

struct Mailbox
{
  int size;
  struct Email *emails;
};

///////////////////////////////////////////////////////////////////////////////
// Function     : initialize
// Description  : Initializes the database for CMSC257 project #2 by manually 
//                entering the records using create_email function
// Inputs       : struct Mailbox *ib - pointer to the database
// Outputs      : void
///////////////////////////////////////////////////////////////////////////////
void initialize(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : display_inbox_menu
// Description  : Displays the inbox menu, and also contains options for the
//                user to select where the would like to go 
// Inputs       : struct Mailbox *ib - pointer to the database;
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void display_inbox_menu(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : create_email
// Description  : Create an email struct given the elements 
// Inputs       : char *sender, char* receiver, char* subject, char* body, 
//                int month, int day, int year, struct Mailbox *ib - pointer
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void create_email(char *sender, char* receiver, char* subject, char* body, int month, int day, int year, struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : show_inbox
// Description  : Display the emails that are within the inbox 
// Inputs       : struct Mailbox *ib - pointer to the database
// Outputs      : void
///////////////////////////////////////////////////////////////////////////////
void show_inbox(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : show_email_by_ID
// Description  : Given the ID of an email, return the email corresponding
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void show_email_by_ID(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : sort_by_sender
// Description  : Sort the mailbox lexicographically by the sender
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void sort_by_sender(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : sort_by_ID
// Description  : Sort the mailbox by the ID number of the email
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void sort_by_ID(struct Mailbox *ib); 

///////////////////////////////////////////////////////////////////////////////
// Function     : search_by_keyword
// Description  : Given a keyword of 10 characters, search through the inbox
//                and return a temp mailbox with the emails that contain that
//                keyword
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void search_by_keyword(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : delete_email
// Description  : Delete the email at the given ID
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void delete_email(struct Mailbox *ib);

///////////////////////////////////////////////////////////////////////////////
// Function     : exit_email
// Description  : Deallocate the emails inside the inbox 
// Inputs       : struct Mailbox *ib - pointer to the database
// Output       : void
///////////////////////////////////////////////////////////////////////////////
void exit_email(struct Mailbox *ib);

#endif // CMSC257_P2SUPPORT_INCLUDED
