CFLAGS = -O3 -I.
#CFLAGS = -O -g -I.
LIBS = -ljack -lpthread -lfftw3f -lm

staticlibname = ../lib/libDttSP.a

OBJ =	am_demod.o\
	banal.o\
	bufvec.o\
	correctIQ.o\
	cwtones.o\
	cxops.o\
	dcblock.o\
	dttspagc.o\
	fastrig.o\
	filter.o\
	graphiceq.o\
	fm_demod.o\
	lmadf.o\
	meter.o\
	noiseblanker.o\
	oscillator.o\
	ovsv.o\
	resample.o\
	ringb.o\
	sdr.o\
	sdrexport.o\
	spectrum.o\
	speechproc.o\
	splitfields.o\
	spottone.o\
	thunk.o\
	window.o\
	wscompand.o\
	update.o

sdr-core:	sdr-main.o
	$(CC) -o sdr-core sdr-main.o $(staticlibname) $(LIBS)

all:	sdr-core ipc

$(OBJ): sdrexport.h

ipc:	
	./setup-ipc

obj:	$(OBJ)

clean:
	/bin/rm -f *.o ../bin/sdr-core $(staticlibname)

staticlib:	$(OBJ)
	ar rcs $(staticlibname) $(OBJ)
	ranlib $(staticlibname)

install:	sdr-core
	mv sdr-core ../bin
