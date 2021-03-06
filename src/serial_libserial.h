//
// Created by andreas on 21.03.19.
//

#ifndef DRIVER_STIM300_SERIAL_LIBSERIAL_H
#define DRIVER_STIM300_SERIAL_LIBSERIAL_H

#include <SerialPort.h>
#include <string>
#include "serial_driver.h"

class SerialLibSerial : public SerialDriver
{
public:
  explicit SerialLibSerial(const std::string& serial_port_name);

  ~SerialLibSerial() override;

  void open(BAUDRATE baudrate) override;

  void close() override;

  bool readByte(uint8_t& byte, unsigned int ms_timeout) override;

  void readChunk(std::vector<unsigned char>& data_buffer, unsigned int num_of_bytes, unsigned int ms_timeout);

  void write(const std::vector<unsigned char>& data_buffer);

  bool isDataAvailable();

private:
  SerialPort serial_port_;
};

#endif  // DRIVER_STIM300_SERIAL_LIBSERIAL_H
