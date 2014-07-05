#-*-coding:utf-8-*-
import threading
import urllib
import urllib2
import cookielib
from bs4 import BeautifulSoup as bs
from os.path import exists
from os import mkdir

class ThreadFunc(object):
    def __init__(self,func,args,name=''):
        self.name=name
        self.func=func
        self.args=args

    def __call__(self):
        apply(self.func,self.args)
def threadtask(a, search, mylock):
    temp1 = ['title', 'author', 'publish', 'ISBN/ISSN', 'date', 'booknum', 'type']
    temp = {}
    m = a.td
    for i in range(len(temp1)):
        m = m.nextSibling
        temp[temp1[i]] = m.string
    mylock.acquire()
    search.append(temp)
    mylock.release()

def borrowtask(a, borrow, mylock):
    temp = {}
    m = a.td.nextSibling.nextSibling
    temp1 = m.string
    temp['title'] = temp1
    m = m.nextSibling.nextSibling.nextSibling.nextSibling
    temp1 = m.string
    temp['borrowtime'] = temp1
    m = m.nextSibling
    temp1 = m.string
    temp['returntime'] = temp1
    m = m.nextSibling.nextSibling
    temp['renew'] = m.string
    mylock.acquire()
    borrow.append(temp)
    mylock.release()

def shelftask(a, shelf, mylock):
    temp1 = ['title', 'author','publish', 'category', 'type']
    temp = {}
    m = a.td
    for i in range(len(temp1)):
        m = m.nextSibling
        try:
            temp[temp1[i]] = m.string.encode('utf-8')
        except:
            temp[temp1[i]] = ''
    mylock.acquire()
    shelf.append(temp)
    mylock.release()
    
def searchbook(input, way):
    ways = ['TITLE', 'AUTHOR', 'ISBN']
    if(way.upper() in ways):
        way = way.upper()
    else:
        return None
        
    page = 'http://202.38.232.10/opac/servlet/opac.go'
    headers = {'Accept':'text/html, application/xhtml+xml, */*', 'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko'}
    postdata = {'cmdACT':'simple.list', 'RDID':'ANONYMOUS', 'ORGLIB':'SCUT', 'MODE':'FRONT'}
    postdata['FIELD1'] = way
    postdata['VAL1'] = input
    postdata = urllib.urlencode(postdata)


    cookie = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
    
    req = urllib2.Request(page, postdata, headers)
    result = opener.open(req)
    html = result.read()
    
    search = []
    soup = bs(html)
    a = soup.findAll('tr')
    fp = open('./search_book.txt','w+b')
    if(len(a)!=2 or '查无符合条件的记录' not in a[1].td.string.encode('utf-8')):
        threads = []
        mylock = threading.Lock()
        for i in range(1, len(a)):
            t = threading.Thread(target=ThreadFunc(threadtask, (a[i], search, mylock), threadtask.__name__))
            threads.append(t)
        for i in range(len(threads)):
            threads[i].start()
        for i in range(len(threads)):
            threads[i].join(20)
    else:
        fp.write('None')
        fp.close()
        return search
    for i in range(len(search)):
      for eachKey in search[i]:
        try:
          search[i][eachKey] = search[i][eachKey].encode('utf-8')
          fp.write(search[i][eachKey] + '\t\t')
        except:
          search[i][eachKey] = ''.encode('utf-8')
          fp.write('None')
      fp.write('\n')
    return search


