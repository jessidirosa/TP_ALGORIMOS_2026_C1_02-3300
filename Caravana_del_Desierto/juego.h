#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "arbol.h"
#include "constantes.h"
#include "cola.h"
#include "config.h"
#include "lista.h"
#include "lista_doble.h"


typedef struct
{
    int vidas;
    int puntos;
    int protegido; //0 no 1 si
    int pierdeTurno; //0 no 1 si
} tJugador;

typedef struct
{
    tNodoD* pos;
    int activo; // 1 = vivo, 0 = eliminado

} tBandido;

typedef struct
{
    char tipoJugador;
    tNodoD* pos;
    int pasos;
    char direccion;

} tMovimiento;

typedef struct {
    int id_jugador;
    int id_partida;
    int puntaje;
    int movimientos;
} tRegistroPartida; //se ultiliza para gurdar el contenido del archivo binario "ARCH_PARTIDAS" y mostrar el ranking


void menu(tConfig *c, tArbol* idx);
void registrarJugador(tArbol* idx);
void identificarJugador(const char* nombreJugador, tArbol* idx);
void altaJugador(tArbol* idx, const char* alias, const char* archJug);
void mostrarDatosYValidar(tArchJug* datosJugador);
void mostrarRanking(const char* archivo);
int casoPruebaBIN(const char* archivo);
int compararPuntosJugadores(const void* a, const void* b);
void mostrarPuntosJugadores(const void* n);
int compararIDJugadores(const void* a, const void* b);
void acumularDuplicados(void* datoLista, const void* datoAInsertar);
void mostrarTop(tLista *pLista,int top);
int ingresar(unsigned tam);
int opcionValida(unsigned opcion);
void ejecutarOpcion(unsigned opcion,tConfig* c, tArbol* idx);
tNodoD* posicionarJugadorEnInicio(tListaD *l);
tNodoD* moverJugador(tNodoD *jugador, int pasos, char dir);
int analizarJuego(tNodoD *nodo, tJugador *jugador, tNodoD *nodoInicio,tNodoD** nodoJugador, tBandido* bandidos, int cantB);
int iniciarCaracteristicasJugador(tJugador *jugador,tConfig *conf);

void iniciarPartida(tConfig *c);
int tirarDado();
int calcularDistanciaAlInicio(tNodoD *nodoJugador);

//MOV BANDIDOS
void posicionarBandidosEnRuta(tBandido* bandidos,tListaD* ruta);
void guardarMovimiento(tMovimiento* movimiento,tNodoD* nodo,char dir,int dado,char tipo);
void determinarMovimientosBandidos(tBandido* bandidos,int cantB,tNodoD* nodoJugador,tCola* colaMovimiento);
void calcularDistanciaMinima(tNodoD* posB,tNodoD* posJ,char* dir);
void eliminarBandido(tBandido* bandidos, int cantB, tNodoD* nodoColision);
tBandido* buscarBandidoPorPosicion(tBandido* bandidos, int cantB, tNodoD* posBuscada);
void moverBandidos(tBandido* bandidos,tMovimiento* movimiento, int cantB);


//GUARDAR HISTORIAL DE MOVIMIENTOS
void registrarMovimientoEnHistorial(tCola* historialMov, int pasos, char direccion);
int mostrarHistorialMovimientos(tCola* historialMov);
#endif // JUEGO_H_INCLUDED
