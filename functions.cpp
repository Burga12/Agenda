#include "libreria.h"

	bool foundF = false;
	extern char opcion[10];


bool compareName(char str[],char str2[])
{
	return strcasecmp(str,str2) < 0;
}

bool validarCorreo(char str[])
{
	char aux[20];
	bool confirm = false;

	//determinar que tenga una @
	for (int i = 0; i < strlen(str); i++)
	{	

		//comparamos si el arroba existe en la cadena y tambien
		//comparamos si el arroba no esta en la ultima posicion de la cadena
		if (str[i] == '@' && i != (strlen(str) - 1))// -2 porque tiene un salto de linea
		{
			confirm = true;
		} 
	}

	// si confirm es false significa que la cadena no tiene arroba
	if (confirm)
	{
		strcpy(aux,strtok(str,"@"));//separamos la cadena del arroba
		strcpy(aux,strtok(NULL,"\n"));//ahora copiamos la cadena y le quitamos el salto de linea

		if (
			(strcasecmp(aux,"gmail.com")   != 0)  && (strcasecmp(aux,"hotmail.com") != 0 ) && 
			(strcasecmp(aux,"hotmail.es")  != 0)  && (strcasecmp(aux,"outlook.es" ) != 0 ) &&
			(strcasecmp(aux,"outlook.com") != 0)  
	   		)
		{
			return false;
		}

	} else
		return false;

	return true;	
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

	//comparamos que sea un numero personal y no un numero de hogar
	/*
	strncpy(aux,phone,2);//tomamos los primeros 2 digitos
	aux[strlen(aux)] = '\0';
	cout << "\n" << aux;
	if (strcmp(aux,"02") == 0)
		return false;
	*/

	//comparamos que el codigo sea uno registrado en el pais
	strncpy(aux,phone,4);//tomaremos los primeros cuatro digitos de la cadena
	aux[4] = '\0';


	if ((strcmp(aux,"0424") != 0) && (strcmp(aux,"0426") != 0) 
	 && (strcmp(aux,"0412") != 0) && (strcmp(aux,"0414") != 0))
		return false;
		
	return true;
}	


