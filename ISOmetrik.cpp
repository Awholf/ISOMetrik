#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

using namespace std;

struct Admin {
    string usuario;
    string contrasena;
};

struct Cliente {
    string usuario;
    string contrasena;
};

struct Proyecto {
    string nombre;
    string descripcion;
    vector<string> requerimientos;
    string cronograma;
    string objetivos;
    string tareas;
    string duracion;
    int duracionSemanas = 0;
    vector<float> presupuestoSemanal;
    string secuencia;
    string recursos;
    string fechas;
    string seguimiento;
    float presupuestoTotal = 0;
    string actividades;
    int numRecursos = 0;
    float costoObjetivos = 0;
    float costoTareas = 0;
    float costoActividades = 0;
    float costoRecursos = 0;
    float costoTotal = 0;
    string fechaPlazo;
    string fechaLimite;
};
void RegistrarUsuario(const string& filename, vector<Admin>& users, vector<Cliente>& usuarios);
bool Login(const vector<Admin>& users, const vector<Cliente>& usuarios);
void AgregarProyecto(vector<Proyecto>& projects);
void AgregarRequisitos(vector<Proyecto>& projects);
void MostrarProyectos(const vector<Proyecto>& projects);
void MostrarRequisitos(const vector<Proyecto>& projects);
void AsignarCronograma(vector<Proyecto>& projects);
int main() {

    const string filename = "users.txt";
    vector<Admin> administradores;
    vector<Proyecto> proyectos;
    vector<Cliente> clientes;
    bool loggeado = false;

    Admin admin1, admin2, admin3, admin4;
    admin1.usuario = "Adolfo";
    admin1.contrasena = "Adolfito24";
    admin2.usuario = "Montenegro";
    admin2.contrasena = "litomireligion20";
    admin3.usuario = "Mendoza";
    admin3.contrasena = "Zanahoria123";
    admin4.usuario = "Avalos";
    admin4.contrasena = "987";

    administradores.push_back(admin1);
    administradores.push_back(admin2);
    administradores.push_back(admin3);
    administradores.push_back(admin4);

    Cliente cliente1, cliente2, cliente3, cliente4;
    cliente1.usuario = "Juan";
    cliente1.contrasena = "Juancito123";
    cliente2.usuario = "Raul";
    cliente2.contrasena = "Raulcito123";
    cliente3.usuario = "Dante";
    cliente3.contrasena = "Dantecito123";
    cliente4.usuario = "Jhon";
    cliente4.contrasena = "Jhoncito123";
    clientes.push_back(cliente1);
    clientes.push_back(cliente2);
    clientes.push_back(cliente3);
    clientes.push_back(cliente4);
    cout << "             Sistema de Gestion de Proyectos - ISOMetrics" << endl << endl;
    while (true) {
        int choice;
        if (loggeado) {
            cout << "Opciones:\n1. Agregar proyecto\n2. Agregar requisitos a proyecto\n3. Mostrar proyectos\n4. Mostrar requisitos de proyecto\n5. Asignar cronograma\n6. Salir" << endl;
        }
        else {
            cout << "Opciones:\n1. Registrarse\n2. Iniciar sesion\n3. Salir" << endl;
        }
        cout << "Por favor elija una opcion: ";
        cin >> choice;
        cout << endl;
        system("cls");
        switch (choice) {
        case 1:
            if (!loggeado) {
                RegistrarUsuario(filename, administradores, clientes);
            }
            else {
                AgregarProyecto(proyectos);
            }
            break;
        case 2:
            if (!loggeado) {
                loggeado = Login(administradores, clientes);
            }
            else {
                AgregarRequisitos(proyectos);
            }
            break;
        case 3:
            if (loggeado) {
                MostrarProyectos(proyectos);
            }
            else
                exit(0);
            break;
        case 4:
            if (loggeado) {
                MostrarRequisitos(proyectos);
            }
            break;
        case 5:
            if (loggeado) {
                AsignarCronograma(proyectos);
            }
            break;
        case 6:
            exit(0);
        default:
            cout << "Opcion no valida. Introduce una opcion valida." << endl;
        }
        cout << endl;
    }
    return 0;
}

void RegistrarUsuario(const string& filename, vector<Admin>& users, vector<Cliente>& usuarios) {
    Admin newAdmin;
    cout << "Ingresa un nombre de usuario: ";
    cin >> newAdmin.usuario;
    cout << "Ingresa una contrasena: ";

    char c;
    newAdmin.contrasena = "";
    while (true) {
        c = _getch();
        if (c == 13) {
            break;
        }
        else if (c == 8 && !newAdmin.contrasena.empty()) {
            cout << "\b \b";
            newAdmin.contrasena.pop_back();
        }
        else {
            newAdmin.contrasena += c;
            cout << '*';
        }
    }

    users.push_back(newAdmin);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << newAdmin.usuario << " " << newAdmin.contrasena << "\n";
        file.close();
        cout << "\nUsuario registrado exitosamente." << endl;
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
    cout << endl;
}

