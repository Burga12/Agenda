/*
	AGENDA TELEFONICA

	Jose Flores

*/

#include "libreria.h"

//Variables de uso global
		bool found = false;
		char opcion[10];


int main(int argc, char const *argv[])
{
	Nodo *lista = NULL;
	Nodo *aux = NULL;

	int cont;

	Datos persona;

	do{

		cls;
		cont = 0;

		do{

			cout << "\n\t Agenda Telefonica 1.0 \n\n\n";

			cout << "\n\t Menu \n\n";

			cout << "\n a -> Agregar un Contacto  ";
			cout << "\n e -> Eliminar Contacto ";
			cout << "\n b -> Buscar un contacto ";
			cout << "\n d -> Editar un contacto ";
			cout << "\n v -> Ver contactos";
			cout << "\n o -> Salir del programa ";
			cout << "\n\n Ingresar: ";
			cin.getline(opcion,10,'\n');

			if ((opcion[0] != 'a') && (opcion[0] != 'e') && (opcion[0] != 'b') && (opcion[0] != 'd')
				&&  (opcion[0] != 's') && (opcion[0] != 'v') && (opcion[0] != 'o') )
			{
				cout << "\n\n opcion ingresada invalida intente de nuevo \n\n";
				system("pause");
			}

			cls;
		}while((opcion[0] != 'a') && (opcion[0] != 'e') && (opcion[0] != 'b') && (opcion[0] != 'd')
				&& (opcion[0] != 's') && (opcion[0] != 'v') && (opcion[0] != 'o'));
	

		switch(opcion[0])
		{
			case 'a':

				do{
				
					cout << "\n\t Agregando contacto(s) nuevo(s) \n\n";
					agregarDatos(persona);
					agregarNodo(lista,persona);

					cout << "\n Desea agregar otro contacto?";
					cout << "\n s -> si";
					cout << "\n Otro -> no";
					cout << "\n Ingresar: ";
					cin.getline(opcion,10,'\n');
					cls;

				}while(opcion[0] == 's');

				cout << "\n\n";

				break;


			case 'e':	

				cls;	
				char str_delete[30];

				if (lista == NULL)
				{
					cout << "\n\n Aun no ha guardado ningun contacto \n\n";
					system("pause");
					break;
				}
					
				do{

					do{

						cout << "\n\t Eliminar contacto \n\n";
						cout << "\n u -> Eliminar un solo contacto";
						cout << "\n a -> Eliminar todos los contactos";
						cout << "\n o -> Salir del programa";
						cout << "\n Otro -> volver al menu";
						cout << "\n Ingresar: ";
						cin.getline(opcion,10,'\n');

						if (opcion[0] != 'u' && opcion[0] != 'a' && opcion[0] != 'o')
						{
							cout << "\n\n Opcion incorrecta. intente de nuevo \n\n";
							system("pause");
						}
						
					}while(opcion[0] != 'u' && opcion[0] != 'a' && opcion[0] != 'o');
					
					switch(opcion[0])
					{
						case 'u':

							do{

								cls;
								aux = lista;
								cout << "\n\t\t Contactos \n\n\n";

								while(aux != NULL)
								{
									cont++;
									mostrarDatos(aux->persona,cont);
									cout << "\n";
									aux = aux -> siguiente;
								}

								cout << "\n\n\n Ingrese 0 para cancelar la operacion";
								cout << "\n\n Ingrese exactamente el nombre del contacto a eliminar: ";
								cin.getline(str_delete,30,'\n');

								if (str_delete[0] != '0')
								{
									aux = lista;//devolvemos aux al primer nodo

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
										cout << "\n n -> no (Volvera al menu)";
										cout << "\n o -> Salir del programa";

										do{
											cout << "\n Ingresar: ";
											cin.getline(opcion,10,'\n');

											if (opcion[0] != 's' && opcion[0] != 'n' && opcion[0] != 'o')
												cout << "\n\n Opcion incorrecta. intente de nuevo \n\n";

										}while(opcion[0] != 's' && opcion[0] != 'n' && opcion[0] != 'o');

									} else {

										cout << "\n Seguro que quiere eliminarlo?";
										cout << "\n s -> si";
										cout << "\n n -> no (Volvera al menu)";
										cout << "\n o -> Salir del programa";
										
										do{
											cout << "\n Ingresar: ";
											cin.getline(opcion,10,'\n');

											if (opcion[0] != 's' && opcion[0] != 'n' && opcion[0] != 'o')
												cout << "\n\n Opcion incorrecta. intente de nuevo \n\n";

										}while(opcion[0] != 's' && opcion[0] != 'n' && opcion[0] != 'o');

										if (opcion[0] == 's')
										{
											Delete(lista,str_delete);

											cout << "\n Desea eliminar otro contacto?";
											cout << "\n s -> si";
											cout << "\n otro -> Volver al menu";
											cout << "\n o -> Salir del programa";
											cout << "\n Ingresar: ";
											cin.getline(opcion,10,'\n');
										}
									}
					
									cls;
								} else {
									cls; 

									cout << "\n Operacion cancelada \n\n";

									cout << "\n Desea eliminar otro contacto?";
									cout << "\n s -> si";
									cout << "\n otro -> Volver al menu";
									cout << "\n o -> Salir del programa";
									cout << "\n Ingresar: ";
									cin.getline(opcion,10,'\n');
								}
							
							}while(opcion[0] == 's');
				
							cout<<endl<<endl;
							cout << str_delete << " Se ha eliminado correctamente \n\n";
							break;

						case 'a':

							if (lista == NULL)
							{
								cout << "\n\n Aun no ha guardado ningun contacto \n\n";
								system("pause");
								break;
							}
				
							cout << "\n Seguro que quiere eliminarlo todos los contactos?";
							cout << "\n s -> si";
							cout << "\n n -> no (volvera al menu)";
							cout << "\n Ingresar: ";
							cin.getline(opcion,10,'\n');


							if (opcion[0] == 's')
							{
								cls;
								aux = lista;

								while(aux != NULL)
								{
									cont++;
									mostrarDatos(aux->persona,cont);
									cout << "\n ";
									aux = aux -> siguiente;
									cout << "\n Eliminando";
									for (int i = 0; i <= 3;i++)
									{	
										cout<<".";
										sleep(1);
									}
									cls;
								}
								deleteAll(lista);

								cout << "\n\n Contactos eliminados correctamente ";
							}
						
					}
				}while(opcion[0] == 'n');

				break;

			case 'v':
				
				if (lista == NULL)
				{
					cout << "\n\n Aun no ha guardado ningun contacto \n\n";
					system("pause");
					break;
				}

				aux = lista;

				cout << "\n\t\t Contactos \n\n  ";

				spaceAndPrintr("Nombre",25); cout <<   "    |  ";
				spaceAndPrintr("Telefono",13); cout <<   "| ";	
				spaceAndPrintr("Correo",7);
				cout<<endl<<endl;

				while(aux != NULL)
				{
					cont++;
					mostrarDatos(aux->persona,cont);
					cout << "\n";
					aux = aux -> siguiente;
				}	

				cout << endl;
	
				cout << "\n\n";
				system("pause");
				break;				

			case 'b':

				if (lista == NULL)
				{
					cout << "\n\n Aun no ha guardado ningun contacto \n\n";
					system("pause");
					break;
				}

				search(lista,persona);
				break;

			case 'd':

				if (lista == NULL)
				{
					cout << "\n\n Aun no ha guardado ningun contacto \n\n";
					system("pause");
					break;
				}

				aux = lista;

				cout<<endl<<endl;

				while(aux != NULL)
				{
					cont++;
					mostrarDatos(aux->persona,cont);
					cout << "\n";
					aux = aux -> siguiente;
				}

				edit(lista,persona);		
		}


		cls;

		if (opcion[0] == 'o')
		{
			cout << "\n Seguro que quiere salir del programa ?";
			cout << "\n\n otro -> voler al menu";
			cout << "\n o -> confirmar salida";
			cout << "\n Ingresar: ";
			cin.getline(opcion,10,'\n');
		}
		
	}while(opcion[0] != 'o');
	
	return 0;
}