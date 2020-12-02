
__GRIDSIZE__ = 4

def inBound(x):
    if x < 0 or x >= __GRIDSIZE__: return False
    return True

def around(coord):
    (x,y) = coord
    toret = []
    for (dx,dy) in [(-1,0), (0,1), (1,0), (0,-1)]:
        if inBound(dx+x) and inBound(dy+y):
            toret.append((dx+x, dy+y))
    return toret

def varToStr(symbol, coord):
    return symbol+str(coord[0]) + str(coord[1])

def printConstraint(symbol1, symbol2, coord):
    for (x,y) in around(coord):
      print("-" + varToStr(symbol1, coord) + " " + varToStr(symbol2,(x,y)) + " 0")

def printConstraintNeg(symbol1, symbol2, coord):
    for (x,y) in around(coord):
      print(varToStr(symbol1, coord) + " -" + varToStr(symbol2,(x,y)) + " 0")

def printExclusionConstraint(symbol1, symbol2, coord):
    print(varToStr(symbol1,coord) + " -" + varToStr(symbol2,coord) + " 0")
    print(varToStr(symbol2,coord) + " -" + varToStr(symbol1,coord) + " 0")

def printAllConstraints(coord):
    printConstraint("3", "4", coord) # A Hole implies wind all around
    printConstraint("1", "2", coord) # A Monster implies odors all around
    printConstraintNeg("2", "1", coord) # No Odor means no monster all around
    printConstraintNeg("4", "3", coord) # No wind implies no hole all around
    printExclusionConstraint("1","3",coord) # A cell cannot contain a Monster and a Hole
    printExclusionConstraint("5","3",coord) # A cell cannot contain a Gold and a Hole
    printExclusionConstraint("5","1",coord) # A cell cannot contain a Gold and a Monster

## Now prints all the constaints

for x in range(__GRIDSIZE__):
    for y in range(__GRIDSIZE__):
        printAllConstraints((x,y))



