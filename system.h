#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <sys/sysinfo.h>
#include <fstream>
#include <thread>
#include <chrono>

std::string bars[6] { "█░░░░░░░░░", 
                      "███░░░░░░░", 
                      "█████░░░░░", 
                      "███████░░░",
                      "█████████░",
                      "██████████"};

int sys_uptime()
{
    struct sysinfo si;
    int uptime = 0;

    if(sysinfo(&si) == 0)
    {
        uptime = si.uptime / 60;
    }

    return uptime;
}

long long cpu_stat()
{
    std::string cpu;
    long long user, nice, system, idle, iowait, irq, softirq, steal, total1, total2, idle1, idle2, delta_total, delta_idle;

    std::ifstream file("/proc/stat");
    file >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    
    total1 = user + nice + system + idle + iowait + irq + softirq + steal;

    idle1 = idle + iowait;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::ifstream file2("/proc/stat");
    
    file2 >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    
    total2 = user + nice + system + idle + iowait + irq + softirq + steal;
    
    idle2 = idle + iowait;        
    
    delta_total = total2 - total1;
    
    delta_idle = idle2 - idle1;

    long long usage = 100 * (delta_total - delta_idle) / delta_total;

    return usage;
}

std::string cpu_bar()
{
    long long stat = cpu_stat();

    if(stat <= 10)
        return bars[0];
    else if(stat > 11 && stat <= 30)
        return bars[1];
    else if(stat > 31 && stat <= 50)
        return bars[2];
    else if(stat > 51 && stat <= 70)
        return bars[3];
    else if(stat > 71 && stat <= 90)
        return bars[4];
    else if(stat > 91 && stat <= 100)
        return bars[5];

    return "";
}

int gpu_stat()
{
    std::ifstream file("/sys/class/drm/card1/device/gpu_busy_percent");
    std::string line;

    file >> line;

    int perc = std::stoi(line);

    return perc;
}

std::string gpu_bar()
{
    long long stat = gpu_stat();

    if(stat <= 10)
        return bars[0];
    else if(stat > 11 && stat <= 30)
        return bars[1];
    else if(stat > 31 && stat <= 50)
        return bars[2];
    else if(stat > 51 && stat <= 70)
        return bars[3];
    else if(stat > 71 && stat <= 90)
        return bars[4];
    else if(stat > 91 && stat <= 100)
        return bars[5];

    return "";
}


float used_ram()
{
    struct sysinfo si;

    if(sysinfo(&si) == 0)
    {
        return (float)(si.totalram - si.freeram)
               / 1024 / 1024 / 1024 / 2;
    }

    return 0;
}
float totalram()
{
    struct sysinfo si;
    if(sysinfo(&si) == 0)
    {
        return (float)si.totalram * si.mem_unit / 1024 / 1024 / 1024;
    }

    return 0;
}

int cpu_temp()
{
    std::ifstream file("/sys/class/hwmon/hwmon4/temp1_input");

    int temp;

    file >> temp;

    return temp;
}

#endif
