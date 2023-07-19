import sympy
import math

x,t,dt,dx = sympy.symbols('x t dt dx')



#forward differn etc..
def fd(function, symbol, d):
    return function.subs(symbol, symbol + d) - function

def bd(function, symbol, d):
    return function - function.subs(symbol, symbol - d)

def cd(function, symbol, d):
    return function.subs(symbol, symbol + 1/2*d) - function.subs(symbol, symbol - 1/2*d)

def cd2(function, symbol, d):
    return cd(cd(function, symbol, d), symbol, d)

#double interval central difference
def docd(function, symbol, d):
    return 1/2 * (fd(function, symbol, d) + bd(function, symbol, d)) * function

def fts(function, symbol, d, presc):
    b = 0
    for i in range(0, presc):
        b += function.diff(symbol, i+1)/math.factorial(i+1)*(d**(i+1))
    return b

def bts(function, symbol, d, presc):
    b = 0
    for i in range(0, presc):
        if(i % 2 == 0):
            b -= function.diff(symbol, i+1)/math.factorial(i+1)*(d**(i+1))
        else:
            b += function.diff(symbol, i+1)/math.factorial(i+1)*(d**(i+1))
    return b

def dots(function, symbol, d, presc):
    return fts(function, symbol, d, presc) + bts(function, symbol, d, presc)


def ptrunkts(f):
    z = fts(f, t, dt, 3)
    g = dots(f, x, dx, 4)
    return (z/(dt)-g/(dx**2))


v = sympy.Function('v')(x, t)
# z = fts(v, t, dt, 3)
# g = dots(v, x, dx, 4)

# print("$")
# print(sympy.latex(z))
# print("$")
# print(sympy.latex(g))
# print("$")

# k = (z/(dt)-g/(dx**2))

#truncate the taylor series : section

xi, eta = sympy.symbols('xi eta')

def trunkfts(function, symbol, d, sub):
    function += (1/2*function.diff(symbol,2)*(d**2)).subs(symbol, sub)
    function += function.diff(symbol)*d
    return function

def trunkbts(function, symbol, d, sub):
    function *= -1
    function += (1/2*function.diff(symbol,2)*(d**2)).subs(symbol, sub)
    function -= function.diff(symbol)*d
    return function

def trunkdots(function, symbol, d, sub):
    return trunkfts(function, symbol, d, sub) + trunkbts(function, symbol, d, sub)

print(trunkfts(v, t, dt, eta))













