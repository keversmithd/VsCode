import re




def integerReplace():

    input = """void CharStringInsert0(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex0, uint8_t& floatIndex0, int& Index0, uint64_t& DataIndex0, uint8_t& DataEntries);
        void CharStringInsert1(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex1, uint8_t& floatIndex1, int& Index1, uint64_t& DataIndex1, uint8_t& DataEntries);
        void CharStringInsert2(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex2, uint8_t& floatIndex2, int& Index2, uint64_t& DataIndex2, uint8_t& DataEntries);
        void CharStringInsert3(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex3, uint8_t& floatIndex3, int& Index3, uint64_t& DataIndex3, uint8_t& DataEntries);
        void CharStringInsert4(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex4, uint8_t& floatIndex4, int& Index4, uint64_t& DataIndex4, uint8_t& DataEntries);
        void CharStringInsert5(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex5, uint8_t& floatIndex5, int& Index5, uint64_t& DataIndex5, uint8_t& DataEntries);
        void CharStringInsert6(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex6, uint8_t& floatIndex6, int& Index6, uint64_t& DataIndex6, uint8_t& DataEntries);
        void CharStringInsert7(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex7, uint8_t& floatIndex7, int& Index7, uint64_t& DataIndex7, uint8_t& DataEntries);
        void CharStringInsert8(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex8, uint8_t& floatIndex8, int& Index8, uint64_t& DataIndex8, uint8_t& DataEntries);
        void CharStringInsert9(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex9, uint8_t& floatIndex9, int& Index9, uint64_t& DataIndex9, uint8_t& DataEntries);
        void CharStringInsert10(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex10, uint8_t& floatIndex10, int& Index10, uint64_t& DataIndex10, uint8_t& DataEntries);
        void CharStringInsert11(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex11, uint8_t& floatIndex11, int& Index11, uint64_t& DataIndex11, uint8_t& DataEntries);
        void CharStringInsert12(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex12, uint8_t& floatIndex12, int& Index12, uint64_t& DataIndex12, uint8_t& DataEntries);
        void CharStringInsert13(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex13, uint8_t& floatIndex13, int& Index13, uint64_t& DataIndex13, uint8_t& DataEntries);
        void CharStringInsert14(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex14, uint8_t& floatIndex14, int& Index14, uint64_t& DataIndex14, uint8_t& DataEntries);
        void CharStringInsert15(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex15, uint8_t& floatIndex15, int& Index15, uint64_t& DataIndex15, uint8_t& DataEntries);
        void CharStringInsert16(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex16, uint8_t& floatIndex16, int& Index16, uint64_t& DataIndex16, uint8_t& DataEntries);
        void CharStringInsert17(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex17, uint8_t& floatIndex17, int& Index17, uint64_t& DataIndex17, uint8_t& DataEntries);
        void CharStringInsert18(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex18, uint8_t& floatIndex18, int& Index18, uint64_t& DataIndex18, uint8_t& DataEntries);
        void CharStringInsert19(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex19, uint8_t& floatIndex19, int& Index19, uint64_t& DataIndex19, uint8_t& DataEntries);
        void CharStringInsert20(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex20, uint8_t& floatIndex20, int& Index20, uint64_t& DataIndex20, uint8_t& DataEntries);
        void CharStringInsert21(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex21, uint8_t& floatIndex21, int& Index21, uint64_t& DataIndex21, uint8_t& DataEntries);
        void CharStringInsert22(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex22, uint8_t& floatIndex22, int& Index22, uint64_t& DataIndex22, uint8_t& DataEntries);
        void CharStringInsert23(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex23, uint8_t& floatIndex23, int& Index23, uint64_t& DataIndex23, uint8_t& DataEntries);
        void CharStringInsert24(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex24, uint8_t& floatIndex24, int& Index24, uint64_t& DataIndex24, uint8_t& DataEntries);
        void CharStringInsert25(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex25, uint8_t& floatIndex25, int& Index25, uint64_t& DataIndex25, uint8_t& DataEntries);
        void CharStringInsert26(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex26, uint8_t& floatIndex26, int& Index26, uint64_t& DataIndex26, uint8_t& DataEntries);
        void CharStringInsert27(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex27, uint8_t& floatIndex27, int& Index27, uint64_t& DataIndex27, uint8_t& DataEntries);
        void CharStringInsert28(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex28, uint8_t& floatIndex28, int& Index28, uint64_t& DataIndex28, uint8_t& DataEntries);
        void CharStringInsert29(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex29, uint8_t& floatIndex29, int& Index29, uint64_t& DataIndex29, uint8_t& DataEntries);
        void CharStringInsert30(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex30, uint8_t& floatIndex30, int& Index30, uint64_t& DataIndex30, uint8_t& DataEntries);
        void CharStringInsert31(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex31, uint8_t& floatIndex31, int& Index31, uint64_t& DataIndex31, uint8_t& DataEntries);
        void CharStringInsert32(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex32, uint8_t& floatIndex32, int& Index32, uint64_t& DataIndex32, uint8_t& DataEntries);
        void CharStringInsert33(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex33, uint8_t& floatIndex33, int& Index33, uint64_t& DataIndex33, uint8_t& DataEntries);
        void CharStringInsert34(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex34, uint8_t& floatIndex34, int& Index34, uint64_t& DataIndex34, uint8_t& DataEntries);
        void CharStringInsert35(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex35, uint8_t& floatIndex35, int& Index35, uint64_t& DataIndex35, uint8_t& DataEntries);
        void CharStringInsert36(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex36, uint8_t& floatIndex36, int& Index36, uint64_t& DataIndex36, uint8_t& DataEntries);
        void CharStringInsert37(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex37, uint8_t& floatIndex37, int& Index37, uint64_t& DataIndex37, uint8_t& DataEntries);
        void CharStringInsert38(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex38, uint8_t& floatIndex38, int& Index38, uint64_t& DataIndex38, uint8_t& DataEntries);
        void CharStringInsert39(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex39, uint8_t& floatIndex39, int& Index39, uint64_t& DataIndex39, uint8_t& DataEntries);
        void CharStringInsert40(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex40, uint8_t& floatIndex40, int& Index40, uint64_t& DataIndex40, uint8_t& DataEntries);
        void CharStringInsert41(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex41, uint8_t& floatIndex41, int& Index41, uint64_t& DataIndex41, uint8_t& DataEntries);
        void CharStringInsert42(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex42, uint8_t& floatIndex42, int& Index42, uint64_t& DataIndex42, uint8_t& DataEntries);
        void CharStringInsert43(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex43, uint8_t& floatIndex43, int& Index43, uint64_t& DataIndex43, uint8_t& DataEntries);
        void CharStringInsert44(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex44, uint8_t& floatIndex44, int& Index44, uint64_t& DataIndex44, uint8_t& DataEntries);
        void CharStringInsert45(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex45, uint8_t& floatIndex45, int& Index45, uint64_t& DataIndex45, uint8_t& DataEntries);
        void CharStringInsert46(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex46, uint8_t& floatIndex46, int& Index46, uint64_t& DataIndex46, uint8_t& DataEntries);
        void CharStringInsert47(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex47, uint8_t& floatIndex47, int& Index47, uint64_t& DataIndex47, uint8_t& DataEntries);
        void CharStringInsert48(PPCFFCharstring& CharData, float* floatStack, int32_t* intStack, uint8_t& intIndex48, uint8_t& floatIndex48, int& Index48, uint64_t& DataIndex48, uint8_t& DataEntries);"""

    words_to_find = [
        "intIndex",
        "floatIndex",
        "Index",
        "DataIndex"
    ]

    patterns = []

    for i in range(len(words_to_find)):
        patterns.append(re.compile(rf'{words_to_find[i]}\d+'))

    result_text = input
    for i in range(len(patterns)):
        result_text = patterns[i].sub(words_to_find[i], result_text)

    print(result_text)


