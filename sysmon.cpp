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
              << totalram() << " GB\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "CPU Temp"
              << cpu_temp() / 1000 << "°C\n";

    std::cout << "│ " << std::left << std::setw(10)
              << "Uptime"
              << sys_uptime_hours() << "h " << sys_uptime_minute() << " min" << "\n";

    std::cout << "╰────────────────────────────────────────╯\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "\033[2J\033[H";
}

    return 0;
}
