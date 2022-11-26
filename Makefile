TARGET = logo

CC = g++
CFLAGS = -Wall

BDIR = bin/
SDIR = src/
ODIR = obj/

SOURCES = $(wildcard $(SDIR)*.cpp)
HEADERS = $(wildcard $(SDIR)*.h)
OBJECTS = $(SOURCES:$(SDIR)%.cpp=$(ODIR)%.o)

all : dirs prog

docs : dokumentacja.pdf

prog : $(BDIR)$(TARGET)

dirs :
	if [ ! -d $(ODIR) ] ; then mkdir $(ODIR) ; fi ;
	if [ ! -d $(BDIR) ] ; then mkdir $(BDIR) ; fi ;

$(BDIR)$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJECTS): $(ODIR)%.o : $(SDIR)%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(ODIR)parser.o  : $(ODIR)scanner.o
$(ODIR)scanner.o : $(ODIR)char_stream.o

dokumentacja.pdf : sprawozdanie.pdf refman.pdf
	pdftk sprawozdanie.pdf refman.pdf cat output dokumentacja.pdf

sprawozdanie.pdf : ./spraw/sprawozdanie.tex
	$(MAKE) -C spraw
	cp ./spraw/sprawozdanie.pdf .

refman.pdf : $(HEADERS) Doxyfile
	doxygen
	$(MAKE) -C latex
	cp ./latex/refman.pdf .

Doxyfile :
	doxygen -g
	mv Doxyfile doxy
	cat doxy | sed -e 's/INPUT[ \t]\+=/INPUT = $(SDIR)g' | sed -e 's/UML_LOOK[ \t]\+=[ \t]\+NO/UML_LOOK = YES/g' | sed -e 's/OUTPUT_LANGUAGE[ \t]\+=[ \t]\+English/OUTPUT_LANGUAGE = Polish/g' | sed -e 's/PROJECT_NAME[ \t]\+=[ \t]\+"My Project"/PROJECT_NAME = "Projekt zaliczeniowy z PPK-SSI"/g' | sed -s 's/GENERATE_HTML[ \t]\+=[ \t]\+YES/GENERATE_HTML = NO/g' > Doxyfile
	rm doxy

.PHONY : clean
clean :
	$(RM) $(OBJECTS)
	if [ -d latex ] ; then rm -r latex ; fi ;
	if [ -d html ] ; then rm -r html ; fi ;
	for f in refman.pdf sprawozdanie.pdf Doxyfile ./bin/*.exe ; do if [ -f $$f ] ; then rm $$f ; fi ; done ;
	$(MAKE) -C spraw clean
