#include <iostream>
#include <vector>
#include <zconf.h>
#include <bitset>
#include <chrono>
#include "driver_stim300.h"
#include "serial_unix.h"
#include "serial_libserial.h"

int main()
{
  // SerialLibSerial serial_driver("/dev/ttyUSB0");
  // usleep(20000);
  // std::vector<unsigned char> buffer;

  // unsigned int buffer_size{876};
  // unsigned int ms_timout{50};

  /*
  serial_driver.open(SerialDriver::BAUDRATE::BAUD_921600);

  serial_driver.write({'?',' ','\r'});
  usleep(10000);
  serial_driver.write({'?',' ','\r'});
  //for(auto i = 0 ;i<15;i++)
  //{

  serial_driver.readChunk(buffer, buffer_size, ms_timout);

    for (auto i : buffer)
    {
      if (i == 0x0D)
        std::cout << std::endl;
      else
      {
        std::cout << i;
        if (i == 0x3E)
          std::cout << "Done";
      }
    }
  */

  std::string serial_port_name{ "/dev/ttyUSB0" };

  SerialUnix serial_driver(serial_port_name);
  usleep(4000);

  DriverStim300 driver_stim300(serial_driver);

  usleep(200);
  usleep(4000);
  uint8_t last_count;
  uint32_t sucsesses{ 0 };
  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 5000; ++i)
  {
    usleep(4000);
    if (!driver_stim300.processPacket())
    {
      // std::cout << "Could not process packet" << std::endl;
      continue;
    }

    if (!driver_stim300.isChecksumGood())
    {
      std::cout << "Checksum_error" << std::endl;
      continue;
    }
    sucsesses++;
    // std::cout <<"ok"<<std::endl;
    // std::cout << "Acc: " <<std::fixed<< driver_stim300.getAccX()
    // <<","<<driver_stim300.getAccY()<<","<<driver_stim300.getAccZ()<<std::endl; std::cout << "Gyro: " <<std::fixed<<
    // driver_stim300.getGyroX() <<","<<driver_stim300.getGyroY()<<","<<driver_stim300.getGyroZ()<<std::endl; std::cout
    // << "Good?: " <<std::fixed<< driver_stim300.isSensorStatusGood()<<std::endl; std::cout << "Temp: " <<std::fixed<<
    // driver_stim300.getAverageTemp() << std::endl; std::cout << "Latency: " << driver_stim300.getLatency_us() <<
    // std::endl; std::cout << "Counter diff: " << (uint)(driver_stim300.getInternalMeasurmentCounter() - last_count) <<
    // std::endl; last_count = driver_stim300.getInternalMeasurmentCounter(); if (driver_stim300.getGyroX()> 16)
    //  std::cout<<"*";
    // else
    //  std::cout<<" ";
    // if (driver_stim300.getGyroY()> 16)
    //  std::cout<<"*";
    // else
    //  std::cout<<" ";
    // if (driver_stim300.getGyroZ()> 16)
    //  std::cout<<"*"<<std::endl;
    // else
    //  std::cout<<" "<<std::endl;
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  std::cout << "Duration: " << duration << " ms" << std::endl;

  std::cout << "Scesese: " << sucsesses << std::endl;

  std::cout << "Sampling rate: " << sucsesses / (duration / 1000) << std::endl;

  return 0;
}