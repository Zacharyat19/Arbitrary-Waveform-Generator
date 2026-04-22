#pragma once
#include <memory>
#include <cstdint>

class Vdac_spi;

class SpiDriver 
{
    public:
        SpiDriver();
        ~SpiDriver();

        void reset();
        void tickClock(uint64_t cycles = 1);
        
        // The core SPI bit-banging function
        void transmit12Bits(uint16_t data);
        
        // Read the physical output of the simulated DAC
        uint16_t readDacOutput() const;

    private:
        std::unique_ptr<Vdac_spi> m_core;
        uint64_t m_time; 
};