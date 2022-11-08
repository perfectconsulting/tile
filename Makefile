
CFLAGS=-std=c99 -g 
INCLUDES=-I.
LIBS=
OBJECTS=tile2.o virtual-machine.o io.o

.c.o:                    
		@echo "Compiling $*.c"                                                                                               
		@$(CC) $(CFLAGS) -c $*.c $(INCLUDES) -DBUILD_NO=$(BUILD_NO)    
        
tile: $(OBJECTS)
		@mkdir -p bin
		@$(CC) -o bin/tile $(OBJECTS) $(LIBS)
		@echo "TILE built"
		      
clean:                                                                                                                  
		@echo "Cleaning TILE files"                                                            
		@$(RM) $(OBJECTS) 
		@$(RM) bin/host/tile  