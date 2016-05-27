#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//Prototipos

int mcd(int Num, int Den);
void mostrarMenu(int &simbolo);
void guardarOperando(ofstream &fichero, double dato);
void guardarOperador(ofstream &fichero, char simbolo);
void pedirDatos(ofstream &fichero, double &resultado);
void sumar(ofstream &fichero, double &resultado, double &dato, double memoria);
void restar(ofstream &fichero, double &resultado, double &dato, double memoria);
void multiplicar(ofstream &fichero, double &resultado, double &dato, double memoria);
void dividir(ofstream &fichero, double &resultado, double &dato, double memoria);
void raizCuadrada(double &resultado, bool &error);
void elevar(ofstream &fichero, double &resultado, double &dato, bool &error);
void factorizar(double &resultado, bool &error);
void pBorrar(double &resultado);
void pSalida(bool &salida);
void pMemoria(double &memoria, double resultado);
void pUsarMemoria(double memoria, double &resultado, double &operando2);
void MostrarResultadoError(ofstream &fichero, double &resultado, bool &error);
void pedirFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen, char &simbolo);
void leerSegundaFraccion(int &datoNum, int &datoDen, char &simbolo);
void sumarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen);
void restarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen);
void multiplicarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen);
void dividirFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen);
void elevarFraccion(int &resultadoNum, int &resultadoDen, int &dato, bool error);
void simplificar(int &resultadoNum, int &resultadoDen);
void borrarFraccion(int &resultadoNum, int &resultadoDen);
void mostrarResultadoErrorFraccion(int &resultadoNum, int &resultadoDen, bool &error);
void cargarConfiguracion(ofstream &fichero, char &bSuma, char &bResta, char &bProducto, char &bDivision, 
						 char &bMemoria, char &bUsarMemoria, char &bRaiz, char &bExponente, char &bFactorial,
						 char &bBorrar, char &bSimplifica, char &bSalir, char &fijar);
void guardarConfiguracion(ifstream &fichero, char &bSuma, char &bResta, char &bProducto, char &bDivision, 
						 char &bMemoria, char &bUsarMemoria, char &bRaiz, char &bExponente, char &bFactorial,
						 char &bBorrar, char &bSimplifica, char &bSalir);

//Implementaciones

//Esta funcion calcula el maximo comun divisor de dos numeros
int mcd(int Num, int Den){
    if	(Num < Den)
		return mcd(Den,Num);
    if	(Den == 0)
		return Num;

    return mcd(Den, Num % Den);
}

//Procedimiento que se encarga de mostrar el Menú de opciones por pantalla
void mostrarMenu(int &simbolo){
	cout << " Elige una opcion: " << endl;
	cout << " ****************************************" << endl;
	cout << " **  1. Calculadora                    **" << endl;
	cout << " **  2. Calculadora: Modo Fracciones   **" << endl;
	cout << " **  3. Configuracion                  **" << endl;
	cout << " **  4. Apagar                         **" << endl;
	cout << " ****************************************" << endl;
	cout << " Opcion: ";
	cin >> simbolo;
	cin.sync();
}

//Implementaciones sobre el fichero log, que guarda lo escrito en la calculadora básica

void guardarOperando(ofstream &fichero, double dato){
	fichero << dato;
}

void guardarOperador(ofstream &fichero, char simbolo){
	fichero << simbolo;
}

//Implementaciones de la calculadora básica

