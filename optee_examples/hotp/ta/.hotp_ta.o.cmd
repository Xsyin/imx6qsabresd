old-cmd-./hotp_ta.o := /home/yin/imx-optee/aarch32/bin/arm-linux-gnueabihf-gcc -std=gnu99 -fdiagnostics-show-option -Wall -Wcast-align -Werror-implicit-function-declaration -Wextra -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wshadow -Wstrict-prototypes -Wswitch-default -Wwrite-strings -Wno-missing-field-initializers -Wno-format-zero-length -Waggregate-return -Wredundant-decls -Wold-style-definition -Wstrict-aliasing=2 -Wundef -pedantic -Wdeclaration-after-statement -mcpu=cortex-a9 -Os -g3 -fpie -mthumb -mthumb-interwork -fno-short-enums -fno-common -mno-unaligned-access -mfloat-abi=hard -funsafe-math-optimizations -funwind-tables -MD -MF ./.hotp_ta.o.d -MT hotp_ta.o -nostdinc -isystem /home/yin/imx-optee/aarch32/bin/../lib/gcc/arm-linux-gnueabihf/6.5.0/include -DCFG_TEE_TA_LOG_LEVEL=3 -I./include -I./. -DARM32=1 -D__ILP32__=1 -DMBEDTLS_SELF_TEST -DTRACE_LEVEL=3 -I. -I/home/yin/imx-optee/imx-optee-os/out/arm-plat-imx/export-ta_arm32/include -DCFG_TA_DYNLINK=1 -DCFG_TEE_TA_LOG_LEVEL='3' -DCFG_SYSTEM_PTA=1 -DCFG_ARM32_ta_arm32=1 -DCFG_TA_MBEDTLS=1 -DCFG_TA_MBEDTLS_SELF_TEST=1 -DCFG_TA_FLOAT_SUPPORT=1 -c hotp_ta.c -o hotp_ta.o