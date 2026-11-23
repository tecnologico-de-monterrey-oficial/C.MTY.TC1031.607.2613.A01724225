#pragma once
#include <iostream>
#include <sstream>
#include <string>

// revisa que sean cuatro numeros del cero al doscientos cincuenta y cinco separados por punto
// si algo no cuadra deja el motivo en err
inline bool ipValida(const std::string& s, std::string& err) {
    int partes = 0;
    std::string parte;
    std::istringstream in(s);
    while (std::getline(in, parte, '.')) {
        bool digitos = !parte.empty() && parte.size() <= 3;
        for (char c : parte) if (c < '0' || c > '9') digitos = false;
        if (!digitos || std::stoi(parte) > 255) {
            err = "cada parte debe ser un numero de 0 a 255";
            return false;
        }
        partes++;
    }
    if (partes != 4 || s.back() == '.') {
        err = "debe tener 4 numeros separados por punto, ej. 10.14.0.9";
        return false;
    }
    return true;
}

// ip guardada como numero para compararla bien
// asi la que termina en punto nueve queda antes que la que termina en punto diez
// antes de construirla hay que revisar que el texto sea una ip valida
struct IP {
    unsigned int valor = 0;
    std::string texto;

    IP() {}
    IP(const std::string& s) : texto(s) {
        std::istringstream in(s);
        std::string parte;
        while (std::getline(in, parte, '.')) valor = valor * 256 + std::stoul(parte);
    }

    bool operator<(const IP& o) const { return valor < o.valor; }
    bool operator>(const IP& o) const { return valor > o.valor; }
    bool operator==(const IP& o) const { return valor == o.valor; }
};

inline std::ostream& operator<<(std::ostream& o, const IP& ip) { return o << ip.texto; }