//Con este procedimiento pedimos datos y distinguirá si es un digito o un signo
void pedirDatos(ofstream &fichero, double &resultado, double &dato, char &simbolo){
	int aux;

	cout << "Introduzca una expresion aritmetica valida: " << endl;
	aux = cin.peek();	//	Evaluamos si lo que entra es un digito o no pero no consumimos lo introducido
	if (isdigit(aux)){
		cin >> dato;
		guardarOperando(fichero, dato);
		cin.get(simbolo);
		guardarOperador(fichero, simbolo);
		resultado = dato;
	}

	else{
		fichero << endl;
		cin.get(simbolo);
		guardarOperador(fichero, simbolo);
	}
}
//Procedimiento que se encarga de calcular la suma de la calculadora básica
void sumar(ofstream &fichero, double &resultado, double &dato, double memoria){
	int aux;
	
	aux = cin.peek();
	if (isdigit(aux)){
		cin >> dato;
		guardarOperando(fichero, dato);
		resultado = resultado + dato;
	}
							
	else
		resultado = resultado + memoria;
}
//Procedimiento que se encarga de calcular la resta de la calculadora básica
void restar(ofstream &fichero, double &resultado, double &dato, double memoria){
	int aux;

	aux = cin.peek();
	if (isdigit(aux)){
		cin >> dato;
		guardarOperando(fichero, dato);
		resultado = resultado - dato;
	}
	
	else
		resultado = resultado - memoria;
}
//Procedimiento que se encarga de calcular el producto de la calculadora básica
void multiplicar(ofstream &fichero, double &resultado, double &dato, double memoria){
	int aux;
	
		aux = cin.peek();
		if (isdigit(aux)){
			cin >> dato;
			guardarOperando(fichero, dato);
			resultado = resultado * dato;
		}
						
		else
			resultado = resultado * memoria;
}
//Procedimiento que se encarga de calcular la division de la calculadora básica
void dividir(ofstream &fichero, double &resultado, double &dato, double memoria){
	int aux;
	
	aux = cin.peek();
	if (isdigit(aux)){
		cin >> dato;
		guardarOperando(fichero, dato);
		resultado = resultado / dato;
	}
	
	else
		resultado = resultado / memoria;
}
//Procedimiento que se encarga de calcular la raiz cuadrada de la calculadora básica
void raizCuadrada(double &resultado, bool &error){
	if (resultado >= 0)
		resultado = sqrt(resultado);
		
	else
		error = true;
}
//Procedimiento que se encarga de calcular el exponente de la calculadora básica
void elevar(ofstream &fichero, double &resultado, double &dato, bool &error){
	double base;

	cin >> dato;
	guardarOperando(fichero, dato);
	if (float(dato) == dato){
		base = resultado;
		if (dato == 0)
			resultado = 1;
	
		else if (dato > 0){
			while (dato > 1){
				resultado = resultado * base;
				dato = dato - 1;
			}
		}
		
		else{
			dato = abs(dato);
			resultado = 1;
			while (dato >= 1){
				resultado = resultado / base; 
				dato = dato - 1;
			}
		}
	}

	else
		error = true;
}
//Procedimiento que se encarga de calcular el factorial de la calculadora básica
void factorizar(double &resultado, bool &error){
int contador;

	contador = resultado;
	if (resultado == 0)
		resultado = 1;
		
	else if ((resultado > 0) && (floor(resultado) == resultado)){
		while (contador > 1){
			contador--;
			resultado = resultado * contador;
		}
	}

	else
		error = true;
}
//Pone el resultado a 0 si se ha introducido el boton de borrado
void pBorrar(double &resultado){
	resultado = 0;
}
//Provoca la salida al Menu principal si se ha introducido el boton de salida
void pSalida(bool &salida){
	salida = true;
}
//Se encarga de guardar el resultado en memoria en la calculadora básica
void pMemoria(double &memoria, double resultado){
	memoria = resultado;
}
//Permite que se pueda usar el resultado guardado en memoria
void pUsarMemoria(double memoria, double &resultado, double &operando2){
	resultado = memoria;
	operando2 = memoria;
}
//Se encarga de que se muestre el resultado o el mensaje de error según lo que se introduczca
void MostrarResultadoError(ofstream &fichero, double &resultado, bool &error){
	if (error){
		fichero << endl;
		cout << "ERROR EN LA OPERACION!!!!" << endl;
		cout << endl;
		fichero << "ERROR EN LA OPERACION!!!!" << endl;
		fichero << endl;
		error = false;
	}

	else {
		cout << ">>>>> " << resultado << endl;
		cout << endl;
		fichero << ">>>>> " << resultado << endl;
		fichero << endl;
	}
}


//Implementaciones del modo Fracción

