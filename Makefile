CC = gcc
CFLAGS = -Wall -g
TARGET = minisql
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = /var/lib/minisql

all: exec

run: exec
	./exec

exec: src/main.c src/sqlEngine.c src/utils.c
	gcc -Wall -g src/main.c src/sqlEngine.c src/utils.c -o exec

#Exemplo:
#exec: src/main.c src/registroDados.c src/registroCabecalho.c src/funcoesFornecidas.c src/funcsUsoGeral.c src/func1.c src/func2.c src/func3.c src/func4.c src/func5.c src/func6.c
#	gcc -Wall -g src/main.c src/registroDados.c src/registroCabecalho.c src/funcoesFornecidas.c src/funcsUsoGeral.c src/func1.c src/func2.c src/func3.c src/func4.c src/func5.c src/func6.c -lm -o exec
#
#exec: main.o registroDados.o funcoesFornecidas.o  func1.o 
#	gcc -Wall -g -o exec main.o registroDados.o funcoesFornecidas.o func1.o 
#
#main.o : main.c
#	gcc -Wall -g -o main.o -c main.c
#
#funcoesFornecidas.o : funcoesFornecidas.c
#	gcc -Wall -g -o funcoesFornecidas.o -c funcoesFornecidas.c
#
#registroDados.o : registroDados.c
#	gcc -Wall -g -o registroDados.o -c registroDados.c
#
#func1.o : func1.c
#	gcc -Wall -g -o func1.o -c func1.c



all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

install: $(TARGET)
	@echo "Instalando o programa..."
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)
	ln -sf $(BINDIR)/$(TARGET) /usr/bin/minisql
	install -d $(DATADIR)
	@echo "Instalação concluída com sucesso."

uninstall:
	@echo "Removendo o programa..."
	rm -f /usr/bin/minisql
	rm -f $(BINDIR)/$(TARGET)
	rm -rf $(DATADIR)
	@echo "Remoção concluída com sucesso."

clean:
	rm -f $(TARGET)
	rm exec

gdb: exec
	gdb exec

valgrind: exec
	valgrind --leak-check=full --show-leak-kinds=all ./exec