# First we need to print clauses
def printClause(clause):
    print(" ".join([str(v) for v in clause]) + " 0")

def equals1a(arrayOfVars):
    printClause(arrayOfVars) 
    for i,x in enumerate(arrayOfVars):
        for y in arrayOfVars[i+1:]:
            printClause([-x, -y])

coord = [(i, j) for i in range(1, 10) for j in range(1, 10)]

def printConstraint(symbol1, symbol2, coord):
    for (x,y) in coord:
        print("un truc")
        
def varToStr(symbol, coord):
    return str(coord[0]) + str(coord[1]) + symbol



