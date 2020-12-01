# Assingment_03
En este repositorio encontraremos las herramientas y programas necesarios para resolver numéricamente una la Ecuación de Calor.
Para este propósito hemos creador tools.h, donde se encuentran las principales funciones que usaremos para resolver este problema usando el método Implícito.

En el archivo, implicit.c se programaron los cálculos para la solución con el método implícito utilizando apuntadores. Para el cálculo numérico de la inversa, se empleó el método Gauss Seidel con un máximo de 10 iteraciones. No obstante, al momento de ejecutarlo, se encontraron problemas de acceso a la memoria.

Por otro lado, en calor_explicito.c se encuentra el método de solución para la EDP usando la forma Explícita, donde usamos la función malloc y calloc, para los vectores y matriz respectivamente,  para generar espacio dinámico de memoria, pero que a su vez las entradas de la matriz solución se inicialicen en 0. 
Creamos la función void arreglo, la cual nos da los puntos de la partición de un intervalo, dado un vector y la separación entre dichos puntos. 
Además de la función int q, donde evaluamos la función que corresponde a la condición inicial.
Usamos el esquema numérico visto en el curso de Análisis Numérico y finalmente se guardará la información solicitada en el archivo "datos_matriz.txt"
Para graficar, se usará GNUPLOT, para esto se debe cambiar el Directorio en el menú y posterior poner el comando "plot 'datos_matriz.tx'" para visualizar la solución numérica en el tiempo dado por el usuario en el programa

