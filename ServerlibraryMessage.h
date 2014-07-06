#ifndef _SERVERLIBRARY_H_
#define _SERVERLIBRARY_H_

enum searchtype
{
  searchbookbytitle,
  searchbookbyauthor,
  searchbookbyisbn,
  personal,
  borrow,
  shelf,
  finance
};

struct InputServerlibraryMessage
{
      char userid[15];
      char passwd[10];
      enum searchtype commandName;
      char book[25];
};

struct OutputServerlibraryMessage
{
      int status;
      char path[100];
};

#endif
