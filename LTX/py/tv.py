import numpy as np
import sympy as sp


r,h,t,x,y = sp.symbols("r,h,t,x,y")


g = r*((2*t)/(1+t**2)) + h

v = sp.Eq(g, 5)
solutions = sp.solve(v, t)
print(solutions[0].simplify())
print(solutions)