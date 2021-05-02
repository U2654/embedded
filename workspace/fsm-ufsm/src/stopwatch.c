#include "stopwatch.h"
static struct ufsm_machine AAAAAAF4_qj8TIuZtIk;
static struct ufsm_region AAAAAAF4_qj8TYua7rM;
static struct ufsm_transition AAAAAAF4_qqfQYxEj3M;
static struct ufsm_transition AAAAAAF4_q6JSYzAYrM;
static struct ufsm_action AAAAAAF5IkyfXI2p0Ys;
static struct ufsm_state AAAAAAF4_qkmGIugg18;
static struct ufsm_region AAAAAAF4_qkmGIuhzBg;
static struct ufsm_transition AAAAAAF4_qrWJIxZH8E;
static struct ufsm_transition AAAAAAF4_quNOIyAmWs;
static struct ufsm_action AAAAAAF5Ikz8N42xN2k;
static struct ufsm_transition AAAAAAF4_uD1Lo0oK5I;
static struct ufsm_action AAAAAAF5IkzJao2tDno;
static struct ufsm_state AAAAAAF4_qnaYIvOtKk;
static struct ufsm_state AAAAAAF4_qn144v0_uA;
static struct ufsm_state AAAAAAF4_qp0rIww2cU;
static struct ufsm_state AAAAAAF4_qpXXIwfY1s;



