SRC_FILES = encode.c decode.c base64.h

encode : encode.c 
	gcc -g -o encode encode.c base64.h
	
decode : decode.c 
	gcc -g -o decode decode.c base64.h
	
test : encode decode
	./encode <example.txt | tee encoded.txt
	./decode <encoded.txt | tee result.txt
	diff example.txt result.txt
	
debug : encode
	gdb encode
	
clean :
	-rm encode decode encoded.txt result.txts
	
submit : $(SRC_FILES)
	mkdir $(USER)_proj1
	cp $(SRC_FILES) $(USER)_proj1
	tar -cvzf $(USER)_proj1.tar.gz $(USER)_proj1
	rm -r $(USER)_proj1