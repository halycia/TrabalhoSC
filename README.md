# Assinador Digital (RSA + SHA)

O presente projeto foi desenvolvido para a disciplina de Segurança Computacional na Universidade de Brasília. Este programa implementa uma versão simplificada do sistema RSA e de uma função hash (SHA-like) para simular o processo de assinatura e verificação digital de mensagens.

A implementação foi feita sem uso de bibliotecas externas de criptografia, conforme as exigências do trabalho.  
Todos os cálculos de módulo, potência e inverso multiplicativo utilizam o algoritmo de Euclides estendido.

O sistema permite:

- Gerar pares de chaves RSA (manualmente ou automaticamente);
- Assinar mensagens digitadas ou armazenadas em arquivos .txt;
- Verificar a validade de assinaturas;
- Salvar e reutilizar chaves e assinaturas.

## Requisitos

- Sistema operacional: Windows
- Compilador: MinGW (https://sourceforge.net/projects/mingw/)
- Editor de código: VSCode
- extensões no VSCode: C/C++ Extension Pack (publicada pela Microsoft) e C/C++ Compile Run (publicada por danielpinto8zz6)

## Arquivos do projeto

| `main.cpp` | Código-fonte principal do programa. Implementa o menu interativo e controla as ações de geração de chaves, assinatura e verificação. |

| `README.md` | Instruções de compilação e execução do programa |

| `chaves.txt` | Armazena os valores `e`, `d` e `n` das chaves RSA geradas. |

| `assinatura.txt` | Armazena o valor da assinatura digital gerada a partir do hash da mensagem. |

| `Makefile` | Automatiza a compilação, execução, limpeza e exibição de ajuda do projeto |

| `rsa.cpp` / `rsa.hpp` | Implementa a estrutura e o comportamento do algoritmo **RSA**. |

| `math_utils.cpp` / `math_utils.hpp` | Contém as funções matemáticas para o funcionamento do RSA. |

| `file_utils.cpp` / `file_utils.hpp` | Gerencia a leitura e gravação de arquivos `.txt`. Fornece `read_file(path, content)` e `write_file(path, content)` para salvar e recuperar chaves e assinaturas. |

| `hash_utils.cpp` / `hash_utils.hpp` | Implementa uma função hash simplificada (`simple_hash(msg)`), inspirada no DJB2, que gera um valor numérico a partir da mensagem — usado como entrada para a assinatura digital. |


## Instruções de compilação e execução do programa

Abra o terminal do VSCode na pasta do projeto e execute o comando:

```bash
Set-Alias make mingw32-make.exe
```
### Compilar o programa
```bash
make all
```

### Executar o programa
```bash
make run
```

### Limpar arquivos gerados
```bash
make clean
```

### Exibir ajuda
```bash
make help
```
