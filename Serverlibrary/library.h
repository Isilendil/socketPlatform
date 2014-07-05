#ifndef _LIBRARY_H_
#define _LIBRARY_H_
//#include "search_library.h"
//#include "searchbook.h"
//#include "IsLogin.h"
#include <map>
#include <string>
#include <list>
#include "ffpython.h"

typedef std::list<std::map<string,string> > std_form;
typedef std::map<string,string> personal_form;
typedef std::list<std::list<std::map<string,string> > > finance_form;

typedef std::list<std::map<string,string> > mystl;

int IsLogin(string s1,string s2)
{
  Py_Initialize();
	ffpython_t::add_path("./");
  ffpython_t ffpython;
  string s3 = "login";
  int a = ffpython.call<int>("library","library",s1,s2,s3);
  int result;
  if(a == 1)
    result = 1;
  else
    result = 0;
  Py_Finalize();
  return result;
}
mystl searchbook(string s1,string s2)
{
  Py_Initialize();
  ffpython_t::add_path("./");
  ffpython_t ffpython;
  mystl result = ffpython.call<mystl>("library","searchbook",s1,s2);
  Py_Finalize();
  return result;
}

personal_form search_library(string s1,string s2)
{
  Py_Initialize();
	ffpython_t::add_path("./");
  ffpython_t ffpython;
  string s3 = "personal";
  personal_form result = ffpython.call<personal_form>("library","library",s1,s2,s3);
  Py_Finalize();
  return result;
}

std_form search_library(string s1,string s2,string s3)
{
  Py_Initialize();
	ffpython_t::add_path("./");
  ffpython_t ffpython;
  std_form result = ffpython.call<std_form>("library","library",s1,s2,s3);
  Py_Finalize();
  return result;
}

finance_form search_library(string s1,string s2,string s3,string s4)
{
  Py_Initialize();
	ffpython_t::add_path("./");
  ffpython_t ffpython;
  finance_form result = ffpython.call<finance_form>("library","library",s1,s2,s3);
  Py_Finalize();
  return result;
}

class library
{
public:
  library(){correct = 0;}
  library(std::string s1,std::string s2);
  //library(library &);
  static mystl searchbookbytitle(std::string s);
  static mystl searchbookbyauthor(std::string s);
  static mystl searchbookbyisbn(std::string s);
  void search_personal();
  void search_borrow();
  void search_shelf();
  void search_finance();
  void init();
  int return_status();
  personal_form return_personal();
  std_form return_borrow();
  std_form return_shelf();
  finance_form return_finance();
  std::string return_userid();
private:
  int correct;
  std::string userid;
  std::string passwd;
  personal_form personal;
  std_form borrow;
  std_form shelf;
  finance_form finance;
};

#endif
