import sympy as sp


k,n = sp.symbols('k n')


expr = 2**(n+1) + (-1)**n +
expr0 = (n**2/(n*(n+1))) + (1/((n+1)*((n+1)+1)))
expr2 = (((k*(k+1))/2)**2) + (k+1)**3
expr.simplify()
expr2.simplify()


print(sp.latex(sp.simplify(expr)))

#print(sp.latex(sp.expand(expr0)))