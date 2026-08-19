#include <iostream>
#include "system.h"
#include <iomanip>
#include <thread>
#include <chrono>

int main()
{
while(true)
{    
    std::cout << "╭──────────── SYSTEM MONITOR ────────────╮\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "CPU" << " " << cpu_bar() << " "
              << cpu_stat() << "%" << "\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "GPU" << " " << gpu_bar() << " "
              << gpu_stat() << "%" << "\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "RAM"
              << used_ram() << " / "
              << totalram() << " GB"
    << std::right << std::setw(12) << "│" << "\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "CPU Temp"
              << cpu_temp() / 1000 << "°C"
    << std::right << std::setw(28) << "│" << "\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "Uptime"
              << sys_uptime() << " min"
    << std::right << std::setw(26) << "│" << "\n";

    std::cout << "╰────────────────────────────────────────╯\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "\033[2J\033[H";
}

    return 0;
}
