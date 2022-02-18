
# --------------------------------------------------------------------
#  Makefile de tarea 3.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega

MODULOS = utils info cadena binario iterador pila colaBinarios usoTads

# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

TESTDIR = test

# extensión de los archivos
EXT = cpp
# compilador
CC = g++ # gcc -x c 
LD = g++ # gcc

# opciones de compilación
# para que los assert tengan efecto 
CCFLAGS = -Wall -Werror -I$(HDIR) -g

# para que los assert NO tengan efecto y no impacten en el tiempo de ejecución
#CCFLAGS = -Wall -Werror -I$(HDIR) -g -DNDEBUG



# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.$(EXT))
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal


# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).$(EXT) Makefile
	@printf 'Compilando $(<) \n'; \
	$(CC) $(CCFLAGS) -c $< -o $@




$(ODIR)/%.o: $(CPPDIR)/%.$(EXT)  $(HDIR)/%.h
	@printf 'Compilando $(<) \n'; \
	$(eval resr = $(shell grep -n -P '_rep_(?!$(basename $(notdir $<)))' $<)) \
	$(eval resh = $(subst #,\#,$(shell grep -n -P 'include(?!.*[.]h)' $< ))) \
	$(eval resc = $(shell grep -n 'nodoCadena' $< )) \
	if [ -z "$(resr)" ] && [ -z "$(resh)" ] && { [ -z "$(resc)" ] || [ -n "$(findstring cadena, $<)" ] ; }; \
	then $(CC) $(CCFLAGS) -c $< -o $@ ; \
	else \
		if [ -n "$(resh)" ]; then printf '  "$(resh)": Include de archivos que no son .h \n' ; fi ; \
		if [ -n "$(resr)" ]; then printf '  "$(resr)": Uso de representación de otros tipos\n' ; fi ; \
		if [ -n "$(resc)" ]; then printf '  "$(resc)": Uso de nodoCadena\n' ; fi ; \
		printf '    NO SE COMPILO $(<)\n' ; \
		rm -f $@; \
	fi


# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE):$(ODIR)/$(PRINCIPAL).o $(OS)
	@printf 'Compilando y enlazando $(@) \n'; \
	$(LD) $(CCFLAGS) $^ -o $@

# casos de prueba
CASOS = 01 02 03 04 05 06 07 300 m-10 t-binario_balanceado t-recorrida_por_niveles


# cadena de archivos, con directorio y extensión
INS=$(CASOS:%=$(TESTDIR)/%.in)
OUTS=$(CASOS:%=$(TESTDIR)/%.out)
SALS=$(CASOS:%=$(TESTDIR)/%.sal)
DIFFS=$(CASOS:%=$(TESTDIR)/%.diff)

$(SALS):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(TESTDIR)/%.sal:$(TESTDIR)/%.in
	-timeout 4 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@ 2>&1
	@if [ $$(stat -L -c %s $@) -ge 20000 ]; then \
		echo "tamaño excedido" > $@;\
	fi

# test de tiempo
$(TESTDIR)/t-%.sal:$(TESTDIR)/t-%.in
	-timeout 10 ./$(EJECUTABLE) < $< > $@ 2>&1


%.diff:Makefile
# cada .diff depende de su .out y de su .sal
%.diff: %.out %.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior.
# En el caso de `diff', si los dos archivos comparados no son iguales,
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.



# crea las reglas t-caso, y cada una depende del ejecutable
tS=$(CASOS:%=t-%)
$(tS):$(EJECUTABLE)

# corre el ejecutable con el .in (el primer prerequisito $<) y lo guarda en un archivo temporal
# hace el diff entre el -out (el segundo prerequisito, echo $(word 2,$^)) y el archivo temporal
# borra el archivo temporal
t-%:$(TESTDIR)/%.in $(TESTDIR)/%.out
	@timeout 4 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@tmp;  \
	diff `echo $(word 2,$^)` $@tmp ; \
	if [ $$? -eq 0 ];                                         \
	then                                                      \
		echo ---- Bien ----;                                    \
	fi;                                                       \
	rm -f $@tmp


t-t-%:$(TESTDIR)/t-%.in $(TESTDIR)/t-%.out
	@timeout 10 ./$(EJECUTABLE) < $< > $@tmp;  \
	diff `echo $(word 2,$^)` $@tmp ; \
	if [ $$? -eq 0 ];                                         \
	then                                                      \
		echo ---- Bien ----;                                    \
	fi;                                                       \
	rm -f $@tmp




# Genera el entregable.
ENTREGA=Entrega4.tar.gz
CPPS_ENTREGA = cadena.cpp binario.cpp iterador.cpp pila.cpp colaBinarios.cpp usoTads.cpp
entrega:
	@rm -f $(ENTREGA)
	tar zcvf $(ENTREGA) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)
	@shasum -b $(ENTREGA) > sha.txt


# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS)

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(TESTDIR)/*.sal $(TESTDIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f *~ $(HDIR)/*~ $(CPPDIR)/*~ $(TESTDIR)/*~



