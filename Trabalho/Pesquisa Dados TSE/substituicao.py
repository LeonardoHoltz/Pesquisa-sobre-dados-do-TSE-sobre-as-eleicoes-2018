file_in = open("candidatos_2018_BRASIL.csv", 'r')
file_out = open("candidatos_2018_BRASIL_updated.csv", 'w+')

for line in file_in:
	line = line.replace("ã","a")
	line = line.replace("á","a")
	line = line.replace("à","a")
	line = line.replace("â","a")
	line = line.replace("ä","a")
	
	line = line.replace("Ã","A")
	line = line.replace("Á","A")
	line = line.replace("À","A")
	line = line.replace("Â","A")
	line = line.replace("Ä","A")
	
	line = line.replace("é","e")
	line = line.replace("è","e")
	line = line.replace("ê","e")
	line = line.replace("ë","e")
	
	line = line.replace("É","E")
	line = line.replace("È","E")
	line = line.replace("Ê","E")
	line = line.replace("Ë","E")
	
	line = line.replace("í","i")
	line = line.replace("ì","i")
	line = line.replace("î","i")
	line = line.replace("ï","i")
	
	line = line.replace("Í","I")
	line = line.replace("Ì","I")
	line = line.replace("Î","I")
	line = line.replace("Ï","I")
	
	line = line.replace("õ","o")
	line = line.replace("ó","o")
	line = line.replace("ò","o")
	line = line.replace("ô","o")
	line = line.replace("ö","o")

	line = line.replace("Õ","O")
	line = line.replace("Ó","O")
	line = line.replace("Ò","O")
	line = line.replace("Ô","O")
	line = line.replace("Ö","O")
	
	line = line.replace("ú","u")
	line = line.replace("ù","u")
	line = line.replace("û","u")
	line = line.replace("ü","u")
	
	line = line.replace("Ú","U")
	line = line.replace("Ù","U")
	line = line.replace("Û","U")
	line = line.replace("Ü","U")
	
	line = line.replace("ç","c")
	line = line.replace("Ç","C")
	
	line = line.replace("ñ","n")
	line = line.replace("Ñ","N")
	
	file_out.write(line)
	
file_in.close()
file_out.close()