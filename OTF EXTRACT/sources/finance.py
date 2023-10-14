import os




check = "C:/Users/Dust/Desktop/ChaseChecking.CSV"
file1 = open(check,'r')
checkdata = file1.readlines()

Categories = checkdata[0].split(',')
datas = []


for i in range(len(checkdata)):
    if i == 0:
        continue
    else:
        dataslip = checkdata[i].split(',')
        
        datas.append(dataslip)








