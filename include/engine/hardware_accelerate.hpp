#ifndef HARDWARE_ACCELERATE_HPP
#define HARDWARE_ACCELERATE_HPP
extern "C"
{
    __declspec(dllexport) int NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#endif