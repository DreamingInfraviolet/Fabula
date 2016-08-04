"""Fabula Tests

Usage:
    test.py [--verbose | -v] [<test>...]
"""

import os
import subprocess
import json
from docopt import docopt

def printGreen(msg):
    print("\033[92m" + str(msg) + "\033[0m")

def printRed(msg):
    print("\033[91m" + str(msg) + "\033[0m")

def printYellow(msg):
    print("\033[93m" + str(msg) + "\033[0m")

if __name__=="__main__":
    #Parse arguments
    arguments = docopt(__doc__, version = "Fabula Tests")
    verbose = arguments["--verbose"] or arguments["-v"]
    tests = arguments["<test>"]

    #If we should run all tests
    if tests == []:
        tests = [f for f in os.listdir('.') if os.path.isdir(f)]

    #Prepare some variables
    tests.sort()
    successes = 0
    failures = 0

    #Run tests
    for folder in tests:

        #Prepare
        print("Running test " + folder)
        if verbose:
            print(os.getcwd())
        os.chdir(folder)

        #Read control json
        json_data = json.load(open("control.json"))

        #Run command
        if subprocess.call(json_data[u"command"], shell=True) != 0:
            printRed("ERROR RUNNING TEST COMMAND `" + json_data[u"command"] + "`")
            continue

        #Get expected and actual
        expectedOutput = open("expected.txt").read().strip()
        actualOutput = ""
        try:
            actualOutput = open("actual.txt").read().strip()
        except IOError:
            printYellow("No output generated")
            actualOutput = "<file not found>"
        else:
            os.remove("actual.txt")

        os.chdir("..")

        passed = None

        passed = expectedOutput.replace(" ", "").replace("\n", "")==actualOutput.replace(" ", "").replace("\n", "")

        if passed:
            successes = successes + 1
            printGreen("PASSED")
        else:
            failures = failures + 1
            printRed("FAILED")
            printRed("Expected: ")
            print(expectedOutput)
            printRed("Actual:   ")
            print(actualOutput)

    #Print summary
    print("Tests completed.")
    if(failures!=0):
        if failures==1:
            printRed("1 failure")
        else:
            printRed(str(failures) + " failures")
    if(failures==0 and successes!=0):
        if successes==1:
            printGreen("1 success")
        else:
            printGreen(str(successes) + " successes")
    elif(successes!=0):
        if successes==1:
            printGreen("1 success")
        else:
            printGreen(str(successes) + " successes")
