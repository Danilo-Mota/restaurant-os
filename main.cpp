#include <iostream>
#include <boost/algorithm/string.hpp>
#include <cstdlib>
#include "restaurante.h"

using namespace std;

bool encerrar(std::string &comando) {
    std::transform(comando.begin(), comando.end(), comando.begin(), ::toupper);
    return (comando == "FIM");
}

int processarEntrada(std::istream &entrada) {
    unsigned int qtdChefs, qtdMesas;
    entrada >> qtdChefs >> qtdMesas;
    std::cin.ignore(); // Pra ignorar o próximo input caso tenha escrito algo depois de ler e ter quebrado a linha

    try {
        Restaurante restaurante(qtdChefs, qtdMesas);

        while (true) {
            std::string linha;
            std::getline(entrada, linha);
            if (encerrar(linha)) break;

            int mesa;
            std::string pedido;
            std::istringstream stream(linha);

            stream >> mesa;
            stream.ignore();
            std::getline(stream, pedido);

            if (encerrar(pedido)) {
                restaurante.finalizarMesa(mesa);
            } else {
                restaurante.fazerPedido(mesa, pedido);
            }
        }

    } catch (exception &ex) {
        std::cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main() {
    return processarEntrada(std::cin);
}