def paramadd(data):
    nestlevel = 0
    param = "Vectoid2& OriginOfPath"
    ndata = ""
    print(len(data))
    for i in range(len(data)):
        if(nestlevel == 0 and data[i] == ')'):
            ndata += ", " + param
            ndata += ')'
        else:
            ndata += data[i]
        
        if(data[i] == '{'):
            nestlevel += 1
        if(data[i] == '}'):
            nestlevel -= 1
    with open("bufferskip.txt",'w') as file:
        file.write(ndata)




def getfuncname(prototype):
    n = ""
    o = False
    c = False
    for i in range(len(prototype)):
        if(prototype[i] == '('):
            c = True
            break
        else:
            if(prototype[i] == ' '):
                o = True
            elif(o == True):
                n += prototype[i]
    return n
def getclassname(header):
    pattern = r"struct\s+(\S+)"
    match = re.search(pattern, header)
    extracted_string = match.group(1)
    return extracted_string



def importpref(prototype, prefix):
    n = ""
    c = False
    for i in range(len(prototype)):
        if(prototype[i] == ' ' and c == False):
            n += " " + prefix + "::"
            c = True
        else:
            n += prototype[i]
    return n

def makexproto(prototype, x, pref=""):
    s = ""
    h = ""
    a = ""

    
    functionname = getfuncname(prototype)
    sourceprototype = ""
    if(pref == ""):
        sourceprototype = prototype
    else:
        sourceprototype = importpref(prototype, pref)

    for i in range(x):
        a += functionname + str(i)

        for j in range(len(sourceprototype)):
            if(sourceprototype[j] == '('):
                h+=str(i)
            if(sourceprototype[j] == ';' or (sourceprototype[j] == ')' and j+1 > len(sourceprototype)-1)):
                h += "{}"
            else:
                h += sourceprototype[j]

            if(j <= len(prototype)-1):
                if(prototype[j] == '('):
                    s+=str(i)
                s += prototype[j]
                if(prototype[j] == ')' and j+1 > len(prototype)-1):
                    s+=";"
        s+='\n'
        h+='\n'
        a+=', '
    
    print(s)

    print(h)

    print(a)


