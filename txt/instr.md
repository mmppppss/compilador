## Compilar GUI:
gcc guimain.c -o ejecutables/gtk_gui `pkg-config --cflags --libs gtk+-3.0`

/
 |-- ejecutables
 |  |-- gtk_gui             # gui
 |  |-- main2               # principal
 |  |-- main                # version ant
 |  |-- struct              # lista enlazada
 |
 |-- txt
 |  |-- instr.md            # instrucciones
 |  |-- simple.txt          # ejemplo
 |  |-- tiempos.txt         # tiempos
 |  |-- 100mb.txt           # 100 millones 
 |  |-- manGCC.txt          # manual gcc
 |
 |-- java
 |  |-- FileLoader.java     # java
