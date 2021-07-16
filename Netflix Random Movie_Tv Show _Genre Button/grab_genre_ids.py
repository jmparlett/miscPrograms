import requests
from var import genereIds
import re

content=[]


def grabhtml(id):
    r=requests.get(f'https://www.netflix.com/browse/genre/{id}')
    return r.text.split('"')

def testUrl(list1):
    fcount=0
    tcount=0
    for id in list1:
        r=requests.get(f'https://www.netflix.com?jbv={id}')
        print(f'fcount is {fcount}', f'tcount is {tcount}')
        if r.status_code==200:
            tcount+=1
        else:
            fcount+=1
    
    return fcount, tcount

def grabUrl(item):
    p=re.compile(r'https:\/\/www\.netflix\.com\/title\/\d+')
    m=p.match(item)
    if m is None:
        return None
    elif type(m.string) == str:
        return m.string

def makeList(inputList,outPutList):
    for i in inputList:
        if type(grabUrl(i)) == str:
            outPutList.append(grabUrl(i))
        else:
            print('Is None')
    return outPutList



movieURLs=[]
    
for id in genereIds:
    i=grabhtml(id)
    makeList(i,movieURLs)