//Se encarga de pedir la primera fracción y comprobar si entra un digito o un signo
void pedirFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen, char &simbolo){
	int aux;
	char botonFraccion = '|';

	cout << "Introduzca una expresion aritmetica valida: " << endl;
	aux = cin.peek();
	if (isdigit(aux)){
		cin >> datoNum;
		resultadoNum = datoNum;
		cin.get(simbolo);
		if (simbolo == botonFraccion){
			cin >> datoDen;
			resultadoDen = datoDen;
			cin.get(simbolo);
		}

		else{
			datoDen = 1;
			resultadoDen = datoDen;
		}
	}
	else
		cin.get(simbolo);
}
//Pide y Lee la segunda fraccion despues de saber el operando
void leerSegundaFraccion(int &datoNum, int &datoDen, char &simbolo){
	char botonFraccion = '|';

	cin >> datoNum;
	cin.get(simbolo);
	if (simbolo == botonFraccion){
		cin >> datoDen;
		cin.get(simbolo);
	}
	else
		datoDen = 1;
}
//Se encarga de calcular la suma entre fracciones
void sumarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen){
	resultadoNum = (resultadoNum * datoDen) + (resultadoDen * datoNum);
	resultadoDen = resultadoDen * datoDen;
}
//Se encarga de calcular la resta entre fracciones
void restarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen){
	resultadoNum = (resultadoNum * datoDen) - (resultadoDen * datoNum);
	resultadoDen = resultadoDen * datoDen;
}
//Se encarga de calcular el producto entre fracciones
void multiplicarFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen){
	resultadoNum = resultadoNum*datoNum;
	resultadoDen = resultadoDen*datoDen;
}
//Se encarga de calcular la división entre fracciones
void dividirFraccion(int &resultadoNum, int &resultadoDen, int &datoNum, int &datoDen){
	resultadoNum = resultadoNum*datoDen;
	resultadoDen = resultadoDen*datoNum;
}
//Se encarga de calcular fracciones elevada a un numero entero
void elevarFraccion(int &resultadoNum, int &resultadoDen, int &dato, bool error){
	int baseNum;
	int baseDen;

	cin >> dato;
	if (float(dato) == dato){
		baseNum = resultadoNum;
		baseDen = resultadoDen;
		if (dato == 0){
			resultadoNum = 1;
			resultadoDen = 1;
		}
		else if (dato > 0){
			while (dato > 1){
				resultadoNum = resultadoNum * baseNum;
				resultadoDen = resultadoDen * baseDen;
				dato = dato - 1;
			}
		}
		else
			error = true;
	}
	else
		error = true;
	
}
//Usando la funcion de calcular el mcd, simplifica las fracciones
void simplificar(int &resultadoNum, int &resultadoDen){
	int comun = mcd(resultadoNum, resultadoDen);

	resultadoNum = resultadoNum / comun;
	resultadoDen = resultadoDen / comun;
}
//Borra el resultado de la fracción si se introduce el numero correspondiente
void borrarFraccion(int &resultadoNum, int &resultadoDen){
	resultadoNum = 0;
	resultadoDen = 1; //El 0 fraccionario se representa con un 1 en el denominador
}
//Muestra el resultado de las operaciones o el mensaje de error si se ha introducido uno
void mostrarResultadoErrorFraccion(int &resultadoNum, int &resultadoDen, bool &error){
	if (error){
		cout << "ERROR EN LA OPERACION!!!!" << endl;
		cout << endl;
		error = false;
	}
	else{
		cout << ">>>>> " << resultadoNum << "|" << resultadoDen << endl;
		cout << endl;
	}
}


//Implementaciones sobre la configuracion

//Se encarga de comprobar si existe un fichero con configuración y lo carga en caso afirmativo
void cargarConfiguracion(ifstream &fichero, char &bSuma, char &bResta, char &bProducto, char &bDivision, 
						 char &bMemoria, char &bUsarMemoria, char &bRaiz, char &bExponente, char &bFactorial,
						 char &bBorrar, char &bSimplifica, char &bSalir){
	fichero.open("conf.txt");
	if (fichero.is_open()){	//Si existe un fichero carga los valores q hay en él
		fichero >> bSuma;
		fichero >> bResta;
		fichero >> bProducto;
		fichero >> bDivision;
		fichero >> bRaiz;
		fichero >> bExponente;
		fichero >> bFactorial;
		fichero >> bBorrar;
		fichero >> bMemoria;
		fichero >> bUsarMemoria;
		fichero >> bSimplifica;
		fichero >> bSalir;
	}
	//De lo contrario si no existe fichero, no carga nada
	fichero.close();
}

