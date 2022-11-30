#include "MsgService.h"
#include "States.h"

extern enum STATES global_state;
extern bool disable_light_system;
extern bool manual_control;
extern bool is_alarm_state;
extern int alpha;
extern bool is_enough_light;
extern bool is_detected;
extern int PE_normal;
extern int PE_pre_alarm;
extern int PE_alarm;
extern float distance;
extern MsgServiceClass *msgManager;

