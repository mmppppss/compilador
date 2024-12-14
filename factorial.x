escribir("Calculo de factorial")
escribir("Ingrese un numero: ")
leer(n)
escribir("calculo de factorial de ", n)
fact = 1
i = 1
si i <= n entonces
	escribir("f: ",fact)
	fact = fact * i
	i = i + 1
	ir_a 7
fin_si
escribir("El factorial de ", n, " es: ", fact)
