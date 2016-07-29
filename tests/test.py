"""Fabula Tests

Usage:
    test.py [--verbose | -v] [<test>...]
"""

import os
import subprocess
import json
from docopt import docopt

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
        print("\033[95mRunning test " + folder)
        if verbose:
        	print(os.getcwd())
        os.chdir(folder)

        #Read control json
        json_data = json.load(open("control.json"))

        #Run command
        if subprocess.call(json_data[u"command"], shell=True) != 0:
            print("\033[91mERROR RUNNING TEST COMMAND `" + json_data[u"command"] + "`")
            continue

        #Get expected and actual
        expectedOutput = open("expected.txt").read().strip()
        actualOutput = open("actual.txt").read().strip()
        os.remove("actual.txt")
        os.chdir("..")

        #Print result
        if verbose:
            print("Expected: " + expectedOutput)
            print("Actual:   " + actualOutput)

        expect_success = json_data[u"expect_success"]
        passed = (expectedOutput==actualOutput)
        passed = passed == expect_success

        if verbose:
            if expect_success:
                print("Testing Actual = Expected")
            else:
                print("Testing Actual != Expected")

        if passed:
            successes = successes + 1
            print("\033[92mPASSED")
        else:
            failures = failures = 1
            print("\033[91mFAILED")

    #Print summary
    print("Tests completed.")
    if(failures!=0):
        if failures==1:
            print("\033[91m1 failure")
        else:
            print("\033[91m" + str(failures) + " failures")
    if(failures==0 and successes!=0):
        if successes==1:
            print("\033[92m1 success")
        else:
            print("\033[92m" + str(successes) + " successes")
    elif(successes!=0):
        if successes==1:
            print("\033[93m1 success")
        else:
            print("\033[93m" + str(successes) + " successes")