void agregarDatos(Datos &p)
{

	char opcion[10];
	char aux[40];

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
		do{
			cout << "\n\n Ingrese el correo: ";
			cin.getline(p.mail,30,'\n');

			strcpy(aux,p.mail);//copiamos la cadena para no afectar la original

			fflush(stdin);

			if (!validarCorreo(aux))
			{
				cout << "\n\n Correo invalido intente de nuevo\n";
				system("pause");
			}

			strcpy(aux,p.mail);//copiamos de nuevo ya que anteriormente se modifico el axuiliar
			
		}while(!validarCorreo(aux));
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

void saveEdit(char phone[], char mail[], char name[], Datos &p)
{	

	char opcion[30];
	char aux[30];
	

	do{
		cls;
		cout << "\n\n Editando datos del contacto \n\n";

		cout << "\n\n Datos de "<< name;
		cout << "\n Telefono: "<<phone;
		cout << "\n Correo: "<<mail;

		cout << "\n\n Que desea editar?\n\n";
		cout << "\n t -> telefono";
		cout << "\n n -> nombre";
		cout << "\n c -> correo";
		cout << "\n a -> todos los datos";

		do{

			cout << "\n Ingresar: ";
			cin.getline(opcion,30,'\n');

			if (opcion[0] != 't' && opcion[0] != 'c' && opcion[0] != 'n' && opcion[0] != 'a')
			{
				cout << "\n\n opcion incorrecta. intente de nuevo";
				system("pause");
			}

		}while(opcion[0] != 't' && opcion[0] != 'c' && opcion[0] != 'n' && opcion[0] != 'a');

		//guardamos los datos previamente 
		strcpy(p.name,name);
		strcpy(p.phone,phone);
		strcpy(p.mail,mail);

		switch(opcion[0])
		{
			case 't':
				
				do{

					cout << "\n\n Ingrese el nuevo telefono: ";
					cin.getline(p.phone,30,'\n');
					fflush(stdin);
					if(!validPhone(p.phone))
					{
						cout << "\n\n Numero de telefono invalido. intente de nuevo\n\n";
						system("pause");
					}

					//guardamos los datos de nuevo para que se copien los nuevos datos ingresados
					strcpy(phone,p.phone);

				}while(!validPhone(p.phone));

				break;

			case 'n':

				cout << "\n\n Ingrese el nuevo nombre: ";
				cin.getline(p.name,30,'\n');
				strcpy(name,p.name);
				break;

			case 'c':

				do{
					cout << "\n\n Ingrese el nuevo correo: ";
					cin.getline(p.mail,30,'\n');

					strcpy(aux,p.mail);//copiamos la cadena para no afectar la original

					fflush(stdin);

					if (!validarCorreo(aux))
					{
						cout << "\n\n Correo invalido intente de nuevo\n";
						system("pause");
					}

					strcpy(aux,p.mail);//copiamos de nuevo ya que anteriormente se modifico el axuiliar
					strcpy(mail,p.mail);

				}while(!validarCorreo(aux));

				break;

			case 'a':

				agregarDatos(p);
		}

		cls;

		cout << "\n\n Desea editar otro atributo?";
		cout << "\n s -> si";
		cout << "\n otro -> no";
		cout << "\n Ingresar: ";
		cin.getline(opcion,30,'\n');

	}while(opcion[0] == 's');
	
}

void edit(Nodo *&lista, Datos &p)
{	

	Nodo *aux = lista;

	char name_aux[40];
	char phone_aux[40];
	char mail_aux[40];
	char user_request[30];

	do{

		aux = lista;
				
		cout << "\n\n Escriba el nombre del usuario a editar (correctamente): ";
		cin.getline(user_request,30,'\n');

		while(aux != NULL)
		{
			if (strcasecmp(user_request,aux->persona.name) == 0)
			{	

				//copiamos los datos para luego editarlos
				strcpy(name_aux,aux->persona.name);
				strcpy(phone_aux,aux->persona.phone);
				strcpy(mail_aux,aux->persona.mail);
				

				Delete(lista,user_request);
				saveEdit(phone_aux,mail_aux,name_aux,p);
				
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
			cout << "\n otro -> volvera al menu";
			cout << "\n Ingresar: ";
			cin.getline(opcion,10,'\n');
			
			cout<<"\n\n\n";
			cls;

		} else {

			cout << "\n\n Que desea hacer?\n\n";
			cout << "\n e -> editar otro contacto";
			cout << "\n otro -> volvera al menu";
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

void search(Nodo *&lista,Datos p)
{	

	cls;
	char sub_search_name[30];
	char sub_search_phone[30];
	char user_request[30], str_delete[100];	
	char to_search_name[30],to_search_phone[30];
	bool found = false;
	int  cont;
	Nodo *aux;

	do{

		cont = 0;
		aux = lista;

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
			sub_search_name[strlen(user_request)]  = '\0';
			//eliminamos el elemento basura que se almacena al final

		
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
			cout << "\n d -> eliminar un contacto";
			cout << "\n otro -> salir";
			cout << "\n Ingresar: ";
			cin.getline(opcion,10,'\n');

			if (opcion[0] == 'e')
				edit(lista,p);

			else if (opcion[0] == 'd')
			{
				do{
					cout << "\n\n Ingrese exactamente el nombre del contacto a eliminar: ";
					cin.getline(str_delete,100,'\n');

					//buscamos si hay alguna coincidencia
					aux = lista;//devolvemos el auxiliar al inicio de la lista
					while(aux != NULL)
					{			

						if (strcasecmp(str_delete,aux->persona.name) == 0)
						{
							found = true;
							break;
						}

						aux = aux -> siguiente;

					}

			
					if (!found)
					{	

										
						cout << "\n\n Nombre incorrecto \n";
						cout << "\n Desea ingresar el nombre de nuevo?";
						cout << "\n s -> si";
						cout << "\n n -> cancelar operacion (Volvera al menu)";


						do{
							cout << "\n Ingresar: ";
							cin.getline(opcion,10,'\n');

							if (opcion[0] != 's' && opcion[0] != 'n')
								cout << "\n\n Opcion incorrecta. intente de nuevo \n\n";

						}while(opcion[0] != 's' && opcion[0] != 'n');

					} else {


						cout << "\n Seguro que quiere eliminarlo?";	
						cout << "\n s -> si";
						cout << "\n n -> cancelar operacion";
										
						do{
							cout << "\n Ingresar: ";
							cin.getline(opcion,10,'\n');

							if (opcion[0] != 's' && opcion[0] != 'n')
								cout << "\n\n Opcion incorrecta. intente de nuevo \n\n";

						}while(opcion[0] != 's' && opcion[0] != 'n');


						if (opcion[0] == 's')
						{
							Delete(lista,str_delete);
							opcion[0] = 'c';
						}

					}
					
					cls;
				}while(opcion[0] == 's');
			}

			cls;
		}


		cout << "\n\n Desea buscar de nuevo?";
		cout << "\n s -> si ";
		cout << "\n otro -> volver al menu";
		cout << "\n Ingresar: ";
		cin.getline(opcion,10,'\n');
		cls;
	}while(opcion[0] == 's');
}