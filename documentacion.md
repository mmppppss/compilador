Lenguaje interpretado 

## tipos de datos 
Cadena: texto definido entre comillas ""
    ejemplo: "hola mundo"

Numero:  numero real separa decimales con .
    ejemplo: 1 3.14

## imprimir en terminal:
escribir
ejemplos:
    escribir("Cadena")
    escribir(variable)
    escribir("Cadena", variable)
    escribir(variable, "Cadena", ...)

## recibir datos del usuario

leer
ejemplos:
    leer(variable)
    leer(var, varx, vary)

## asignar una variable
id = num
ejemplos:
    var = 1
    varx = var*1
    var = 4/2

## condicional

si condicion entonces
    ...
fin_si
ejemplos
    si 2>1 entonces
        escribir("2 es mayor a 1")
    fin_si

## salto de linea
ir_a NUM 
//para ir de una linea a otra de codigo
ejemplos:
    escribir("linea 1")
    ir_a 1
    //esta no deberia imprimirse 
    escribir("despues del salto")
