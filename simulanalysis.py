"""
Gruppe:
Philipp-Marvin Quach
Camilo Andres Daza Barrios
"""

def simanalysis(input_file,output_file):
    #Define Arrays
    temp = []
    pres = []
    IE = []
    ORM = []

    data = open(input_file).read()
    pos_temp = 0
    pos_pres = 0
    pos_IE = 0
    pos_mol = 0

    while True:
        try:
            pos_temp = data.index("temperature:", pos_temp + 1)
            temp.append(float(data[pos_temp+14:pos_temp+19]))


            pos_pres = data.index("pressure:",pos_pres)
            pres.append(float(data[pos_pres+12:pos_pres+17]))

            pos_IE = data.index("E(intermolecular):",pos_IE)
            IE.append(float(data[pos_IE+20:pos_IE+24]))

            count = 0
            for i in range(1,13):
                if i<10:
                    pos_mol = data.index("molecule 00"+str(i),pos_mol)
                else:
                    pos_mol = data.index("molecule 0"+str(i),pos_mol)


                if data[pos_mol+15:pos_mol+17] == "ye":
                    count += 1

            ORM.append(count)

        except:
            break

    printResult(temp,pres,IE,ORM,output_file)



def mittelwert(arr):
    N = len(arr)
    sum = 0
    for n in arr:
        sum += n

    return float(sum)/N


def standAb(arr,x): # x= mittelwert
    N = len(arr)
    sum = 0
    for n in arr:
        sum += pow(n-x,2)

    return pow((float(sum)/N),(1./2))


def printResult(temp,pres,IE,ORM,output_file):

    tem_mit = mittelwert(temp)
    tem_stand = str(standAb(temp,tem_mit))
    tem_mit = str(tem_mit)

    pres_mit = mittelwert(pres)
    pres_stand = str(standAb(pres,pres_mit))
    pres_mit = str(pres_mit)

    IE_mit = mittelwert(IE)
    IE_stand = str(standAb(IE,IE_mit))
    IE_mit = str(IE_mit)

    ORM_mit = mittelwert(ORM)
    ORM_stand = str(standAb(ORM,ORM_mit))
    ORM_mit = str(ORM_mit)


    f = open(output_file,'w')
    f.write("=== ERGEBNISSE ===\n")
    f.write(" - Temperatur: "+tem_mit+" +/- "+tem_stand+"\n")
    f.write("   Wertebereich: "+str(min(temp))+" - "+str(max(temp))+"\n")
    f.write(" - Druck: "+pres_mit+" +/- "+pres_stand+"\n")
    f.write("   Wertebereich: "+str(min(pres))+" - "+str(max(pres))+"\n")
    f.write(" - intermolekulare Energie: "+IE_mit+" +/- "+IE_stand+"\n")
    f.write("   Wertebereich: "+str(min(IE))+" - "+str(max(IE))+"\n")
    f.write(" - Molekuele ausser Reichweite: "+ORM_mit+" +/- "+ORM_stand+"\n")
    f.write("   Wertebereich: "+str(min(ORM))+" - "+str(max(ORM))+"\n")

defaultinput="simulation_data.txt"
defaultoutput="simulation_analysis.out"
inputfile = input("enter input-file-name. empty for defaultname:\n");
outputfile = input("enter output-file-name. empty for defaultname:\n");

if inputfile == '' and outputfile == '':
	simanalysis(defaultinput,defaultoutput)
elif inputfile == '':
	simanalysis(defaultinput,outputfile)
elif outputfile == '':
	simanalysis(inputfile,defaultoutput)
else:
	simanalysis(inputfile,outputfile)

