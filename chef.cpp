#include "chef.h"

unsigned int Chef::contador = 0;

Chef::Chef() : id(++contador) {
    std::stringstream nome;
    nome << "ChefeCozinha_" << id;

    std::ofstream log;
    log.open(nome.str() + ".txt");
    log << nome.str() << std::endl;
    log.close();
}

Chef::~Chef() {
}

void Chef::iniciarAtendimento(const unsigned int mesa) {
    std::cout << "Chefe " << id << " começando atendimento à mesa " << mesa << std::endl;
}

void Chef::preparar(const std::string &pedido) {
    std::cout << "Chefe " << id << " está preparando: " << pedido << std::endl;
    sleep(25);
    registrarPedido(pedido);
}

void Chef::finalizarAtendimento() {
    std::cout << "Chefe " << id << " finalizou atendimento." << std::endl;
}

void Chef::registrarPedido(const std::string &pedido) {
    pedidos.push_back(pedido);
    std::ofstream log("ChefeCozinha_" + std::to_string(id) + ".txt", std::ios::app);
    log << "Mesa " << id << ":\n";
    for (const auto &p : pedidos) {
        log << "- " << p << std::endl;
    }
    log.close();
}
