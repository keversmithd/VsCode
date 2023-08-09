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


#truncated example


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
    return function.diff(symbol,2) * d**2  - (1/12*function.diff(symbol,4) * dt**4).subs(symbol,sub)


u = sympy.Function('u')(x,t)
v = sympy.Function('v')(x, t)
xi, eta = sympy.symbols('xi eta')
def TruncatedTruncationError():
    return (1/2 * u.diff(t,2) * dt).subs(t,eta) - (1/12*u.diff(x,4)*dx**2).subs(x,xi)
     
# a factor of dt/dx^2 appears in the factorized truncated error of the scheme
# since ut = uxx every where, it can be factotred


#eta lies from t and t+dt













