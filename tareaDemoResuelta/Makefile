
principal:obj/principal.o obj/a.o obj/b.o
	g++ obj/principal.o obj/a.o obj/b.o   -o principal
	
obj/principal.o:principal.cpp
	g++ -c principal.cpp -o obj/principal.o

obj/a.o:src/a.cpp
	g++ -c src/a.cpp -o obj/a.o
	
obj/b.o:src/b.cpp
	g++ -c src/b.cpp -o obj/b.o	

clean:
	rm obj/* principal

# Genera el entregable.
ENTREGA=EntregaDemo.tar.gz
entrega:
	@rm -f $(ENTREGA)
	tar zcvf $(ENTREGA) -C src a.cpp b.cpp
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)