//Guarda los cambios de configuración hechos por el usuario, cuando se entra en el modo configuración
void guardarConfiguracion(ofstream &fichero, char &bSuma, char &bResta, char &bProducto, char &bDivision, 
						 char &bMemoria, char &bUsarMemoria, char &bRaiz, char &bExponente, char &bFactorial,
						 char &bBorrar, char &bSimplifica, char &bSalir, char &fijar){
	
	fichero.open("conf.txt");
			
	cout << "Cambiar caracter de suma " << "(" << bSuma << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){ //En caso de que se introduzca un INTRO, se quedará la configuración que ya estaba
		cin >> bSuma;
		fichero << bSuma << endl;
		cin.sync();
	}
				
	else {
		fichero << bSuma << endl;
		cin.sync();
	}

	cout << "Cambiar caracter de resta " << "(" << bResta << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bResta;
		fichero << bResta << endl;
		cin.sync();
	}
				
	else {
		fichero << bResta << endl;
		cin.sync();
	}
					
	cout << "Cambiar caracter de producto " << "(" << bProducto << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bProducto;
		fichero << bProducto << endl;
		cin.sync();
	}
				
	else {
		fichero << bProducto << endl;
		cin.sync();
	}
				
	cout << "Cambiar caracter de division " << "(" << bDivision << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bDivision;
		fichero << bDivision << endl;
		cin.sync();
	}
				
	else {
		fichero << bDivision << endl;
		cin.sync();
	}
				
	cout << "Cambiar caracter de la raiz " << "(" << bRaiz << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bRaiz;
		fichero << bRaiz << endl;
		cin.sync();
	}
					
	else {
		fichero << bRaiz << endl;
		cin.sync();
	}
				
	cout << "Cambiar caracter del exponente " << "(" << bExponente << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bExponente;
		fichero << bExponente << endl;
		cin.sync();
	}
					
	else {
		fichero << bExponente << endl;
		cin.sync();
	}
				
	cout << "Cambiar caracter del factorial " << "(" << bFactorial << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bFactorial;
		fichero << bFactorial << endl;
		cin.sync();
	}
				
	else {
		fichero << bFactorial << endl;
		cin.sync();
	}
					
	cout << "Cambiar caracter de borrar " << "(" << bBorrar << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bBorrar;
		fichero << bBorrar << endl;
	cin.sync();
	}
				
	else {
		fichero << bBorrar << endl;
		cin.sync();
	}
					
	cout << "Cambiar caracter de guardar en memoria " << "(" << bMemoria << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bMemoria;
		fichero << bMemoria << endl;
		cin.sync();
	}
				
	else {
		fichero << bMemoria << endl;
		cin.sync();
	}
		
	cout << "Cambiar caracter de usar valor de memoria " << "(" << bUsarMemoria << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bUsarMemoria;
		fichero << bUsarMemoria << endl;
		cin.sync();
	}
					
	else {
		fichero << bUsarMemoria << endl;
		cin.sync();
	}
	
	cout << "Cambiar caracter de simplificar " << "(" << bSimplifica << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bSimplifica;
		fichero << bSimplifica << endl;
		cin.sync();
	}
				
	else {
		fichero << bSimplifica << endl;
		cin.sync();
	}

	cout << "Cambiar caracter de salida " << "(" << bSalir << ") <INTRO> para mantener" << endl;
	fijar = cin.peek();
	if (fijar != '\n'){
		cin >> bSalir;
		fichero << bSalir << endl;
		cin.sync();
	}
				
	else {
		fichero << bSalir << endl;
		cin.sync();
	}
	
	cout << " " << endl;
	fichero.close();
	
}

//Aplicación (Programa Principal)