def insertcommands(sourcelist,command,nums = 0):
    open = 0
    insertion = ""
    e = 0
    
    for i in range(len(sourcelist)):

        if sourcelist[i] == '}' and open == True:
            if nums != 0:
                insertion += command.replace(re.search(r"([0-9]+)",command).group(),str(nums[e]))
            else:
                insertion += command.replace(re.search(r"([0-9]+)",command).group(),str(e))
            e+=1
            open = False
        insertion += sourcelist[i]
        if sourcelist[i] == '{' and open == False:
            open = True
        
        
    
    print(insertion)
        
nums =["0","2","4","6","8","10","12","13","14"]
         
insertcommands("""if(format=0){
            EncodingRecordFormat0 RF = F_EncodingRecordFormat0(_F);
        }
        if(format=2){
        EncodingRecordFormat2 RF = F_EncodingRecordFormat2(_F);}
        if(format=4){
        EncodingRecordFormat4 RF = F_EncodingRecordFormat4(_F);}
        if(format=6){
        EncodingRecordFormat6 RF = F_EncodingRecordFormat6(_F);}
        if(format=8){
        EncodingRecordFormat8 RF = F_EncodingRecordFormat8(_F);}
        if(format=10){
        EncodingRecordFormat10 RF = F_EncodingRecordFormat10(_F);}
        if(format=12){
        EncodingRecordFormat12 RF = F_EncodingRecordFormat12(_F);}
        if(format=13){
        EncodingRecordFormat13 RF = F_EncodingRecordFormat13(_F);}
        if(format=14){
        EncodingRecordFormat14 RF = F_EncodingRecordFormat14(_F);}""", "HandleRecordFormat0(RF);",nums)



def makematch(string, i, match):
    e = 0
    while(string[i] == match[e] and e < len(match)):
        if(e == len(match)-1):
            return True
        i += 1
        e += 1

    return False

def absorbparamters(prototype):
    looking = False
    found = False
    classname = getclassname(prototype)
    paramaters = ""
    for i in range(len(prototype)):
        if(looking == True):
            found = makematch(prototype,i,classname)
            if(found == True):
                break
            paramaters+=prototype[i] 
        if(prototype[i] == '{'):
            looking = True
        if(found == True):
            break

    s = paramaters.split(' ')
    stringfind = ";"
    filtered_list = [c.split(';')[0] for c in s if stringfind in c]
    return filtered_list

def makebool(str1):
    arr = str1.split(' ')
    b = ""

    for i in range(len(arr)):
        t = arr[i].split('&')
        
        if(len(t) > 1):
            b += "("+str(i+1)+"*(data[i] == " + t[0] + " && " + "data[i+1] == " + t[1]+")" + ")" + " + "
        else:
            b += "("+str(i+1)+"*(data[i] == " + arr[i] + ")" + ")" + " + "

    print(b)


# n = getfuncname("void PrivateOperatorExtraction(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);")

# makexproto("void PrivateOperatorExtraction(PPCFFPrivateData& DictData, float* floatStack, int32_t* intStack, uint8_t& intIndex, uint8_t& floatIndex, int& index, uint64_t& DataIndex, uint8_t& DataEntries);", 18, "PPCFF")

