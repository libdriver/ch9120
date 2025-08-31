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
 * @file      driver_ch9120_register_test.c
 * @brief     driver ch9120 register test source file
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

#include "driver_ch9120_register_test.h"
#include <stdlib.h>

static ch9120_handle_t gs_handle;        /**< ch9120 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ch9120_register_test(void)
{
    uint8_t res;
    uint8_t version;
    uint8_t timeout;
    uint8_t timeout_check;
    uint8_t ip[4];
    uint8_t ip_check[4];
    uint8_t mask[4];
    uint8_t mask_check[4];
    uint16_t num;
    uint16_t num_check;
    uint32_t baud;
    uint32_t baud_check;
    uint32_t len;
    uint32_t len_check;
    uint8_t data_bit;
    uint8_t stop_bit;
    uint16_t ms;
    uint16_t ms_check;
    uint8_t reg;
    ch9120_bool_t enable;
    ch9120_parity_t parity;
    ch9120_info_t info;
    ch9120_status_t status;
    ch9120_mode_t mode;

    /* link interface function */
    DRIVER_CH9120_LINK_INIT(&gs_handle, ch9120_handle_t);
    DRIVER_CH9120_LINK_UART_INIT(&gs_handle, ch9120_interface_uart_init);
    DRIVER_CH9120_LINK_UART_DEINIT(&gs_handle, ch9120_interface_uart_deinit);
    DRIVER_CH9120_LINK_UART_READ(&gs_handle, ch9120_interface_uart_read);
    DRIVER_CH9120_LINK_UART_WRITE(&gs_handle, ch9120_interface_uart_write);
    DRIVER_CH9120_LINK_UART_FLUSH(&gs_handle, ch9120_interface_uart_flush);
    DRIVER_CH9120_LINK_RESET_GPIO_INIT(&gs_handle, ch9120_interface_reset_gpio_init);
    DRIVER_CH9120_LINK_RESET_GPIO_DEINIT(&gs_handle, ch9120_interface_reset_gpio_deinit);
    DRIVER_CH9120_LINK_RESET_GPIO_WRITE(&gs_handle, ch9120_interface_reset_gpio_write);
    DRIVER_CH9120_LINK_CFG_GPIO_INIT(&gs_handle, ch9120_interface_cfg_gpio_init);
    DRIVER_CH9120_LINK_CFG_GPIO_DEINIT(&gs_handle, ch9120_interface_cfg_gpio_deinit);
    DRIVER_CH9120_LINK_CFG_GPIO_WRITE(&gs_handle, ch9120_interface_cfg_gpio_write);
    DRIVER_CH9120_LINK_DELAY_MS(&gs_handle, ch9120_interface_delay_ms);
    DRIVER_CH9120_LINK_DEBUG_PRINT(&gs_handle, ch9120_interface_debug_print);

    /* get ch9120 information */
    res = ch9120_info(&info);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip information */
        ch9120_interface_debug_print("ch9120: chip is %s.\n", info.chip_name);
        ch9120_interface_debug_print("ch9120: manufacturer is %s.\n", info.manufacturer_name);
        ch9120_interface_debug_print("ch9120: interface is %s.\n", info.interface);
        ch9120_interface_debug_print("ch9120: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ch9120_interface_debug_print("ch9120: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ch9120_interface_debug_print("ch9120: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ch9120_interface_debug_print("ch9120: max current is %0.2fmA.\n", info.max_current_ma);
        ch9120_interface_debug_print("ch9120: max temperature is %0.1fC.\n", info.temperature_max);
        ch9120_interface_debug_print("ch9120: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start register test */
    ch9120_interface_debug_print("ch9120: start register test.\n");

    /* ch9120 init */
    res = ch9120_init(&gs_handle);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: init failed.\n");

        return 1;
    }

    /* ch9120_get_version test */
    ch9120_interface_debug_print("ch9120: ch9120_get_version test.\n");

    /* get version */
    res = ch9120_get_version(&gs_handle, &version);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get version failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: version is 0x%02X.\n", version);

    /* ch9120_save_to_eeprom test */
    ch9120_interface_debug_print("ch9120: ch9120_save_to_eeprom test.\n");

    /* save to eeprom */
    res = ch9120_save_to_eeprom(&gs_handle);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: save to eeprom failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check save to eeprom %s.\n", res == 0 ? "ok" : "error");

    /* ch9120_exit test */
    ch9120_interface_debug_print("ch9120: ch9120_exit test.\n");

    /* exit */
    res = ch9120_exit(&gs_handle);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: exit failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check exit %s.\n", res == 0 ? "ok" : "error");
    
    /* ch9120_set_disconnect_with_no_rj45/ch9120_get_disconnect_with_no_rj45 test */
    ch9120_interface_debug_print("ch9120: ch9120_set_disconnect_with_no_rj45/ch9120_get_disconnect_with_no_rj45 test.\n");

    /* disable */
    res = ch9120_set_disconnect_with_no_rj45(&gs_handle, CH9120_BOOL_FALSE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set disconnect with no rj45 failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: disable disconnect with no rj45.\n");
    res = ch9120_get_disconnect_with_no_rj45(&gs_handle, &enable);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get disconnect with no rj45 failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: check disconnect with no rj45 %s.\n", enable == CH9120_BOOL_FALSE ? "ok" : "error");

    /* enable */
    res = ch9120_set_disconnect_with_no_rj45(&gs_handle, CH9120_BOOL_TRUE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set disconnect with no rj45 failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: enable disconnect with no rj45.\n");
    res = ch9120_get_disconnect_with_no_rj45(&gs_handle, &enable);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get disconnect with no rj45 failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: check disconnect with no rj45 %s.\n", enable == CH9120_BOOL_TRUE ? "ok" : "error");

    /* ch9120_set_dhcp test */
    ch9120_interface_debug_print("ch9120: ch9120_set_dhcp test.\n");

    /* disable dhcp */
    res = ch9120_set_dhcp(&gs_handle, CH9120_BOOL_FALSE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set dhcp failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* disable dhcp */
    ch9120_interface_debug_print("ch9120: disable dhcp.\n");

    /* output */
    ch9120_interface_debug_print("ch9120: check dhcp %s.\n", res == 0 ? "ok" : "error");

    /* enable dhcp */
    res = ch9120_set_dhcp(&gs_handle, CH9120_BOOL_TRUE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set dhcp failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* enable dhcp */
    ch9120_interface_debug_print("ch9120: enable dhcp.\n");

    /* output */
    ch9120_interface_debug_print("ch9120: check dhcp %s.\n", res == 0 ? "ok" : "error");
    
    /* ch9120_set_ip/ch9120_get_ip test */
    ch9120_interface_debug_print("ch9120: ch9120_set_ip/ch9120_get_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set ip */
    res = ch9120_set_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set ip failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set ip %d.%d.%d.%d.\n",
                                 ip[0], ip[1], ip[2], ip[3]);

    /* get ip */
    res = ch9120_get_ip(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get ip failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9120_set_subnet_mask/ch9120_get_subnet_mask test */
    ch9120_interface_debug_print("ch9120: ch9120_set_subnet_mask/ch9120_get_subnet_mask test.\n");

    /* random mask */
    mask[0] = rand() % 0xFF;
    mask[1] = rand() % 0xFF;
    mask[2] = rand() % 0xFF;
    mask[3] = rand() % 0xFF;

    /* set subnet mask */
    res = ch9120_set_subnet_mask(&gs_handle, mask);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set subnet mask failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set subnet mask %d.%d.%d.%d.\n",
                                 mask[0], mask[1], mask[2], mask[3]);

    /* get subnet mask */
    res = ch9120_get_subnet_mask(&gs_handle, mask_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get subnet mask failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check subnet mask %s.\n", memcmp(mask, mask_check, 4) == 0 ? "ok" : "error");

    /* ch9120_set_gateway/ch9120_get_gateway test */
    ch9120_interface_debug_print("ch9120: ch9120_set_gateway/ch9120_get_gateway test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set gateway */
    res = ch9120_set_gateway(&gs_handle, ip);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set gateway failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set gateway %d.%d.%d.%d.\n",
                                 ip[0], ip[1], ip[2], ip[3]);

    /* get gateway */
    res = ch9120_get_gateway(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get gateway failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check gateway %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9120_get_status test */
    ch9120_interface_debug_print("ch9120: ch9120_get_status test.\n");

    /* status */
    res = ch9120_get_status(&gs_handle, &status);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get status failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: get status %s.\n", status == CH9120_STATUS_CONNECT ? "connect" : "disconnect");

    /* ch9120_set_mode/ch9120_get_mode test */
    ch9120_interface_debug_print("ch9120: ch9120_set_mode/ch9120_get_mode test.\n");

    /* tcp server */
    res = ch9120_set_mode(&gs_handle, CH9120_MODE_TCP_SERVER);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set tcp server mode.\n");

    res = ch9120_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check mode %s.\n", mode == CH9120_MODE_TCP_SERVER ? "ok" : "error");

    /* tcp client */
    res = ch9120_set_mode(&gs_handle, CH9120_MODE_TCP_CLIENT);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set tcp client mode.\n");

    res = ch9120_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check mode %s.\n", mode == CH9120_MODE_TCP_CLIENT ? "ok" : "error");

    /* udp server */
    res = ch9120_set_mode(&gs_handle, CH9120_MODE_UDP_SERVER);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set udp server mode.\n");

    res = ch9120_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check mode %s.\n", mode == CH9120_MODE_UDP_SERVER ? "ok" : "error");

    /* udp client */
    res = ch9120_set_mode(&gs_handle, CH9120_MODE_UDP_CLIENT);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set udp client mode.\n");

    res = ch9120_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get mode failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check mode %s.\n", mode == CH9120_MODE_UDP_CLIENT ? "ok" : "error");

    /* ch9120_set_source_port/ch9120_get_source_port test */
    ch9120_interface_debug_print("ch9120: ch9120_set_source_port/ch9120_get_source_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port */
    res = ch9120_set_source_port(&gs_handle, num);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set source port failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set source %d.\n", num);

    /* get source port */
    res = ch9120_get_source_port(&gs_handle, &num_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get source port failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9120_interface_debug_print("ch9120: check source port %s.\n", num_check == num ? "ok" : "error");
    
    /* ch9120_set_dest_ip/ch9120_get_dest_ip test */
    ch9120_interface_debug_print("ch9120: ch9120_set_dest_ip/ch9120_get_dest_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* port */
    res = ch9120_set_dest_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set dest ip failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set dest ip %d.%d.%d.%d.\n", ip[0], ip[1], ip[2], ip[3]);

    /* get dest ip */
    res = ch9120_get_dest_ip(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get dest ip failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check dest ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");
    
    /* ch9120_set_dest_port/ch9120_get_dest_port test */
    ch9120_interface_debug_print("ch9120: ch9120_set_dest_port/ch9120_get_dest_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port */
    res = ch9120_set_dest_port(&gs_handle, num);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set dest port failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set dest %d.\n", num);

    /* get dest port */
    res = ch9120_get_dest_port(&gs_handle, &num_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get dest port failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check dest port %s.\n", num_check == num ? "ok" : "error");

    /* ch9120_set_uart_baud/ch9120_get_uart_baud test */
    ch9120_interface_debug_print("ch9120: ch9120_set_uart_baud/ch9120_get_uart_baud test.\n");

    /* 9600 */
    baud = 9600;

    /* port */
    res = ch9120_set_uart_baud(&gs_handle, baud);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart baud failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set uart baud %d.\n", baud);

    /* get uart baud */
    res = ch9120_get_uart_baud(&gs_handle, &baud_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart baud failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check uart baud %s.\n", baud_check == baud ? "ok" : "error");

    /* ch9120_set_uart_config/ch9120_get_uart_config test */
    ch9120_interface_debug_print("ch9120: ch9120_set_uart_config/ch9120_get_uart_config test.\n");

    /* set uart config */
    res = ch9120_set_uart_config(&gs_handle, 8, CH9120_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart config failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set data_bit 8, parity none, stop_bit 1.\n");

    /* get uart config */
    res = ch9120_get_uart_config(&gs_handle, &data_bit, &parity, &stop_bit);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart config failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check uart data bit %s.\n", data_bit == 8 ? "ok" : "error");
    ch9120_interface_debug_print("ch9120: check uart parity %s.\n", parity == CH9120_PARITY_NONE ? "ok" : "error");
    ch9120_interface_debug_print("ch9120: check uart stop bit %s.\n", stop_bit == 1 ? "ok" : "error");

    /* ch9120_set_uart_timeout/ch9120_get_uart_timeout test */
    ch9120_interface_debug_print("ch9120: ch9120_set_uart_timeout/ch9120_get_uart_timeout test.\n");

    /* random timeout */
    timeout = rand() % 0xFF;

    /* set uart timeout */
    res = ch9120_set_uart_timeout(&gs_handle, timeout);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart timeout failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: set uart timeout %d.\n", timeout);

    /* get uart timeout */
    res = ch9120_get_uart_timeout(&gs_handle, &timeout_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart timeout failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check uart timeout %s.\n", timeout_check == timeout ? "ok" : "error");

    /* ch9120_set_source_port_random test */
    ch9120_interface_debug_print("ch9120: ch9120_set_source_port_random test.\n");

    /* enable */
    res = ch9120_set_source_port_random(&gs_handle, CH9120_BOOL_TRUE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set source port random failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: enable source port random.\n");

    /* output */
    ch9120_interface_debug_print("ch9120: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* disable */
    res = ch9120_set_source_port_random(&gs_handle, CH9120_BOOL_FALSE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set source port random failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: disable source port random.\n");

    /* output */
    ch9120_interface_debug_print("ch9120: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* ch9120_set_uart_buffer_length/ch9120_get_uart_buffer_length test */
    ch9120_interface_debug_print("ch9120: ch9120_set_uart_buffer_length/ch9120_get_uart_buffer_length test.\n");

    /* random len */
    len = 128 + rand() % 50;
    res = ch9120_set_uart_buffer_length(&gs_handle, len);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart buffer length failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: set uart buffer length %d.\n", len);
    res = ch9120_get_uart_buffer_length(&gs_handle, &len_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart buffer length failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9120_interface_debug_print("ch9120: check uart buffer length %s.\n", len == len_check ? "ok" : "error");
    
    /* ch9120_set_uart_flush test/ch9120_get_uart_flush */
    ch9120_interface_debug_print("ch9120: ch9120_set_uart_flush test/ch9120_get_uart_flush.\n");

    /* enable uart flush */
    res = ch9120_set_uart_flush(&gs_handle, CH9120_BOOL_TRUE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart flush failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: enable uart flush.\n");
    res = ch9120_get_uart_flush(&gs_handle, &enable);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart flush failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: check uart flush %s.\n", enable == CH9120_BOOL_TRUE ? "ok" : "error");

    /* disable uart flush */
    res = ch9120_set_uart_flush(&gs_handle, CH9120_BOOL_FALSE);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: set uart flush failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: disable uart flush.\n");
    res = ch9120_get_uart_flush(&gs_handle, &enable);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: get uart flush failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }
    ch9120_interface_debug_print("ch9120: check uart flush %s.\n", enable == CH9120_BOOL_FALSE ? "ok" : "error");
    
    /* ch9120_uart_timeout_convert_to_register/ch9120_uart_timeout_convert_to_data test */
    ch9120_interface_debug_print("ch9120: ch9120_uart_timeout_convert_to_register/ch9120_uart_timeout_convert_to_data test.\n");

    /* random ms */
    ms = (rand() % 10) * 5;

    /* uart timeout convert to register */
    res = ch9120_uart_timeout_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: uart timeout convert to register failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: uart timeout convert to register %d.\n", ms);

    /* uart timeout convert to data */
    res = ch9120_uart_timeout_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        ch9120_interface_debug_print("ch9120: uart timeout convert to data failed.\n");
        (void)ch9120_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9120_interface_debug_print("ch9120: check uart timeout convert %s.\n", ms == ms_check ? "ok" : "error");

    /* finish register test */
    ch9120_interface_debug_print("ch9120: finish register test.\n");
    (void)ch9120_deinit(&gs_handle);

    return 0;
}
