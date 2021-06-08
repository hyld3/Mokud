#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>

// WIP
void heartbeat() {
  
}


int main(int argc, char * argv[]) {
  pid_t pid, sid;

  pid = fork();

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  } else if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  umask(0);

  openlog("mokud", LOG_NOWAIT | LOG_PID, LOG_USER);
  syslog(LOG_NOTICE, "[+] Sucessfully started mokud");

  sid = setsid();

  if (sid < 0) {
    syslog(LOG_ERR, "Could not generate session ID for child process");

    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    syslog(LOG_ERR, "Could not change workdir to /");

    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  const int SLEEP_INTERVAL = 5;

  while(1)
    {
      // Execute daemon heartbeat, where your recurring activity occurs
      heartbeat();

      // Sleep for a period of time
      sleep(SLEEP_INTERVAL);
    }

  // Close system logs for the child process
  syslog(LOG_NOTICE, "Stopping mokud");
  closelog();

  // Terminate the child process when the daemon completes
  exit(EXIT_SUCCESS);
  
}
