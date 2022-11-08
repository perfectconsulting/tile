
CFLAGS=-std=c99 -g
INCLUDES=-I.
LIBS=-lcurses
OBJECTS=tile2.o virtual-machine.o io.o

.c.o:                                                                                                                   
		@$(CC) $(CFLAGS) -c $*.c $(INCLUDES) -DBUILD_NO=$(BUILD_NO)    
        
tile: $(OBJECTS)
		@mkdir -p bin
		@$(CC) -o bin/tile $(OBJECTS) $(LIBS)
      
clean:                                                                                                                  
		@echo "Cleaning TILE files"                                                            
		@$(RM) $(OBJECTS) 
		@$(RM) bin/host/tile  