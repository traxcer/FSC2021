//includes
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

//eventos
#define MANDA_MENSAJE 0
#define TIMEOUT 1
#define CTS 2
#define TX_FINISHED 3
#define CTS_OFF 4

//estados
#define LISTO 0
#define RETRASO_TX 1
#define ESPERA_CTS 2
#define ESPERA_TX_FINISH 3
#define RETRASO_RTS_OFF 4
#define ESPERA_CTS_OFF 5

int pfd[2]; //global para poder usarla en manejadores y main

void h_timeout(int s){
  uint8_t e = TIMEOUT;
  write(pfd[1], &e, 1);
  signal(SIGALRM, h_timeout); //por compatibilidad System V
}

void h_manda_mensaje(int s){
  uint8_t e = MANDA_MENSAJE;
  write(pfd[1], &e, 1);
  signal(SIGINT, h_manda_mensaje); //por compatibilidad System V
}

void h_CTS(int s){
  uint8_t e = CTS;
  write(pfd[1], &e, 1);
  signal(SIGTERM, h_CTS); //por compatibilidad System V
}

void h_TX_FINISHED(int s){
  uint8_t e = TX_FINISHED;
  write(pfd[1], &e, 1);
  signal(SIGUSR1, h_TX_FINISHED); //por compatibilidad System V
}

void h_CTS_OFF(int s){
  uint8_t e = CTS_OFF;
  write(pfd[1], &e, 1);
  signal(SIGUSR2, h_CTS_OFF); //por compatibilidad System V
}

int espera_evento(){
  uint8_t e;
  ssize_t leidos;
  leidos = read(pfd[0], &e, 1);
  if(leidos != 1){
	printf("Error en read!\n");
	return -1;
  }
  printf("<evento recibido %d>\n",e);
  return e; //un uint8_t cabe en un int, no hace falta casting
}

int main(){
 
  if(pipe(pfd)<0){
    perror("Error en la creacion de la pipe");
    exit(1);
  }
  
  signal(SIGINT, h_manda_mensaje);
  signal(SIGALRM, h_timeout);
  signal(SIGTERM, h_CTS);
  signal(SIGUSR1, h_TX_FINISHED);
  signal(SIGUSR2, h_CTS_OFF);

  printf("El pid del proceso es: %d\n",getpid());
  
  int estado = LISTO;
  int fin = 0;
  struct itimerval timerval;
  struct timeval valor;
  struct timeval intervalo_cero;
  //nuestros temporizadores no son periodicos!
  intervalo_cero.tv_sec = 0;
  intervalo_cero.tv_usec = 0; 
  timerval.it_interval = intervalo_cero;
  
  while(!fin){
    int evento = espera_evento();
    switch(estado){
      case LISTO:
	if(evento == MANDA_MENSAJE){
	  valor.tv_sec = 1;
	  valor.tv_usec = 500000;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  estado = RETRASO_TX;
	}else{
	  printf("LISTO: evento no esperado\n");
	}
	break;
      case RETRASO_TX:
	if(evento == TIMEOUT){
	  printf("RTS activa\n");
	  valor.tv_sec = 3;
	  valor.tv_usec = 300000;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  estado = ESPERA_CTS;
	}else{
	  printf("RETRASO_TX: evento no esperado\n");
	}
	break;
      case ESPERA_CTS:
	if(evento == CTS){
	  valor.tv_sec = 0;
	  valor.tv_usec = 0;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  printf("CTS activa\n");
	  estado = ESPERA_TX_FINISH;
	}else if(evento == TIMEOUT){
	  printf("Error: CTS no activa\n");
	  fin = 1;
	}else{
	  printf("ESPERA_CTS: evento no esperado\n");
	}
	break;
      case ESPERA_TX_FINISH:
	if(evento == TX_FINISHED){
	  valor.tv_sec = 1;
	  valor.tv_usec = 500000;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  estado = RETRASO_RTS_OFF;
	}else{
	  printf("ESPERA_TX_FINISH: evento no esperado\n");
	}
	break;
      case RETRASO_RTS_OFF:
	if(evento == TIMEOUT){
	  printf("RTS desactivada\n");
	  valor.tv_sec = 4;
	  valor.tv_usec = 200000;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  estado = ESPERA_CTS_OFF;
	}else{
	  printf("RETRASO_RTS_OFF: evento no esperado\n");
	}
	break;
      case ESPERA_CTS_OFF:
	if(evento == CTS_OFF){
	  valor.tv_sec = 0;
	  valor.tv_usec = 0;
	  timerval.it_value = valor;
	  setitimer(ITIMER_REAL, &timerval, NULL);
	  printf("CTS desactivada\n");
	  estado = LISTO;
	}else if(evento == TIMEOUT){
	  printf("Error: CTS no desactivada\n");
	  fin = 1;
	}else{
	  printf("ESPERA_CTS_OFF: evento no esperado\n");
	}
	break;
    }
    
  }//fin del while
  close(pfd[0]);
  close(pfd[1]);
  return 0;
}