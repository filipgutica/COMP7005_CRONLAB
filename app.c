
#include "app.h"

int main(int argc, char *argv[])
{
  int opt;
  char* datetime = NULL;
  char* emailAddr = NULL;
  char* attachment = NULL;

  while ( (opt = getopt(argc, argv, "d:e:a:")) != -1 )
  {
    switch (opt)
    {
      case 'd':
        datetime = optarg;
        break;
      case 'e':
        emailAddr = optarg;
        break;
      case 'a':
        attachment = optarg;
        break;
      default:
        printUsage();
        exit(0);
    }
  }

  if (argc < 4)
  {
    printUsage();
    exit(0);
  }

  printf("%s %s %s\n", datetime, emailAddr, attachment);

  return 0;
}

void printUsage()
{
  printf("Usage: SendEmail -d date/time -e emailAddress [-a attachmentpath]\n");
}
