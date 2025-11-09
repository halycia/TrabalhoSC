# ============================================================
# Makefile para o projeto RSA Assinador Digital
# Uso: mingw32-make.exe all | run | clean | help
#
# Para configurar o makefile, rode primeiramente no seu terminal
# Set-Alias make mingw32-make.exe
# ============================================================

# Compilador e opções
CXX = C:\MinGW\bin\g++.exe
CXXFLAGS = -Wall -Wextra -g3 -std=c++17

# Nome do executável
OUT = main.exe

# Pasta de saída
OUTDIR = output

# Arquivos-fonte (.cpp)
SRC = src/main.cpp src/rsa.cpp src/math_utils.cpp src/file_utils.cpp src/hash_utils.cpp

# Dependências (.hpp)
HEADERS = src/rsa.hpp src/math_utils.hpp src/file_utils.hpp src/hash_utils.hpp

# Cria a pasta de saída se não existir
$(OUTDIR):
	@if not exist "$(OUTDIR)" mkdir "$(OUTDIR)"


# Alvo principal: compila tudo
all: $(OUTDIR) $(OUTDIR)\$(OUT)

# Regra de compilação
$(OUTDIR)\$(OUT): $(SRC) $(HEADERS)
	chcp 65001
	@echo Compilando o projeto...
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUTDIR)\$(OUT)
	@echo.
	@echo Compilação concluída com sucesso!
	@echo.

# Executa o programa (com terminal UTF-8)
run:
	chcp 65001
	@echo Executando o programa...
	@$(OUTDIR)\$(OUT)

# Limpa arquivos gerados
clean:
	chcp 65001
	@if exist "$(OUTDIR)\$(OUT)" del "$(OUTDIR)\$(OUT)"
	@echo Limpeza concluída com sucesso!

# Ajuda
help:
	chcp 65001
	@echo Comandos disponíveis:
	@echo mingw32-make all   - Compila o programa
	@echo mingw32-make run   - Executa o programa
	@echo mingw32-make clean - Remove o executável gerado
	@echo mingw32-make help  - Mostra esta ajuda
