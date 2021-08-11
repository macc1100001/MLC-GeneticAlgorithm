CC = gcc
CFLAGS = -g -Wall -Wextra -I$(HDRDIR)
LDFLAGS = -lgsl -lgslcblas -lm -lplot -lpng
EXEC = genalg
SRCDIR = sources
HDRDIR = headers
OBJDIR = obj
OBJ_NAMES = main.o genalg.o
OBJS = $(addprefix $(OBJDIR)/,$(OBJ_NAMES))

all: mkndirs $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $^
		
.PHONY: clean cleanest mkndirs

clean:
	rm $(EXEC)
	
cleanest:
	rm $(OBJDIR)/*.o
	
mkndirs:
	if [ ! -e $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	if [ ! -e $(SRCDIR) ]; then mkdir $(SRCDIR); fi
	if [ ! -e $(HDRDIR) ]; then mkdir $(HDRDIR); fi
	
