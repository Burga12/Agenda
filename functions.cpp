#include "libreria.h"

	bool foundF = false;
	extern char opcion[10];


bool compareName(char str[],char str2[])
{
	return strcasecmp(str,str2) < 0;
}

bool only_numbers(char str[])
{

    for (int i = 0; i<strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9' && str[i] != ' ')
            return true;
    }

    return false;
}


bool only_characters(char str[])
{

    for (int i = 0; i<strlen(str); i++)
    {
        if (str[i] < 'A' || str[i] > 'z')
            if (str[i] != ' ')
                return true;
    }

    return false;
}

void spaceAndPrintr(char str[],int spaces) //poner espacios a la derecha
{
	spaces -= strlen(str);	
	cout << str;	
	while(spaces-- > 0)
			cout << " ";
}

void spaceAndPrintl(char str[],int spaces) //poner espacios a la izquierda
{
	spaces -= strlen(str);	
	while(spaces-- > 0)
			cout << " ";
	cout << str;
}

bool validPhone(char phone[])
{
	if (only_numbers(phone))
		return false;
	else if (strlen(phone) != 11)
		return false;

	char aux[30];//cadena auxiliar para comparar que sea un numero valido

	/*
	strcnpy(aux,phone,4);//tomaremos los primeros cuatro digitos de la cadena

	if (strcmp(aux,"0424") != 0)
		return false;
	else if (strcmp(aux,"0426") != 0)
		return false;
	else if (strcmp(aux,"0412") != 0)
		return false;
	*/
	return true;
}	


void agregarDatos(Datos &p)
{

	char opcion[10];

	cout << "\n\n Como desea nombrar el contacto: ";
	cin.getline(p.name,30,'\n');
	fflush(stdin);

	do{

		cout << "\n\n Numero de telefono: ";
		cin.getline(p.phone,30,'\n');
		fflush(stdin);
		if(!validPhone(p.phone))
		{
			cout << "\n\n Numero de telefono invalido. intente de nuevo\n\n";
			system("pause");
		}

	}while(!validPhone(p.phone));
	

	cout << "\n\n Desea agregar un correo electronico: ";
	cout << "\n s -> si ";
	cout << "\n otro -> no";
	cout << "\n Ingresar: ";
	cin.getline(opcion,10,'\n');
	

	if(opcion[0] == 's'){
		//do{
			cout << "\n\n Ingrese el correo: ";
			cin.getline(p.mail,30,'\n');
			fflush(stdin);
		//}while()
	} 
	else 
		strcpy(p.mail,"No asignado");
		
}

void agregarNodo(Nodo *&lista, Datos p)
{
	Nodo *nuevo_nodo = new Nodo();//Reservamos memoria

	nuevo_nodo -> persona = p;//guardamos el dato en el nodo

	//declaramos las variables de tipo nodo auxiliares
	Nodo *aux1 = lista;
	Nodo *aux2;

	if (aux1 != NULL)
	{
		//bucle para guardar ordenadamente los datos
		while((aux1 != NULL) && (compareName(aux1->persona.name,p.name)))
		{
			aux2 = aux1;
			aux1 = aux1 -> siguiente;
		}

	}
	
	
	if (lista == aux1)//guardar al principio
		lista = nuevo_nodo;
	else
		aux2 -> siguiente = nuevo_nodo;//guardamos al medio o al final del a lista

	nuevo_nodo -> siguiente = aux1; //aignamos al nuevo nodo el nodo siguiente de el

	fflush(stdin);//limpiar buffer
}

void mostrarDatos(Datos aux,int n)
{
	cout << "  "<< n << "# ";
	spaceAndPrintr(aux.name,25); cout <<     " |  ";
	spaceAndPrintr(aux.phone,13); cout <<   "| ";	
	spaceAndPrintr(aux.mail,7);
}


