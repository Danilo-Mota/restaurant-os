#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <string>
#include <iostream>
#include "chef.h"
#include <queue>
#include <map>
#include <vector>

class Restaurante {
public:
    Restaurante(unsigned int qtdChefs, unsigned int qtdMesas);
    void fazerPedido(unsigned int mesa, const std::string &item);
    void finalizarMesa(unsigned int mesa);
    void processarListaDeEspera(); // Processa pedidos em espera

private:
    static const unsigned int MAX_CHEFS = 100;
    std::vector<Chef> chefs;
    std::queue<std::pair<unsigned int, std::string>> listaDeEspera;
    std::map<unsigned int, Chef*> mesasOcupadas;

    Chef *getChefLivre();
};

#endif
