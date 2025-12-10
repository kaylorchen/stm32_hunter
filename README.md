---

[中文文档](readme_cn.md) | English

---

This tutorial is applicable to Ubuntu 22.04 (in principle, Ubuntu 24.04 should also work, but has not been tested). Windows can actually be used as well, but the configuration becomes quite troublesome and is not recommended.

---

# Software Installation
## [Install CLion IDE](https://www.jetbrains.com/clion/)
If you don't know how to install the software, please search for instructions yourself.

## [Install STM32CubeMx](https://www.st.com/en/development-tools/stm32cubemx.html)
If you don't know how to install it, please search for instructions yourself.

## Install Compiler, Dependencies and Common Tools
```bash
sudo apt update
sudo apt install -y gcc-arm-none-eabi libnewlib-dev libstdc++-arm-none-eabi-newlib libnewlib-arm-none-eabi 
sudo apt install -y cmake make gdb openocd
sudo apt install -y git picocom # optional
```

# Configuration
## Configure CLion
### Global Configuration  
**File->Settings**
![](Doc/img.png)

### Project Configuration
When opening the project, CLion will generate a configuration wizard, follow the prompts to configure.  
If you didn't use the configuration wizard, you can right-click the **CMakeLists_template.txt** file in the file window and select "Update CMake ..."

#### Build Configuration
![](Doc/img_1.png)  
![](Doc/img_2.png)  

#### Run Configuration
![](Doc/img_3.png)
![](Doc/img_4.png)
```
source [find interface/stlink.cfg]

transport select hla_swd

# increase working area to 64KB
set WORKAREASIZE 0x10000

source [find target/stm32f4x.cfg]

reset_config none
```
Note the content of the run configuration file. The `reset_config none` is because the SWD debug mode used does not connect the hardware reset pin, so it is set to none.
