/*
 * File: control_1.h
 *
 * Code generated for Simulink model 'control_1'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Dec  6 22:24:29 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_control_1_h_
#define RTW_HEADER_control_1_h_
#ifndef control_1_COMMON_INCLUDES_
#define control_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* control_1_COMMON_INCLUDES_ */

#include "control_1_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE;                 /* '<Root>/Delay' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  int16_T encoder_b;                   /* '<Root>/Data Store Memory1' */
  int16_T encoder_a;                   /* '<Root>/Data Store Memory2' */
} DW_control_1_T;

/* Real-time Model Data Structure */
struct tag_RTM_control_1_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_control_1_T control_1_DW;

/* Model entry point functions */
extern void control_1_initialize(void);
extern void control_1_step(void);
extern void control_1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_control_1_T *const control_1_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'control_1'
 */
#endif                                 /* RTW_HEADER_control_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
