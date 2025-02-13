"""
Program Name: EECS 348 Assignment 2
Description: The purpose of this assignment is to become more familiar
             with regex syntax, new libraries, and understanding requirements.

Inputs: test file labeled Assignment2_Test_File.txt
Output: matched values from the input file or "no match found"

Collaborators/Sources: Looked at the following resources for guidance on how to use the "re" module
                            https://docs.python.org/3/library/re.html#re.MULTILINE
                            https://www.youtube.com/watch?v=UQQsYXa1EHs
                       specifically found the search() and group() methods through these sources.

Author: Aiman Boullaouz
Creation Date: 02/12/2025
"""

import re

#Here I make a list of all the regex patterns listed in the Assignment 2 Instructions PDF. They are in the same order as they appear on canvas
patterns = [r"..", r"^a", r"^ab", r"a$", r"ma+n", r"b", r"ac", r"^abra", "abra$", r"ca.",
            r"r.*b", r"ac.*a", r"cx?a", r"[a-fXY0-9]", r"[^a-fXY0-9]", r"flea|tick",
            r"(My|Your) (dog|cat)", r"\bDogg\b", r"\d", r"\s", r"\w+"]


#The first 5 regex expressions from the tables are tested with multiple strings
#I am going to use this list to extract the correct number of strings from the test file for those first 5 regex expressions
tables = [4, 3, 2, 3, 5]


#If the test file is in a different order than the tables on canvas this will not work properly


#Opening the test file and cleaning the data
with open("Assignment2_Test_File.txt", "r") as file:
    raw_data = file.readlines()                         #Reading every line in the file and storing as list
    text_data = [x.strip() for x in raw_data]           #Going through all the entries and stripping the new line character



#Using the zip function to iterate through copies of the patterns and tables lists at the same time
#    The pattern variable will get the regex pattern from the list
#    The reps variable will get the number of times the inner loop should run
for pattern, reps in zip(patterns[:], tables[:]):
    print(f"Current Pattern: {pattern}")

    #This inner loop applies the same regex to all the strings that pattern should be used for (from the tables on canvas)
    for i in range(reps):                                   
        matched = re.search(pattern, text_data.pop(0))     #searched for the pattern in the text returned from the pop(). 
                                                           #Popping from front so future loop can continue from where this one ended

        #If we have a match print it to the screen, else print no match found
        if matched:
            print(f"\t{matched.group()}")       #Indenting output because it looks nicer (group() makes the object printable)
        else:
            print("\tno match found")           #Indenting output because it looks nicer
    patterns.pop(0)                                        #Popping from the front of the list so future loop can start where this one ended


#Iterating through the remainder of the patterns and text_data lists at the same time with the zip() function
for pattern, text in zip(patterns, text_data):
    print(f"Current Pattern: {pattern}")
    matched = re.search(pattern, text)          #Applying the regex to the text and storing the result

    if matched:
        print(f"\t{matched.group()}")           #Print the match
    else:
        print("\tno match found")               #Print no match found



"""
If you are grading this and it is not working for you, for more context this is what I was testing my code with:

a
ac
acd
acde
a
abc
bac
abc
acb
a
formula
cab
mn
man
maaan
main
woman
abracadabra
abracadabra
abracadabra
abracadabra
abracadabra
abracadabra
abracadabra
abracadabra
My dog has fleas.
Your dog has fleas.
My dog has fleas.
My dog has fleas.
Snoop Doggy Dogg has fleas.
File your 1040 form!
File your 1040 form!
File your 1040 form!

"""