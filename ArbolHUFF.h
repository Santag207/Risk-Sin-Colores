#ifndef RISKSINCOLOR_ARBOLHUFF_H
#define RISKSINCOLOR_ARBOLHUFF_H

#include "NodoHUFF.h"
#include <vector>
#include <utility>
#include <cstdint>

class ArbolHUFF{
private:
    NodoHUFF * raiz;
public:
    //constructores
    ArbolHUFF();
    ArbolHUFF(std::pair<int8_t, int64_t>& raiz);
    //desstructores
    ~ArbolHUFF();
    //getters
    NodoHUFF * getRaiz();
    //setters
    void setRaiz(NodoHUFF * raiz);
    //operaciones
    void insertar(std::vector<std::pair<int8_t, int64_t>> simbolos);
    void codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t> codigo);
    void decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>> simbolos);

};

#endif //RISKSINCOLOR_ARBOLHUFF_H
