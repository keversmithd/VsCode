import sympy as sp

import numpy as np

def norm(matrix):
    re = 0
    coeffs = [sp.Symbol('x'), sp.Symbol('y'), sp.Symbol('z')]
    v = 0
    for x in matrix:
        re += x.coeff(coeffs[v])**2 * coeffs[v]
        v += 1
        
    return sp.sqrt(re)

def gradV(eq):
    return sp.Matrix([eq[0].diff(x), eq[1].diff(y), eq[2].diff(z)])

def gradE(eq):
    return sp.Matrix([eq.diff(x), eq.diff(y), eq.diff(z)])

def lapE(eq):
    return eq.diff(x) + eq.diff(y) + eq.diff(z)

pi = sp.pi


# Define symbols
Q, q, r1, r2, r3, rp1, rp2, rp3, dc = sp.symbols('Q q r1 r2 r3 rp1 rp2 rp3 dc')

x,y,z = sp.symbols('x y z')


# Define vectors and potential
# r = r1 * N.i + r2 * N.j + r3 * N.k
# rp = rp1 * N.i + rp2 * N.j + rp3 * N.k

r = sp.Matrix([2*x, 2*y, 3*z])
rp = sp.Matrix([14*x, 5*y, 2*z])

F = (1 / (4 * pi * dc)) * (Q * q / (norm(r - rp)**3))

phi = (1 / (4 * pi * dc)) * q  / norm(r - rp)

Er = -Q*gradE(phi)

#potential energy of test charge Q
W = Q*phi


