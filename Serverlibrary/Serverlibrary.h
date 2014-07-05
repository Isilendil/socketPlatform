#ifndef _SERVERLIBRARY_H_
#define _SERVERLIBRARY_H_

#include "Server.h"
#include "library.h"
//#include "ServerlibraryMessage.h"

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
      char path[80];
};
class Serverlibrary : public Server
{
public:
  Serverlibrary();
  ~Serverlibrary();


protected:
	void work();

  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
	InputServerlibraryMessage *myInput;
	OutputServerlibraryMessage *myOutput;
        std::list<library> librarys;
  //qrobot::QrobotController &controller;
};

#endif
