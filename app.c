
#include "app.h"

int main(int argc, char *argv[])
{
  int opt;
  int year, month, day, hour, minute;
  char* datetime = NULL;
  char* emailAddr = NULL;
  char* attachment = NULL;
  char cronjob[1024];
  struct tm tm = {0};
  FILE* crontab;
  time_t t;

  // Parse command line args
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

  // Quick Error check
  if (argc < 5)
  {
    printUsage();
    exit(0);
  }

  if ( (strptime(datetime, "%m-%d-%H:%M", &tm)) == NULL )
  {
    printUsage();
    exit(0);
  }


  // Parse the time
  month = 1 + tm.tm_mon;
  day = tm.tm_mday;
  hour = tm.tm_hour;
  minute = tm.tm_min;

  /*
  std::cout << "Month " << 1 + tm.tm_mon << std::endl;
  std::cout << "Day " << tm.tm_mday << std::endl;
  std::cout << "Hour " << tm.tm_hour << std::endl;
  std::cout << "Min " << tm.tm_min << std::endl;

  printf("%s %s %s\n", datetime, emailAddr, attachment);*/

  // Open crontab for writing
  crontab = fopen("/etc/crontab", "a");
  //  Create the cron job command
  sprintf(cronjob, "%d %d %d %d * mail -s cronlab! -a %s %s < /dev/null\n", minute, hour, day, month, , attachment, emailAddr);

  std::cout << "CRONJOB:: " << cronjob;

  //Write the cron job to the crontab
  fprintf(crontab, "%s", cronjob);

  //Close the file when finished
  fclose(crontab);

  return 0;
}

void printUsage()
{
  printf("Usage: SendEmail -d date/time(mm-dd-hh:mm) -e emailAddress -a attachmentpath\n");
}
