Sometimes I want to check that a program got transferred to my CP/M disk
correctly.  A quick and dirty method is checksum.

I went looking for a checksum program that runs on CP/M and found nothing 
(almost).  There was a version in assembler but it not produce an output
that was compatible with checksum on the linux host machine.

So I grabbed a version I found on git hub and hacked it to work in the
very limited CP/M environment.  The original author is Martin C. Atkins.

To run this code you need to get the SUM.COM program on to your CP/M 
machine, then you use "sum -s PROGRAM.NAME"  on linux and on your
CP/M system you say "sum PROGRAM.NAME"  (note the -s flag).  That tells
linux to use the SysV sum calculation.  Not needed on CP/M.

Here is the Linux run:
The new code checking sum on the CP/M executable.
./sum SUM.COM
662033
6683
6683     30 SUM.COM
The Linux code checking sum on the CP/M executable.
sum -s SUM.COM
6683 30 SUM.COM

Here is the CP/M run:
C>sum sum.com
662033
6683
6683     30 SUM.COM

The CP/M version is printing some debug values, these seem to be needed
just now.  Some problem with the compiler.   It will clear up in time.