int main(){
	
	// Declaraciones de variables
	
	double operando1, operando2, resultado; //Variables de la calculadora básica
	int numerador1, numerador2, denominador1, denominador2, resultadoNum, resultadoDen; //Variables de la calculadora fraccionaria
	double memoria = 0;	//	Sirve para guardar un valor, si el usuario lo desea
	char operador;	//	Indicara la operacion a realizar por la calculadora
	//	Las siguientes variables recogen todos los operandores que la calculadora usara para operar
	char botonSuma = '+', botonResta = '-', botonProducto = '*', botonDivision = '/', botonMemoria = 'm', botonUsarMemoria = 'n';
    char botonRaiz = 'r', botonExponente = '^', botonFactorial = '!', botonBorrar = 'c', botonSalir = 'x'; 
	char botonSimplificar = 's';
	char mantener; // Variable que se usa para comprobar si se deja la configuracion como estaba
	bool error = false;	//	Esta variable nos indicara si el usuario introdujo algo mal por pantalla
	bool salida = false;	//	Se activara cuando el usuario quiera salir del programa
	bool borrar = false;	//	Se activara cuando el usuario quiera borrar y poner a 0 la calculadora
	int opcion;	//	Se utiliza en el menu para seleccionar una opción
	//Variables tipo fichero, dos para la configuración y una para guardar las operaciones de la calculadora básica
	ofstream archivo;
	ifstream conf_lectura;
	ofstream conf_escritura;
	
	//Antes de empezar el programa comprobamos si existe una configuración guardada y si la hay se carga
	cargarConfiguracion(conf_lectura, botonSuma, botonResta, botonProducto, botonDivision, botonMemoria,
						botonUsarMemoria, botonRaiz, botonExponente, botonFactorial, botonBorrar,
						botonSimplificar, botonSalir);

	//Mostramos por primera vez el Menú
	mostrarMenu(opcion);
	
	while (opcion != 4) {	//	Comienza el bucle que pedira que se introduzca una opcion valida en el Menú
		
		switch (opcion) {
	
		//En este caso se llevaran a cabo todas las operaciones de la calculadora básica
			case 1 :

				archivo.open("log.txt"); //Abrimos el fichero donde se guardaran las operaciones de la calculadora
				resultado = 0;	//Inicializamos a 0 siempre que se inicie la calculadora desde el menu
				do{
					salida = false;
					pedirDatos(archivo, resultado, operando1, operador);

					//Evalua la operación pedida a menos que se introduzca un INTRO, un error o salida
					while ((operador != '\n') && (error == false) && (salida == false)){
						if (operador == botonSuma)
							sumar(archivo, resultado, operando2, memoria);

						else if (operador == botonResta)
							restar(archivo, resultado, operando2, memoria);
      
						else if (operador == botonProducto)
							multiplicar(archivo, resultado, operando2, memoria);
					
						else if (operador == botonDivision)
							dividir(archivo, resultado, operando2, memoria);
					
						else if (operador == botonRaiz)
							raizCuadrada(resultado,error);
					
						else if (operador == botonExponente)
							elevar(archivo, resultado, operando2, error);
					
						else if (operador == botonFactorial)
							factorizar(resultado ,error);
						
						else if (operador == botonBorrar)
							pBorrar(resultado);

						else if (operador == botonSalir)
							pSalida(salida);
						
						else if (operador == botonMemoria)
							pMemoria(memoria, resultado);
						
						else if (operador == botonUsarMemoria)
							pUsarMemoria(memoria, resultado, operando2);

					//En cualquier otro caso en el que el operador no sea ninguna operación conocida, dará error

						else
							error = true;

					//FIN DE LOS OPERADORES
				
						if (error == true)
							cin.sync();	//Al detectarse el error quita todo lo introducido despues por el usuario
						
						else{	//Volvemos a pedir un operador para poder evaluar la situación de la expresión introducida por el usuario
							cin.get(operador);
							guardarOperador(archivo, operador);
						}
					}
				
					if (salida == false)
						MostrarResultadoError(archivo, resultado, error);
				
				} while (salida == false);

				break;

			case 2 :
				//Inicializamos el resultado fraccionario a 0
				resultadoNum = 0;
				resultadoDen = 1;

				do {
					salida = false;
					pedirFraccion(resultadoNum, resultadoDen, numerador1, denominador1, operador);
						//Evalua las operaciones hasta introducirse un error, INTRO o se quiera salir
						while ((operador != '\n') && (error == false) && (salida == false)){
						
							if (operador == botonSuma){
								leerSegundaFraccion(numerador2, denominador2, operador);
								sumarFraccion(resultadoNum, resultadoDen, numerador2, denominador2);
							}

							else if (operador == botonResta){
								leerSegundaFraccion(numerador2, denominador2, operador);
								restarFraccion(resultadoNum, resultadoDen, numerador2, denominador2);
							}

							else if (operador == botonProducto){
								leerSegundaFraccion(numerador2, denominador2, operador);
								multiplicarFraccion(resultadoNum, resultadoDen, numerador2, denominador2);
							}
						
							else if (operador == botonDivision){
								leerSegundaFraccion(numerador2, denominador2, operador);
								dividirFraccion(resultadoNum, resultadoDen, numerador2, denominador2);
							}
							
							else if (operador == botonExponente){
								elevarFraccion(resultadoNum, resultadoDen, numerador2, error);
								cin.get(operador);
							}
							
							else if (operador == botonSimplificar){
								simplificar(resultadoNum, resultadoDen);
								cin.get(operador);
							}
							
							else if (operador == botonBorrar){
								borrarFraccion(resultadoNum, resultadoDen);
								cin.get(operador);
							}
							
							else if (operador == botonSalir)
								pSalida(salida);
								
							else
								error = true;
							
							if (error == true)
								cin.sync();

						}
						
						if (salida == false)
							mostrarResultadoErrorFraccion(resultadoNum, resultadoDen, error);
						
				} while (salida == false);

				break;

			
			case 3 : 
			//Esta es la parte en la que el usuario accederá a la configuración de la calculadora
				guardarConfiguracion(conf_escritura, botonSuma, botonResta, botonProducto, botonDivision,
									 botonMemoria, botonUsarMemoria, botonRaiz, botonExponente, botonFactorial,
									 botonBorrar, botonSimplificar, botonSalir, mantener);
				
				break;
		}
	mostrarMenu(opcion);

	}
		archivo.close(); //Importante cerrar el archivo de escritura de la calculadora básica
		return 0;
		
}