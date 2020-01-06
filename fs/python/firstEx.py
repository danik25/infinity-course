#!/usr/bin/python

def main():
    #ans = isLeapYear()
    #print ans
    #isLong(3)
    #flip(12)
    #print grade(95)

    #print(rec_factorial(4))
    a = [66.25, 333, 333, 1, 1234.5]
    print a.count(333), a.count(66.25), a.count('x')

def rec_factorial(num):
    if(num == 1):
        return 1;

    return num * rec_factorial(num - 1)
def isLeapYear():
    year = int(raw_input( "enter year: " ))

    if(year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)):
        return "leap year!"

    return "no!"

def isLong(num):

    print type(num) == long

def flip(num):
    newNum = 0

    while(num > 0):
        newNum *= 10
        newNum += num % 10
        num /= 10

    print newNum

def grade(num):
    if(num <= 10):
        return "F"
    elif(num <= 30):
        return "E"
    elif(num <= 50):
        return "D"
    elif(num <= 70):
        return "C"
    elif(num <= 90):
        return "B"
    else:
        return "A"
    
    

main()
