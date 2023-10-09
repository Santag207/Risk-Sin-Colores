#ifndef ARBOL_HUFF_H
#define ARBOL_HUFF_H

#include <utility>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <unordered_map>

class NodoHUFF {
public:
    NodoHUFF() {
        this->simbolo = std::make_pair(-1, 0);
        this->hijoI = nullptr;
        this->hijoD = nullptr;
    }

    NodoHUFF(std::pair<int8_t, int64_t> simbolo) {
        this->simbolo = simbolo;
        this->hijoI = nullptr;
        this->hijoD = nullptr;
    }

    std::pair<int8_t, int64_t> getSimbolo() const {
        return this->simbolo;
    }

    void setSimbolo(std::pair<int8_t, int64_t> simbolo) {
        this->simbolo = simbolo;
    }

    NodoHUFF* getHijoI() const {
        return this->hijoI;
    }

    void setHijoI(NodoHUFF* hijoI) {
        this->hijoI = hijoI;
    }

    NodoHUFF* getHijoD() const {
        return this->hijoD;
    }

    void setHijoD(NodoHUFF* hijoD) {
        this->hijoD = hijoD;
    }

    int64_t getFrecuencia() const {
        return this->frecuencia;
    }

    void setFrecuencia(int64_t frecuencia) {
        this->frecuencia = frecuencia;
    }

private:
    std::pair<int8_t, int64_t> simbolo;
    NodoHUFF* hijoI;
    NodoHUFF* hijoD;
    int64_t frecuencia;
};

class ArbolHUFF {
public:
    ArbolHUFF();
    ArbolHUFF(std::pair<int8_t, int64_t>& raiz);
    ~ArbolHUFF();

    NodoHUFF* getRaiz() const;
    void setRaiz(NodoHUFF* raiz);

    void decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>>& simbolos);
    void codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t>& codigo);
    void insertar(std::vector<std::pair<int8_t, int64_t>> simbolos);

private:
    NodoHUFF* raiz;

    void construirCodigoHuffman(NodoHUFF* nodo, std::vector<int> codigo, std::unordered_map<int8_t, std::vector<int>>& CodigoHuffman);
    NodoHUFF* buscarNodo(int8_t simbolo);
};

#endif //ARBOL_HUFF_H