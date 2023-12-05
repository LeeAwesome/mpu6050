/*
 * File: control.h
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

#ifndef RTW_HEADER_control_h_
#define RTW_HEADER_control_h_
#ifndef control_COMMON_INCLUDES_
#define control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* control_COMMON_INCLUDES_ */

#include "control_types.h"

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
} DW_control;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T encoder_left;                 /* '<Root>/encoder_left' */
  real_T encoder_right;                /* '<Root>/encoder_right' */
  real_T movement;                     /* '<Root>/movement' */
  real_T angle;                        /* '<Root>/angle' */
  real_T gyro;                         /* '<Root>/gyro' */
} ExtU_control;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T vertical_velocity;            /* '<Root>/vertical_velocity' */
} ExtY_control;

/* Real-time Model Data Structure */
struct tag_RTM_control {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_control control_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_control control_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_control control_Y;

/* Model entry point functions */
extern void control_initialize(void);
extern void control_step(void);

/* Real-time Model object */
extern RT_MODEL_control *const control_M;

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
 * '<Root>' : 'control'
 */
#endif                                 /* RTW_HEADER_control_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] control.h
 */