def getformatstyles(string):
    lines = string.split('\n')

    print(lines[0].split('\t'))
    s = ""
    pz = []

    pattern = r"\[(.*?)\]"
    for i in range(len(lines)):
        x = lines[i].split('\t')
        if(len(x) < 2):
            x = ""
        else:    
            z = x[1]
            b = x[0]
            
            if("[ ]" in x[1]):
                z = x[1].replace("[ ]", "")
                b += "*"
            
            
            s += b + " " + z + " = 0;" "\n"
            pz.append(z)
    

    inner = re.findall(pattern,s)
    for match in inner:
        match = inner[0]
        local_pattern = "(\S+) (\S+)\[" +match +"\]"
        subber = re.findall(local_pattern,s)
        for sub in subber:
            a = sub[0] + "* "
            b = sub[1].replace("[" + match + "]","")
            s = s.replace(sub[0]+" "+sub[1]+"[" + match + "]", a+b)
                

    
        

    print(s)
    return

# getformatstyles("""uint16	endPtsOfContours[numberOfContours]	Array of point indices for the last point of each contour, in increasing numeric order.
# uint16	instructionLength	Total number of bytes for instructions. If instructionLength is zero, no instructions are present for this glyph, and this field is followed directly by the flags field.
# uint8	instructions[instructionLength]	Array of instruction byte code for the glyph.
# uint8	flags[variable]	Array of flag elements. See below for details regarding the number of flag array elements.
# uint8 or int16	xCoordinates[variable]	Contour point x-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.
# uint8 or int16	yCoordinates[variable]	Contour point y-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.""")

def cmapextract(string, structure, filename):
    lines = string.split('\n')
    pz = []
    emisize = 0
    s = ""

    pattern = r"\[(.*?)\]"
    for i in range(len(lines)):
        x = lines[i].split('\t')
        if(len(x) < 2):
            x = ""
        else:
            z = x[1]
            b = x[0]

            if("[ ]" in x[1]):
                z = x[1].replace("[ ]", "")
                b += "*"



            match = re.search(pattern,z)
            if match:
                match = match.group().strip(']').strip('[')
                for i in range(len(pz)):
                    Parameter = pz[i]
                    if match in Parameter:
                        if "X2" in Parameter:
                            emisize = structure+"."+Parameter + "/2"
                        else:
                            emisize = structure+"."+Parameter
                        break
                s += structure + "." + z.replace("[" + match + "]", "") + " = (" + b + "*)malloc(sizeof(" + b + ") * " + str(emisize) + ");\n"
                s += "fread("+structure+"."+z.replace("[" + match + "]", "")+",sizeof("+b+"),"+str(emisize)+","+str(filename)+");\n" 
            else:
                if(b == "uint8"):
                    s += structure + "." + z + " = ReadE("+filename+");\n"
                if(b == "int8"):
                    s += structure + "." + z + " = ReadIE("+filename+");\n"
                if(b == "uint16"):
                    s += structure + "." + z + " = ReadST("+filename+");\n"
                if(b == "int16"):
                    s += structure + "." + z + " = ReadIST("+filename+");\n"
                if(b == "uint32"):
                    s += structure + "." + z + " = ReadTT("+filename+");\n"
                if(b == "int32"):
                    s += structure + "." + z + " = ReadITT("+filename+");\n"
            pz.append(z)

    print(s)

cmapextract("""int16	xMin	Minimum x for coordinate data.
int16	yMin	Minimum y for coordinate data.
int16	xMax	Maximum x for coordinate data.
int16	yMax	Maximum y for coordinate data.""", "Glyf","F")

def buildconversions(strings):
    for i in range(len(strings)):
        print("void "+strings[i]+"Convert(void* self, void* userptr)\n{\n}\n")

def makestring(nums,s,z=0):
    
    for i in range(len(nums)):
        i = str(nums[i])
        v = s
        pattern = r"([0-9])+"
        numeric = re.search(pattern,v)
        g = numeric.group()
        if numeric:
            v = v.replace(numeric.group(),i)
        if z != 0:
            v+=';'
        print(v)


