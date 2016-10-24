#include <TimedAction.h>
#include "sensors_info.h"

//Criando as threads
TimedAction thread1 = TimedAction(500, print_red);
TimedAction thread2 = TimedAction(500, print_green);
TimedAction thread_sonar = TimedAction(500, get_distance);
TimedAction thread_listen = TimedAction(500, listen_infos);

void check_sonar(){
  thread_sonar.check();
}

void check_print_red(){
  thread1.check();
}

void check_print_green(){
  thread2.check();
}

void check_instructions(){
  thread_listen.check();
}


