#include "ArbolHUFF.h"
#include <utility>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <unordered_map>


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
// Constructor del árbol de Huffman
ArbolHUFF::ArbolHUFF(std::vector<std::pair<int8_t, int64_t>> simbolos) {
    // Crear una lista de nodos
    std::vector<NodoHUFF*> nodos;
    for (const std::pair<int8_t, int64_t>& par : simbolos) {
        NodoHUFF* nuevo = new NodoHUFF(par);
        nodos.push_back(nuevo);
    }

    // Crear el árbol de Huffman
    while (nodos.size() > 1) {
        // Ordenar la lista de nodos por frecuencia (de menor a mayor)
        std::sort(nodos.begin(), nodos.end(), [](NodoHUFF* a, NodoHUFF* b) {
            return a->getSimbolo().second > b->getSimbolo().second;
        });

        // Tomar los dos nodos con las frecuencias más bajas
        NodoHUFF* izquierdo = nodos[0];
        NodoHUFF* derecho = nodos[1];

        // Crear un nuevo nodo interno que combine los dos nodos anteriores
        NodoHUFF* interno = new NodoHUFF(std::make_pair(-1, izquierdo->getSimbolo().second + derecho->getSimbolo().second));
        interno->setHijoI(izquierdo);
        interno->setHijoD(derecho);

        // Eliminar los dos nodos anteriores de la lista y agregar el nuevo nodo interno
        nodos.erase(nodos.begin(), nodos.begin() + 2);
        nodos.push_back(interno);
    }

    // Establecer la raíz del árbol
    this->raiz = nodos[0];
}

// Función de decodificación de Huffman
void ArbolHUFF::decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>>& simbolos) {
    // Iniciar el nodo actual en la raíz del árbol
    NodoHUFF* nodoActual = raiz;

    // Decodificar los bits
    for (int64_t bit : codigo) {
        if (bit == 0) {
            nodoActual = nodoActual->getHijoI();
        } else {
            nodoActual = nodoActual->getHijoD();
        }

        // Si el nodo actual tiene un símbolo, agregarlo a la lista de símbolos
        if (nodoActual->getSimbolo().first != -1) {
            simbolos.push_back(nodoActual->getSimbolo());
            nodoActual = raiz;
        }
    }
}

// Función de codificación de Huffman
void ArbolHUFF::codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t>& codigo) {
    // Crear un mapa de códigos Huffman
    std::unordered_map<int8_t, std::vector<int>> CodigoHuffman;
    construirCodigoHuffman(raiz, {}, CodigoHuffman);

    // Codificar los símbolos
    for (const auto& simbolo : simbolos) {
        int8_t caracter = simbolo.first;
        if (CodigoHuffman.find(caracter) != CodigoHuffman.end()) {
            std::vector<int> codigoCaracter = CodigoHuffman[caracter];
            for (int bit : codigoCaracter) {
                codigo.push_back(bit);
            }
        }
    }
}

// Función de inserción de nuevos datos
void ArbolHUFF::insertar(std::vector<std::pair<int8_t, int64_t>> simbolos) {
    // Crear una lista de nodos
    std::vector<NodoHUFF*> nodos;

    // Agregar los nuevos símbolos a la lista de nodos
    for (const std::pair<int8_t, int64_t>& par : simbolos) {
        NodoHUFF* nuevo = new NodoHUFF(par);
        nodos.push_back(nuevo);
    }

    // Actualizar la frecuencia de los símbolos existentes
    for (NodoHUFF* nodo : nodos) {
        if (nodo->getSimbolo().first != -1) {
            // Buscar el nodo que representa el símbolo en el árbol
            NodoHUFF* nodoEncontrado = buscarNodo(nodo->getSimbolo().first);

            // Actualizar la frecuencia del nodo encontrado
            nodoEncontrado->setFrecuencia(nodoEncontrado->getFrecuencia() + nodo->getFrecuencia());
        }
    }

    // Construir el árbol de Huffman actualizado
    while (nodos.size() > 1) {
        // Ordenar la lista de nodos por frecuencia (de menor a mayor)
        std::sort(nodos.begin(), nodos.end(), [](NodoHUFF* a, NodoHUFF* b) {
            return a->getFrecuencia() > b->getFrecuencia();
        });

        // Tomar los dos nodos con las frecuencias más bajas
        NodoHUFF* izquierdo = nodos[0];
        NodoHUFF* derecho = nodos[1];

        // Crear un nuevo nodo interno que combine los dos nodos anteriores
        NodoHUFF* interno = new NodoHUFF(std::make_pair(-1, izquierdo->getFrecuencia() + derecho->getFrecuencia()));
        interno->setHijoI(izquierdo);
        interno->setHijoD(derecho);

        // Eliminar los dos nodos anteriores de la lista y agregar el nuevo nodo interno
        nodos.erase(nodos.begin(), nodos.begin() + 2);
        nodos.push_back(interno);
    }

    // Establecer la raíz del árbol actualizado
    this->raiz = nodos[0];
}

// Función de construcción de códigos Huffman
void ArbolHUFF::construirCodigoHuffman(NodoHUFF* nodo, std::vector<int> codigo, std::unordered_map<int8_t, std::vector<int>>& CodigoHuffman) {
    // Si el nodo es una hoja, agregar el código al mapa de códigos Huffman
    if (nodo->getSimbolo().first != -1) {
        CodigoHuffman[nodo->getSimbolo().first] = codigo;
    }

    // Si el nodo no es una hoja, construir el código para sus hijos
    if (nodo->getHijoI() != nullptr) {
        std::vector<int> codigoI = codigo;
        codigoI.push_back(0);
        construirCodigoHuffman(nodo->getHijoI(), codigoI, CodigoHuffman);
    }
    if (nodo->getHijoD() != nullptr) {
        std::vector<int> codigoD = codigo;
        codigoD.push_back(1);
        construirCodigoHuffman(nodo->getHijoD(), codigoD, CodigoHuffman);
    }
}

void ArbolHUFF::addToDeque(std::deque< NodoHUFF * >& simbolos, NodoHUFF * nuevo){
    std::deque< NodoHUFF * >::iterator it = simbolos.begin();
    while(it != simbolos.end() && (*it)->getSimbolo().second <= nuevo->getSimbolo().second){
        it++;
    }
    simbolos.insert(it, nuevo);
}

void ArbolHUFF::armarArbol(std::vector<std::pair<int8_t, int64_t>> simbolos) {

    std::deque< NodoHUFF * > simbolosD;
    int64_t nulo = 0;

    for(std::pair<int8_t, int64_t> s : simbolos){
        std::pair<int8_t, int64_t> p (s.first, s.second);
        NodoHUFF * n = new NodoHUFF(p);
        simbolosD.push_back(n);
    }

    while(simbolosD.size() > 1){
        //sacar 2 menores
        NodoHUFF * izq = simbolosD.front();
        simbolosD.pop_front();
        NodoHUFF * der = simbolosD.front();
        simbolosD.pop_front();

        //crear nodo intermedio
        NodoHUFF * intm = new NodoHUFF(izq->getSimbolo().second + der->getSimbolo().second);
        intm->setHijoI(izq);
        intm->setHijoD(der);

        addToDeque(simbolosD, intm);

    }

    this->raiz = simbolosD.front();
}

