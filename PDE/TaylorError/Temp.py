import sympy as sp

x,t,c = sp.symbols('x t c')

U = sp.Function('U')(x,t)


E = sp.Eq(U.diff(t), c*U.diff(x,2))
initial_condition = sp.Eq(U.subs(t,0), 0)
solution = sp.dsolve(E, ics={initial_condition})

print(solution)



