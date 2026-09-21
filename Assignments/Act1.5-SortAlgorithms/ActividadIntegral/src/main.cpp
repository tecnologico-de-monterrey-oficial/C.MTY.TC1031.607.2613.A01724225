#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Registro {
    long long fechaHora;
    string lineaOriginal;

    bool operator<(const Registro &otro) const {
        return fechaHora < otro.fechaHora;
    }

    bool operator>(const Registro &otro) const {
        return fechaHora > otro.fechaHora;
    }

    bool operator<=(const Registro &otro) const {
        return fechaHora <= otro.fechaHora;
    }
};

int numeroMes(const string &mes) {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;

    return 0;
}

long long crearClaveFecha(
    int anio,
    int mes,
    int dia,
    int hora,
    int minuto,
    int segundo
) {
    long long clave = anio;

    clave = clave * 100 + mes;
    clave = clave * 100 + dia;
    clave = clave * 100 + hora;
    clave = clave * 100 + minuto;
    clave = clave * 100 + segundo;

    return clave;
}

vector<Registro> leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<Registro> registros;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << '\n';
        return registros;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        istringstream entrada(linea);
        string mesTexto;
        string horaTexto;
        int dia;
        int anio;

        entrada >> mesTexto >> dia >> anio >> horaTexto;

        int mes = numeroMes(mesTexto);

        if (entrada.fail() || mes == 0 || horaTexto.size() != 8) {
            cout << "Linea invalida: " << linea << '\n';
            continue;
        }

        int hora = stoi(horaTexto.substr(0, 2));
        int minuto = stoi(horaTexto.substr(3, 2));
        int segundo = stoi(horaTexto.substr(6, 2));

        Registro registro;
        registro.fechaHora = crearClaveFecha(
            anio,
            mes,
            dia,
            hora,
            minuto,
            segundo
        );
        registro.lineaOriginal = linea;

        registros.push_back(registro);
    }

    return registros;
}

bool guardarArchivo(
    const string &nombreArchivo,
    const vector<Registro> &registros
) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo: " << nombreArchivo << '\n';
        return false;
    }

    for (const Registro &registro : registros) {
        archivo << registro.lineaOriginal << '\n';
    }

    return true;
}

template <typename T>
vector<T> swapSort(vector<T> v) {
    for (size_t i = 0; i + 1 < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[i]) {
                swap(v[j], v[i]);
            }
        }
    }

    return v;
}

template <typename T>
vector<T> selectionSort(vector<T> v) {
    for (size_t i = 0; i + 1 < v.size(); i++) {
        size_t index = i;

        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[index]) {
                index = j;
            }
        }

        if (index != i) {
            swap(v[i], v[index]);
        }
    }

    return v;
}

template <typename T>
vector<T> bubbleSort(vector<T> v) {
    for (size_t i = 1; i < v.size(); i++) {
        bool huboCambio = false;

        for (size_t j = 0; j < v.size() - i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                huboCambio = true;
            }
        }

        if (!huboCambio) {
            break;
        }
    }

    return v;
}

template <typename T>
vector<T> insertionSort(vector<T> v) {
    for (size_t i = 1; i < v.size(); i++) {
        size_t j = i;

        while (j > 0 && v[j] < v[j - 1]) {
            swap(v[j], v[j - 1]);
            j--;
        }
    }

    return v;
}

template <typename T>
int part(vector<T> &v, int inicio, int final) {
    T pivot = v[inicio];
    int i = inicio + 1;

    for (int j = inicio + 1; j <= final; j++) {
        if (v[j] <= pivot) {
            swap(v[i], v[j]);
            i++;
        }
    }

    swap(v[inicio], v[i - 1]);
    return i - 1;
}

template <typename T>
void quickSort(vector<T> &v, int inicio, int final) {
    if (inicio < final) {
        int pivote = part(v, inicio, final);
        quickSort(v, inicio, pivote - 1);
        quickSort(v, pivote + 1, final);
    }
}

template <typename T>
vector<T> shellSort(vector<T> v) {
    for (size_t salto = v.size() / 2; salto > 0; salto /= 2) {
        for (size_t i = salto; i < v.size(); i++) {
            T actual = v[i];
            size_t j = i;

            while (j >= salto && actual < v[j - salto]) {
                v[j] = v[j - salto];
                j -= salto;
            }

            v[j] = actual;
        }
    }

    return v;
}

template <typename T>
void combinar(vector<T> &v, size_t izquierda, size_t mitad, size_t derecha) {
    vector<T> temporal;
    temporal.reserve(derecha - izquierda + 1);

    size_t i = izquierda;
    size_t j = mitad + 1;

    while (i <= mitad && j <= derecha) {
        if (v[i] <= v[j]) {
            temporal.push_back(v[i]);
            i++;
        } else {
            temporal.push_back(v[j]);
            j++;
        }
    }

    while (i <= mitad) {
        temporal.push_back(v[i]);
        i++;
    }

    while (j <= derecha) {
        temporal.push_back(v[j]);
        j++;
    }

    for (size_t k = 0; k < temporal.size(); k++) {
        v[izquierda + k] = temporal[k];
    }
}

