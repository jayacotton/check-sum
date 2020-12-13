/* sum - checksum a file		Author: Martin C. Atkins */

/*
 *	This program was written by:
 *		Martin C. Atkins,
 *		University of York,
 *		Heslington,
 *		York. Y01 5DD
 *		England
 *	and is released into the public domain, on the condition
 *	that this comment is always included without alteration.
 */
/* Stdio removed Alan Cox 2015 */

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE (8192)

int rc = 0;

char *defargv[] = { "-", 0 };

void error (const char *s, const char *f);
void sum (int fd, char *fname);

int
main (int argc, char *argv[])
{
  register int fd;

  if (*++argv == 0)
    argv = defargv;
  for (; *argv; argv++)
    {
      if (argv[0][0] == '-' && argv[0][1] == '\0')
	fd = 0;
      else
	fd = open (*argv, O_RDONLY, 0);

      if (fd == -1)
	{
	  error ("can't open ", *argv);
	  rc = 1;
	  continue;
	}
      sum (fd, *argv );
      if (fd != 0)
	close (fd);
    }
  return (rc);
}

void
error (const char *s, const char *f)
{

  printf ("sum: ");
  printf ("%s ", s);

  if (f)
    printf ("%s", f);
  printf ("\n");
}

unsigned total_bytes = 0;
unsigned long r = 0;
unsigned long s = 0;
unsigned int crc = 0;
unsigned char buf[BUFFER_SIZE];
void
sum (int fd, char *fname)
{
  register int i, n;
  unsigned blks;

  while ((n = read (fd, buf, BUFFER_SIZE)) > 0)
    {
      for (i = 0; i < n; i++)
	{
	  s += buf[i];
	}
      total_bytes += n;
    }

  if (n < 0)
    {
      if (fname)
	error ("read error on ", fname);
      rc = 1;
      return;
    }
//   s -= 0x1a;  // eof marker
printf("%lu\n",s);
  r = (s & 0xffff) + ((s & 0xffff0000) >> 16);
printf("%lu\n",r);
  crc = (r & 0xffff) + (r >> 16);
  blks = (total_bytes + 511) / 512;
  printf ("%u %6d %s\n", crc, blks, fname);
}
