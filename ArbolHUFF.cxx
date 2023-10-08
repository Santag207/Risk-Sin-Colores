#include "ArbolHUFF.h"
#include <utility>
#include <cstdint>

//constructores
// --------------------------------------------------------------------
ArbolHUFF::ArbolHUFF(){
    this->raiz = nullptr;
}
ArbolHUFF::ArbolHUFF(std::pair<int8_t, int64_t>& raiz){
    NodoHUFF * nuevo = new NodoHUFF(raiz);
    this->raiz = nuevo;
}

//desstructores
// --------------------------------------------------------------------
ArbolHUFF::~ArbolHUFF(){
    this->raiz = nullptr;
};

//getters
// --------------------------------------------------------------------

NodoHUFF * ArbolHUFF::getRaiz(){
    return this->raiz;
}

//setters
// --------------------------------------------------------------------
void ArbolHUFF::setRaiz(NodoHUFF * raiz){
    this->raiz = raiz;
}

//operaciones
// --------------------------------------------------------------------
void ArbolHUFF::insertar(std::vector<std::pair<int8_t, int64_t>> simbolos){

}
void ArbolHUFF::codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t> codigo){

}
void ArbolHUFF::decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>> simbolos){

}