pb = """EncodingRecordFormat0 F_EncodingRecordFormat0(FILE* F)
{
    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.glyphIdArray = (uint8*)malloc(sizeof(uint8) * 0);
    fread(Record.glyphIdArray,sizeof(uint8),0,F);

}
EncodingRecordFormat2 F_EncodingRecordFormat2(FILE* F)
{
    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.subHeaderKeys = (uint16*)malloc(sizeof(uint16) * 0);
    fread(Record.subHeaderKeys,sizeof(uint16),0,F);
}
EncodingRecordFormat4 F_EncodingRecordFormat4(FILE* F)
{
    EncodingRecordFormat4 Record;
    Record.format = 4;
    
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.segCountX2 = ReadST(F);
    Record.searchRange = ReadST(F);
    Record.entrySelector = ReadST(F);
    Record.rangeShift = ReadST(F);
    Record.endCode = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);
    fread(Record.endCode,sizeof(uint16),Record.segCountX2/2,F);
    Record.reservedPad = ReadST(F);
    Record.startCode = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);
    fread(Record.startCode,sizeof(uint16),Record.segCountX2/2,F);
    Record.idDelta = (int16*)malloc(sizeof(int16) * Record.segCountX2/2);
    fread(Record.idDelta,sizeof(int16),Record.segCountX2/2,F);
    Record.idRangeOffsets = (uint16*)malloc(sizeof(uint16) * Record.segCountX2/2);
    fread(Record.idRangeOffsets,sizeof(uint16),Record.segCountX2/2,F);
    int glyphIdArraySize = Record.idRangeOffsets[(Record.segCountX2/2)-1] - Record.idRangeOffsets[0];

    return Record;

}
EncodingRecordFormat6 F_EncodingRecordFormat6(FILE* F)
{
    Record.format = ReadST(F);
    Record.length = ReadST(F);
    Record.language = ReadST(F);
    Record.firstCode = ReadST(F);
    Record.entryCount = ReadST(F);
    Record.glyphIdArray = (uint16*)malloc(sizeof(uint16) * Record.entryCount);
    fread(Record.glyphIdArray,sizeof(uint16),Record.entryCount,F);
}
EncodingRecordFormat8 F_EncodingRecordFormat8(FILE* F)
{
    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.is32 = (uint8*)malloc(sizeof(uint8) * 0);
    fread(Record.is32,sizeof(uint8),0,F);
    Record.numGroups = ReadTT(F);
    Record.groups = (SequentialMapGroup*)malloc(sizeof(SequentialMapGroup) * Record.numGroups);
    fread(Record.groups,sizeof(SequentialMapGroup),Record.numGroups,F);
}
EncodingRecordFormat10 F_EncodingRecordFormat10(FILE* F)
{
    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.startCharCode = ReadTT(F);
    Record.numChars = ReadTT(F);
    Record.glyphIdArray = (uint16*)malloc(sizeof(uint16) * Record.format);
    fread(Record.glyphIdArray,sizeof(uint16),Record.format,F);
}
EncodingRecordFormat12 F_EncodingRecordFormat12(FILE* F)
{
    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.numGroups = ReadTT(F);
    Record.groups = (SequentialMapGroup*)malloc(sizeof(SequentialMapGroup) * Record.numGroups);
    fread(Record.groups,sizeof(SequentialMapGroup),Record.numGroups,F);
}
EncodingRecordFormat13 F_EncodingRecordFormat13(FILE* F)
{
    Record.format = ReadST(F);
    Record.reserved = ReadST(F);
    Record.length = ReadTT(F);
    Record.language = ReadTT(F);
    Record.numGroups = ReadTT(F);
    Record.groups = (ConstantMapGroup*)malloc(sizeof(ConstantMapGroup) * Record.numGroups);
    fread(Record.groups,sizeof(ConstantMapGroup),Record.numGroups,F);
}
EncodingRecordFormat14 F_EncodingRecordFormat14(FILE* F)
{
    Record.format = ReadST(F);
    Record.length = ReadTT(F);
    Record.numVarSelectorRecords = ReadTT(F);
    Record.varSelector = (VariationSelector*)malloc(sizeof(VariationSelector) * Record.numVarSelectorRecords);
    fread(Record.varSelector,sizeof(VariationSelector),Record.numVarSelectorRecords,F);
}"""

z = ""
e = 0
for i in range(len(pb)):
    char = pb[i]
    if(char == '{'):
        z += "{\n\tEncodingRecordFormat"+str(e)+" Record;\n\tRecord.format = " + str(e) + ";\n"
        e += 2
    else:
        z+= char

print(z)

def destroyswitch(switchstatement):

    
    switchstatement = switchstatement.replace("break;","")
    switchpat = re.search(r"switch\((\S+)\)",switchstatement)
    detox = re.search(r"\((\S+)\)",switchpat.group())
    inner = detox.group().strip('(').strip(')')

    itotype = inner

    switchstatement = switchstatement.replace(switchpat.group(), "")


    printeddocument = ""

    cases = []
    lines = switchstatement.split('\n')
    for i in range(len(lines)):
        case = re.search(r"case ([0-9]+):",lines[i])
        
        if case:
            caseinnervalue = re.search(r"([0-9]+)", case.group())
            cases.append(case)
            lines[i] = lines[i]
            lines[i] = lines[i].replace(case.group(),  "}\nif("+itotype+"=="+caseinnervalue.group()+");{\n")
            printeddocument += lines[i].strip(' ')
        else:
            printeddocument += lines[i].strip(' ')
        
    print(printeddocument)




