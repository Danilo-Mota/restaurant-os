#ifndef CHEF_H
#define CHEF_H

#include <fstream>
#include <string>
#include <iostream>
#include <csignal>
#include <sstream>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

class Chef {
public:
    Chef();
    void iniciarAtendimento(const unsigned int mesa);
    void preparar(const std::string &pedido);
    void finalizarAtendimento();

    unsigned int getId() const { return id; }

private:
    static unsigned int contador; // Contador para atribuir IDs únicos aos chefs
    unsigned int id;
    std::vector<std::string> pedidos;

    void registrarPedido(const std::string &pedido);
};

#endif
