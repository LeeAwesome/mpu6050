/*
 * File: control_1.c
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

#include "control_1.h"
#include "control_1_private.h"

/* Block states (default storage) */
DW_control_1_T control_1_DW;

/* Real-time model */
static RT_MODEL_control_1_T control_1_M_;
RT_MODEL_control_1_T *const control_1_M = &control_1_M_;

/* Model step function */
void control_1_step(void)
{
  /* Sum: '<Root>/Add1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  DataStoreRead: '<Root>/Data Store Read2'
   *  DataStoreRead: '<Root>/Data Store Read3'
   *  Delay: '<Root>/Delay'
   *  Product: '<Root>/Divide'
   *  Product: '<Root>/Divide1'
   *  Sum: '<Root>/Add'
   */
  control_1_DW.Delay_DSTATE = (real_T)(int16_T)(control_1_DW.encoder_a +
    control_1_DW.encoder_b) * 0.2 + 0.8 * control_1_DW.Delay_DSTATE;

  /* Sum: '<Root>/Add4' incorporates:
   *  Constant: '<Root>/target_speed'
   *  DataStoreWrite: '<Root>/Data Store Write1'
   *  Delay: '<Root>/Delay'
   *  Sum: '<Root>/Add3'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  control_1_DW.UnitDelay_DSTATE = (control_1_DW.Delay_DSTATE +
    control_1_DW.UnitDelay_DSTATE) - 1.0;
}

/* Model initialize function */
void control_1_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void control_1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
