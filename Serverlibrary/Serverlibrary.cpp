#include "Serverlibrary.h"
#include <unistd.h>

using namespace std;

Serverlibrary::Serverlibrary()
{
  name = "Serverlibrary";

  myInput = new InputServerlibraryMessage;
  myOutput = new OutputServerlibraryMessage;

  inputMessage = myInput;
  outputMessage = myOutput;

  //QrobotController::Instance() = QrobotController::Instance();

  myRegister();
}

Serverlibrary::~Serverlibrary()
{
	delete myInput;
	delete myOutput;
}

size_t Serverlibrary::getInputMessageSize()
{
	return sizeof(InputServerlibraryMessage);
}

size_t Serverlibrary::getOutputMessageSize()
{
	return sizeof(OutputServerlibraryMessage);
}

void Serverlibrary::work()
{
  searchtype command = myInput->commandName;
  if(command < 3)
  {
     switch(command)
     {
        case 0:
          library::searchbookbytitle(string(myInput->book));
          break;
        case 1:
          library::searchbookbyauthor(string(myInput->book));
          break;
        case 2:
          library::searchbookbyisbn(string(myInput->book));
          break;
    }
    char buf[80];
    getcwd(buf,sizeof(buf));
    myOutput->status = 1;
    int i;
    for (i=0;buf[i]!='\0';i++)
      myOutput->path[i] = buf[i];
    char *s = "search_book.txt";
    int j;
    for (j=0;s[j] != '\0';j++)
      myOutput->path[i+j] = s[j];
    myOutput->path[i+j] = '\0';
  }
  else
  {
/*
    list<library>::iterator pos;
    for (pos = librarys.begin();pos != librarys.end();pos++)
    {
      if(pos->return_userid() == string(myInput->userid)) 
        break;
    }
    if(pos != librarys.end())
    {
      myOutput->status = pos->return_status();
    }
    else
    { 
      library l(myInput->userid,myInput->passwd);
      librarys.push_back(l);
      myOutput->status = l.return_status();
    }
    char buf[80];
    getcwd(buf,sizeof(buf));
    int i,j;
    for(i = 0;buf[i] != '\0';i++)
      myOutput->path[i] = buf[i];
    for(i = 0;myInput->userid[j] != '\0';i++)
      myOutput->path[i+j+1] = myInput->userid[j];
    myOutput->path[i+j+1] = '\0';
*/
    library l(myInput->userid,myInput->passwd);
    char buf[80];
    getcwd(buf,sizeof(buf));
    myOutput->status = l.return_status();
    int i;
    for(i=0;buf[i]!='\0';i++)
      myOutput->path[i] = buf[i];
    myOutput->path[i] = '\0';
  }
}


int main(int argc,char **argv)
{
	Serverlibrary s;
	s.serve();
	return 0;
}
