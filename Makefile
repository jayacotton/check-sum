CFLAGS	= -list --c-code-in-asm  -Wall  
#CFLAGS	= -O3 --list --c-code-in-asm
DESTDIR = ~/HostFileBdos/c/
CP = cp

all: sum 

sum: sum.c 
	zcc +cpm -create-app -$(CFLAGS) -osum sum.c 
	$(CP) SUM.COM $(DESTDIR)sum.com

install:
	sudo cp ./*.COM /var/www/html/. 

documents:
	doxygen 
