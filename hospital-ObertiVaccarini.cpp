#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;
struct pacientes {
	char nombre[20];
	int edad;
	int DNI;
	int diasInternado;
};


int validacionCamasFilas ();
int validacionCamasColumnas ();
int totalCamas (int, int);
int validacionCamas(int, int);
void informacionPacientes (pacientes[100][100], int, int, int[100][100]);
void validacionEdad (pacientes[100][100], int, int);
void validacionDNI (pacientes[100][100], int, int);
void validacionDiasInternados (pacientes[100][100], int, int);
void archivoInformacionPacientes (pacientes[100][100], int, int, int);
void pacientesCincoDias (pacientes[100][100], int, int);
float promedioEdadesPacientes (pacientes[100][100], int, int, int);
void pacientesEdadesMayoresPromedio (pacientes[100][100], float, int, int);
void busquedaPaciente (pacientes[100][100], int, int, int, int);
void pacientesContagiados (pacientes[100][100], int, int, int, int, int[100][100]);

int main() {

system("Color 71");

	pacientes datosPacientes[100][100];
	int existenciaPosicion[100][100];
	int camaFila;
	int camaColumna;
	int camasTotales;
	float promedioEdades;
	int posicionFila;
	int posicionColumna;
	int posicionFilaContagiado;
	int posicionColumnaContagiado;

	cout<<"*****************************************************************************************"<<endl;
	cout<<"*******************************HOSPITAL PRIVADO DE CORDOBA*******************************"<<endl;
	cout<<"**************************CASOS DE CORONAVIRUS: CEPA BRASILERA***************************"<<endl;
	cout<<"*****************************************************************************************"<<endl;

	do {

		camaFila=validacionCamasFilas();

	} while(!camaFila || camaFila<0);

	do {

		camaColumna=validacionCamasColumnas();

	} while(!camaColumna || camaColumna<0);

	camasTotales=totalCamas(camaFila, camaColumna);

	do {
		if (camasTotales<=50 && camasTotales>0) {

			cout<<endl<<"La cantidad total de camas ocupadas es de: "<<camasTotales<<endl;
		}
		else {
			do {

				if (camasTotales>50) {
					cout<<endl<<"La cantidad de camas en la habitacion es invalida. Por favor, ingrese nuevamente."<<endl;

					do {

						camaFila=validacionCamasFilas();

					} while(!camaFila || camaFila<0);

					do {

						camaColumna=validacionCamasColumnas();

					} while(!camaColumna || camaColumna<0);
				}

				camasTotales=totalCamas(camaFila, camaColumna);

				if (camasTotales<=50 && camasTotales>0) {

					cout<<endl<<"La cantidad total de camas ocupadas es de: "<<camasTotales<<endl;
				}

			} while (camasTotales>50 || camasTotales<0);
		}
	} while(camasTotales>50 || camasTotales<0);


	cout<<endl<<"*****************************************************************************************"<<endl;
	cout<<"***************************DATOS DE LOS PACIENTES DEL HOSPITAL***************************"<<endl;
	informacionPacientes(datosPacientes, camaFila, camaColumna, existenciaPosicion);
	archivoInformacionPacientes(datosPacientes, camaFila, camaColumna, camasTotales);
	cout<<endl<<"*****************************************************************************************"<<endl;

	pacientesCincoDias(datosPacientes, camaFila, camaColumna);

	promedioEdades=promedioEdadesPacientes(datosPacientes, camaFila, camaColumna, camasTotales);
	cout<<endl<<"*******************************PROMEDIO DE LAS EDADES************************************"<<endl;
	cout<<endl<<"El promedio de edad dentro de la habitacion es de: "<<promedioEdades<<endl;

	pacientesEdadesMayoresPromedio(datosPacientes, promedioEdades, camaFila, camaColumna);

	cout<<endl<<"*****************************************************************************************"<<endl;
	cout<<"*******************************DATOS DEL PACIENTE DESEADO********************************"<<endl;
	cout<<"******************RECUERDE QUE SE INICIA DESDE LA FILA Y COLUMNA 1 (UNO)*****************"<<endl;
	cout<<"*****************************************************************************************"<<endl;
	cout<<"Ingrese la posicion de la fila de la cama del paciente: ";
	cin>>posicionFila;
	cout<<"Ingrese la posicion de la columna de la cama del paciente: ";
	cin>>posicionColumna;

	busquedaPaciente(datosPacientes, camaFila, camaColumna, posicionFila, posicionColumna);
	cout<<endl<<"*****************************************************************************************"<<endl;

	cout<<endl<<"*****************************************************************************************"<<endl;
	cout<<"***********************************PACIENTE INFECTADO************************************"<<endl;
	cout<<"******************RECUERDE QUE SE INICIA DESDE LA FILA Y COLUMNA 1 (UNO)*****************"<<endl;
	cout<<"*****************************************************************************************"<<endl;
	cout<<"Ingrese la posicion de la fila de la cama del paciente: ";
	cin>>posicionFilaContagiado;
	cout<<"Ingrese la posicion de la columna de la cama del paciente: ";
	cin>>posicionColumnaContagiado;

	pacientesContagiados(datosPacientes, camaFila, camaColumna, posicionFilaContagiado, posicionColumnaContagiado, existenciaPosicion);
	cout<<endl<<"*****************************************************************************************"<<endl;

	return 0;
}