void Delete(Nodo *&lista, char name[])
{
	if (lista == NULL)
		cout << "\n\n lista vacia\n";
	else
	{
		Nodo *aux_delete = lista;
		Nodo *anterior = NULL;

		while((aux_delete!=NULL) && strcasecmp(aux_delete->persona.name,name) != 0)
		{
			anterior = aux_delete;
			aux_delete = aux_delete -> siguiente;
		}

		if (aux_delete == NULL)
			cout << "\n Elemento a eliminar no existe \n";
		else if (anterior == NULL){

			lista = lista -> siguiente;
			delete aux_delete;

		} else {
			anterior->siguiente = aux_delete -> siguiente;
			delete aux_delete;
		}
	}
}


void edit(Nodo *&lista, Datos &p)
{	

	Nodo *aux = lista;

	char user_request[30];

	do{

		aux = lista;
				
		cout << "\n\n Escriba el nombre del usuario a editar (correctamente): ";
		cin.getline(user_request,30,'\n');

		while(aux != NULL)
		{
			if (strcasecmp(user_request,aux->persona.name) == 0)
			{	

				Delete(lista,user_request);
				cout << "\n\n Editando datos del contacto \n\n";
				agregarDatos(p);
				fflush(stdin);
				agregarNodo(lista,p);
				//ordenar(lista,aux->persona,aux);
				foundF = true;
			}
			aux = aux -> siguiente;
		}
		
		if (!foundF)
		{
			cout << "\n Nombre ingresado incorrectamente\n\n";

			cout << "\n\n Que desea hacer?\n\n";
			cout << "\n e -> editar un contacto";
			cout << "\n otro -> salir";
			cout << "\n Ingresar: ";
			cin.getline(opcion,10,'\n');
			
			cout<<"\n\n\n";
			cls;

		} else {

			cout << "\n\n Que desea hacer?\n\n";
			cout << "\n e -> editar otro contacto";
			cout << "\n otro -> salir";
			cout << "\n Ingresar: ";
			cin.getline(opcion,10,'\n');
		}

		

	}while(opcion[0] == 'e');
				
}

void deleteAll(Nodo *& lista)
{
	Nodo *aux_delete = lista;

	while(lista != NULL)
	{
		delete aux_delete;
		lista = lista -> siguiente;
	}
}

void search(Nodo *lista,Datos p)
{	

	cls;
	char sub_search_name[30];
	char sub_search_phone[30];
	char user_request[30];	
	char to_search_name[30],to_search_phone[30];
	int cont   = 0;
	Nodo *aux  = lista;

	cout << "\n\n\t Menu de Busqueda \n\n\n";

	cout << "\n Ingrese el nombre o telefono a buscar: ";

	cin.getline(user_request,30,'\n');

	cout << "\n\n Mejores coincidencias \n\n\n";

	//spaceAndPrintr("Nombre",16);     cout <<      " |  ";
	//spaceAndPrintr("telefono",13);	 cout <<   "| \n\n";	

	while(aux != NULL)
	{	

		//guardamos el nombre y el telefono de la persona actual	
		strcpy(to_search_name,aux->persona.name);
		strcpy(to_search_phone,aux->persona.phone);

		//separamos la cadena determinado por el numero de caracteres ingresado por el usuario
		strncpy(sub_search_name, to_search_name, strlen(user_request));
		strncpy(sub_search_phone, to_search_phone, strlen(user_request));

		sub_search_phone[strlen(user_request)] = '\0';
		sub_search_name[strlen(user_request)] = '\0';

		
		if ((strcasecmp(sub_search_name,user_request)) == 0 || 
		    (strcmp(sub_search_phone,user_request)  == 0))
		{
			cont++;
			mostrarDatos(aux -> persona,cont);
			foundF = true;
			cout <<"\n";
		}

		aux = aux -> siguiente;
		
	}

	if (!foundF)
		cout << "\n\n Ningun elemento encontrado \n\n";
	else
	{
		
		cout << "\n\n Que desea hacer?\n\n";
		cout << "\n e -> editar un contacto";
		cout << "\n otro -> salir";
		cout << "\n Ingresar: ";
		cin.getline(opcion,10,'\n');

		if (opcion[0] == 'e')
			edit(lista,p);
		
	}

}