#ifndef _LIBRERIA
#define _LIBRERIA

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#ifdef _WIN32
#define cls system("cls");
#else
#define cls system("clear");
#endif

using namespace std;


struct Datos
{
	char phone[30];
	char name[30];
	char mail[30];
};

struct Nodo
{	
	Datos persona;
	Nodo *siguiente;
};

bool compareName(char str[],char str2[]);
bool only_numbers(char str[]);
bool only_characters(char str[]);
void spaceAndPrintr(char str[],int spaces);//poner espacios a la derecha
void spaceAndPrintl(char str[],int spaces); //poner espacios a la izquierda
bool validPhone(char phone[]);
void agregarDatos(Datos &p);
void agregarNodo(Nodo *&lista, Datos p);
void mostrarDatos(Datos aux,int n);
void Delete(Nodo *&lista, char name[]);
void edit(Nodo *&lista, Datos &p);
void deleteAll(Nodo *& lista);
void search(Nodo *&lista,Datos p);
bool validarCorreo(char str[]);

#endif