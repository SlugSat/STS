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

#define ENCODER_COUNTS_PER_REV 1024
#define LIFT_THRESHOLD_DEG 10


/* Accelerometer Calibration Values */
static const float accScaleMatrix[3][3] =  {{ 0.0037, -0.0000, -0.0000},
                                            {-0.0001,  0.0039,  0.0000},
                                            {-0.0001,  0.0000,  0.0036}};
static const float accOffsetVector[3]   =   {-0.9859, -0.0477,  0.8850};


/* [] END OF FILE */
