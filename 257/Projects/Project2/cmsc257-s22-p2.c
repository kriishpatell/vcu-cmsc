///////////////////////////////////////////////////////////////////////
// File          : cmsc257-s22-p2.c
// Description   : This is the main function of project2 for CMSC257
//
// Author        : Krish Patel
// Last Modified : 11/04/2022
//Do not modify anything below this line

#include <stdio.h>
#include <stdlib.h>
#include "p2-support.h"

int main(){
  struct Mailbox* ib;
  ib = (struct Mailbox*) malloc(sizeof(struct Mailbox));
  initialize(ib);
  display_inbox_menu(ib);
  free (ib);
  return 0;
}