template <typename T>
void mergeSortAux(vector<T> &v, size_t izquierda, size_t derecha) {
    if (izquierda >= derecha) {
        return;
    }

    size_t mitad = izquierda + (derecha - izquierda) / 2;
    mergeSortAux(v, izquierda, mitad);
    mergeSortAux(v, mitad + 1, derecha);
    combinar(v, izquierda, mitad, derecha);
}

template <typename T>
vector<T> mergeSort(vector<T> v) {
    if (!v.empty()) {
        mergeSortAux(v, 0, v.size() - 1);
    }

    return v;
}

struct InfoAlgoritmo {
    string nombre;
    string mejorCaso;
    string peorCaso;
};

const InfoAlgoritmo ALGORITMOS[] = {
    {"Swap Sort", "O(n^2)", "O(n^2)"},
    {"Bubble Sort", "O(n)", "O(n^2)"},
    {"Selection Sort", "O(n^2)", "O(n^2)"},
    {"Insertion Sort", "O(n)", "O(n^2)"},
    {"Merge Sort", "O(n log n)", "O(n log n)"},
    {"Quick Sort", "O(n log n)", "O(n^2)"},
    {"Shell Sort", "O(n log n)", "O(n^2)"}
};

int leerOpcion(int minimo, int maximo) {
    int opcion;

    while (!(cin >> opcion) || opcion < minimo || opcion > maximo) {
        if (cin.eof()) {
            return maximo;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida. Intenta nuevamente: ";
    }

    return opcion;
}

vector<Registro> ordenarRegistros(
    const vector<Registro> &registros,
    int algoritmo
) {
    switch (algoritmo) {
        case 1:
            return swapSort(registros);
        case 2:
            return bubbleSort(registros);
        case 3:
            return selectionSort(registros);
        case 4:
            return insertionSort(registros);
        case 5:
            return mergeSort(registros);
        case 6: {
            vector<Registro> resultado = registros;

            if (!resultado.empty()) {
                quickSort(resultado, 0, static_cast<int>(resultado.size()) - 1);
            }

            return resultado;
        }
        case 7:
            return shellSort(registros);
        default:
            return registros;
    }
}

void mostrarAlgoritmos() {
    cout << "\n===== ALGORITMOS DISPONIBLES =====\n";

    for (int i = 0; i < 7; i++) {
        cout << i + 1 << ". " << ALGORITMOS[i].nombre << '\n';
    }
}

bool convertirFechaIngresada(const string &texto, long long &clave) {
    istringstream entrada(texto);
    string mesTexto;
    string horaTexto;
    string contenidoExtra;
    int dia;
    int anio;

    if (!(entrada >> mesTexto >> dia >> anio >> horaTexto) ||
        (entrada >> contenidoExtra)) {
        return false;
    }

    int mes = numeroMes(mesTexto);
    int hora;
    int minuto;
    int segundo;
    char primerSeparador;
    char segundoSeparador;
    char caracterExtra;
    istringstream entradaHora(horaTexto);

    if (mes == 0 ||
        !(entradaHora >> hora >> primerSeparador >> minuto
                      >> segundoSeparador >> segundo) ||
        (entradaHora >> caracterExtra) ||
        primerSeparador != ':' || segundoSeparador != ':' ||
        dia < 1 || dia > 31 ||
        hora < 0 || hora > 23 ||
        minuto < 0 || minuto > 59 ||
        segundo < 0 || segundo > 59) {
        return false;
    }

    clave = crearClaveFecha(anio, mes, dia, hora, minuto, segundo);
    return true;
}

long long leerFechaHora(const string &tipoLimite) {
    string texto;
    long long clave;

    while (true) {
        cout << "Fecha y hora de " << tipoLimite
             << " (formato: Sep 08 2024 14:37:38): ";
        getline(cin, texto);

        if (convertirFechaIngresada(texto, clave)) {
            return clave;
        }

        cout << "Formato invalido. Usa un mes en ingles y el formato indicado.\n";
    }
}

size_t buscarPrimerMayorIgual(
    const vector<Registro> &registros,
    long long limite
) {
    size_t izquierda = 0;
    size_t derecha = registros.size();

    while (izquierda < derecha) {
        size_t mitad = izquierda + (derecha - izquierda) / 2;

        if (registros[mitad].fechaHora < limite) {
            izquierda = mitad + 1;
        } else {
            derecha = mitad;
        }
    }

    return izquierda;
}

size_t buscarPrimerMayor(
    const vector<Registro> &registros,
    long long limite
) {
    size_t izquierda = 0;
    size_t derecha = registros.size();

    while (izquierda < derecha) {
        size_t mitad = izquierda + (derecha - izquierda) / 2;

        if (registros[mitad].fechaHora <= limite) {
            izquierda = mitad + 1;
        } else {
            derecha = mitad;
        }
    }

    return izquierda;
}

vector<Registro> seleccionarRango(
    const vector<Registro> &registros,
    long long fechaInicio,
    long long fechaFin
) {

    size_t inicio = buscarPrimerMayorIgual(registros, fechaInicio);
    size_t finExclusivo = buscarPrimerMayor(registros, fechaFin);

    if (inicio >= finExclusivo) {
        return {};
    }

    return vector<Registro>(
        registros.begin() + inicio,
        registros.begin() + finExclusivo
    );
}

int main() {
    char repetir = 's';

    while (repetir == 's' || repetir == 'S') {
        cout << "\n===== SELECCION DEL ARCHIVO =====\n"
             << "1. log607-1.txt (desordenado)\n"
             << "2. log607-2.txt (casi ordenado)\n"
             << "Selecciona el archivo: ";

        int opcionArchivo = leerOpcion(1, 2);
        string nombreArchivo = opcionArchivo == 1
            ? "data/log607-1.txt"
            : "data/log607-2.txt";

        vector<Registro> registros = leerArchivo(nombreArchivo);

        if (registros.empty()) {
            cout << "No se encontraron registros. Verifica que el archivo "
                 << "este en la carpeta desde la que ejecutas el programa.\n";
        } else {
            mostrarAlgoritmos();
            cout << "Selecciona el algoritmo: ";
            int opcionAlgoritmo = leerOpcion(1, 7);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string prediccion;
            cout << "\nEscribe tu prediccion para esta combinacion.\n"
                 << "Indica que tan rapida o lenta esperas que sea y por que:\n";
            getline(cin, prediccion);

            cout << "\nEjecutando "
                 << ALGORITMOS[opcionAlgoritmo - 1].nombre << "...\n";

            auto inicio = chrono::high_resolution_clock::now();
            vector<Registro> ordenados = ordenarRegistros(
                registros,
                opcionAlgoritmo
            );
            auto fin = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> duracion = fin - inicio;

            cout << fixed << setprecision(4)
                 << "\n===== RESULTADOS =====\n"
                 << "Algoritmo: "
                 << ALGORITMOS[opcionAlgoritmo - 1].nombre << '\n'
                 << "Archivo: " << nombreArchivo << '\n'
                 << "Cantidad de registros: " << registros.size() << '\n'
                 << "Tiempo de ordenamiento: " << duracion.count()
                 << " milisegundos\n"
                 << "Mejor caso teorico: "
                 << ALGORITMOS[opcionAlgoritmo - 1].mejorCaso << '\n'
                 << "Peor caso teorico: "
                 << ALGORITMOS[opcionAlgoritmo - 1].peorCaso << '\n'
                 << "Prediccion inicial: " << prediccion << '\n';

            char coincidencia;
            cout << "El resultado coincidio con tu prediccion? (s/n): ";
            cin >> coincidencia;

            if (coincidencia == 's' || coincidencia == 'S') {
                cout << "El resultado si coincidio con la prediccion.\n";
            } else {
                cout << "El resultado no coincidio con la prediccion.\n";
            }

            if (guardarArchivo("out/output608.txt", ordenados)) {
                cout << "Resultado guardado en out/output608.txt\n";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n===== BUSQUEDA POR RANGO =====\n"
                 << "El rango es inclusivo: se consideran tanto la fecha de "
                 << "inicio como la fecha de fin.\n"
                 << "Si un limite coincide con timestamps duplicados, se "
                 << "incluyen todos una sola vez.\n";

            long long fechaInicio;
            long long fechaFin;

            while (true) {
                fechaInicio = leerFechaHora("inicio");
                fechaFin = leerFechaHora("fin");

                if (fechaInicio <= fechaFin) {
                    break;
                }

                cout << "La fecha de inicio no puede ser posterior a la fecha "
                     << "de fin. Intenta nuevamente.\n";
            }

            vector<Registro> rango = seleccionarRango(
                ordenados,
                fechaInicio,
                fechaFin
            );

            cout << "\n===== REGISTROS EN EL RANGO =====\n";

            if (rango.empty()) {
                cout << "No se encontraron registros en ese rango.\n";
            } else {
                for (const Registro &registro : rango) {
                    cout << registro.lineaOriginal << '\n';
                }
            }

            cout << "Total de registros encontrados: " << rango.size() << '\n';

            if (guardarArchivo("out/range607.txt", rango)) {
                cout << "Resultado guardado en out/range607.txt\n";
            }
        }

        cout << "\nDeseas realizar otra corrida? (s/n): ";
        cin >> repetir;
    }

    cout << "\nPrograma terminado.\n";
    return 0;
}
