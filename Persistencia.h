#ifndef RISKSINCOLOR_PERSISTENCIA_H
#define RISKSINCOLOR_PERSISTENCIA_H

#include "ArbolHUFF.h"
#include "Partida.h"
#include <vector>
#include <string>

class Persistencia{
private:
    std::vector<std::pair<int8_t, int64_t>> simbolos;
    std::vector<int64_t> codigo;
    std::string info;
    ArbolHUFF arbol;
public:
    //constructores
    Persistencia();
    //getters
    std::vector<std::pair<int8_t, int64_t>> getSimbolos();
    std::vector<int64_t> getCodigo();
    std::string getInfo();
    ArbolHUFF getArbol();
    //setters
    void aggSimbolo(std::pair<int8_t, int64_t> simboloNuevo);
    void setSimbolos(std::string info);
    void aggCodigo(int64_t codigoNuevo);
    void aggInfo(std::string caracterNuevo);
    void setArbol(ArbolHUFF arbol);
    //operaciones
    void escribirArchivoTxt(std::string nameFile, Partida& partida);
    bool leerArchivoTxt(std::string nameFile);
    void crearArbol();
    void recuperarPartidaConTxt(std::string nameFile, Partida& partida);

};

#endif //RISKSINCOLOR_PERSISTENCIA_H