bool Login(const vector<Admin>& users, const vector<Cliente>& usuarios) {
    string username, password;
    cout << "Ingresa tu nombre de usuario: ";
    cin >> username;
    cout << "Ingresa tu contrasena: ";

    char c;
    password = "";
    while (true) {
        c = _getch();
        if (c == 13) {
            break;
        }
        else if (c == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password += c;
            cout << '*';
        }
    }
    system("cls");
    for (const Admin& user : users) {
        if (user.usuario == username && user.contrasena == password) {
            cout << "\nIniciaste sesion con exito." << endl;
            return true;
        }
    }

    for (const Cliente& user : usuarios) {
        if (user.usuario == username && user.contrasena == password) {
            cout << "\nIniciaste sesion con exito." << endl;
            return true;
        }
    }

    cout << "\nUsuario o contrasena incorrectos." << endl;
    return false;

}

void AgregarProyecto(vector<Proyecto>& projects) {
    do {
        Proyecto newProject;
        cout << "Nombre del proyecto: ";
        cin.ignore();
        getline(cin, newProject.nombre);
        cout << "Descripcion del proyecto: ";
        getline(cin, newProject.descripcion);
        projects.push_back(newProject);
        cout << "Proyecto agregado exitosamente." << endl;

        char respuesta;
        cout << "Desea agregar otro proyecto? (S/N): ";
        cin >> respuesta;
        if (respuesta != 'S' && respuesta != 's') {
            break;
        }
    } while (true);
    cout << endl;
}


void AgregarRequisitos(vector<Proyecto>& projects) {
    int projectIndex;
    if (projects.empty()) {
        cout << "No hay proyectos disponibles para agregar requisitos. Primero agrega proyectos." << endl;
        return;
    }
    cout << "Proyectos Disponibles:\n";
    cout << "--------------------------------\n";
    cout << "Indice\tNombre del Proyecto\n";
    cout << "--------------------------------";
    for (size_t i = 0; i < projects.size(); ++i) {
        cout << "\n   " << i + 1 << "\t      " << projects[i].nombre << endl;
    }
    cout << "--------------------------------\n";
    cout << "Selecciona el proyecto al que deseas agregar requisitos (indice): ";
    cin >> projectIndex;
    if (projectIndex >= 1 && projectIndex <= projects.size()) {
        string requirement;
        cout << "Selecciona el requisito que deseas agregar al proyecto:" << endl;
        cout << "Opciones:\n";
        cout << "\t1. Clausula 4 - Determinar las cuestiones externas e internas que son pertinentes para su proposito y que afectan a su capacidad para lograr los resultados previstos de su sistema de gestion antisoborno.\n";
        cout << "\t--------------------------------\n";
        cout << "\t2. Clausula 5 - La alta direccion debe establecer, mantener y revisar una politica antisoborno.\n";
        cout << "\t--------------------------------\n";
        cout << "\t3. Clausula 6 - La organizacion debe establecer los objetivos del sistema de gestion antisoborno para las funciones y niveles pertinentes.\n";
        cout << "\t--------------------------------\n";
        cout << "\t4. Clausula 7 - La organizacion debe determinar y proporcionar los recursos necesarios para el establecimiento, implementacion, mantenimiento y mejora continua del sistema de gestion antisoborno.\n";
        cout << "\t--------------------------------\n";
        cout << "\t5. Clausula 8 - La organizacion debe planificar, implementar, revisar y controlar los procesos necesarios para cumplir los requisitos del sistema de gestion antisoborno.\n";
        cout << "\t--------------------------------\n";
        cout << "\t6. Clausula 9 - La organizacion debe llevar a cabo auditorias internas a intervalos planificados, para proporcionar informacion acerca de si el sistema de gestion antisoborno.\n";
        cout << "\t--------------------------------\n";
        cout << "\t7. Clausula 10 - La organizacion debe mejorar continuamente la idoneidad, adecuacion y eficacia del sistema de gestion antisoborno.\n";
        cout << "\t--------------------------------\n";
        int eleccion;
        cin >> eleccion;
        switch (eleccion) {
        case 1:
            requirement = "Implementacion de la clausula 4 - Determinar las cuestiones externas e internas que son pertinentes para su proposito y que afectan a su capacidad para lograr los resultados previstos de su sistema de gestion antisoborno.";
            break;
        case 2:
            requirement = "Implementacion de la clausula 5 - La alta direccion debe establecer, mantener y revisar una politica antisoborno.";
            break;
        case 3:
            requirement = "Implementacion de la clausula 6 - La organizacion debe establecer los objetivos del sistema de gestion antisoborno para las funciones y niveles pertinentes.";
            break;
        case 4:
            requirement = "Implementacion de la clausula 7 - La organizacion debe determinar y proporcionar los recursos necesarios para el establecimiento, implementacion, mantenimiento y mejora continua del sistema de gestion antisoborno.";
            break;
        case 5:
            requirement = "Implementacion de la clausula 8 - La organizacion debe planificar, implementar, revisar y controlar los procesos necesarios para cumplir los requisitos del sistema de gestion antisoborno.";
            break;
        case 6:
            requirement = "Implementacion de la clausula 9 - La organizacion debe llevar a cabo auditorias internas a intervalos planificados, para proporcionar informacion acerca de si el sistema de gestion antisoborno.";
            break;
        case 7:
            requirement = "Implementacion de la clausula 10 - La organizacion debe mejorar continuamente la idoneidad, adecuacion y eficacia del sistema de gestion antisoborno.";
            break;
        default:
            cout << "Opcion no valida. Introduce una opcion valida." << endl;
            return;
        }

        projects[projectIndex - 1].requerimientos.push_back(requirement);
        cout << "Requisito agregado exitosamente." << endl;
    }
    else {
        cout << "Indice de proyecto no valido." << endl;
    }

    cout << endl;
}