static struct ufsm_machine AAAAAAF4_qj8TIuZtIk = {
  .id     = "AAAAAAF4+qj8TIuZtIk=", 
  .name   = "StateMachine1", 
  .region = &AAAAAAF4_qj8TYua7rM,    
  .next = NULL,
  .parent_state = NULL, 
};
static struct ufsm_region AAAAAAF4_qj8TYua7rM = {
  .id = "AAAAAAF4+qj8TYua7rM=",
  .name = "StateMachine1region0",
  .state = &AAAAAAF4_qkmGIugg18,
  .has_history = false,
  .history = NULL,
  .transition = &AAAAAAF4_qqfQYxEj3M,
  .parent_state = NULL,
  .next = NULL,
};
static struct ufsm_transition AAAAAAF4_qqfQYxEj3M = {
  .id = "AAAAAAF4+qqfQYxEj3M=",
  .name = "",
  .trigger = NULL,
  .kind = 0,
  .action = NULL,
  .defer = false,
  .guard = NULL,
  .source = &AAAAAAF4_qpXXIwfY1s,
  .dest = &AAAAAAF4_qkmGIugg18,
  .next = &AAAAAAF4_q6JSYzAYrM,
};
static struct ufsm_trigger AAAAAAF4_q6JSYzAYrM_triggers[] = {
{
  .trigger = 0,
  .name = "reset",
},
 {
  .trigger = -1,
  .name = NULL,
},
};
static struct ufsm_transition AAAAAAF4_q6JSYzAYrM = {
  .id = "AAAAAAF4+q6JSYzAYrM=",
  .name = "",
  .trigger = AAAAAAF4_q6JSYzAYrM_triggers,
  .kind = 0,
  .action = &AAAAAAF5IkyfXI2p0Ys,
  .defer = false,
  .guard = NULL,
  .source = &AAAAAAF4_qkmGIugg18,
  .dest = &AAAAAAF4_qkmGIugg18,
  .next = NULL,
};
static struct ufsm_action AAAAAAF5IkyfXI2p0Ys = {
  .id = "AAAAAAF5IkyfXI2p0Ys=",
  .name = "resetTime",
  .f = &resetTime,
  .next = NULL,
};
static struct ufsm_state AAAAAAF4_qkmGIugg18 = {
  .id   = "AAAAAAF4+qkmGIugg18=",
  .name = "Active",
  .kind = 0,
  .parent_region = &AAAAAAF4_qj8TYua7rM,
  .entry = NULL,
  .doact = NULL,
  .exit = NULL,
  .region = &AAAAAAF4_qkmGIuhzBg,
  .submachine = NULL,
  .next = &AAAAAAF4_qpXXIwfY1s,
};
static struct ufsm_region AAAAAAF4_qkmGIuhzBg = {
  .id = "AAAAAAF4+qkmGIuhzBg=",
  .name = "Activeregion0",
  .state = &AAAAAAF4_qnaYIvOtKk,
  .has_history = false,
  .history = NULL,
  .transition = &AAAAAAF4_qrWJIxZH8E,
  .parent_state = &AAAAAAF4_qkmGIugg18,
  .next = NULL,
};
static struct ufsm_transition AAAAAAF4_qrWJIxZH8E = {
  .id = "AAAAAAF4+qrWJIxZH8E=",
  .name = "",
  .trigger = NULL,
  .kind = 0,
  .action = NULL,
  .defer = false,
  .guard = NULL,
  .source = &AAAAAAF4_qp0rIww2cU,
  .dest = &AAAAAAF4_qnaYIvOtKk,
  .next = &AAAAAAF4_quNOIyAmWs,
};
static struct ufsm_trigger AAAAAAF4_quNOIyAmWs_triggers[] = {
{
  .trigger = 1,
  .name = "startstop",
},
 {
  .trigger = -1,
  .name = NULL,
},
};
static struct ufsm_transition AAAAAAF4_quNOIyAmWs = {
  .id = "AAAAAAF4+quNOIyAmWs=",
  .name = "",
  .trigger = AAAAAAF4_quNOIyAmWs_triggers,
  .kind = 0,
  .action = &AAAAAAF5Ikz8N42xN2k,
  .defer = false,
  .guard = NULL,
  .source = &AAAAAAF4_qn144v0_uA,
  .dest = &AAAAAAF4_qnaYIvOtKk,
  .next = &AAAAAAF4_uD1Lo0oK5I,
};
static struct ufsm_action AAAAAAF5Ikz8N42xN2k = {
  .id = "AAAAAAF5Ikz8N42xN2k=",
  .name = "stopTime",
  .f = &stopTime,
  .next = NULL,
};
static struct ufsm_trigger AAAAAAF4_uD1Lo0oK5I_triggers[] = {
{
  .trigger = 1,
  .name = "startstop",
},
 {
  .trigger = -1,
  .name = NULL,
},
};
static struct ufsm_transition AAAAAAF4_uD1Lo0oK5I = {
  .id = "AAAAAAF4+uD1Lo0oK5I=",
  .name = "",
  .trigger = AAAAAAF4_uD1Lo0oK5I_triggers,
  .kind = 0,
  .action = &AAAAAAF5IkzJao2tDno,
  .defer = false,
  .guard = NULL,
  .source = &AAAAAAF4_qnaYIvOtKk,
  .dest = &AAAAAAF4_qn144v0_uA,
  .next = NULL,
};
static struct ufsm_action AAAAAAF5IkzJao2tDno = {
  .id = "AAAAAAF5IkzJao2tDno=",
  .name = "startTime",
  .f = &startTime,
  .next = NULL,
};
static struct ufsm_state AAAAAAF4_qnaYIvOtKk = {
  .id   = "AAAAAAF4+qnaYIvOtKk=",
  .name = "Stopped",
  .kind = 0,
  .parent_region = &AAAAAAF4_qkmGIuhzBg,
  .entry = NULL,
  .doact = NULL,
  .exit = NULL,
  .region = NULL,
  .submachine = NULL,
  .next = &AAAAAAF4_qn144v0_uA,
};
static struct ufsm_state AAAAAAF4_qn144v0_uA = {
  .id   = "AAAAAAF4+qn144v0+uA=",
  .name = "Running",
  .kind = 0,
  .parent_region = &AAAAAAF4_qkmGIuhzBg,
  .entry = NULL,
  .doact = NULL,
  .exit = NULL,
  .region = NULL,
  .submachine = NULL,
  .next = &AAAAAAF4_qp0rIww2cU,
};
static struct ufsm_state AAAAAAF4_qp0rIww2cU = {
  .id   = "AAAAAAF4+qp0rIww2cU=",
  .name = "Init",
  .kind = 1,
  .parent_region = &AAAAAAF4_qkmGIuhzBg,
  .entry = NULL,
  .doact = NULL,
  .exit = NULL,
  .region = NULL,
  .submachine = NULL,
  .next = NULL,
};
static struct ufsm_state AAAAAAF4_qpXXIwfY1s = {
  .id   = "AAAAAAF4+qpXXIwfY1s=",
  .name = "Init",
  .kind = 1,
  .parent_region = &AAAAAAF4_qj8TYua7rM,
  .entry = NULL,
  .doact = NULL,
  .exit = NULL,
  .region = NULL,
  .submachine = NULL,
  .next = NULL,
};

struct ufsm_machine * get_StateMachine1(void) { return &AAAAAAF4_qj8TIuZtIk; }
