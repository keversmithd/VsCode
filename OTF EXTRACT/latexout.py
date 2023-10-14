import re

def subnext(string, i, delim):
    delimln = len(delim)
    if(delimln == 1):
        return (string[i] == delim)
    else:
        stringlen = len(string)
        
        j = 0
        while(i < stringlen and j < delimln and string[i] == delim[j]):
            i+=1
            j+=1
        return (j == delimln)

def advnext(string,i,delims):
    delimln = len(delims)
    if(delimln == 1):
        return subnext(string,i,delims[0]),0
    else:
        for j in range(len(delims)):
            if(subnext(string,i,delims[j]) == True):
                return True,j
            
    return False,0

def allcharactersbefore(string, delim):
    s = ""
    for i in range(len(string)):
        if subnext(string,i,delim) == False:
            s += delim
        else:
            return s
    
    return s

def allcharactersbefore(string, ti, delim):
    s = ""
    l = 0
    for i in range(ti,len(string)):
        if subnext(string,i,delim) == False:
            s += string[i]
            l += 1
        else:
            return s,l
    return s,l

def findallchar(string, char):
    j = []
    
    for i in range(len(string)):
        if string[i] == char:
            j.append(i)
    return j

def findallchars(string,ti,char):
    j = []
    for ti in range(len(string)):
        if string[ti] == char:
            j.append(ti)
    return j

def findaroundchars(string, charlocations):
    str = []
    z = ""
    for i in range(len(charlocations)):
        c = ""
        c += string[charlocations[i]-1]
        c += string[charlocations[i]]
        c += string[charlocations[i]+1]
        c += string[charlocations[i]+2]
        str.append(c)
        z+=c

    return str,c

def getafterandbefore(string, i, before, after):

    cool = False
    c = ""
    for i in range(len(string)):
        if subnext(string, i, before):
            Cool = True
        if Cool == True:
            if subnext(string,i,after):
                Cool = False
            else:
                c += string[i]




class texblob:
    macros=[]
    macronames=[]
    macroparameters=[]
    macrobodies=[]
    latex = ""
    body = []
    lastIndex = 0
    def __init__(self,latex):
        with open(latex,"r") as file:
            self.latex  = file.read()
        self.gethead()
        self.getbody()

    def getmacroname(self,ti):
        z = allcharactersbefore(self.latex,ti,"{")
        return z
    
    def defineparams(self,line):
        #isolate = allcharactersbefore(line, '{')
        paramlocation = findallchar(line[0],'#')
        return findaroundchars(line[0], paramlocation)
    
    def printbody(self, i, parms):

        inb=""

        for j in range(len(self.macrobodies[i])):
            if(self.macrobodies[i][j] == "#"):
                parmCode = int(self.macrobodies[i][j+1])
                inb+=parms[parmCode-1]
                j+=1
            else:
                inb+=self.macrobodies[i][j]

        return inb

    def getparams(self,line,i,params):
        parms = []
        c = ""
        l = 0
        for k in range(len(params)):
            if(line[i] == params[k][0]):
                i+=1
                l+=1
                while(i < len(line) and line[i] != params[k][3]): 
                    c += line[i]
                    i+=1
                    l+=1
                l+=1
            parms.append(c)
                
                
            

        return parms,l-1

    def getmacrobody(self,ti):
        open = 0
        b = ""
        l = 0
        inmath = False
        mathdelims = ["$","$$$","\\begin\{equation\}","\\end\{equation\}"]
        b+="\\text{"
        for i in range(ti,len(self.latex)):
            if(self.latex[i] == "%"):
                continue
            MathDelim = advnext(self.latex, i, mathdelims)
            if(MathDelim[0] == True):
                if(inmath == True):
                    inmath == False
                    b+="\\text{"
                else:
                    inmath = True
                    b+="}"
                i += len(mathdelims[MathDelim[1]])
            elif(self.latex[i] == '{'):
                if open > 0:
                    b+=self.latex[i]
                open += 1
            elif(self.latex[i] == '}'):
                if open > 0:
                    b+=self.latex[i]
                open -=1
                if(self.latex[i] == '}' and open == 0):
                    return b,l
                
            else:
                b+=self.latex[i]
            l+=1
        
        return b,l

    def getmacro(self,ti):
        macroname = self.getmacroname(ti)
        bodypack = self.getmacrobody(ti+macroname[1])

        parampack = self.defineparams(macroname)
        
        realmacroname = macroname[0].replace(parampack[1],"").replace('\n',"")
        self.macronames.append(realmacroname)
        self.macroparameters.append(parampack[0])
        self.macrobodies.append(bodypack[0])
        return macroname[1]+bodypack[1]
      
    def gethead(self):
        i = 0
        while i < len(self.latex):
            if subnext(self.latex,i,"\\begin{document}") == False:
                if subnext(self.latex,i,"\\def"):
                    i += 4
                    MacroInformation = self.getmacro(i)
                    i += MacroInformation
            else:
                self.lastIndex = i+16
                return
            i+=1
    
    def getbody(self):
        
        b=""
        inmath = False
        mathdelims = ["$","$$$","\\begin\{equation\}","\\end\{equation\}"]
        b+="\\text{"
        i = self.lastIndex
        while(i < len(self.latex)):
            if(i == 671):
                print("here")
            if(i < len(self.latex) and i+1 < len(self.latex) and self.latex[i] == "\\" and self.latex[i+1] == "\\"):
                if(inmath == False):
                    b+="}"
                    inmath = True
                while(i < len(self.latex) and i+1 < len(self.latex) and self.latex[i] == "\\" and self.latex[i+1] == "\\"):
                    b+="\\\\"
                    i+=2
                b+="\\text{"
                inmath = False

            if(subnext(self.latex, i, "\\end{document}") == True):
                if(inmath == False):
                    b+="}"
                    inmath  = True
                with open("latexout.txt","w") as file:
                    file.write(b)
                return
    
            MathDelim = advnext(self.latex, i, mathdelims)
            if(MathDelim[0] == True):
                if(inmath == True):
                    inmath = False
                    b+="\\text{"
                else:
                    inmath = True
                    b+="}"
                    
                i += len(mathdelims[MathDelim[1]])-1
            else:
                MacroFound = advnext(self.latex,i,self.macronames)
                if(MacroFound[0] == True):
                    MacroParameters = self.macroparameters[MacroFound[1]]
                    i += len(self.macronames[MacroFound[1]])
                    ParameterValues = self.getparams(self.latex,i,MacroParameters)
                    if(inmath == False):
                        b+="}"
                        inmath  = True
                    b += self.printbody(MacroFound[1], ParameterValues[0])
                    
                    if(inmath == True):
                        b+="\\text{"
                        inmath = False

                    inmath = False
                    i += ParameterValues[1]
                else:
                    b+=self.latex[i]
            
            i+=1

        if(inmath == False):
            b+="}"
            inmath  = True
        with open("latexout.txt","w") as file:
                    file.write(b)    
        
            

        


                
            

texblob ("""latexin.txt""")

