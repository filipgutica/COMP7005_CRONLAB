
#include "app.h"

int main(int argc, char *argv[])
{
  int opt;
  int year, month, day, hour, minute;
  char* datetime = NULL;
  char* emailAddr = NULL;
  char* attachment = NULL;
  struct tm tm = {0};
  FILE* crontab;
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

  if (argc < 5)
  {
    printUsage();
    exit(0);
  }

  strptime(datetime, "%Y-%m-%d-%H:%M", &tm);

  year = 1900 + tm.tm_year;
  month = 1 + tm.tm_mon;
  day = tm.tm_mday;
  hour = tm.tm_hour;
  minute = tm.tm_min;

  std::cout << "Year " << 1900 + tm.tm_year << std::endl;
  std::cout << "Month " << 1 + tm.tm_mon << std::endl;
  std::cout << "Day " << tm.tm_mday << std::endl;
  std::cout << "Hour " << tm.tm_hour << std::endl;
  std::cout << "Min " << tm.tm_min << std::endl;

  printf("%s %s %s\n", datetime, emailAddr, attachment);


  crontab = fopen("/etc/crontab", "a");

  char cronjob[1024];

  sprintf(cronjob, "%d %d %d %d * mail -s cronlab! %s < %s", minute, hour, day, month, emailAddr, attachment);

  std::cout << "CRONJOB " << cronjob;

  fprintf(crontab, "%s", cronjob);

  return 0;
}

void printUsage()
{
  printf("Usage: SendEmail -d date/time(dd-mm-dd-hh:mm) -e emailAddress [-a attachmentpath]\n");
}