int validacionCamasFilas () {
	int camasFila;

	cout<<endl<<"Indique la cantidad de camas que tienen las filas de la habitacion: ";
	cin.clear();
	cin>>camasFila;

	if (!camasFila || camasFila<0) {
		cout<<endl<<"La cantidad de camas por filas es invalido. Por favor, ingrese nuevamente.";
		cin.clear();
		cin.ignore();
	}

	return camasFila;
}

int validacionCamasColumnas () {
	int camasColumna;

	cout<<endl<<"Indique la cantidad de camas que tienen las columnas de la habitacion: ";
	cin.clear();
	cin>>camasColumna;

	if (!camasColumna || camasColumna<0) {
		cout<<endl<<"La cantidad de camas por columnas es invalido. Por favor, ingrese nuevamente.";
		cin.clear();
		cin.ignore();
	}

	return camasColumna;
}

int totalCamas (int camaFila, int camaColumna) {
	int camasTotal;

	camasTotal=camaFila*camaColumna;

	return camasTotal;
}

void informacionPacientes (pacientes datosPacientes[100][100], int camaFila, int camaColumna, int existenciaPosicion[100][100]){
	int i;
	int j;

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {

			cout<<endl<<"DATOS DEL PACIENTE QUE SE ENCUENTRA EN LA "<<i+1<<"° FILA Y LA "<<j+1<<"° COLUMNA DE CAMAS."<<endl;

			cin.ignore();
			cout<<"Ingrese el nombre del paciente: ";
			cin.getline(datosPacientes[i][j].nombre, 20, '\n');
			do {
				cout<<"Ingrese la edad del paciente: ";
				cin>>datosPacientes[i][j].edad;

				validacionEdad(datosPacientes, i, j);

			} while (!datosPacientes[i][j].edad || datosPacientes[i][j].edad>100 || datosPacientes[i][j].edad<0);

			do {
				cout<<"Ingrese el DNI del paciente: ";
				cin>>datosPacientes[i][j].DNI;

				validacionDNI(datosPacientes, i, j);

			} while (!datosPacientes[i][j].DNI || datosPacientes[i][j].DNI<0 || datosPacientes[i][j].DNI<1000000);

			do {
				cout<<"Ingrese la cantidad de dias internados: ";
				cin>>datosPacientes[i][j].diasInternado;

				validacionDiasInternados(datosPacientes, i, j);

			} while (!datosPacientes[i][j].diasInternado || datosPacientes[i][j].diasInternado<0);

			existenciaPosicion[i][j]=1;

		}
	}

}

void validacionEdad (pacientes datosPacientes[100][100], int i, int j) {

	if (!datosPacientes[i][j].edad || datosPacientes[i][j].edad>100 || datosPacientes[i][j].edad<0) {
		cout<<"Por favor, ingrese una edad valida."<<endl;
		cin.clear();
		cin.ignore();
	}

}

void validacionDNI (pacientes datosPacientes[100][100], int i, int j) {

	if (!datosPacientes[i][j].DNI || datosPacientes[i][j].DNI<0 || datosPacientes[i][j].DNI<1000000) {
		cout<<"Por favor, ingrese un DNI valido."<<endl;
		cin.clear();
		cin.ignore();;
	}
}

void validacionDiasInternados (pacientes datosPacientes[100][100], int i, int j) {

	if (!datosPacientes[i][j].diasInternado || datosPacientes[i][j].diasInternado<0) {
		cout<<"Por favor, ingrese una cantidad de dias valida."<<endl;
		cin.clear();
		cin.ignore();
	}
}

void archivoInformacionPacientes(pacientes datosPacientes[100][100], int camaFila, int camaColumna, int camasTotales) {
	int i;
	int j;
	ofstream pacientesHospital;

	pacientesHospital.open("pacientesHospitalPrivado.txt");

	pacientesHospital << "La cantidad de pacientes internados es de: " << camasTotales <<endl;

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {
			pacientesHospital << endl<<"DATOS DEL PACIENTE QUE SE ENCUENTRA EN LA "<<i+1<<"° FILA Y LA "<<j+1<<"° COLUMNA DE CAMAS."<<endl;
			pacientesHospital << "Nombre: "<<datosPacientes[i][j].nombre<<endl;
			pacientesHospital << "Edad: "<<datosPacientes[i][j].edad<<endl;
			pacientesHospital << "DNI: "<<datosPacientes[i][j].DNI<<endl;
			pacientesHospital << "Dias internado: "<<datosPacientes[i][j].diasInternado<<endl;
			pacientesHospital <<endl;
		}
	}
}

void pacientesCincoDias (pacientes datosPacientes[100][100], int camaFila, int camaColumna) {

	int i;
	int j;

	ofstream internadosDias;

	internadosDias.open("PICincoDiasOMas.txt");

	internadosDias << "Nombres de los pacientes que con mas de 5 dias internados:\n";

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {

			if (datosPacientes[i][j].diasInternado>=5) {

				internadosDias << datosPacientes[i][j].nombre <<endl;
			}
		}
	}

	internadosDias.close();
}

