using namespace std;
#include "rsa.hpp"
#include "hash_utils.hpp"
#include "file_utils.hpp"


int main() {
    RSA rsa;
    bool hasKeys = false;

    while (true) {
        cout << "\n=== Assinador Digital Simplificado ===\n";
        cout << "1. Gerar chaves automaticamente\n";
        cout << "2. Informar p, q e e manualmente\n";
        cout << "3. Assinar mensagem (arquivo ou texto)\n";
        cout << "4. Verificar assinatura\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";

        int op;
        cin >> op;
        cin.ignore();

        if (op == 0) break;

        if (op == 1) {
            rsa.generate_auto();
            hasKeys = true;
            cout << "\nChaves geradas automaticamente!\n";
            cout << "p=" << rsa.p << " q=" << rsa.q << " n=" << rsa.n << " phi=" << rsa.phi << "\n";
            cout << "e=" << rsa.e << " d=" << rsa.d << "\n";
            write_file("chaves.txt", to_string(rsa.e) + " " + to_string(rsa.d) + " " + to_string(rsa.n));
            cout << "Chaves salvas em 'chaves.txt'.\n";
        }

        else if (op == 2) {
            u64 p, q, e;
            cout << "Informe p (primo): ";
            cin >> p;
            cout << "Informe q (primo e diferente de p): ";
            cin >> q;
            cout << "Informe e: ";
            cin >> e;
            if (!rsa.init(p, q, e)) {
                cout << "Erro ao inicializar RSA.\n";
                continue;
            }
            hasKeys = true;
            cout << "\nChave pública: (e=" << rsa.e << ", n=" << rsa.n << ")\n";
            cout << "Chave privada: (d=" << rsa.d << ", n=" << rsa.n << ")\n";
            write_file("chaves.txt", to_string(rsa.e) + " " + to_string(rsa.d) + " " + to_string(rsa.n));
            cout << "Chaves salvas em 'chaves.txt'.\n";
        }

        else if (op == 3) {
            if (!hasKeys) {
                cout << "Gere ou informe as chaves primeiro.\n";
                continue;
            }
            cout << "1. Assinar texto digitado\n2. Assinar arquivo .txt\nEscolha: ";
            int modo;
            cin >> modo;
            cin.ignore();
            string msg;
            if (modo == 1) {
                cout << "Digite a mensagem:\n> ";
                getline(cin, msg);
            } else {
                cout << "Caminho do arquivo: ";
                string path;
                getline(cin, path);
                if (!read_file(path, msg)) {
                    cout << "Erro ao ler arquivo.\n";
                    continue;
                }
            }
            u64 h = simple_hash(msg);
            u64 assinatura = rsa.sign(h);
            cout << "Hash simplificado: " << h << "\n";
            cout << "Assinatura: " << assinatura << "\n";
            write_file("assinatura.txt", to_string(assinatura));
            cout << "Assinatura salva em 'assinatura.txt'.\n";
        }

        else if (op == 4) {
            if (!hasKeys) {
                cout << "Gere ou informe as chaves primeiro.\n";
                continue;
            }
            cout << "1. Verificar texto digitado\n2. Verificar arquivo .txt\nEscolha: ";
            int modo;
            cin >> modo;
            cin.ignore();
            string msg;
            if (modo == 1) {
                cout << "Digite a mensagem:\n> ";
                getline(cin, msg);
            } else {
                cout << "Caminho do arquivo: ";
                string path;
                getline(cin, path);
                if (!read_file(path, msg)) {
                    cout << "Erro ao ler arquivo.\n";
                    continue;
                }
            }
            string sigStr;
            if (!read_file("assinatura.txt", sigStr)) {
                cout << "Não foi possível ler 'assinatura.txt'.\n";
                continue;
            }
            u64 assinatura = stoull(sigStr);
            u64 h = simple_hash(msg);
            bool ok = rsa.verify(h, assinatura);
            cout << (ok ? "Assinatura válida\n" : "Assinatura inválida\n");
        }

        else {
            cout << "Opção inválida.\n";
        }
    }

    cout << "Encerrando programa.\n";
    return 0;
}
