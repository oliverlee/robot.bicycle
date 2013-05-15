#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

template <class T>
class constants {
 public:
  // Standard engineering constants
  static constexpr T pi = 4.0*std::atan(1.0);
  static constexpr T pi_2 = 2.0*std::atan(1.0);
  static constexpr T pi_4 = std::atan(1.0);
  static constexpr T two_pi = 2.0*pi;
  static constexpr T rad_per_degree = pi / 180.0;
  static constexpr T degree_per_rad = 180 / pi;
  static constexpr T e = std::exp(1.0);
  static constexpr T g = 9.81;

  // Gyroscope constants
  static constexpr T Thermometer_offset = 36.53;
  static constexpr T Thermometer_sensitivity = 1.0 / 340.0;
  static constexpr T Gyroscope_sensitivity = rad_per_degree / 131.0;

  // Accelerometer constants
  static constexpr T Accelerometer_sensitivity = g / 16384.0;

  // Steer angle
  static constexpr int Steer_CPR = 5000;
  static constexpr int Steer_halfquad_CPR = 2 * Steer_CPR;
  static constexpr int Steer_quad_CPR = 4 * Steer_CPR;
  static constexpr T Steer_rad_per_count = two_pi / Steer_CPR;
  static constexpr T Steer_rad_per_halfquad_count = two_pi / Steer_halfquad_CPR;
  static constexpr T Steer_rad_per_quad_count = two_pi / Steer_quad_CPR;

  // Wheel rates and steer rate
  static constexpr int Wheel_CPR = 200;
  static constexpr int  Wheel_halfquad_CPR = 2 * Wheel_CPR;
  static constexpr int  Wheel_quad_CPR = 4 * Wheel_CPR;
  static constexpr T Wheel_rad_per_count = two_pi / Wheel_CPR;
  static constexpr T Wheel_rad_per_halfquad_count = two_pi / Wheel_halfquad_CPR;
  static constexpr T Wheel_rad_per_quad_count = two_pi / Wheel_quad_CPR;

  static constexpr T Rate_Timer_Frequency = 4.0e6;
  static constexpr T Rate_Timer_sec_per_count = 1.0 / Rate_Timer_Frequency;

  // Current command constants
  static constexpr T Current_max_rw = 12.0;     //  Copley ADP-090-36
  static constexpr T Current_max_steer = 6.0;   //  Copley ACJ-055-18

  // Physical bicycle parameters
  static constexpr T rr = 0.3359;
  static constexpr T rf = 0.3359;
  static constexpr T Jr = 0.1138;
  static constexpr T Jf = 0.0923;
  static constexpr T mT = 37.0;
  static constexpr T J = rr*rr*mT + Jr + (rr*rr/rf/rf)*Jf;
  static constexpr T c_rw = 0.01;
  static constexpr T kT_rw = 6.654987675770698;
  static constexpr T Nm_per_ozfin = 0.00706155182175;
  static constexpr T kT_steer = 106.459 * Nm_per_ozfin;
  static constexpr T kT_steer_inv = 1.0 / kT_steer;
};

class reg {
 public:
  static constexpr uint32_t PWM_ARR = 0xFFFE;
  static constexpr uint32_t ENC_ARR = 0xFFFF;
};

class con {
 public:
  static constexpr uint32_t T_ms = 5;   // main loop update rate in ms
  static constexpr uint32_t RW_N = 10;  // rear wheel control update prescalar
                                        // makes rear wheel control run slower
  static constexpr uint32_t YC_N = 1;   // yaw rate control update prescalar
                                        // makes yaw rate controller run slower
};

typedef constants<float> cf;
typedef constants<double> cd;

#endif
