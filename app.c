
#include "app.h"

int main(int argc, char *argv[])
{
  int opt;
  char* datetime = NULL;
  char* emailAddr = NULL;
  char* attachment = NULL;
  struct tm tm;
  time_t t;

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

  strptime(datetime, "%Y-%m-%d-%H:%M:%S:", &tm);
  t = mktime(&tm);

  std::cout << t << std::endl;

  printf("%s %s %s\n", datetime, emailAddr, attachment);

  return 0;
}

void printUsage()
{
  printf("Usage: SendEmail -d date/time(dd-mm-dd-hh:mm:ss) -e emailAddress [-a attachmentpath]\n");
}
