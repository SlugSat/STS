/* ========================================
 * FILE:   config.h
 * AUTHOR: Caleb Cotter
 *
 * CREATED ON MAY 17, 2020, 3:54 PM
 *
 * ========================================
 *
 * Copyright SLUGSAT, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF SLUGSAT.
 *
 * ========================================
*/

#define RECORD_DURATION_US  30000
#define ACC_CHANNEL_SAMPLE_PERIOD   0.000001

#define ENCODER_COUNTS_PER_REV 4096
#define LIFT_THRESHOLD_DEG 10
#define DROP_ANGLE_THRESHOLD_DEG 5
#define RECORD_ANGLE_THRESHOLD_DEG 2

#define ACC_SCALE_FACTOR    1.46484375
#define ACC_OFFSET          2048

/* Accelerometer Calibration Values */
static const float accScaleMatrix[3][3] =  {{ 0.0037, -0.0000, -0.0000},
                                            {-0.0001,  0.0039,  0.0000},
                                            {-0.0001,  0.0000,  0.0036}};
static const float accOffsetVector[3]   =   {-0.9859, -0.0477,  0.8850};


/* [] END OF FILE */