float promedioEdadesPacientes (pacientes datosPacientes[100][100], int camaFila, int camaColumna, int camasTotales){

	int i;
	int j;
	float sumaEdades;
	float promedio;

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {

			sumaEdades=sumaEdades+datosPacientes[i][j].edad;
		}
	}

	promedio=sumaEdades/camasTotales;

	return promedio;
}

void pacientesEdadesMayoresPromedio (pacientes datosPacientes[100][100], float promedio, int camaFila, int camaColumna) {

	int i;
	int j;

	ofstream internadosEdades;

	internadosEdades.open("PIEdadMayorPromedio.txt");

	internadosEdades << "Nombres y DNI de los pacientes que con edades mayores al promedio:\n";

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {

			if (datosPacientes[i][j].edad>promedio) {

				internadosEdades << datosPacientes[i][j].nombre <<" - ";
				internadosEdades << datosPacientes[i][j].DNI <<endl;
			}
		}
	}

	internadosEdades.close();
}

void busquedaPaciente (pacientes datosPacientes[100][100], int camaFila, int camaColumna, int posicionFila, int posicionColumna) {

	int i;
	int j;

	for(i=0;i<camaFila;i++) {

		for(j=0;j<camaColumna;j++) {

			if (posicionFila==(i+1) && posicionColumna==(j+1)){
				cout<<endl<<"Nombre del paciente: "<<datosPacientes[i][j].nombre<<endl;
				cout<<"Edad del paciente: "<<datosPacientes[i][j].edad<<endl;
				cout<<"DNI del paciente: "<<datosPacientes[i][j].DNI<<endl;
				cout<<"Dias que estuvo internado: "<<datosPacientes[i][j].diasInternado<<endl;
			}
		}
	}

}

void pacientesContagiados (pacientes datosPacientes[100][100], int camaFila, int camaColumna, int posicionFilaContagiado, int posicionColumnaContagiado, int existenciaPosicion[100][100]=0) {

	int i;
	int j;
	int totalPacientesContagiados=0;

	ofstream pacientesInfectados;

	pacientesInfectados.open("PContagiados.txt");

	pacientesInfectados << "Nombres de los pacientes infectados:\n";

	if (posicionFilaContagiado<=camaFila && posicionColumnaContagiado<=camaColumna && posicionFilaContagiado>0 && posicionColumnaContagiado>0){

		for(i=0;i<camaFila;i++) {

			for(j=0;j<camaColumna;j++) {

				if (posicionFilaContagiado==(i+1) && posicionColumnaContagiado==(j+1)){

					if (existenciaPosicion[i][j-1]==1){
						pacientesInfectados << datosPacientes[i][j-1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i][j+1]==1){
						pacientesInfectados << datosPacientes[i][j+1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i-1][j]==1){
						pacientesInfectados << datosPacientes[i-1][j].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i-1][j-1]==1){
						pacientesInfectados << datosPacientes[i-1][j-1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i-1][j+1]==1){
						pacientesInfectados << datosPacientes[i-1][j+1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i+1][j]==1){
						pacientesInfectados << datosPacientes[i+1][j].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i+1][j-1]==1){
						pacientesInfectados << datosPacientes[i+1][j-1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}

					if (existenciaPosicion[i+1][j+1]==1){
						pacientesInfectados << datosPacientes[i+1][j+1].nombre <<endl;
						totalPacientesContagiados=totalPacientesContagiados+1;
					}
				}
			}
		}
	}

	else {
		do {

			if (posicionFilaContagiado>camaFila){
				cout<<"La posicion deseada no puede ser mayor a la cantidad de camas por fila. Por favor, ingrese nuevamente la posicion de la fila de la cama del paciente: "<<endl;
				cin>>posicionFilaContagiado;
			}

			if (posicionColumnaContagiado>camaColumna){
				cout<<"La posicion deseada no puede ser mayor a la cantidad de camas por columna. Por favor, ingrese nuevamente la posicion de la columna de la cama del paciente: "<<endl;
				cin>>posicionColumnaContagiado;
			}

			if (posicionFilaContagiado<0){
				cout<<"La posicion deseada no puede ser negativa. Por favor, ingrese nuevamente la posicion de la fila de la cama del paciente: "<<endl;
				cin>>posicionFilaContagiado;
			}

			if (posicionColumnaContagiado<0){
				cout<<"La posicion deseada no puede ser negativa. Por favor, ingrese nuevamente la posicion de la columna de la cama del paciente: "<<endl;
				cin>>posicionColumnaContagiado;
			}

		} while (posicionFilaContagiado>camaFila || posicionColumnaContagiado>camaColumna || posicionFilaContagiado<0 || posicionColumnaContagiado<0);
	}

	cout<<endl<<"La cantidad de pacientes infectados que tiene alrededor son: "<<totalPacientesContagiados<<endl;

	pacientesInfectados.close();
}
