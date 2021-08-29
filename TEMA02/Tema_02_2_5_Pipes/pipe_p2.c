/*
Realice una variación del ejercicio anterior donde esta vez el hijo 
será el que ponga fin a los dos procesos cuando alcance la cuenta de 
X caracteres leídos por la pipe (este valor se puede obtener como 
argumento al programa). 
En esta ocasión, se creará una pipe adicional para que el hijo le 
pueda transmitir al padre si éste debe continuar leyendo mensajes del 
usuario por teclado o debe finalizar.

El algoritmo es el que sigue:
Padre lee mensaje de teclado del usuario y lo manda al hijo por la pipe
original.
Hijo lee mensaje por la pipe original, lo muestra por pantalla y actualiza 
su cuenta de bytes leídos. Si se alcanza o supera el máximo X entonces 
utiliza la pipe nueva para enviar al padre el carácter 'n' y termina. 
Si no se alcanza X, entonces utiliza la pipe nueva para enviar al padre 
el carácter 'y' y vuelve a (b).
El padre lee por la pipe nueva un carácter. Si es 'y' vuelve al paso (a). 
Si es 'n', hace wait() del hijo y termina la ejecución.
*/