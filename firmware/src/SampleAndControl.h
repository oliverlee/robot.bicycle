#ifndef SAMPLEANDCONTROL_H
#define SAMPLEANDCONTROL_H

#include <array>
#include <cstddef>

#include "ch.h"
#include "hal.h"
#include "ff.h"

#include "sample.pb.h"
#include "Singleton.h"
#include "MPU6050.h"
#include "RearWheel.h"
#include "YawRateController.h"
#include "SystemState.h"

class SampleAndControl : public Singleton<SampleAndControl> {
  friend class Singleton<SampleAndControl>;
 public:
  msg_t Start(const char * filename);
  msg_t Stop();

  const char * fileName() const;
  void sampleMotorState(Sample & s) const;
  uint32_t systemState() const;
  static void enableSensorsMotors();
  static void disableSensorsMotors();

  static void controlThread_(void* arg);
  static void shellcmd_(BaseSequentialStream *chp, int argc, char *argv[]);

 private:
  SampleAndControl();
  SampleAndControl(const SampleAndControl &) = delete;
  SampleAndControl & operator=(const SampleAndControl &) = delete;

  void shellcmd(BaseSequentialStream *chp, int argc, char *argv[]);
  void controlThread();
  static void writeThread_(char* filename);
  void writeThread(char* filename);

  // Data collection related
  static void sampleTimers(Sample & s);
  void sampleSetPoints(Sample & s);

  // Data writing related
  static size_t getMessageSize(const Sample & s);

  WORKING_AREA(waControlThread, 4096);
  WORKING_AREA(waWriteThread, 4096);
  
  static const uint16_t write_size_ = 512;
  static const uint16_t buffer_size_ = write_size_ + sizeof(Sample);
  std::array<uint8_t, buffer_size_> buffer0_;
  std::array<uint8_t, buffer_size_> buffer1_;

  FIL f_;
  Thread * tp_control;
  Thread * tp_write;
  uint32_t state_;
};

#include "SampleAndControl_priv.h"
#endif // SAMPLEANDCONTROL_H
