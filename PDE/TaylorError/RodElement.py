import sympy
import numpy as np
def RodElementOrdinary():
    #Symbolic Terminology
    #Axial  force in the rod and the external forces must be in equilibrium
    P, sig, E, A, x, F = sympy.symbols('P sig E A x F')
    u = sympy.Function('u')(x)
    eq = sympy.Eq(u.diff(x, 1), -F)
    eq = eq.subs(u,  E*A*u.diff(x,1))
    solution = sympy.dsolve(eq, u)
    print(solution)

def FindingShapeFunctions():
    #back substitution

    c0, c1, c2, c3, c4, x, y, L = sympy.symbols('c0 c1 c2 c3 c4 x y L')
    polynomial = [1, x, x**2, x**3, x**4]
    constants = [c0, c1, c2, c3, c4]
    w = np.dot(polynomial, constants)
    
    c0s = sympy.solve(w.subs(x, 0), c0)[0]
    w = w.subs(c0, c0s)

    c1s = sympy.solve(w.diff(x, 1).subs(x, 0), c1)[0]
    
    #start at the second to last derivative

    dw3 = w.diff(x,3).subs(x,L)

    c3s = sympy.solve(dw3, c3)[0]

    dw2 = w.diff(x,2).subs(x,L).subs(c3, c3s)

    c2s = sympy.solve(dw2, c2)[0]



    

    




    
    
    # four boundary conditions
    # w(0) = 0
    #dw/dx(0) = 0
    
def RodMatrixEquation():
    L = 22
    E = 0.5
    A = 0.3
    F = np.array([10, 400])
    K = np.array([[1, -1], [-1, 1]])

    U, singular_values, V_transpose = np.linalg.svd(K)

    # Calculate the pseudo-inverse of K using SVD
    tolerance = np.finfo(float).eps * max(K.shape)  # Set tolerance based on machine epsilon
    singular_values_inverse = np.where(np.abs(singular_values) > tolerance, 1 / singular_values, 0)
    K_pseudo_inverse = V_transpose.T @ np.diag(singular_values_inverse) @ U.T

    # Solve the system of equations using the pseudo-inverse
    x = ((E * A / L) * K_pseudo_inverse) @ F
    print(x)

def RodMassElement():
    #Unrestrained rod in free longitudinal vibration.
    #In order to model this, this is substituted as a mass times acceleration where p is the mass per unit volume.
    N1, N2, N3, N4, p, A, E, x,t, u = sympy.symbols('N1 N2 N3 N4 p A E x t u')

    u = sympy.Function('u')
    U = u(x,t)
    eq = U.diff(x) +  U.diff(t)
    print(sympy.pdsolve(eq))

    


    

    
RodMassElement()