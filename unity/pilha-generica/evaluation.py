import xml.etree.ElementTree as ET
import sys

def commentLong( line ):
    print( "<|--\n" + line  + "\n --|>" )

def commentShort( text ):
    print( "Comment :=>> " + text )

def printGrade( grade ):
    print( "Grade :=>> ", grade )

def checkForFunctionPresence( module, functionName ):
    foundCall = False

    for line in open( module+".c", "r").readlines():
		# remove comments
        idx = line.find( "//" )
        if ( idx >=0 ): line = line[0:idx]
        idx = line.find( "/*" )
        if ( idx >=0 ): line = line[0:idx]

        if line.find( functionName+"(" ) != -1:
            foundCall = True
            continue
        if line.find( functionName+" (" ) != -1:
            foundCall = True
            continue
        if line.find( functionName+"  (" ) != -1:
            foundCall = True
            continue
    return (foundCall)

def analyze_valgrind_xml(file):
	count = 0
	tree = ET.ElementTree()
	tree.parse(file)
	root = tree.getroot()
	for n in root.findall('error'):
		for t in n.findall('kind'):
#			print t.text
			if t.text == "Leak_DefinitelyLost":
				count = count + 1
#	print count
	return count

def call_analyze():
    #analyze_valgrind_xml("teste-leak.xml")
    erros = analyze_valgrind_xml("leak-memcheck.xml")
    if(erros>0):
        print ("Comment :=>> Erros de vazamento de memoria: %d." % (erros)) 
    nota = float(sys.argv[1])
    if(erros == 1):
        nota = nota * 0.8
        print ("Comment :=>> Penalidade de 20%.") 
    if(erros > 1):
        nota = nota * 0.6
        print ("Comment :=>> Penalidade de 40%.") 
    nota_int = int(nota)
    diff_float = nota-nota_int
    if(diff_float < 0.25):
        nota=nota_int
    elif (diff_float<0.75):
        nota=float(nota_int+0.5)
    else:
        nota=nota_int+1
    return nota

def checkForGlobalVariablePresence(file_name):
	f = open(file_name, 'r')
	has_global = False
	for line in f:
		array_line = line.split("|")
		array_line[2] = str.strip(array_line[2])
		array_line[3] = str.strip(array_line[3])
		if (array_line[2] == "C" or array_line[2] == "U" or array_line[2] == "b" or array_line[2] == "D") and array_line[3] == "OBJECT":
			has_global = True
			commentShort("Variavel global \""+str.strip(array_line[0])+"\" usada no programa.")
	return has_global

#===========================================
nota = call_analyze()
commentShort("Acabou a avaliacao de vazamento de memoria.")
commentShort("Iniciando a avaliacao da funcao exit.")
for i in range(2, len(sys.argv)):
	tem_exit = checkForFunctionPresence(sys.argv[i],"exit")
	if(tem_exit):
		commentShort("O teu codigo nao pode ter uma chamada da funcao >>exit<<");
		nota = 0
commentShort("Acabou a avaliacao da funcao exit.")
commentShort("Comment :=>> Iniciando avaliacao de variavel global.")
has_global = checkForGlobalVariablePresence("global.txt")
if(has_global):
	commentShort("O teu codigo tem variavel global (-5).");
	nota = nota - 5
commentShort("Acabou a avaliacao de variavel global.")
commentShort("Comment :=>> Iniciando avaliacao do uso das operacoes de pilha.")
funcoes = ["pilha_cria", "pilha_destroi", "pilha_empilha", "pilha_desempilha", "pilha_vazia"]
for func in funcoes:
	usou_funcao = checkForFunctionPresence(sys.argv[2], func)
	if(usou_funcao == False):
		commentShort("A sua solucao para o problema do estacionamento nao esta completa. Utilize as operacoes ou existem operacoes nao utilizadas do TDA pilha generico (0).");
		#nota = 0 #somente dar zero se o problema for resolvido
commentShort("Acabou a avaliacao do uso das operacoes de pilha.")
if(nota < 0):
	nota = 0
print ("Grade :=>> %.1f" % (nota))
	
