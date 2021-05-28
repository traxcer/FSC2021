#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

/*estados*/
#define OCIOSO 0
#define FILTRANDO 1

/*eventos*/
#define OFF 0
#define ON 1
#define MENSAJE 2
#define FIN 3
#define TIMEOUT 4

/*cadena global, compartida por espera_evento y la maquina de estados*/
#define T 100


void m(int signo) {
	signal(SIGALRM, m);
}

int espera_evento(char * mensaje)
{
	errno = 0;
	int leidos = read(0, mensaje, T - 1);
	if (leidos < 0)
	{
		if (errno == EINTR) {
			strcpy(mensaje, "Temporizador expirado\n");
			return TIMEOUT;
		} else {
			return -1;
		}
		
	}
	else
	{
		mensaje[leidos - 1] = '\0'; //convierte en cadena y quita el '\n' del buffer de teclado
		if (strcmp("/on", mensaje) == 0)
		{
			return ON;
		}
		else if (strcmp("/off", mensaje) == 0)
		{
			return OFF;
		}
		else if (strcmp("/fin", mensaje) == 0)
		{
			return FIN;
		}
		else
		{
			return MENSAJE;
		}
	}
}

int main()
{
	int estado = OCIOSO;
	int evento;
	int tacos = 0;
	int fin = 0;
	char *posicion;
	char mensaje[T];

	struct timeval tv_off, tv_zero;
	tv_off.tv_sec = 5;
	tv_off.tv_usec = 500000;
	tv_zero.tv_sec = 0;
	tv_zero.tv_usec = 0;
	struct itimerval it_off, it_zero;
	it_off.it_value = tv_off;
	it_off.it_interval = tv_zero;
	it_zero.it_value = tv_zero;
	it_zero.it_interval = tv_zero;

	if (signal(SIGALRM, m) == SIG_ERR ) {
		perror("signal");
		exit(-1);
	}

	while (!fin)
	{

		printf("(ESTADO %d) Introduzca comando [/on, /off, /fin] o mensaje:\n", estado);
		evento = espera_evento(mensaje);
		switch (estado)
		{
		case OCIOSO:
			switch (evento)
			{
			case ON:
				estado = FILTRANDO;
				//activamos el temporizador
				if (setitimer(ITIMER_REAL, &it_off, NULL) < 0)
				{
					perror("setitimer");
					exit(-1);
				}
				break;
			case MENSAJE:
				printf("Mensaje: %s\n", mensaje);
				break;
			case FIN:
				fin = 1;
				break;
			default:
				printf("Evento %d no esperado en OCIOSO\n", evento);
				break;
			}
			break;

		case FILTRANDO:
			switch (evento)
			{
			case MENSAJE:
				posicion = strstr(mensaje, "taco");
				while (posicion != NULL)
				{
					int i;
					for (i = 0; i < 4; i++)
					{
						*(posicion + i) = 'x';
					} /* equivale a: strncpy(posicion,"xxxx",4); */
					tacos++;
					posicion = strstr(posicion, "taco");
				}
				printf("Mensaje: %s\n", mensaje);
				//rearmar el temporizador
				if (setitimer(ITIMER_REAL, &it_off, NULL) < 0)
				{
					perror("setitimer");
					exit(-1);
				}
				break;
			case OFF:
				estado = OCIOSO;
				tacos = 0;
				//deshabilitar temporizador
				if (setitimer(ITIMER_REAL, &it_zero, NULL) < 0)
				{
					perror("setitimer");
					exit(-1);
				}
				break;
			case TIMEOUT:
				estado = OCIOSO;
				printf("Mensaje: %s\n", mensaje);
				tacos = 0;
				break;
			case FIN:
				fin = 1;
				break;
			default:
				printf("Evento %d no esperado en FILTRANDO\n", evento);
				break;
			}
			break;
		default:
			printf("Estado %d no esperado!!\n", estado);
			break;
		}
	} //end del while
	return 0;
}
