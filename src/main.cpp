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
            write_file("./output/chaves.txt", to_string(rsa.e) + " " + to_string(rsa.d) + " " + to_string(rsa.n));
            cout << "Chaves salvas em './output/chaves.txt'.\n";
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
            write_file("./output/chaves.txt", to_string(rsa.e) + " " + to_string(rsa.d) + " " + to_string(rsa.n));
            cout << "Chaves salvas em './output/chaves.txt'.\n";
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
            u64 h = simple_hash(msg) % rsa.n; 
            u64 assinatura = rsa.sign(h);
            cout << "Mensagem original: " << msg << "\n";
            cout << "Hash simplificado: " << h << "\n";
            cout << "Assinatura: " << assinatura << "\n";
            write_file("./output/assinatura.txt", to_string(assinatura));
            cout << "Assinatura salva em './output/assinatura.txt'.\n";
        }

        else if (op == 4) {
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
            cout << "Informe o resumo criptografado (assinatura) ou caminho do arquivo de assinatura: ";
            string sigInput;
            getline(cin, sigInput);

            u64 assinatura;
            if (sigInput.size() > 4 && sigInput.substr(sigInput.size()-4) == ".txt") {
                if (!read_file(sigInput, sigStr)) {
                    cout << "Não foi possível ler '" << sigInput << "'.\n";
                    continue;
                }
                assinatura = stoull(sigStr);
            } else {
                assinatura = stoull(sigInput);
            }

            u64 hash_recalculado = simple_hash(msg) % rsa.n; 
            u64 resumo_descriptografado = rsa.decrypt_with_public(assinatura);

            cout << "\n--- Verificação da assinatura ---\n";
            cout << "Mensagem recebida: " << msg << "\n";
            cout << "Hash recalculado da mensagem: " << hash_recalculado << "\n";
            cout << "Assinatura recebida: " << assinatura << "\n";
            cout << "Resumo descriptografado (assinatura com chave pública): " << resumo_descriptografado << "\n";

            if (hash_recalculado == resumo_descriptografado) {
                cout << "Resultado: Assinatura válida! Mensagem não foi alterada e pertence ao emissor.\n";
            } else {
                cout << "Resultado: Assinatura inválida! Mensagem pode ter sido alterada ou não pertence ao emissor.\n";
            }
        }
    }

    cout << "Encerrando programa.\n";
    return 0;
}
