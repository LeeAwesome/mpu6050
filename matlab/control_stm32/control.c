/*
 * File: control.c
 *
 * Code generated for Simulink model :control.
 *
 * Model version      : 1.2
 * Simulink Coder version    : 9.6 (R2021b) 14-May-2021
 * TLC version       : 9.6 (Aug 25 2021)
 * C/C++ source code generated on  : Tue Dec  5 21:54:53 2023
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#include "control.h"
#include "control_private.h"
//restructure matlab code, use value directly, instead of input value
/* Block states (default storage) */
DW_control control_DW;

/* External inputs (root inport signals with default storage) */
ExtU_control control_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_control control_Y;

/* Real-time model */
static RT_MODEL_control control_M_;
RT_MODEL_control *const control_M = &control_M_;

/* Model step function */
void control_step(void)
{
  real_T tmp;
  control_DW.Delay_DSTATE = (control_U.encoder_left + control_U.encoder_right) *
    0.2 + 0.8 * control_DW.Delay_DSTATE;
  control_DW.UnitDelay_DSTATE = (control_DW.Delay_DSTATE +
    control_DW.UnitDelay_DSTATE) - control_U.movement;
  if (control_DW.UnitDelay_DSTATE > 10000.0) {
    tmp = 10000.0;
  } else if (control_DW.UnitDelay_DSTATE < -10000.0) {
    tmp = -10000.0;
  } else {
    tmp = control_DW.UnitDelay_DSTATE;
  }

  control_Y.vertical_velocity = ((control_U.angle - 1.0) + control_U.gyro) +
    (control_DW.Delay_DSTATE + tmp);
}

/* Model initialize function */
void control_initialize(void)
{
  /* (no initialization code required) */
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] control.c
 */
