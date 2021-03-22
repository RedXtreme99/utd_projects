#   Basil El-Hindi
#   CS 4365.HON
#   Homework 2 CSP Solver
#   main.py

import sys

# Global variable to track branch number for output
branchNum = 0


# Function to print correctly formatted output
def print_output(assignment, success):

    global branchNum
    branchNum += 1
    outstr = str(branchNum) + '. '
    for key, value in assignment.items():
        outstr += str(key) + '=' + str(value) + ', '
    outstr = outstr[:-2]
    if success:
        outstr += '  solution'
    else:
        outstr += '  failure'
    print(outstr)
    if branchNum == 200:
        sys.exit()
    return

# Function to select variable by applying the most constrained heuristic,
# breaking ties with most constraining heuristic, and breaking those ties
# alphabetically.
def select_variable(variables, varMap, constraints):
    
    # If only one variable available, select it
    if len(variables) == 1:
        return variables[0]

    # For each unassigned variable, determine the number of legal values and
    # place all the variables with the smallest domain into mostConstrained
    mostConstrained = []
    domainSize = 999999
    for variable in variables:
        if len(varMap[variable]) < domainSize:
            domainSize = len(varMap[variable])
            mostConstrained.clear()
        if len(varMap[variable]) == domainSize:
            mostConstrained.append(variable)
    # If one variable remains after applying the most constrained heuristic,
    # select that variable
    if len(mostConstrained) == 1:
        return mostConstrained[0]

    # If more variables remain, consider the candidates from applying the most
    # constrained heuristic, and then determine among the remaining unassigned
    # variables which is the most constrained by counting the number of 
    # constraints applied to our candidates
    mostConstraining = []
    constraintCount = 0
    mostConstraints = -1
    for candidate in mostConstrained:
        constraintCount = 0
        for variable in variables:
            if candidate == variable:
                continue
            for constraint in constraints:
                if candidate in constraint and variable in constraint:
                    constraintCount += 1
        if constraintCount > mostConstraints:
            mostConstraints = constraintCount
            mostConstraining.clear()
        if constraintCount == mostConstraints:
            mostConstraining.append(candidate)
    # If one candidate remains, that is most constrained and will be our
    # variable. If more than one remains, sorting will place them
    # alphabetically and we access the first element
    mostConstraining.sort()
    return mostConstraining[0]

# Function to select values for a variable according to least constraining
# value heuristic, breaking ties by smaller value
def select_value(variable, unassigned, varMap, accessed, constraints):
    numConstraining = -1
    leastConstraining = []
    valList = [value for value in varMap[variable] if value not in accessed]
    for value in valList:
        count = 0
        for var in unassigned:
            constrained = False
            for constraint in constraints:
                if variable in constraint and var in constraint:
                    constrained = True
                    if constraint[1] == '>':
                        if variable == constraint[0]:
                            for val in varMap[var]:
                                if value > val:
                                    count += 1
                        else:
                            for val in varMap[var]:
                                if value < val:
                                    count += 1
                    elif constraint[1] == '<':
                        if variable == constraint[0]:
                            for val in varMap[var]:
                                if value < val:
                                    count += 1
                        else:
                            for val in varMap[var]:
                                if value > val:
                                    count += 1
                    elif constraint[1] == '=':
                        for val in varMap[var]:
                            if value == val:
                                count += 1
                    else: # constraint[1] == '!'
                        for val in varMap[var]:
                            if value != val:
                                count += 1
            if not constrained:
                count += len(varMap[var])
        if count > numConstraining:
            numConstraining = count
            leastConstraining.clear()
        if count == numConstraining:
            leastConstraining.append(value)
    leastConstraining.sort()
    return leastConstraining[0]

def isConsistent(variable, value, constraints, assignment):
    for var in assignment.keys():
        if var == variable:
            continue
        for constraint in constraints:
            if variable in constraint and var in constraint:
                if constraint[1] == '>':
                    if variable == constraint[0]:
                        if not value > assignment[var]:
                            return False
                    else:
                        if not value < assignment[var]:
                            return False
                elif constraint[1] == '<':
                    if variable == constraint[0]:
                        if not value < assignment[var]:
                            return False
                    else:
                        if not value > assignment[var]:
                            return False
                elif constraint[1] == '=':
                    if not value == assignment[var]:
                        return False
                else: #constraint[1] == '!'
                    if value == assignment[var]:
                        return False
    return True

# Backtracking recursive function, add a variable to assignment until a
# satisfying assignment is determined via backtracking
def backtrack(varMap, constraints, assignment):

    # Base case: all variables have been assigned a valid value
    # This is a solution
    if len(assignment) == len(varMap):
        print_output(assignment, True)
        sys.exit()
        return

    # Select a variable that has not been assigned yet
    unassigned = [var for var in varMap.keys() if var not in assignment.keys()]
    variable = select_variable(unassigned, varMap, constraints)
    unassigned.remove(variable)

    # Try each value for that variable, choosing values according to heuristic
    accessed = []
    for i in range(0, len(varMap[variable])):
        value = select_value(variable, unassigned, varMap, accessed, constraints)
        assignment[variable] = value
        if isConsistent(variable, value, constraints, assignment):
            backtrack(varMap, constraints, assignment)
        else:
            print_output(assignment, False)
        del assignment[variable]
        accessed.append(value)

    return

# Forward checking recursive function, add a variable to assignment until a
# satisfying assignment is found via forward checking
def forwardcheck(varMap, constraints, assignment):

    return

def main():

    # Check for correct number of inputs
    if not len(sys.argv) == 4:
        print("Incorrect number of command line arguments")
        sys.exit()

    # Check that each input is what is expected
    varfilename = sys.argv[1]
    if not varfilename[-4:] == '.var':
        print("Invalid var file name")
        sys.exit()
    confilename = sys.argv[2]
    if not confilename[-4:] == '.con':
        print("Invalid con file name")
        sys.exit()
    procedure = sys.argv[3]
    if not (procedure == 'fc' or procedure == 'none'):
        print("Invalid procedure given")
        sys.exit()
    
    # Read var file and store variables and their domains in a map
    # varMap is a map of string to integer list
    varfile = open(varfilename, 'r')
    varMap = {}
    for line in varfile:
        key = line[0]
        line = list(map(int, line[3:].split()))
        varMap[key] = line
    varfile.close()

    # Read con file and store constraints as a string list
    # Each element is length 3 with structure VAR OP VAR
    confile = open(confilename, 'r')
    constraints = []
    for line in confile:
        constraints.append(line[0::2])
    confile.close()

    # Call appropriate function based on whether we are solbing using 
    # backtracking or forward checking
    if procedure == 'none':
        backtrack(varMap, constraints, {})
    else:
        forwardcheck(varMap, constraints, {})
    return

if __name__ == "__main__":
    main()
