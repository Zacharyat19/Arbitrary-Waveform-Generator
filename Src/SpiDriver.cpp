#include <verilated.h>

#include "Vdac_spi.h"
#include "Inc/SpiDriver.h"

SpiDriver::SpiDriver() : m_core(std::make_unique<Vdac_spi>()), m_time(0) 
{
    // Initialize SPI pins to idle states
    m_core->cs_n = 1; 
    m_core->sclk = 0;
    m_core->mosi = 0;
    reset();
}

SpiDriver::~SpiDriver() 
{
    m_core->final();
}

void SpiDriver::reset() 
{
    m_core->rst = 1;
    tickClock(5);
    m_core->rst = 0;
}

void SpiDriver::tickClock(uint64_t cycles) 
{
    for (uint64_t i = 0; i < cycles; ++i) 
    {
        m_core->clk = 0;
        m_core->eval();
        m_core->clk = 1;
        m_core->eval();
        m_time++;
    }
}

void SpiDriver::transmit12Bits(uint16_t data) 
{
    // Pull CS low to start transaction
    m_core->cs_n = 0;
    tickClock();

    // Shift out 12 bits, MSB first
    for (int i = 11; i >= 0; i--) 
    {
        m_core->mosi = (data >> i) & 0x01; 
        
        m_core->sclk = 1; // Rising edge (hardware samples here)
        tickClock();
        
        m_core->sclk = 0; // Falling edge
        tickClock();
    }

    // Pull CS high to end transaction and latch DAC
    m_core->cs_n = 1;
    tickClock(); 
}

uint16_t SpiDriver::readDacOutput() const 
{
    return m_core->dac_out;
}