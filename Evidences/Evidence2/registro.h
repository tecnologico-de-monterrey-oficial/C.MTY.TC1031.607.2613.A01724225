#pragma once
#include <iostream>
#include <sstream>
#include <string>

// Un renglon de la bitacora ya validado y convertido
struct Registro {
    long long clave = 0;   // yyyymmddhhmmss, comparable como numero
    std::string ip;
    std::string desc;
    std::string original;  // linea tal cual, para reescribir el archivo

    long long dia() const { return clave / 1000000; }  // yyyymmdd
};

inline std::ostream& operator<<(std::ostream& o, const Registro& r) { return o << r.original; }

inline int numeroMes(const std::string& m) {
    static const char* meses[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++) if (m == meses[i]) return i + 1;
    return 0;
}

inline bool diaValido(int anio, int mes, int dia) {
    static const int dm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
    int max = dm[mes - 1] + (mes == 2 && bisiesto);
    return dia >= 1 && dia <= max;
}

inline bool soloDigitos(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) if (c < '0' || c > '9') return false;
    return true;
}

// Valida "Mes dd yyyy" y regresa la clave yyyymmdd (0 si es invalido; motivo en err)
inline long long parseDia(const std::string& mesS, const std::string& diaS, const std::string& anioS, std::string& err) {
    int mes = numeroMes(mesS);
    if (!mes) { err = "mes invalido '" + mesS + "'"; return 0; }
    if (!soloDigitos(anioS) || anioS.size() != 4) { err = "anio invalido '" + anioS + "'"; return 0; }
    if (!soloDigitos(diaS) || diaS.size() > 2) { err = "dia invalido '" + diaS + "'"; return 0; }
    int anio = std::stoi(anioS), dia = std::stoi(diaS);
    if (!diaValido(anio, mes, dia)) { err = "el dia " + diaS + " no existe en ese mes"; return 0; }
    return (long long)anio * 10000 + mes * 100 + dia;
}

// Formato: "Mmm dd yyyy hh:mm:ss a.b.c.d descripcion"
// Devuelve false y llena err si la linea no cumple
inline bool parseRegistro(const std::string& linea, Registro& r, std::string& err) {
    std::istringstream in(linea);
    std::string mes, dia, anio, hora, ip, desc;
    in >> mes >> dia >> anio >> hora >> ip;
    if (in.fail()) { err = "faltan campos (se esperan fecha, hora, IP y descripcion)"; return false; }
    std::getline(in >> std::ws, desc);
    if (desc.empty()) { err = "descripcion vacia"; return false; }

    long long d = parseDia(mes, dia, anio, err);
    if (!d) return false;

    // hora hh:mm:ss
    if (hora.size() != 8 || hora[2] != ':' || hora[5] != ':' ||
        !soloDigitos(hora.substr(0, 2)) || !soloDigitos(hora.substr(3, 2)) || !soloDigitos(hora.substr(6, 2))) {
        err = "hora invalida '" + hora + "' (se espera hh:mm:ss)";
        return false;
    }
    int h = std::stoi(hora.substr(0, 2)), m = std::stoi(hora.substr(3, 2)), s = std::stoi(hora.substr(6, 2));
    if (h > 23 || m > 59 || s > 59) { err = "hora fuera de rango '" + hora + "'"; return false; }

    // IP: cuatro numeros 0-255 separados por punto
    std::istringstream ipS(ip);
    std::string oct;
    int partes = 0;
    while (std::getline(ipS, oct, '.')) {
        if (!soloDigitos(oct) || oct.size() > 3 || std::stoi(oct) > 255) { err = "IP invalida '" + ip + "'"; return false; }
        partes++;
    }
    if (partes != 4 || ip.back() == '.') { err = "IP invalida '" + ip + "'"; return false; }

    r.clave = d * 1000000 + h * 10000 + m * 100 + s;
    r.ip = ip;
    r.desc = desc;
    r.original = linea;
    return true;
}
