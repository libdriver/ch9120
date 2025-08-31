/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-09-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/09/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ch9120_basic.h"
#include "driver_ch9120_register_test.h"
#include "driver_ch9120_net_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     ch9120 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ch9120(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"data", required_argument, NULL, 1},
        {"dip", required_argument, NULL, 2},
        {"dport", required_argument, NULL, 3},
        {"gateway", required_argument, NULL, 4},
        {"mask", required_argument, NULL, 5},
        {"mode", required_argument, NULL, 6},
        {"sip", required_argument, NULL, 7},
        {"sport", required_argument, NULL, 8},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    char data[49] = "LibDriver";
    uint8_t dest_ip[4] = {192, 168, 1, 10};
    uint16_t dest_port = 1000;
    uint8_t gateway[4] = {192, 168, 1, 1};
    uint8_t mask[4] = {255, 255, 255, 0};
    ch9120_mode_t mode = CH9120_MODE_TCP_CLIENT;
    uint8_t source_ip[4] = {192, 168, 1, 230};
    uint16_t source_port = 2000;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* data */
            case 1 :
            {
                /* copy data */
                memset(data, 0, sizeof(char) * 48);
                strncpy(data, optarg, 48);
                
                break;
            }
            
            /* dip */
            case 2 :
            {
                int buf[4];
                
                /* get the ip */
                (void)sscanf(optarg, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3]);
                dest_ip[0] = (uint8_t)buf[0];
                dest_ip[1] = (uint8_t)buf[1];
                dest_ip[2] = (uint8_t)buf[2];
                dest_ip[3] = (uint8_t)buf[3];
                
                break;
            }
            
            /* dport */
            case 3 :
            {
                /* set dest port */
                dest_port = atoi(optarg);
                
                break;
            }
            
            /* gateway */
            case 4 :
            {
                int buf[4];
                
                /* get the gateway */
                (void)sscanf(optarg, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3]);
                gateway[0] = (uint8_t)buf[0];
                gateway[1] = (uint8_t)buf[1];
                gateway[2] = (uint8_t)buf[2];
                gateway[3] = (uint8_t)buf[3];
                
                break;
            }
             
            /* mask */
            case 5 :
            {
                int buf[4];
                
                /* get the mask */
                (void)sscanf(optarg, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3]);
                mask[0] = (uint8_t)buf[0];
                mask[1] = (uint8_t)buf[1];
                mask[2] = (uint8_t)buf[2];
                mask[3] = (uint8_t)buf[3];
                
                
                break;
            } 
            
            /* mode */
            case 6 :
            {
                /* get the mode */
                if (strcmp("TCP_CLIENT", optarg) == 0)
                {
                    mode = CH9120_MODE_TCP_CLIENT;
                }
                else if (strcmp("TCP_SERVER", optarg) == 0)
                {
                    mode = CH9120_MODE_TCP_SERVER;
                }
                else if (strcmp("UDP_CLIENT", optarg) == 0)
                {
                    mode = CH9120_MODE_UDP_CLIENT;
                }
                else if (strcmp("UDP_SERVER", optarg) == 0)
                {
                    mode = CH9120_MODE_UDP_SERVER;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* sip */
            case 7 :
            {
                int buf[4];
                
                /* get the source ip */
                (void)sscanf(optarg, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3]);
                source_ip[0] = (uint8_t)buf[0];
                source_ip[1] = (uint8_t)buf[1];
                source_ip[2] = (uint8_t)buf[2];
                source_ip[3] = (uint8_t)buf[3];
                
                break;
            } 
            
            /* sport */
            case 8 :
            {
                /* set source port */
                source_port = atoi(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (ch9120_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_net", type) == 0)
    {
        /* run net test */
        if (ch9120_net_test(mode, 10000) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_net-init", type) == 0)
    {
        /* net init */
        if (ch9120_basic_init() != 0)
        {
            return 1;
        }
        
        /* output */
        ch9120_interface_debug_print("ch9120: net init.\n");
        
        return 0;
    }
    else if (strcmp("e_net-deinit", type) == 0)
    {
        /* net deinit */
        if (ch9120_basic_deinit() != 0)
        {
            return 1;
        }
        
        /* output */
        ch9120_interface_debug_print("ch9120: net deinit.\n");
        
        return 0;
    }
    else if (strcmp("e_net-cfg", type) == 0)
    {
        /* net cfg */
        if (ch9120_basic_config(mode,
                                source_ip, source_port, 
                                mask, gateway,
                                dest_ip, dest_port) != 0)
        {
            return 1;
        }
        
        /* output */
        ch9120_interface_debug_print("ch9120: source ip %d.%d.%d.%d.\n", source_ip[0], source_ip[1], source_ip[2], source_ip[3]);
        ch9120_interface_debug_print("ch9120: source port %d.\n", source_port);
        ch9120_interface_debug_print("ch9120: subnet mask %d.%d.%d.%d.\n", mask[0], mask[1], mask[2], mask[3]);
        ch9120_interface_debug_print("ch9120: gateway %d.%d.%d.%d.\n", gateway[0], gateway[1], gateway[2], gateway[3]);
        ch9120_interface_debug_print("ch9120: dest ip %d.%d.%d.%d.\n", dest_ip[0], dest_ip[1], dest_ip[2], dest_ip[3]);
        ch9120_interface_debug_print("ch9120: dest port %d.\n", dest_port);
        
        return 0;
    }
    else if (strcmp("e_net-write", type) == 0)
    {
        /* net write */
        if (ch9120_basic_write((uint8_t *)data, strlen((char*)data)) != 0)
        {
            return 1;
        }
        
        /* output */
        ch9120_interface_debug_print("ch9120: net write %s.\n", data);
        
        return 0;
    }
    else if (strcmp("e_net-read", type) == 0)
    {
        uint16_t l;
        
        /* 48 byte */
        l = 48;
        memset(data, 0, sizeof(char) * 48);
        
        /* net read */
        if (ch9120_basic_read((uint8_t *)data, &l) != 0)
        {
            return 1;
        }
        
        /* output */
        ch9120_interface_debug_print("ch9120: net read %s.\n", data);
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ch9120_interface_debug_print("Usage:\n");
        ch9120_interface_debug_print("  ch9120 (-i | --information)\n");
        ch9120_interface_debug_print("  ch9120 (-h | --help)\n");
        ch9120_interface_debug_print("  ch9120 (-p | --port)\n");
        ch9120_interface_debug_print("  ch9120 (-t reg | --test=reg)\n");
        ch9120_interface_debug_print("  ch9120 (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]\n");
        ch9120_interface_debug_print("  ch9120 (-e net-init | --example=net-init)\n");
        ch9120_interface_debug_print("  ch9120 (-e net-deinit | --example=net-deinit)\n");
        ch9120_interface_debug_print("  ch9120 (-e net-cfg | --example=net-cfg) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]\n");
        ch9120_interface_debug_print("         [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]\n");
        ch9120_interface_debug_print("  ch9120 (-e net-write | --example=net-write) [--data=<str>]\n");
        ch9120_interface_debug_print("  ch9120 (-e net-read | --example=net-read)\n");
        ch9120_interface_debug_print("\n");
        ch9120_interface_debug_print("Options:\n");
        ch9120_interface_debug_print("  -e <net-init | net-deinit | net-cfg | net-write | net-read>, --example=<net-init | net-deinit | net-cfg | net-write | net-read>\n");
        ch9120_interface_debug_print("                             Run the driver example.\n");
        ch9120_interface_debug_print("      --data=<str>           Set write data.([default: LibDriver])\n");
        ch9120_interface_debug_print("      --dip=<dip>            Set the dest ip.([default: 192.168.1.10])\n");
        ch9120_interface_debug_print("      --dport=<dport>        Set dest port.([default: 1000])\n");
        ch9120_interface_debug_print("      --gateway=<gateway>    Set the gateway.([default: 192.168.1.1])\n");
        ch9120_interface_debug_print("  -h, --help                 Show the help.\n");
        ch9120_interface_debug_print("  -i, --information          Show the chip information.\n");
        ch9120_interface_debug_print("      --mask=<mask>          Set the subnet mask.([default: 255.255.255.0])\n");
        ch9120_interface_debug_print("      --mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER\n");
        ch9120_interface_debug_print("                             Set the chip mode.([default: TCP_CLIENT])\n");
        ch9120_interface_debug_print("  -p, --port                 Display the pin connections of the current board.\n");
        ch9120_interface_debug_print("      --sip=<sip>            Set the source ip.([default: 192.168.1.230])\n");
        ch9120_interface_debug_print("      --sport=<sport>        Set source port.([default: 2000])\n");
        ch9120_interface_debug_print("  -t <reg | net>, --test=<reg | net>\n");
        ch9120_interface_debug_print("                             Run the driver test.\n");
          
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ch9120_info_t info;
        
        /* print ch9120 info */
        ch9120_info(&info);
        ch9120_interface_debug_print("ch9120: chip is %s.\n", info.chip_name);
        ch9120_interface_debug_print("ch9120: manufacturer is %s.\n", info.manufacturer_name);
        ch9120_interface_debug_print("ch9120: interface is %s.\n", info.interface);
        ch9120_interface_debug_print("ch9120: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ch9120_interface_debug_print("ch9120: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ch9120_interface_debug_print("ch9120: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ch9120_interface_debug_print("ch9120: max current is %0.2fmA.\n", info.max_current_ma);
        ch9120_interface_debug_print("ch9120: max temperature is %0.1fC.\n", info.temperature_max);
        ch9120_interface_debug_print("ch9120: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ch9120_interface_debug_print("ch9120: TX connected to GPIOA PIN3.\n");
        ch9120_interface_debug_print("ch9120: RX connected to GPIOA PIN2.\n");
        ch9120_interface_debug_print("ch9120: RESET connected to GPIOA PIN0.\n");
        ch9120_interface_debug_print("ch9120: CFG_EN connected to GPIOA PIN8.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register ch9120 function */
    shell_init();
    shell_register("ch9120", ch9120);
    uart_print("ch9120: welcome to libdriver ch9120.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ch9120: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ch9120: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ch9120: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ch9120: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ch9120: param is invalid.\n");
            }
            else
            {
                uart_print("ch9120: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