def library(userid, passwd, way):
    ways = ['login','personal', 'borrow', 'shelf', 'finance']
    way = way.lower()
    path = './' + userid
    if(not exists(path)):
      mkdir(path)
    if(way not in ways):
        return None
    homepage = 'http://202.38.232.10/opac/servlet/opac.go'
    borrowpage = 'http://202.38.232.10/opac/servlet/opac.go?cmdACT=loan.list'
    shelfpage = 'http://202.38.232.10/opac/servlet/opac.go?cmdACT=bookshelf.list'
    financepage = 'http://202.38.232.10/opac/servlet/opac.go?cmdACT=finance.list'
    
    cookie = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
    
    postdata = {"cmdACT":"mylibrary.login", "method":"mylib", "user_login":"%E7%99%BB%E5%BD%95"}
    postdata['userid'] = userid
    postdata['passwd'] = passwd
    postdata = urllib.urlencode(postdata)
    headers = {'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8','Content-Type':'application/x-www-form-urlencoded','User-Agent' : 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:30.0) Gecko/20100101 Firefox/30.0',  'Referer' : 'http://202.38.232.10/opac/servlet/opac.go?cmdACT=mylibrary.index'}  
    
    #homepage
    req = urllib2.Request(homepage, postdata, headers)
    result = opener.open(req)
    if(way=='login'):
        html = result.read()
        if(userid in html):
            return 1
        else:
            return 0
    elif(way=='personal'):
        html = result.read()
        
        soup = bs(html)
        a = soup.findAll('th')
        personal = {}
        for i in range(len(a)):
            temp1 = a[i].string
            temp2 = a[i].nextSibling.string
            if(temp2 == None):
                temp2 = ''
            personal[temp1.encode('utf-8')] = temp2.encode('utf-8')
        if("有效" in personal["状态"]):
          personal["状态"] = "有效"
        fp = open(path + '/personal.txt','w+b')
        for eachKey in personal:
          fp.write(eachKey + '\t\t' + personal[eachKey] + '\n')
        fp.close() 
        return personal
    elif(way=='borrow'):
    #borrowpage
        req = urllib2.Request(url = borrowpage)
        result = opener.open(req)
        html = result.read()
        
        soup = bs(html)
        a = soup.findAll('tr')
        borrow = []
        if(len(a)!=2 or '当前没有借阅' not in a[1].td.string.encode('utf-8')):
            threads = []
            mylock = threading.Lock()
            for i in range(1, len(a)):
                t = threading.Thread(target=ThreadFunc(borrowtask, (a[i], borrow, mylock), borrowtask.__name__))
                threads.append(t)
            for i in range(len(threads)):
                threads[i].start()
            for i in range(len(threads)):
                threads[i].join(20)
        else:
          pass
        fp = open(path + '/borrow.txt','w+b')
        for i in range(len(borrow)):
            for eachKey in borrow[i]:
                try:
                    borrow[i][eachKey] = borrow[i][eachKey].encode('utf-8')
                    fp.write(borrow[i][eachKey] + '\t\t')
                except:
                    borrow[i][eachKey] = ''
                    fp.write('None')
            fp.write('\n')
        fp.close()
        return borrow
    #shelfpage
    elif(way=='shelf'):
        req = urllib2.Request(url = shelfpage)
        result = opener.open(req)
        html = result.read()
        
        soup = bs(html)
        a = soup.findAll('tr')
        shelf = []
        if(len(a)!=2 or '当前没有借阅书籍' not in a[1].td.string):
            mylock = threading.Lock()
            threads = []
            for i in range(1, len(a)):
                t = threading.Thread(target=ThreadFunc(shelftask, (a[i], shelf, mylock), borrowtask.__name__))
                threads.append(t)
            for i in range(len(threads)):
                threads[i].start()
            for i in range(len(threads)):
                threads[i].join(20)
        else:
            pass
        fp = open(path + '/shelf.txt','w+b')
        for i in range(len(shelf)):
          for eachKey in shelf[i]:
            fp.write(shelf[i][eachKey] + '\t\t')
          fp.write('\n')
        fp.close()
        return shelf
        
    #financepage
    elif(way=='finance'):
        req = urllib2.Request(url = financepage)
        result = opener.open(req)
        html = result.read()
        
        soup = bs(html)
        a = soup.findAll('p')
        temp = a[0].nextSibling.nextSibling
        soup = bs(str(temp))
        b = soup.findAll('tr')
        debt = []
        if(len(b) == 2 and '读者当前没有欠费记录' in b[1].td.string.encode('utf-8')):
            pass
        else:
            for i in range(1, len(b)):
                temp = {}
                c = b[i].td
                temp['place'] = c.string.encode('utf-8')
                c = c.nextSibling
                temp['type'] = c.string.encode('utf-8')
                c = c.nextSibling
                temp['amount'] = c.string.encode('utf-8')
                c = c.nextSibling
                temp['time'] = c.string.encode('utf-8')
                debt.append(temp)
        fp = open(path + '/debt.txt','w+b')
        for i in range(len(debt)):
          for eachKey in debt[i]:
            fp.write(debt[i][eachKey])
          fp.write('\n')
        fp.close()
        temp = a[1].nextSibling.nextSibling
        soup = bs(str(temp))
        b=soup.findAll('tr')
        bill = []
        for i in range(1, len(b)):
            temp = {}
            c = b[i].td
            temp['place'] = c.string.encode('utf-8')
            c = c.nextSibling
            temp['type'] = c.string.encode('utf-8')
            c = c.nextSibling
            temp['amount'] = c.string.encode('utf-8')
            c = c.nextSibling
            temp['time'] = c.string.encode('utf-8')
            bill.append(temp)
        fp = open(path + '/bill.txt','w+b')
        for i in range(len(bill)):
          for eachKey in bill[i]:
            fp.write(bill[i][eachKey] + '\t\t')
          fp.write('\n')
        fp.close()
        finance = [debt,bill]
        return finance