void MostrarProyectos(const vector<Proyecto>& projects) {
    cout << "Lista de proyectos:" << endl;
    for (size_t i = 0; i < projects.size(); ++i) {
        cout << i + 1 << ". " << projects[i].nombre << "\nDescripcion: " << projects[i].descripcion << endl;
    }
    cout << endl;
}

void MostrarRequisitos(const vector<Proyecto>& projects) {
    if (projects.empty()) {
        cout << "No hay proyectos disponibles. Debes agregar proyectos primero." << endl;
        return;
    }

    cout << "Lista de proyectos:" << endl;
    cout << "--------------------------------\n";
    cout << "ID\tNombre del Proyecto\n";
    cout << "--------------------------------\n";

    for (size_t i = 0; i < projects.size(); ++i) {
        cout << i + 1 << "\t" << projects[i].nombre << endl;
    }

    int projectIndex;
    cout << "Selecciona el proyecto del que deseas ver los requisitos (indice): ";
    cin >> projectIndex;

    if (projectIndex >= 1 && projectIndex <= projects.size()) {
        const Proyecto& project = projects[projectIndex - 1];
        cout << "Requisitos para el proyecto '" << project.nombre << "':" << endl;
        cout << "--------------------------------\n";
        cout << "ID\tRequisito\n";
        cout << "--------------------------------\n";

        if (project.requerimientos.empty()) {
            cout << "Sin requisitos" << endl;
        }
        else {
            for (size_t i = 0; i < project.requerimientos.size(); ++i) {
                cout << i + 1 << "\t" << project.requerimientos[i] << endl;
            }
        }
    }
    else {
        cout << "Indice de proyecto no valido." << endl;
    }
    cout << endl;
}
void AsignarCronograma(vector<Proyecto>& projects) {
    int projectIndex;

    cout << "Seleccione un proyecto para asignar un cronograma:" << endl;
    cout << "------------------------------------" << endl;

    for (size_t i = 0; i < projects.size(); ++i) {
        cout << i + 1 << ". " << projects[i].nombre << endl;
    }
    cout << endl;
    cout << "------------------------------------" << endl;
    cin >> projectIndex;
    cout << "------------------------------------" << endl;
    if (projectIndex >= 1 && projectIndex <= projects.size()) {
        Proyecto& project = projects[projectIndex - 1];

        int submenuChoice;
        do {
            cout << "------------------------------------" << endl;
            cout << "Submenu de Asignacion de Cronograma:" << endl;
            cout << "------------------------------------" << endl;
            cout << "1. Definir los Objetivos del Proyecto" << endl;
            cout << "2. Identificar las Tareas y Actividades" << endl;
            cout << "3. Asignar Recursos" << endl;
            cout << "4. Establecer Plazos y Fechas Limite" << endl;
            cout << "5. Descargar documentacion" << endl;
            cout << "6. Finalizar asignacion de cronograma" << endl;
            cout << "------------------------------------" << endl;
            cin >> submenuChoice;
            cout << "------------------------------------" << endl;
            string name;
            char download = ' ';
            project.costoTotal = project.costoActividades + project.costoObjetivos + project.costoRecursos + project.costoTareas;
            switch (submenuChoice) {

            case 1:
                cout << "Ingrese la cantidad de objetivos del proyecto: ";
                int numObjetivos;
                cin >> numObjetivos;
                cin.ignore();

                cout << "Ingrese los objetivos del proyecto (uno por linea):" << endl;
                project.objetivos.clear();
                for (int i = 0; i < numObjetivos; i++) {
                    cout << " ";
                    cout << " ";
                    string objetivo;
                    getline(cin, objetivo);
                    project.objetivos += objetivo;
                    if (i < numObjetivos - 1) {
                        project.objetivos += "\n";
                    }
                }
                for (int i = 0; i < numObjetivos; i++) {
                    cout << " ";
                    cout << "Costo para el Objetivo " << i + 1 << ": $";
                    float costoObjetivo;
                    cin >> costoObjetivo;
                    project.costoObjetivos += costoObjetivo;
                }
                break;
            case 2:
                int numTareas, numActividades;

                cout << "Ingrese la cantidad de tareas: ";
                cin >> numTareas;
                cin.ignore();

                cout << "Ingrese las tareas del proyecto (una por linea):" << endl;
                project.tareas.clear();
                for (int i = 0; i < numTareas; i++) {
                    cout << " ";
                    string tarea;
                    getline(cin, tarea);
                    project.tareas += tarea;
                    if (i < numTareas - 1) {
                        project.tareas += "\n";
                    }
                }
                project.costoTareas = 0;
                for (int i = 0; i < numTareas; i++) {
                    cout << " ";
                    cout << "Costo para la Tarea " << i + 1 << ": $";
                    float costoTarea;
                    cin >> costoTarea;
                    project.costoTareas += costoTarea;
                }

                cout << "Ingrese la cantidad de actividades: ";
                cin >> numActividades;
                cin.ignore();

                cout << "Ingrese las actividades del proyecto (una por linea):" << endl;
                project.actividades.clear();
                for (int i = 0; i < numActividades; i++) {
                    cout << " ";
                    string actividad;
                    getline(cin, actividad);
                    project.actividades += actividad;
                    if (i < numActividades - 1) {
                        project.actividades += "\n";
                    }
                }
                project.costoActividades = 0;
                for (int i = 0; i < numActividades; i++) {
                    cout << " ";
                    cout << "Costo para la Actividad " << i + 1 << ": $";
                    float costoActividad;
                    cin >> costoActividad;
                    project.costoActividades += costoActividad;
                }
                break;
            case 3:

                cout << "Ingrese la cantidad de recursos necesarios: ";
                cin >> project.numRecursos;
                cin.ignore();

                cout << "Ingrese los recursos necesarios del proyecto (uno por linea):" << endl;
                project.recursos.clear();
                for (int i = 0; i < project.numRecursos; i++) {
                    cout << " ";
                    string recurso;
                    getline(cin, recurso);
                    project.recursos += recurso;
                    if (i < project.numRecursos - 1) {
                        project.recursos += "\n";
                    }
                }
                project.costoRecursos = 0;
                for (int i = 0; i < project.numRecursos; i++) {
                    cout << " ";
                    cout << "Costo para el Recurso " << i + 1 << ": $";
                    float costoRecurso;
                    cin >> costoRecurso;
                    project.costoRecursos += costoRecurso;
                }
                break;
            case 4:
                cout << " Establezca plazos y fechas limite (formato dd/mm/aaaa): ";
                cin.ignore();
                cout << endl;
                cout << "Fecha de inicio: ";
                getline(cin, project.fechaPlazo);
                cout << "Fecha limite: ";
                getline(cin, project.fechaLimite);
                break;

            case 5:
                cout << " Digite el nombre del proyecto: ";
                cin >> name;
                cout << "  Desea descargar la documentacion? (S/N): ";
                cin >> download;
                cin.ignore();

                if (download == 'S' || download == 's') {
                    ofstream archivo(name + ".txt");

                    archivo << "\t" << project.nombre << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Objetivos del proyecto:\n" << project.objetivos << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Requisito: " << project.requerimientos[0] << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Tareas del proyecto:\n" << project.tareas << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Actividades del proyecto:\n" << project.actividades << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Recursos necesarios (" << project.numRecursos << "):\n" << project.recursos << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Fecha de inicio: " << project.fechaPlazo << "\nFecha limite: " << project.fechaLimite << endl;
                    archivo << "------------------------------------" << endl;
                    archivo << "Costo Total: $" << project.costoTotal << endl;

                    archivo.close();
                    cout << "------------------------------------" << endl;
                    cout << "El archivo " << name << ".txt ha sido descargado." << endl;
                    cout << "____________________________________" << endl;
                }
                else {
                    break;
                }
                project.cronograma = "Cronograma generado y documentado.";
                break;

            case 6:
                cout << " Asignacion de cronograma finalizada." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
            }
        } while (submenuChoice != 6);
    }
    else {
        cout << "Indice de proyecto no valido." << endl;
    }
}