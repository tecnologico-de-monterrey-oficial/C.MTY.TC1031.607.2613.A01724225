#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "IP.h"

// un registro de la bitacora ya validado
struct Registro {
    long long clave = 0;
    IP ip;
    std::string desc;
    std::string linea;

    // primero por fecha y hora, si empatan por ip y luego por mensaje
    // asi el orden siempre sale igual aunque el heap no sea estable
    bool operator<(const Registro& o) const {
        if (clave != o.clave) return clave < o.clave;
        if (!(ip == o.ip)) return ip < o.ip;
        return desc < o.desc;
    }
    bool operator>(const Registro& o) const { return o < *this; }
};

inline std::ostream& operator<<(std::ostream& o, const Registro& r) { return o << r.linea; }

inline const char* const MESES[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

inline int numeroMes(const std::string& m) {
    for (int i = 0; i < 12; i++) if (m == MESES[i]) return i + 1;
    return 0;
}

inline bool soloDigitos(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) if (c < '0' || c > '9') return false;
    return true;
}

inline bool diaValido(int anio, int mes, int dia) {
    static const int dm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
    int max = dm[mes - 1] + (mes == 2 && bisiesto);
    return dia >= 1 && dia <= max;
}

// busca la clave en una linea del json y regresa su valor como texto
// sirve para valores entre comillas y para numeros
inline bool valorJson(const std::string& linea, const std::string& clave, std::string& valor) {
    size_t p = linea.find("\"" + clave + "\"");
    if (p == std::string::npos) return false;
    p = linea.find(':', p);
    if (p == std::string::npos) return false;
    p = linea.find_first_not_of(" \t", p + 1);
    if (p == std::string::npos) return false;

    valor.clear();
    if (linea[p] == '"') {
        for (p++; p < linea.size() && linea[p] != '"'; p++) {
            if (linea[p] == '\\' && p + 1 < linea.size()) p++;
            valor += linea[p];
        }
        return p < linea.size();
    }
    size_t fin = linea.find_first_of(",}", p);
    valor = linea.substr(p, fin == std::string::npos ? std::string::npos : fin - p);
    while (!valor.empty() && valor.back() == ' ') valor.pop_back();
    return true;
}

// convierte una linea del json en registro
// regresa false y deja el motivo en err si algo falta o esta mal
inline bool parseRegistro(const std::string& linea, Registro& r, std::string& err) {
    std::string mesS, diaS, anioS, hora, ipS, desc;
    const char* claves[] = {"month", "day", "year", "time", "ip", "message"};
    std::string* destinos[] = {&mesS, &diaS, &anioS, &hora, &ipS, &desc};
    for (int i = 0; i < 6; i++) {
        if (!valorJson(linea, claves[i], *destinos[i])) {
            err = std::string("falta el campo ") + claves[i];
            return false;
        }
    }

    int mes = numeroMes(mesS);
    if (!mes) { err = "mes invalido '" + mesS + "'"; return false; }
    if (!soloDigitos(anioS) || anioS.size() != 4) { err = "anio invalido '" + anioS + "'"; return false; }
    if (!soloDigitos(diaS) || diaS.size() > 2) { err = "dia invalido '" + diaS + "'"; return false; }
    int anio = std::stoi(anioS), dia = std::stoi(diaS);
    if (!diaValido(anio, mes, dia)) { err = "el dia " + diaS + " no existe en " + mesS; return false; }

    if (hora.size() != 8 || hora[2] != ':' || hora[5] != ':' ||
        !soloDigitos(hora.substr(0, 2)) || !soloDigitos(hora.substr(3, 2)) || !soloDigitos(hora.substr(6, 2))) {
        err = "hora invalida '" + hora + "', se espera hh:mm:ss";
        return false;
    }
    int h = std::stoi(hora.substr(0, 2)), m = std::stoi(hora.substr(3, 2)), s = std::stoi(hora.substr(6, 2));
    if (h > 23 || m > 59 || s > 59) { err = "hora fuera de rango '" + hora + "'"; return false; }

    std::string errIp;
    if (!ipValida(ipS, errIp)) { err = "IP invalida '" + ipS + "'"; return false; }
    if (desc.empty()) { err = "mensaje vacio"; return false; }

    r.clave = ((long long)anio * 10000 + mes * 100 + dia) * 1000000 + h * 10000 + m * 100 + s;
    r.ip = IP(ipS);
    r.desc = desc;

    std::ostringstream o;
    o << mesS << " " << std::setfill('0') << std::setw(2) << dia << " " << anio << " " << hora << " " << ipS << " " << desc;
    r.linea = o.str();
    return true;
}
