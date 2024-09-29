#include "restaurante.h"

Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) : chefs() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    for (int i = 0; i < qtdChefs; i++) {
        chefs.emplace_back(this); // Passa a referência do restaurante para os chefs
    }
}

Chef *Restaurante::getChefLivre() {
    for (auto &chef : chefs) {
        bool chefOcupado = false;
        for (const auto &parMesaChef : mesasOcupadas) {
            if (parMesaChef.second == &chef) {
                chefOcupado = true;
                break;
            }
        }
        if (!chefOcupado) {
            return &chef;
        }
    }
    return nullptr;
}

void Restaurante::fazerPedido(unsigned int mesa, const std::string &item) {
    Chef *chef = getChefLivre();
    if (chef) {
        std::cout << "Chefe disponível para a mesa " << mesa << std::endl;
        mesasOcupadas[mesa] = chef; // Associa o chef à mesa
        pid_t pid = fork();

        if (pid == 0) {
            chef->iniciarAtendimento(mesa);
            chef->preparar(item);
            chef->finalizarAtendimento();
            exit(0); // Termina o processo filho
        } else if (pid < 0) {
            std::cerr << "Erro ao criar processo para atender a mesa " << mesa << std::endl;
        }
    } else {
        listaDeEspera.push({mesa, item});
        std::ofstream log("MesasNaoAtendidas.txt", std::ios::app);
        log << "Mesa " << mesa << " não atendida. Pedido: " << item << std::endl;
        log.close();
        std::cout << "Mesa " << mesa << " não pôde ser atendida. Pedido adicionado à lista de espera." << std::endl;
    }
}

void Restaurante::finalizarMesa(unsigned int mesa) {
    if (mesasOcupadas.count(mesa) == 0) {
        std::cerr << "A mesa " << mesa << " não está sendo atendida por nenhum chef!" << std::endl;
        return;
    }

    Chef *chef = mesasOcupadas[mesa];
    chef->finalizarAtendimento();
    mesasOcupadas.erase(mesa); // Remove a mesa da lista de mesas ocupadas
    processarListaDeEspera();
}

void Restaurante::processarListaDeEspera() {
    while (!listaDeEspera.empty()) {
        auto pedido = listaDeEspera.front();
        listaDeEspera.pop();
        std::cout << "Processando pedido na lista de espera: Mesa " << pedido.first << " - " << pedido.second << std::endl;
        fazerPedido(pedido.first, pedido.second);
    }
}
