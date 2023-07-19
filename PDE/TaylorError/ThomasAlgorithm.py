#Thomas Algorithm : Solving

import Truncation

import sympy



#def of function
x,t, dx, mu = sympy.symbols('x t dx mu')
U = sympy.Function('U')(x,t)

U1 = U.subs(t, t+1)

#n = time
#j = space


#visual system of equations
print(U1)


