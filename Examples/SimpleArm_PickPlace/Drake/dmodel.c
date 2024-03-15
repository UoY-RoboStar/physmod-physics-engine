
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ctype.h>

#ifdef DEBUG
# define DPRINTF(arg) printf arg
#else
# define DPRINTF(arg)
#endif

#define err_abort(code,text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(code)); \
	abort(); \
	} while(0)

#define errno_abort(text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(errno)); \
	abort(); \
	} while (0)


// Temporary solution to trim strings taken from http://www.martinbroadhurst.com/trim-a-string-in-c.html

char *ltrim(char *str, const char *seps)
{
  size_t totrim;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  totrim = strspn(str, seps);
  if (totrim > 0) {
    size_t len = strlen(str);
    if (totrim == len) {
      str[0] = '\0';
    }
    else {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
  return str;
}

char *rtrim(char *str, const char *seps)
{
  int i;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  i = strlen(str) - 1;
  while (i >= 0 && strchr(seps, str[i]) != NULL) {
    str[i] = '\0';
    i--;
  }
  return str;
}

char *trim(char *str, const char *seps)
{
  return ltrim(rtrim(str, seps), seps);
}

char* concat(char *str1, char *str2) {
  char* result = malloc(sizeof(char)*(strlen(str1)+strlen(str2)));
  char* s1 = strcat(result, str1);
  char* s2 = strcat(result, str2);
  return result;
}


FILE* log_file;

/* Representation of enum M_PickPlace_output */

typedef enum {
  M_PickPlace_output_PrePick,
  M_PickPlace_output_PrePlace,
  M_PickPlace_output_Return,
  M_PickPlace_output__done_,
} M_PickPlace_output_Type;

typedef union {
} M_PickPlace_output_Data;

typedef struct {
  M_PickPlace_output_Type type;
  M_PickPlace_output_Data data;
} M_PickPlace_output_Enum;

M_PickPlace_output_Enum create_M_PickPlace_output_PrePick() {
  M_PickPlace_output_Data data;

  M_PickPlace_output_Type type = M_PickPlace_output_PrePick;

  M_PickPlace_output_Enum aux = (M_PickPlace_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_output_Enum create_M_PickPlace_output_PrePlace() {
  M_PickPlace_output_Data data;

  M_PickPlace_output_Type type = M_PickPlace_output_PrePlace;

  M_PickPlace_output_Enum aux = (M_PickPlace_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_output_Enum create_M_PickPlace_output_Return() {
  M_PickPlace_output_Data data;

  M_PickPlace_output_Type type = M_PickPlace_output_Return;

  M_PickPlace_output_Enum aux = (M_PickPlace_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_output_Enum create_M_PickPlace_output__done_() {
  M_PickPlace_output_Data data;

  M_PickPlace_output_Type type = M_PickPlace_output__done_;

  M_PickPlace_output_Enum aux = (M_PickPlace_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum STATUS */

typedef enum {
  STATUS_ENTER_STATE,
  STATUS_ENTER_CHILDREN,
  STATUS_EXECUTE_STATE,
  STATUS_EXIT_CHILDREN,
  STATUS_EXIT_STATE,
  STATUS_INACTIVE,
} STATUS_Type;

typedef union {
} STATUS_Data;

typedef struct {
  STATUS_Type type;
  STATUS_Data data;
} STATUS_Enum;

STATUS_Enum create_STATUS_ENTER_STATE() {
  STATUS_Data data;

  STATUS_Type type = STATUS_ENTER_STATE;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATUS_Enum create_STATUS_ENTER_CHILDREN() {
  STATUS_Data data;

  STATUS_Type type = STATUS_ENTER_CHILDREN;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATUS_Enum create_STATUS_EXECUTE_STATE() {
  STATUS_Data data;

  STATUS_Type type = STATUS_EXECUTE_STATE;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATUS_Enum create_STATUS_EXIT_CHILDREN() {
  STATUS_Data data;

  STATUS_Type type = STATUS_EXIT_CHILDREN;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATUS_Enum create_STATUS_EXIT_STATE() {
  STATUS_Data data;

  STATUS_Type type = STATUS_EXIT_STATE;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATUS_Enum create_STATUS_INACTIVE() {
  STATUS_Data data;

  STATUS_Type type = STATUS_INACTIVE;

  STATUS_Enum aux = (STATUS_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum RESULT */

typedef enum {
  RESULT_WAIT,
  RESULT_CONT,
} RESULT_Type;

typedef union {
} RESULT_Data;

typedef struct {
  RESULT_Type type;
  RESULT_Data data;
} RESULT_Enum;

RESULT_Enum create_RESULT_WAIT() {
  RESULT_Data data;

  RESULT_Type type = RESULT_WAIT;

  RESULT_Enum aux = (RESULT_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
RESULT_Enum create_RESULT_CONT() {
  RESULT_Data data;

  RESULT_Type type = RESULT_CONT;

  RESULT_Enum aux = (RESULT_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum STATES_stm_ref0 */

typedef enum {
  STATES_stm_ref0_NONE,
  STATES_stm_ref0_Finding_Object,
  STATES_stm_ref0_Finding_Goal,
  STATES_stm_ref0_PrePicking,
  STATES_stm_ref0_PrePlacing,
  STATES_stm_ref0_Returning,
} STATES_stm_ref0_Type;

typedef union {
} STATES_stm_ref0_Data;

typedef struct {
  STATES_stm_ref0_Type type;
  STATES_stm_ref0_Data data;
} STATES_stm_ref0_Enum;

STATES_stm_ref0_Enum create_STATES_stm_ref0_NONE() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_NONE;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATES_stm_ref0_Enum create_STATES_stm_ref0_Finding_Object() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_Finding_Object;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATES_stm_ref0_Enum create_STATES_stm_ref0_Finding_Goal() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_Finding_Goal;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATES_stm_ref0_Enum create_STATES_stm_ref0_PrePicking() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_PrePicking;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATES_stm_ref0_Enum create_STATES_stm_ref0_PrePlacing() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_PrePlacing;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
STATES_stm_ref0_Enum create_STATES_stm_ref0_Returning() {
  STATES_stm_ref0_Data data;

  STATES_stm_ref0_Type type = STATES_stm_ref0_Returning;

  STATES_stm_ref0_Enum aux = (STATES_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum TRANSITIONS_stm_ref0 */

typedef enum {
  TRANSITIONS_stm_ref0_NONE,
  TRANSITIONS_stm_ref0_stm_ref0_t10,
  TRANSITIONS_stm_ref0_stm_ref0_t18,
  TRANSITIONS_stm_ref0_stm_ref0_t5,
  TRANSITIONS_stm_ref0_stm_ref0_t2,
  TRANSITIONS_stm_ref0_stm_ref0_t3,
  TRANSITIONS_stm_ref0_stm_ref0_t9,
  TRANSITIONS_stm_ref0_stm_ref0_t1,
  TRANSITIONS_stm_ref0_stm_ref0_t6,
  TRANSITIONS_stm_ref0_stm_ref0_t0,
  TRANSITIONS_stm_ref0_stm_ref0_t7,
  TRANSITIONS_stm_ref0_stm_ref0_t14,
} TRANSITIONS_stm_ref0_Type;

typedef union {
} TRANSITIONS_stm_ref0_Data;

typedef struct {
  TRANSITIONS_stm_ref0_Type type;
  TRANSITIONS_stm_ref0_Data data;
} TRANSITIONS_stm_ref0_Enum;

TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_NONE() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_NONE;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t10() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t10;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t18() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t18;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t5() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t5;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t2() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t2;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t3() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t3;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t9() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t9;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t1() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t1;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t6() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t6;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t0() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t0;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t7() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t7;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
TRANSITIONS_stm_ref0_Enum create_TRANSITIONS_stm_ref0_stm_ref0_t14() {
  TRANSITIONS_stm_ref0_Data data;

  TRANSITIONS_stm_ref0_Type type = TRANSITIONS_stm_ref0_stm_ref0_t14;

  TRANSITIONS_stm_ref0_Enum aux = (TRANSITIONS_stm_ref0_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum C_ctrl_ref0_output */

typedef enum {
  C_ctrl_ref0_output_PrePick,
  C_ctrl_ref0_output_PrePlace,
  C_ctrl_ref0_output_Return,
  C_ctrl_ref0_output__done_,
} C_ctrl_ref0_output_Type;

typedef union {
} C_ctrl_ref0_output_Data;

typedef struct {
  C_ctrl_ref0_output_Type type;
  C_ctrl_ref0_output_Data data;
} C_ctrl_ref0_output_Enum;

C_ctrl_ref0_output_Enum create_C_ctrl_ref0_output_PrePick() {
  C_ctrl_ref0_output_Data data;

  C_ctrl_ref0_output_Type type = C_ctrl_ref0_output_PrePick;

  C_ctrl_ref0_output_Enum aux = (C_ctrl_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_output_Enum create_C_ctrl_ref0_output_PrePlace() {
  C_ctrl_ref0_output_Data data;

  C_ctrl_ref0_output_Type type = C_ctrl_ref0_output_PrePlace;

  C_ctrl_ref0_output_Enum aux = (C_ctrl_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_output_Enum create_C_ctrl_ref0_output_Return() {
  C_ctrl_ref0_output_Data data;

  C_ctrl_ref0_output_Type type = C_ctrl_ref0_output_Return;

  C_ctrl_ref0_output_Enum aux = (C_ctrl_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_output_Enum create_C_ctrl_ref0_output__done_() {
  C_ctrl_ref0_output_Data data;

  C_ctrl_ref0_output_Type type = C_ctrl_ref0_output__done_;

  C_ctrl_ref0_output_Enum aux = (C_ctrl_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum stm_ref0_output */

typedef enum {
  stm_ref0_output_PrePlace,
  stm_ref0_output_PrePick,
  stm_ref0_output_Return,
  stm_ref0_output__done_,
} stm_ref0_output_Type;

typedef union {
} stm_ref0_output_Data;

typedef struct {
  stm_ref0_output_Type type;
  stm_ref0_output_Data data;
} stm_ref0_output_Enum;

stm_ref0_output_Enum create_stm_ref0_output_PrePlace() {
  stm_ref0_output_Data data;

  stm_ref0_output_Type type = stm_ref0_output_PrePlace;

  stm_ref0_output_Enum aux = (stm_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_output_Enum create_stm_ref0_output_PrePick() {
  stm_ref0_output_Data data;

  stm_ref0_output_Type type = stm_ref0_output_PrePick;

  stm_ref0_output_Enum aux = (stm_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_output_Enum create_stm_ref0_output_Return() {
  stm_ref0_output_Data data;

  stm_ref0_output_Type type = stm_ref0_output_Return;

  stm_ref0_output_Enum aux = (stm_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_output_Enum create_stm_ref0_output__done_() {
  stm_ref0_output_Data data;

  stm_ref0_output_Type type = stm_ref0_output__done_;

  stm_ref0_output_Enum aux = (stm_ref0_output_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum M_PickPlace_input */

typedef enum {
  M_PickPlace_input_detectGoal,
  M_PickPlace_input_detectObject,
  M_PickPlace_input__done_,
  M_PickPlace_input__terminate_,
} M_PickPlace_input_Type;

typedef struct {
  bool v1;
} M_PickPlace_input_detectGoal_Data;

typedef struct {
  bool v1;
} M_PickPlace_input_detectObject_Data;

typedef union {
  M_PickPlace_input_detectGoal_Data detectGoal;
  M_PickPlace_input_detectObject_Data detectObject;
} M_PickPlace_input_Data;

typedef struct {
  M_PickPlace_input_Type type;
  M_PickPlace_input_Data data;
} M_PickPlace_input_Enum;

M_PickPlace_input_Enum create_M_PickPlace_input_detectGoal(bool v1) {
  M_PickPlace_input_Data data;
  data.detectGoal.v1 = v1;

  M_PickPlace_input_Type type = M_PickPlace_input_detectGoal;

  M_PickPlace_input_Enum aux = (M_PickPlace_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_input_Enum create_M_PickPlace_input_detectObject(bool v1) {
  M_PickPlace_input_Data data;
  data.detectObject.v1 = v1;

  M_PickPlace_input_Type type = M_PickPlace_input_detectObject;

  M_PickPlace_input_Enum aux = (M_PickPlace_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_input_Enum create_M_PickPlace_input__done_() {
  M_PickPlace_input_Data data;

  M_PickPlace_input_Type type = M_PickPlace_input__done_;

  M_PickPlace_input_Enum aux = (M_PickPlace_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
M_PickPlace_input_Enum create_M_PickPlace_input__terminate_() {
  M_PickPlace_input_Data data;

  M_PickPlace_input_Type type = M_PickPlace_input__terminate_;

  M_PickPlace_input_Enum aux = (M_PickPlace_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum stm_ref0_input */

typedef enum {
  stm_ref0_input_detectGoal,
  stm_ref0_input_detectObject,
  stm_ref0_input__done_,
  stm_ref0_input__terminate_,
} stm_ref0_input_Type;

typedef struct {
  bool v1;
} stm_ref0_input_detectGoal_Data;

typedef struct {
  bool v1;
} stm_ref0_input_detectObject_Data;

typedef union {
  stm_ref0_input_detectGoal_Data detectGoal;
  stm_ref0_input_detectObject_Data detectObject;
} stm_ref0_input_Data;

typedef struct {
  stm_ref0_input_Type type;
  stm_ref0_input_Data data;
} stm_ref0_input_Enum;

stm_ref0_input_Enum create_stm_ref0_input_detectGoal(bool v1) {
  stm_ref0_input_Data data;
  data.detectGoal.v1 = v1;

  stm_ref0_input_Type type = stm_ref0_input_detectGoal;

  stm_ref0_input_Enum aux = (stm_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_input_Enum create_stm_ref0_input_detectObject(bool v1) {
  stm_ref0_input_Data data;
  data.detectObject.v1 = v1;

  stm_ref0_input_Type type = stm_ref0_input_detectObject;

  stm_ref0_input_Enum aux = (stm_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_input_Enum create_stm_ref0_input__done_() {
  stm_ref0_input_Data data;

  stm_ref0_input_Type type = stm_ref0_input__done_;

  stm_ref0_input_Enum aux = (stm_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
stm_ref0_input_Enum create_stm_ref0_input__terminate_() {
  stm_ref0_input_Data data;

  stm_ref0_input_Type type = stm_ref0_input__terminate_;

  stm_ref0_input_Enum aux = (stm_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
/* Representation of enum C_ctrl_ref0_input */

typedef enum {
  C_ctrl_ref0_input_detectObject,
  C_ctrl_ref0_input_detectGoal,
  C_ctrl_ref0_input__done_,
  C_ctrl_ref0_input__terminate_,
} C_ctrl_ref0_input_Type;

typedef struct {
  bool v1;
} C_ctrl_ref0_input_detectObject_Data;

typedef struct {
  bool v1;
} C_ctrl_ref0_input_detectGoal_Data;

typedef union {
  C_ctrl_ref0_input_detectObject_Data detectObject;
  C_ctrl_ref0_input_detectGoal_Data detectGoal;
} C_ctrl_ref0_input_Data;

typedef struct {
  C_ctrl_ref0_input_Type type;
  C_ctrl_ref0_input_Data data;
} C_ctrl_ref0_input_Enum;

C_ctrl_ref0_input_Enum create_C_ctrl_ref0_input_detectObject(bool v1) {
  C_ctrl_ref0_input_Data data;
  data.detectObject.v1 = v1;

  C_ctrl_ref0_input_Type type = C_ctrl_ref0_input_detectObject;

  C_ctrl_ref0_input_Enum aux = (C_ctrl_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_input_Enum create_C_ctrl_ref0_input_detectGoal(bool v1) {
  C_ctrl_ref0_input_Data data;
  data.detectGoal.v1 = v1;

  C_ctrl_ref0_input_Type type = C_ctrl_ref0_input_detectGoal;

  C_ctrl_ref0_input_Enum aux = (C_ctrl_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_input_Enum create_C_ctrl_ref0_input__done_() {
  C_ctrl_ref0_input_Data data;

  C_ctrl_ref0_input_Type type = C_ctrl_ref0_input__done_;

  C_ctrl_ref0_input_Enum aux = (C_ctrl_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}
C_ctrl_ref0_input_Enum create_C_ctrl_ref0_input__terminate_() {
  C_ctrl_ref0_input_Data data;

  C_ctrl_ref0_input_Type type = C_ctrl_ref0_input__terminate_;

  C_ctrl_ref0_input_Enum aux = (C_ctrl_ref0_input_Enum) {
      .type = type,
      .data = data
  };

  return aux;
}

/* Representation of record stm_ref0_inputstate */
typedef struct {
  bool detectGoal;
  bool detectGoal_value;
  bool detectObject;
  bool detectObject_value;
  int _clock_C;
  TRANSITIONS_stm_ref0_Enum _transition_;
} stm_ref0_inputstate;
/* Representation of record stm_ref0_state */
typedef struct {
  bool done;
  STATES_stm_ref0_Enum state;
  STATES_stm_ref0_Enum target_state;
  STATUS_Enum status;
  bool tr_PickPlaceS_t10_done;
  int tr_PickPlaceS_t10_counter;
  bool tr_PickPlaceS_t5_done;
  int tr_PickPlaceS_t5_counter;
  bool tr_PickPlaceS_t2_done;
  int tr_PickPlaceS_t2_counter;
  bool tr_PickPlaceS_t9_done;
  int tr_PickPlaceS_t9_counter;
  bool tr_PickPlaceS_t6_done;
  int tr_PickPlaceS_t6_counter;
  bool tr_PickPlaceS_t0_done;
  int tr_PickPlaceS_t0_counter;
  bool tr_PickPlaceS_t7_done;
  int tr_PickPlaceS_t7_counter;
  bool tr_PickPlaceS_t14_done;
  int tr_PickPlaceS_t14_counter;
} stm_ref0_state;
/* Representation of record stm_ref0_memory */
typedef struct {
  float CYCLE;
} stm_ref0_memory;

typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  stm_ref0_input_Enum value;
} stm_ref0_input_Enum_Channel;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  stm_ref0_output_Enum value;
} stm_ref0_output_Enum_Channel;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  C_ctrl_ref0_output_Enum value;
} C_ctrl_ref0_output_Enum_Channel;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  M_PickPlace_input_Enum value;
} M_PickPlace_input_Enum_Channel;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  M_PickPlace_output_Enum value;
} M_PickPlace_output_Enum_Channel;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  C_ctrl_ref0_input_Enum value;
} C_ctrl_ref0_input_Enum_Channel;

typedef struct {
  M_PickPlace_output_Enum_Channel* end_PickPlace;
  M_PickPlace_input_Enum_Channel* start_PickPlace;
} control_Channels;

/* Declaration of function signatures */
char* print_STATUS(STATUS_Enum* value);
void mod_PickPlace_step(C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0
                        , C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0);
RESULT_Enum tr_PickPlaceS_t0(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_stm_ref0_state(stm_ref0_state* state);
RESULT_Enum tr_PickPlaceS_t6(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t14(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_STATES_stm_ref0(STATES_stm_ref0_Enum* value);
RESULT_Enum tr_PickPlaceS_t7(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum stm_stm_ref0_step(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memorystate, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t10(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t5(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
void ctrl_ctrl_ref0_step(stm_ref0_input_Enum_Channel* start_stm_ref0
                         , stm_ref0_output_Enum_Channel* end_stm_ref0);
RESULT_Enum tr_PickPlaceS_t9(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t2(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);

void *control(void *arg) {
  control_Channels* channels = (control_Channels*) arg;
  M_PickPlace_output_Enum_Channel* end_PickPlace = channels->end_PickPlace;
  M_PickPlace_input_Enum_Channel* start_PickPlace = channels->start_PickPlace;
  {
    bool terminate__ = false;
    while (!terminate__) {
      {
        bool inputdone = false;
        while (!inputdone) {
          {
            char _s0[256];
            sprintf(_s0, "%s", "Enter an event:");
            printf("%s", _s0);
          }
          char* _event_;
          char _temp_0[256];
          if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
          _event_ = trim(_temp_0,NULL);
          if (strcmp(_event_, "") == 0) {
            {
              int status = pthread_mutex_lock(&start_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_PickPlace->value = create_M_PickPlace_input__done_();

              status = pthread_cond_signal(&start_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            inputdone = true;
          }
          else if (strcmp(_event_, "detectObject") == 0) {
            {
              char _s0[256];
              sprintf(_s0, "%s", "Found event detectObject");
              printf("%s\n", _s0);}
            {
              char _s0[256];
              sprintf(_s0, "%s", "Enter value for event detectObject of type boolean: ");
              printf("%s", _s0);
            }
            {
              char* _svalue_;
              char _temp_0[256];
              if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
              _svalue_ = trim(_temp_0,NULL);
              bool _value_ = false;
              _value_ = ((strcmp(_svalue_,"true") == 0)?true:false);
              {
                int status = pthread_mutex_lock(&start_PickPlace->mutex);
                if (status != 0)
                  err_abort(status, "Lock mutex");

                start_PickPlace->value = create_M_PickPlace_input_detectObject(_value_);

                status = pthread_cond_signal(&start_PickPlace->cond);
                if (status != 0)
                  err_abort(status, "Signal cond");

                status = pthread_mutex_unlock(&start_PickPlace->mutex);
                if (status != 0)
                  err_abort(status, "Unlock mutex");
              }
            }
          }
          else if (strcmp(_event_, "detectGoal") == 0) {
            {
              char _s0[256];
              sprintf(_s0, "%s", "Found event detectGoal");
              printf("%s\n", _s0);}
            {
              char _s0[256];
              sprintf(_s0, "%s", "Enter value for event detectGoal of type boolean: ");
              printf("%s", _s0);
            }
            {
              char* _svalue_;
              char _temp_0[256];
              if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
              _svalue_ = trim(_temp_0,NULL);
              bool _value_ = false;
              _value_ = ((strcmp(_svalue_,"true") == 0)?true:false);
              {
                int status = pthread_mutex_lock(&start_PickPlace->mutex);
                if (status != 0)
                  err_abort(status, "Lock mutex");

                start_PickPlace->value = create_M_PickPlace_input_detectGoal(_value_);

                status = pthread_cond_signal(&start_PickPlace->cond);
                if (status != 0)
                  err_abort(status, "Signal cond");

                status = pthread_mutex_unlock(&start_PickPlace->mutex);
                if (status != 0)
                  err_abort(status, "Unlock mutex");
              }
            }
          }
          else if (strcmp(_event_, "$end") == 0) {
            {
              int status = pthread_mutex_lock(&start_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_PickPlace->value = create_M_PickPlace_input__terminate_();

              status = pthread_cond_signal(&start_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            {
              char _s0[256];
              sprintf(_s0, "%s", "Terminating system. One more cycle will run before this program ends.");
              printf("%s\n", _s0);}
            terminate__ = true;
            inputdone = true;
          }
          else {
            {
              char _s0[256];
              sprintf(_s0, "%s%s", "Unknown event: ", _event_);
              printf("%s\n", _s0);}
          }
        }
      }
      {
        // communicating block with inputs: end_PickPlace)
        int status = pthread_mutex_lock(&end_PickPlace->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");
        bool outputdone = false;
        while (!outputdone) {
          M_PickPlace_output_Enum _output_;
          {
            int status = pthread_cond_wait(&end_PickPlace->cond, &end_PickPlace->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _output_ = end_PickPlace->value;
          }
          if (_output_.type == M_PickPlace_output_PrePlace) {
            {
              char _s0[256];
              sprintf(_s0, "%s", "output PrePlace");
              printf("%s\n", _s0);}
          }
          else if (_output_.type == M_PickPlace_output_Return) {
            {
              char _s0[256];
              sprintf(_s0, "%s", "output Return");
              printf("%s\n", _s0);}
          }
          else if (_output_.type == M_PickPlace_output_PrePick) {
            {
              char _s0[256];
              sprintf(_s0, "%s", "output PrePick");
              printf("%s\n", _s0);}
          }
          else if (_output_.type == M_PickPlace_output__done_) {
            outputdone = true;
            {
              char _s0[256];
              sprintf(_s0, "%s", "---------------------");
              printf("%s\n", _s0);}
          }
        }
        status = pthread_mutex_unlock(&end_PickPlace->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");

      }
    }
  }
}
typedef struct {
  M_PickPlace_input_Enum_Channel* start_PickPlace;
  C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0;
  M_PickPlace_output_Enum_Channel* end_PickPlace;
  C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0;
} mod_PickPlace_thread_Channels;

/* Declaration of function signatures */
char* print_STATUS(STATUS_Enum* value);
void mod_PickPlace_step(C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0
                        , C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0);
RESULT_Enum tr_PickPlaceS_t0(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_stm_ref0_state(stm_ref0_state* state);
RESULT_Enum tr_PickPlaceS_t6(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t14(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_STATES_stm_ref0(STATES_stm_ref0_Enum* value);
RESULT_Enum tr_PickPlaceS_t7(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum stm_stm_ref0_step(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memorystate, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t10(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t5(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
void ctrl_ctrl_ref0_step(stm_ref0_input_Enum_Channel* start_stm_ref0
                         , stm_ref0_output_Enum_Channel* end_stm_ref0);
RESULT_Enum tr_PickPlaceS_t9(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t2(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);

void *mod_PickPlace_thread(void *arg) {
  mod_PickPlace_thread_Channels* channels = (mod_PickPlace_thread_Channels*) arg;
  M_PickPlace_input_Enum_Channel* start_PickPlace = channels->start_PickPlace;
  C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0 = channels->end_ctrl_ref0;
  M_PickPlace_output_Enum_Channel* end_PickPlace = channels->end_PickPlace;
  C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0 = channels->start_ctrl_ref0;
  {
    bool terminate__ = false;
    while (!terminate__) {
      {
        // communicating block with inputs: start_PickPlace)
        int status = pthread_mutex_lock(&start_PickPlace->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");
        bool inputDone = false;
        while (!inputDone) {
          {
            char _s0[256];
            sprintf(_s0, "%s", "- Waiting for input on channel start_PickPlace");
            fprintf(log_file, "DEBUG: %s\n", _s0);
          }
          M_PickPlace_input_Enum _input_;
          {
            int status = pthread_cond_wait(&start_PickPlace->cond, &start_PickPlace->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _input_ = start_PickPlace->value;
          }
          {
            char _s0[256];
            sprintf(_s0, "%s", "- Read input on channel start_PickPlace");
            fprintf(log_file, "DEBUG: %s\n", _s0);
          }
          if (_input_.type == M_PickPlace_input_detectGoal) {
            bool _aux1_ = _input_.data.detectGoal.v1;
            {
              int status = pthread_mutex_lock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_ctrl_ref0->value = create_C_ctrl_ref0_input_detectGoal(_aux1_);

              status = pthread_cond_signal(&start_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_input_.type == M_PickPlace_input_detectObject) {
            bool _aux1_ = _input_.data.detectObject.v1;
            {
              int status = pthread_mutex_lock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_ctrl_ref0->value = create_C_ctrl_ref0_input_detectObject(_aux1_);

              status = pthread_cond_signal(&start_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_input_.type == M_PickPlace_input__done_) {
            {
              int status = pthread_mutex_lock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_ctrl_ref0->value = create_C_ctrl_ref0_input__done_();

              status = pthread_cond_signal(&start_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            inputDone = true;
          }
          else if (_input_.type == M_PickPlace_input__terminate_) {
            {
              int status = pthread_mutex_lock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_ctrl_ref0->value = create_C_ctrl_ref0_input__terminate_();

              status = pthread_cond_signal(&start_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            terminate__ = true;
          }
        }
        status = pthread_mutex_unlock(&start_PickPlace->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");

      }
      {
        char _s0[256];
        sprintf(_s0, "%s", "Finished reading inputs of module PickPlace");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      mod_PickPlace_step(start_ctrl_ref0
                         , end_ctrl_ref0);
      {
        // communicating block with inputs: end_ctrl_ref0)
        int status = pthread_mutex_lock(&end_ctrl_ref0->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");
        bool outputDone = false;
        while (!outputDone) {
          C_ctrl_ref0_output_Enum _output_;
          {
            int status = pthread_cond_wait(&end_ctrl_ref0->cond, &end_ctrl_ref0->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _output_ = end_ctrl_ref0->value;
          }
          if (_output_.type == C_ctrl_ref0_output_PrePick) {
            {
              int status = pthread_mutex_lock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_PickPlace->value = create_M_PickPlace_output_PrePick();

              status = pthread_cond_signal(&end_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == C_ctrl_ref0_output_PrePlace) {
            {
              int status = pthread_mutex_lock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_PickPlace->value = create_M_PickPlace_output_PrePlace();

              status = pthread_cond_signal(&end_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == C_ctrl_ref0_output_Return) {
            {
              int status = pthread_mutex_lock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_PickPlace->value = create_M_PickPlace_output_Return();

              status = pthread_cond_signal(&end_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == C_ctrl_ref0_output__done_) {
            {
              int status = pthread_mutex_lock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_PickPlace->value = create_M_PickPlace_output__done_();

              status = pthread_cond_signal(&end_PickPlace->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_PickPlace->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            outputDone = true;
          }
        }
        status = pthread_mutex_unlock(&end_ctrl_ref0->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");

      }
    }
  }
}
typedef struct {
  stm_ref0_input_Enum_Channel* start_stm_ref0;
  stm_ref0_output_Enum_Channel* end_stm_ref0;
} stm_stm_ref0_Channels;

/* Declaration of function signatures */
char* print_STATUS(STATUS_Enum* value);
void mod_PickPlace_step(C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0
                        , C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0);
RESULT_Enum tr_PickPlaceS_t0(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_stm_ref0_state(stm_ref0_state* state);
RESULT_Enum tr_PickPlaceS_t6(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t14(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_STATES_stm_ref0(STATES_stm_ref0_Enum* value);
RESULT_Enum tr_PickPlaceS_t7(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum stm_stm_ref0_step(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memorystate, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t10(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t5(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
void ctrl_ctrl_ref0_step(stm_ref0_input_Enum_Channel* start_stm_ref0
                         , stm_ref0_output_Enum_Channel* end_stm_ref0);
RESULT_Enum tr_PickPlaceS_t9(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t2(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);

void *stm_stm_ref0(void *arg) {
  stm_stm_ref0_Channels* channels = (stm_stm_ref0_Channels*) arg;
  stm_ref0_input_Enum_Channel* start_stm_ref0 = channels->start_stm_ref0;
  stm_ref0_output_Enum_Channel* end_stm_ref0 = channels->end_stm_ref0;
  {
    // state machine variable declarations;
    stm_ref0_inputstate inputstate = (stm_ref0_inputstate) {
        .detectGoal = false,
        .detectGoal_value = false,
        .detectObject = false,
        .detectObject_value = false,
        ._clock_C = 0
        ,
        ._transition_ = create_TRANSITIONS_stm_ref0_NONE()
    };
    stm_ref0_state state = (stm_ref0_state) {
        .done = false,
        .state = create_STATES_stm_ref0_NONE(),
        .target_state = create_STATES_stm_ref0_NONE(),
        .status = create_STATUS_ENTER_STATE(),
        .tr_PickPlaceS_t10_done = false,
        .tr_PickPlaceS_t10_counter = 0
        ,
        .tr_PickPlaceS_t5_done = false,
        .tr_PickPlaceS_t5_counter = 0
        ,
        .tr_PickPlaceS_t2_done = false,
        .tr_PickPlaceS_t2_counter = 0
        ,
        .tr_PickPlaceS_t9_done = false,
        .tr_PickPlaceS_t9_counter = 0
        ,
        .tr_PickPlaceS_t6_done = false,
        .tr_PickPlaceS_t6_counter = 0
        ,
        .tr_PickPlaceS_t0_done = false,
        .tr_PickPlaceS_t0_counter = 0
        ,
        .tr_PickPlaceS_t7_done = false,
        .tr_PickPlaceS_t7_counter = 0
        ,
        .tr_PickPlaceS_t14_done = false,
        .tr_PickPlaceS_t14_counter = 0
    };
    stm_ref0_memory memorystate = (stm_ref0_memory) {
        .CYCLE = 1.0E-4
    };
    // state machine loop;
    while (!(state).done) {
      {
        {
          char _s0[256];
          sprintf(_s0, "%s", "- Waiting for input on channel start_stm_ref0");
          fprintf(log_file, "DEBUG: %s\n", _s0);
        }
        bool inputDone = false;
        while (!inputDone) {
          stm_ref0_input_Enum _input_;
          {
            int status = pthread_cond_wait(&start_stm_ref0->cond, &start_stm_ref0->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _input_ = start_stm_ref0->value;
          }
          {
            char _s0[256];
            sprintf(_s0, "%s", "- Read input on channel start_stm_ref0");
            fprintf(log_file, "DEBUG: %s\n", _s0);
          }
          if (_input_.type == stm_ref0_input_detectGoal) {
            bool _aux_ = _input_.data.detectGoal.v1;
            (inputstate).detectGoal = true;
            (inputstate).detectGoal_value = _aux_;
          }
          else if (_input_.type == stm_ref0_input_detectObject) {
            bool _aux_ = _input_.data.detectObject.v1;
            (inputstate).detectObject = true;
            (inputstate).detectObject_value = _aux_;
          }
          else if (_input_.type == stm_ref0_input__done_) {
            inputDone = true;
          }
          else if (_input_.type == stm_ref0_input__terminate_) {
            inputDone = true;
          }
        }
      }
      RESULT_Enum ret = create_RESULT_CONT();
      while (	ret.type == create_RESULT_CONT().type
      ) {
        char* temp_;
        temp_ = print_stm_ref0_state(&state);
        {
          char _s0[256];
          sprintf(_s0, "%s", "	");
          printf("%s", _s0);
        }
        {
          char _s0[256];
          sprintf(_s0, "%s", temp_);
          printf("%s\n", _s0);}
        ret = stm_stm_ref0_step(&state, &inputstate, &memorystate, end_stm_ref0);
      }
      {
        int status = pthread_mutex_lock(&end_stm_ref0->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");

        end_stm_ref0->value = create_stm_ref0_output__done_();

        status = pthread_cond_signal(&end_stm_ref0->cond);
        if (status != 0)
          err_abort(status, "Signal cond");

        status = pthread_mutex_unlock(&end_stm_ref0->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");
      }
      // update clocks;
      (inputstate)._clock_C = ((inputstate)._clock_C + 1);
      // reset input events;
      (inputstate).detectObject = false;
      (inputstate).detectGoal = false;
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Sent output _done_ on channel end_stm_ref0");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }

    }
  }
}
typedef struct {
  C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0;
  stm_ref0_output_Enum_Channel* end_stm_ref0;
  C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0;
  stm_ref0_input_Enum_Channel* start_stm_ref0;
} ctrl_ctrl_ref0_thread_Channels;

/* Declaration of function signatures */
char* print_STATUS(STATUS_Enum* value);
void mod_PickPlace_step(C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0
                        , C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0);
RESULT_Enum tr_PickPlaceS_t0(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_stm_ref0_state(stm_ref0_state* state);
RESULT_Enum tr_PickPlaceS_t6(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t14(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
char* print_STATES_stm_ref0(STATES_stm_ref0_Enum* value);
RESULT_Enum tr_PickPlaceS_t7(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum stm_stm_ref0_step(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memorystate, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t10(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t5(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
void ctrl_ctrl_ref0_step(stm_ref0_input_Enum_Channel* start_stm_ref0
                         , stm_ref0_output_Enum_Channel* end_stm_ref0);
RESULT_Enum tr_PickPlaceS_t9(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);
RESULT_Enum tr_PickPlaceS_t2(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output);

void *ctrl_ctrl_ref0_thread(void *arg) {
  ctrl_ctrl_ref0_thread_Channels* channels = (ctrl_ctrl_ref0_thread_Channels*) arg;
  C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0 = channels->start_ctrl_ref0;
  stm_ref0_output_Enum_Channel* end_stm_ref0 = channels->end_stm_ref0;
  C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0 = channels->end_ctrl_ref0;
  stm_ref0_input_Enum_Channel* start_stm_ref0 = channels->start_stm_ref0;
  {
    bool terminate__ = false;
    while (!terminate__) {
      {
        // communicating block with inputs: start_ctrl_ref0)
        int status = pthread_mutex_lock(&start_ctrl_ref0->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");
        bool inputDone = false;
        while (!inputDone) {
          {
            char _s0[256];
            sprintf(_s0, "%s", "- Waiting for input on channel start_ctrl_ref0");
            fprintf(log_file, "DEBUG: %s\n", _s0);
          }
          C_ctrl_ref0_input_Enum _input_;
          {
            int status = pthread_cond_wait(&start_ctrl_ref0->cond, &start_ctrl_ref0->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _input_ = start_ctrl_ref0->value;
          }
          {
            char _s0[256];
            sprintf(_s0, "%s", "- Read input on channel start_ctrl_ref0");
            fprintf(log_file, "DEBUG: %s\n", _s0);
          }
          if (_input_.type == C_ctrl_ref0_input_detectObject) {
            bool _aux1_ = _input_.data.detectObject.v1;
            {
              int status = pthread_mutex_lock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_stm_ref0->value = create_stm_ref0_input_detectObject(_aux1_);

              status = pthread_cond_signal(&start_stm_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_input_.type == C_ctrl_ref0_input_detectGoal) {
            bool _aux1_ = _input_.data.detectGoal.v1;
            {
              int status = pthread_mutex_lock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_stm_ref0->value = create_stm_ref0_input_detectGoal(_aux1_);

              status = pthread_cond_signal(&start_stm_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_input_.type == C_ctrl_ref0_input__done_) {
            {
              int status = pthread_mutex_lock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_stm_ref0->value = create_stm_ref0_input__done_();

              status = pthread_cond_signal(&start_stm_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            inputDone = true;
          }
          else if (_input_.type == C_ctrl_ref0_input__terminate_) {
            {
              int status = pthread_mutex_lock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              start_stm_ref0->value = create_stm_ref0_input__terminate_();

              status = pthread_cond_signal(&start_stm_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&start_stm_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            terminate__ = true;
          }
        }
        status = pthread_mutex_unlock(&start_ctrl_ref0->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");

      }
      {
        char _s0[256];
        sprintf(_s0, "%s", "	Finished reading inputs of controller ctrl_ref0");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      ctrl_ctrl_ref0_step(start_stm_ref0
                          , end_stm_ref0);
      {
        // communicating block with inputs: end_stm_ref0)
        int status = pthread_mutex_lock(&end_stm_ref0->mutex);
        if (status != 0)
          err_abort(status, "Lock mutex");
        bool outputDone = false;
        while (!outputDone) {
          stm_ref0_output_Enum _output_;
          {
            int status = pthread_cond_wait(&end_stm_ref0->cond, &end_stm_ref0->mutex);
            if (status != 0)
              err_abort(status, "Wait on cond");

            _output_ = end_stm_ref0->value;
          }
          if (_output_.type == stm_ref0_output_PrePick) {
            {
              int status = pthread_mutex_lock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_ctrl_ref0->value = create_C_ctrl_ref0_output_PrePick();

              status = pthread_cond_signal(&end_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == stm_ref0_output_Return) {
            {
              int status = pthread_mutex_lock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_ctrl_ref0->value = create_C_ctrl_ref0_output_Return();

              status = pthread_cond_signal(&end_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == stm_ref0_output_PrePlace) {
            {
              int status = pthread_mutex_lock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_ctrl_ref0->value = create_C_ctrl_ref0_output_PrePlace();

              status = pthread_cond_signal(&end_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
          }
          else if (_output_.type == stm_ref0_output__done_) {
            {
              int status = pthread_mutex_lock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Lock mutex");

              end_ctrl_ref0->value = create_C_ctrl_ref0_output__done_();

              status = pthread_cond_signal(&end_ctrl_ref0->cond);
              if (status != 0)
                err_abort(status, "Signal cond");

              status = pthread_mutex_unlock(&end_ctrl_ref0->mutex);
              if (status != 0)
                err_abort(status, "Unlock mutex");
            }
            outputDone = true;
          }
        }
        status = pthread_mutex_unlock(&end_stm_ref0->mutex);
        if (status != 0)
          err_abort(status, "Unlock mutex");

      }
    }
  }
}

int main(int argc, char* argv[]) {
  //let _ = WriteLogger::init(
  //	LevelFilter::Trace, Config::default(), File::create("test.log").unwrap());
  log_file = fopen("test.log", "w");

  //let _args: Vec<String> = std::env::args().collect();
  if (argc  <= 0) {
    fprintf(stderr, "error: Not enough arguments.");
    exit(1);
  }

  // Module channel declarations;;
  M_PickPlace_input_Enum_Channel* start_PickPlace = (M_PickPlace_input_Enum_Channel*)malloc(sizeof(M_PickPlace_input_Enum_Channel));
  M_PickPlace_output_Enum_Channel* end_PickPlace = (M_PickPlace_output_Enum_Channel*)malloc(sizeof(M_PickPlace_output_Enum_Channel));
  C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0 = (C_ctrl_ref0_input_Enum_Channel*)malloc(sizeof(C_ctrl_ref0_input_Enum_Channel));
  C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0 = (C_ctrl_ref0_output_Enum_Channel*)malloc(sizeof(C_ctrl_ref0_output_Enum_Channel));
  stm_ref0_input_Enum_Channel* start_stm_ref0 = (stm_ref0_input_Enum_Channel*)malloc(sizeof(stm_ref0_input_Enum_Channel));
  stm_ref0_output_Enum_Channel* end_stm_ref0 = (stm_ref0_output_Enum_Channel*)malloc(sizeof(stm_ref0_output_Enum_Channel));
  // Instantiate threads;;
  int status;
  pthread_t control_id;
  control_Channels* control_channels = (control_Channels*)malloc(sizeof(control_Channels));

  control_channels->end_PickPlace = end_PickPlace;
  control_channels->start_PickPlace = start_PickPlace;

  status = pthread_create(&control_id, NULL, control, control_channels);
  if (status != 0)
    err_abort(status, "Create control thread");
  pthread_t mod_PickPlace_thread_id;
  mod_PickPlace_thread_Channels* mod_PickPlace_thread_channels = (mod_PickPlace_thread_Channels*)malloc(sizeof(mod_PickPlace_thread_Channels));

  mod_PickPlace_thread_channels->start_PickPlace = start_PickPlace;
  mod_PickPlace_thread_channels->end_ctrl_ref0 = end_ctrl_ref0;
  mod_PickPlace_thread_channels->end_PickPlace = end_PickPlace;
  mod_PickPlace_thread_channels->start_ctrl_ref0 = start_ctrl_ref0;

  status = pthread_create(&mod_PickPlace_thread_id, NULL, mod_PickPlace_thread, mod_PickPlace_thread_channels);
  if (status != 0)
    err_abort(status, "Create mod_PickPlace_thread thread");
  pthread_t stm_stm_ref0_id;
  stm_stm_ref0_Channels* stm_stm_ref0_channels = (stm_stm_ref0_Channels*)malloc(sizeof(stm_stm_ref0_Channels));

  stm_stm_ref0_channels->start_stm_ref0 = start_stm_ref0;
  stm_stm_ref0_channels->end_stm_ref0 = end_stm_ref0;

  status = pthread_create(&stm_stm_ref0_id, NULL, stm_stm_ref0, stm_stm_ref0_channels);
  if (status != 0)
    err_abort(status, "Create stm_stm_ref0 thread");
  pthread_t ctrl_ctrl_ref0_thread_id;
  ctrl_ctrl_ref0_thread_Channels* ctrl_ctrl_ref0_thread_channels = (ctrl_ctrl_ref0_thread_Channels*)malloc(sizeof(ctrl_ctrl_ref0_thread_Channels));

  ctrl_ctrl_ref0_thread_channels->start_ctrl_ref0 = start_ctrl_ref0;
  ctrl_ctrl_ref0_thread_channels->end_stm_ref0 = end_stm_ref0;
  ctrl_ctrl_ref0_thread_channels->end_ctrl_ref0 = end_ctrl_ref0;
  ctrl_ctrl_ref0_thread_channels->start_stm_ref0 = start_stm_ref0;

  status = pthread_create(&ctrl_ctrl_ref0_thread_id, NULL, ctrl_ctrl_ref0_thread, ctrl_ctrl_ref0_thread_channels);
  if (status != 0)
    err_abort(status, "Create ctrl_ctrl_ref0_thread thread");

  status = pthread_join(control_id, NULL);
  if (status != 0)
    err_abort(status, "Join control thread");
  status = pthread_join(mod_PickPlace_thread_id, NULL);
  if (status != 0)
    err_abort(status, "Join mod_PickPlace_thread thread");
  status = pthread_join(stm_stm_ref0_id, NULL);
  if (status != 0)
    err_abort(status, "Join stm_stm_ref0 thread");
  status = pthread_join(ctrl_ctrl_ref0_thread_id, NULL);
  if (status != 0)
    err_abort(status, "Join ctrl_ctrl_ref0_thread thread");

  return 0;;
}

char* print_STATUS(STATUS_Enum* value) {
  if (value->type == STATUS_ENTER_STATE) {
    return "ENTER_STATE";
  }
  else if (value->type == STATUS_ENTER_CHILDREN) {
    return "ENTER_CHILDREN";
  }
  else if (value->type == STATUS_EXECUTE_STATE) {
    return "EXECUTE_STATE";
  }
  else if (value->type == STATUS_EXIT_CHILDREN) {
    return "EXIT_CHILDREN";
  }
  else if (value->type == STATUS_EXIT_STATE) {
    return "EXIT_STATE";
  }
  else if (value->type == STATUS_INACTIVE) {
    return "INACTIVE";
  }
}
void mod_PickPlace_step(C_ctrl_ref0_input_Enum_Channel* start_ctrl_ref0
                        , C_ctrl_ref0_output_Enum_Channel* end_ctrl_ref0) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Started step of module PickPlace");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  {
    char _s0[256];
    sprintf(_s0, "%s", "Finished step of module PickPlace");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
}
RESULT_Enum tr_PickPlaceS_t0(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t0.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t0_counter == 0 ) {
    (*state).tr_PickPlaceS_t0_counter = 1;
    return create_RESULT_WAIT();
  } else {
    (state)->tr_PickPlaceS_t0_done = true;
    return create_RESULT_CONT();
  }
}
char* print_stm_ref0_state(stm_ref0_state* state) {
  char* temp1_;
  temp1_ = print_STATES_stm_ref0(&(state)->state);
  char* temp2_;
  temp2_ = print_STATUS(&(state)->status);
  return concat(concat(concat(temp1_, " ("), temp2_), ")");
}
RESULT_Enum tr_PickPlaceS_t6(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t6.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t6_counter == 0 ) {
    (*inputstate)._clock_C = 0;
    (*state).tr_PickPlaceS_t6_counter = 1;
    return create_RESULT_CONT();
  } else if (	(state)->tr_PickPlaceS_t6_counter == 1 ) {
    {
      int status = pthread_mutex_lock(&output->mutex);
      if (status != 0)
        err_abort(status, "Lock mutex");

      output->value = create_stm_ref0_output_PrePick();

      status = pthread_cond_signal(&output->cond);
      if (status != 0)
        err_abort(status, "Signal cond");

      status = pthread_mutex_unlock(&output->mutex);
      if (status != 0)
        err_abort(status, "Unlock mutex");
    }
    (*state).tr_PickPlaceS_t6_counter = 2;
    return create_RESULT_CONT();
  } else {
    (state)->tr_PickPlaceS_t6_done = true;
    return create_RESULT_CONT();
  }
}
RESULT_Enum tr_PickPlaceS_t14(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t14.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t14_counter == 0 ) {
    (*state).tr_PickPlaceS_t14_counter = 1;
    return create_RESULT_WAIT();
  } else {
    (state)->tr_PickPlaceS_t14_done = true;
    return create_RESULT_CONT();
  }
}
char* print_STATES_stm_ref0(STATES_stm_ref0_Enum* value) {
  if (value->type == STATES_stm_ref0_NONE) {
    return "NONE";
  }
  else if (value->type == STATES_stm_ref0_Finding_Object) {
    return "Finding_Object";
  }
  else if (value->type == STATES_stm_ref0_Finding_Goal) {
    return "Finding_Goal";
  }
  else if (value->type == STATES_stm_ref0_PrePicking) {
    return "PrePicking";
  }
  else if (value->type == STATES_stm_ref0_PrePlacing) {
    return "PrePlacing";
  }
  else if (value->type == STATES_stm_ref0_Returning) {
    return "Returning";
  }
}
RESULT_Enum tr_PickPlaceS_t7(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t7.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t7_counter == 0 ) {
    (*inputstate)._clock_C = 0;
    (*state).tr_PickPlaceS_t7_counter = 1;
    return create_RESULT_CONT();
  } else if (	(state)->tr_PickPlaceS_t7_counter == 1 ) {
    {
      int status = pthread_mutex_lock(&output->mutex);
      if (status != 0)
        err_abort(status, "Lock mutex");

      output->value = create_stm_ref0_output_PrePlace();

      status = pthread_cond_signal(&output->cond);
      if (status != 0)
        err_abort(status, "Signal cond");

      status = pthread_mutex_unlock(&output->mutex);
      if (status != 0)
        err_abort(status, "Unlock mutex");
    }
    (*state).tr_PickPlaceS_t7_counter = 2;
    return create_RESULT_CONT();
  } else {
    (state)->tr_PickPlaceS_t7_done = true;
    return create_RESULT_CONT();
  }
}
RESULT_Enum stm_stm_ref0_step(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memorystate, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "		Running step of state machine PickPlaceS");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if ((*state).state.type == create_STATES_stm_ref0_NONE().type) {
    {
      char _s0[256];
      sprintf(_s0, "%s", "		Executing initial junction of PickPlaceS");
      fprintf(log_file, "DEBUG: %s\n", _s0);
    }
    {
      (*state).state = create_STATES_stm_ref0_Finding_Object();
    }
    return create_RESULT_CONT();
  }
  else if ((*state).state.type == create_STATES_stm_ref0_Finding_Object().type) {
    if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering state Finding_Object");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        (*state).status = create_STATUS_ENTER_CHILDREN();
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering children of state Finding_Object");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXECUTE_STATE();
      {
        (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_NONE();
      }
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Executing state Finding_Object");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_NONE().type
      ) {
        if (!(inputstate)->detectObject) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t2();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else if ((inputstate)->detectObject) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t6();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else {
          return create_RESULT_CONT();
        }
      } else {
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting children of state Finding_Object");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXIT_STATE();
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting state Finding_Object");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t2().type
        ) {
          if (!(state)->tr_PickPlaceS_t2_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t2(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_Finding_Object();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t2_done = false;
            (*state).tr_PickPlaceS_t2_counter = 0;
            return create_RESULT_CONT();
          }
        } else if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t6().type
        ) {
          if (!(state)->tr_PickPlaceS_t6_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t6(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_PrePicking();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t6_done = false;
            (*state).tr_PickPlaceS_t6_counter = 0;
            return create_RESULT_CONT();
          }
        } else {
          (*state).status = create_STATUS_INACTIVE();
          (*state).state = create_STATES_stm_ref0_NONE();
          return create_RESULT_CONT();
        }
      }
    }
    else if ((*state).status.type == create_STATUS_INACTIVE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		State Finding_Object is inactive");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      return create_RESULT_CONT();
    }
  }
  else if ((*state).state.type == create_STATES_stm_ref0_Finding_Goal().type) {
    if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering state Finding_Goal");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        (*state).status = create_STATUS_ENTER_CHILDREN();
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering children of state Finding_Goal");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXECUTE_STATE();
      {
        (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_NONE();
      }
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Executing state Finding_Goal");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_NONE().type
      ) {
        if (!(inputstate)->detectGoal) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t0();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else if ((inputstate)->detectGoal) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t7();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else {
          return create_RESULT_CONT();
        }
      } else {
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting children of state Finding_Goal");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXIT_STATE();
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting state Finding_Goal");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t0().type
        ) {
          if (!(state)->tr_PickPlaceS_t0_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t0(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_Finding_Goal();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t0_done = false;
            (*state).tr_PickPlaceS_t0_counter = 0;
            return create_RESULT_CONT();
          }
        } else if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t7().type
        ) {
          if (!(state)->tr_PickPlaceS_t7_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t7(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_PrePlacing();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t7_done = false;
            (*state).tr_PickPlaceS_t7_counter = 0;
            return create_RESULT_CONT();
          }
        } else {
          (*state).status = create_STATUS_INACTIVE();
          (*state).state = create_STATES_stm_ref0_NONE();
          return create_RESULT_CONT();
        }
      }
    }
    else if ((*state).status.type == create_STATUS_INACTIVE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		State Finding_Goal is inactive");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      return create_RESULT_CONT();
    }
  }
  else if ((*state).state.type == create_STATES_stm_ref0_PrePicking().type) {
    if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering state PrePicking");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        (*state).status = create_STATUS_ENTER_CHILDREN();
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering children of state PrePicking");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXECUTE_STATE();
      {
        (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_NONE();
      }
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Executing state PrePicking");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_NONE().type
      ) {
        if ((inputstate)->_clock_C > (2 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t18();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else if ((inputstate)->_clock_C <= (2 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t5();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else {
          return create_RESULT_CONT();
        }
      } else {
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting children of state PrePicking");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXIT_STATE();
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting state PrePicking");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t18().type
        ) {
          (*state).state = create_STATES_stm_ref0_Finding_Goal();
          (*state).status = create_STATUS_ENTER_STATE();
          return create_RESULT_CONT();
        } else if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t5().type
        ) {
          if (!(state)->tr_PickPlaceS_t5_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t5(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_PrePicking();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t5_done = false;
            (*state).tr_PickPlaceS_t5_counter = 0;
            return create_RESULT_CONT();
          }
        } else {
          (*state).status = create_STATUS_INACTIVE();
          (*state).state = create_STATES_stm_ref0_NONE();
          return create_RESULT_CONT();
        }
      }
    }
    else if ((*state).status.type == create_STATUS_INACTIVE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		State PrePicking is inactive");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      return create_RESULT_CONT();
    }
  }
  else if ((*state).state.type == create_STATES_stm_ref0_PrePlacing().type) {
    if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering state PrePlacing");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        (*state).status = create_STATUS_ENTER_CHILDREN();
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering children of state PrePlacing");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXECUTE_STATE();
      {
        (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_NONE();
      }
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Executing state PrePlacing");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_NONE().type
      ) {
        if ((inputstate)->_clock_C <= (4 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t10();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else if ((inputstate)->_clock_C > (4 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t9();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else {
          return create_RESULT_CONT();
        }
      } else {
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting children of state PrePlacing");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXIT_STATE();
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting state PrePlacing");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t10().type
        ) {
          if (!(state)->tr_PickPlaceS_t10_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t10(state
                                      , inputstate
                                      , memorystate
                                      , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_PrePlacing();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t10_done = false;
            (*state).tr_PickPlaceS_t10_counter = 0;
            return create_RESULT_CONT();
          }
        } else if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t9().type
        ) {
          if (!(state)->tr_PickPlaceS_t9_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t9(state
                                     , inputstate
                                     , memorystate
                                     , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_Returning();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t9_done = false;
            (*state).tr_PickPlaceS_t9_counter = 0;
            return create_RESULT_CONT();
          }
        } else {
          (*state).status = create_STATUS_INACTIVE();
          (*state).state = create_STATES_stm_ref0_NONE();
          return create_RESULT_CONT();
        }
      }
    }
    else if ((*state).status.type == create_STATUS_INACTIVE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		State PrePlacing is inactive");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      return create_RESULT_CONT();
    }
  }
  else if ((*state).state.type == create_STATES_stm_ref0_Returning().type) {
    if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering state Returning");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        (*state).status = create_STATUS_ENTER_CHILDREN();
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Entering children of state Returning");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXECUTE_STATE();
      {
        (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_NONE();
      }
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Executing state Returning");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_NONE().type
      ) {
        if ((inputstate)->_clock_C > (2 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t3();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else if ((inputstate)->_clock_C <= (2 / (memorystate)->CYCLE)) {
          (*inputstate)._transition_ = create_TRANSITIONS_stm_ref0_stm_ref0_t14();
          (*state).status = create_STATUS_EXIT_CHILDREN();
          return create_RESULT_CONT();
        } else {
          return create_RESULT_CONT();
        }
      } else {
        return create_RESULT_CONT();
      }
    }
    else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting children of state Returning");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      (*state).status = create_STATUS_EXIT_STATE();
      return create_RESULT_CONT();
    }
    else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		Exiting state Returning");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      {
        if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t3().type
        ) {
          (*state).state = create_STATES_stm_ref0_Finding_Object();
          (*state).status = create_STATUS_ENTER_STATE();
          return create_RESULT_CONT();
        } else if (	(*inputstate)._transition_.type == create_TRANSITIONS_stm_ref0_stm_ref0_t14().type
        ) {
          if (!(state)->tr_PickPlaceS_t14_done) {
            RESULT_Enum _ret_;
            _ret_ = tr_PickPlaceS_t14(state
                                      , inputstate
                                      , memorystate
                                      , output);
            return _ret_;
          } else {
            (*state).state = create_STATES_stm_ref0_Returning();
            (*state).status = create_STATUS_ENTER_STATE();
            (*state).tr_PickPlaceS_t14_done = false;
            (*state).tr_PickPlaceS_t14_counter = 0;
            return create_RESULT_CONT();
          }
        } else {
          (*state).status = create_STATUS_INACTIVE();
          (*state).state = create_STATES_stm_ref0_NONE();
          return create_RESULT_CONT();
        }
      }
    }
    else if ((*state).status.type == create_STATUS_INACTIVE().type) {
      {
        char _s0[256];
        sprintf(_s0, "%s", "		State Returning is inactive");
        fprintf(log_file, "DEBUG: %s\n", _s0);
      }
      return create_RESULT_CONT();
    }
  }
}
RESULT_Enum tr_PickPlaceS_t10(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t10.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t10_counter == 0 ) {
    (*state).tr_PickPlaceS_t10_counter = 1;
    return create_RESULT_WAIT();
  } else {
    (state)->tr_PickPlaceS_t10_done = true;
    return create_RESULT_CONT();
  }
}
RESULT_Enum tr_PickPlaceS_t5(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t5.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t5_counter == 0 ) {
    (*state).tr_PickPlaceS_t5_counter = 1;
    return create_RESULT_WAIT();
  } else {
    (state)->tr_PickPlaceS_t5_done = true;
    return create_RESULT_CONT();
  }
}
void ctrl_ctrl_ref0_step(stm_ref0_input_Enum_Channel* start_stm_ref0
                         , stm_ref0_output_Enum_Channel* end_stm_ref0) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "	Started step of controller ctrl_ref0");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
}
RESULT_Enum tr_PickPlaceS_t9(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t9.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t9_counter == 0 ) {
    (*inputstate)._clock_C = 0;
    (*state).tr_PickPlaceS_t9_counter = 1;
    return create_RESULT_CONT();
  } else if (	(state)->tr_PickPlaceS_t9_counter == 1 ) {
    {
      int status = pthread_mutex_lock(&output->mutex);
      if (status != 0)
        err_abort(status, "Lock mutex");

      output->value = create_stm_ref0_output_Return();

      status = pthread_cond_signal(&output->cond);
      if (status != 0)
        err_abort(status, "Signal cond");

      status = pthread_mutex_unlock(&output->mutex);
      if (status != 0)
        err_abort(status, "Unlock mutex");
    }
    (*state).tr_PickPlaceS_t9_counter = 2;
    return create_RESULT_CONT();
  } else {
    (state)->tr_PickPlaceS_t9_done = true;
    return create_RESULT_CONT();
  }
}
RESULT_Enum tr_PickPlaceS_t2(stm_ref0_state* state, stm_ref0_inputstate* inputstate, stm_ref0_memory* memory, stm_ref0_output_Enum_Channel* output) {
  {
    char _s0[256];
    sprintf(_s0, "%s", "Running transition action of transition PickPlaceS_t2.");
    fprintf(log_file, "DEBUG: %s\n", _s0);
  }
  if (	(state)->tr_PickPlaceS_t2_counter == 0 ) {
    (*state).tr_PickPlaceS_t2_counter = 1;
    return create_RESULT_WAIT();
  } else {
    (state)->tr_PickPlaceS_t2_done = true;
    return create_RESULT_CONT();
  }
}


