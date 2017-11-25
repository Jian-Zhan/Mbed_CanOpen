openocd \
    -f /opt/local/share/openocd/scripts/interface/stlink-v2.cfg \
    -f /opt/local/share/openocd/scripts/target/stm32f1x.cfg \
    -c init \
    -c adapter_khz 100 \
    -c targets \
    -c "reset_config none separate" \
    -c "reset" \
    -c "sleep 100" \
    -c "halt" \
    -c "sleep 100" \
    -c "flash write_image erase BUILD/TAOBAO_F103RB/GCC_ARM/Mbed_CanOpen.elf" \
    -c "verify_image BUILD/TAOBAO_F103RB/GCC_ARM/Mbed_CanOpen.elf" \
    -c "reset run" -c shutdown

