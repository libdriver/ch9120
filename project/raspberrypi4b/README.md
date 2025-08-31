### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: TX/RX GPIO14/GPIO15.

GPIO Pin: RESET/CFG GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./ch9120_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ch9120 REQUIRED)
```

### 3. CH9120

#### 3.1 Command Instruction

1. Show ch9120 chip and driver information.

   ```shell
   ch9120 (-i | --information)
   ```

2. Show ch9120 help.

   ```shell
   ch9120 (-h | --help)
   ```

3. Show ch9120 pin connections of the current board.

   ```shell
   ch9120 (-p | --port)
   ```

4. Run ch9120 register test.

   ```shell
   ch9120 (-t reg | --test=reg)
   ```

5. Run ch9120 net test.

   ```shell
   ch9120 (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
   ```

6. Run ch9120 net init function.

   ```shell
   ch9120 (-e net-init | --example=net-init)
   ```

7. Run ch9120 net deinit function.

   ```shell
   ch9120 (-e net-deinit | --example=net-deinit)
   ```

8. Run ch9120 config function, sip is the source ip, sport is the source port, mask is the subnet mask, gateway is the gateway, dip is the dest ip and dport is the dest port.

   ```shell
   ch9120 (-e net-cfg | --example=net-cfg) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>] [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
   ```

9. Run ch9120 net write function, str is the write data.

   ```shell
   ch9120 (-e net-write | --example=net-write) [--data=<str>]
   ```

10. Run ch9120 net read function.

    ```shell
    ch9120 (-e net-read | --example=net-read)
    ```

#### 3.2 Command Example

```shell
./ch9120 -i

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
```

```shell
./ch9120 -p

ch9120: TX connected to GPIO15(BCM).
ch9120: RX connected to GPIO14(BCM).
ch9120: RESET connected to GPIO27(BCM).
ch9120: CFG_EN connected to GPIO17(BCM).
```

```shell
./ch9120 -t reg

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
ch9120: start register test.
ch9120: ch9120_get_version test.
ch9120: version is 0x11.
ch9120: ch9120_save_to_eeprom test.
ch9120: check save to eeprom ok.
ch9120: ch9120_exit test.
ch9120: check exit ok.
ch9120: ch9120_set_disconnect_with_no_rj45/ch9120_get_disconnect_with_no_rj45 test.
ch9120: disable disconnect with no rj45.
ch9120: check disconnect with no rj45 ok.
ch9120: enable disconnect with no rj45.
ch9120: check disconnect with no rj45 ok.
ch9120: ch9120_set_dhcp test.
ch9120: disable dhcp.
ch9120: check dhcp ok.
ch9120: enable dhcp.
ch9120: check dhcp ok.
ch9120: ch9120_set_ip/ch9120_get_ip test.
ch9120: set ip 238.222.184.95.
ch9120: check ip ok.
ch9120: ch9120_set_subnet_mask/ch9120_get_subnet_mask test.
ch9120: set subnet mask 243.101.60.12.
ch9120: check subnet mask ok.
ch9120: ch9120_set_gateway/ch9120_get_gateway test.
ch9120: set gateway 132.184.213.22.
ch9120: check gateway ok.
ch9120: ch9120_get_status test.
ch9120: get status disconnect.
ch9120: ch9120_set_mode/ch9120_get_mode test.
ch9120: set tcp server mode.
ch9120: check mode ok.
ch9120: set tcp client mode.
ch9120: check mode ok.
ch9120: set udp server mode.
ch9120: check mode ok.
ch9120: set udp client mode.
ch9120: check mode ok.
ch9120: ch9120_set_source_port/ch9120_get_source_port test.
ch9120: set source 42594.
ch9120: check source port ok.
ch9120: ch9120_set_dest_ip/ch9120_get_dest_ip test.
ch9120: set dest ip 3.237.223.191.
ch9120: check dest ip ok.
ch9120: ch9120_set_dest_port/ch9120_get_dest_port test.
ch9120: set dest 57116.
ch9120: check dest port ok.
ch9120: ch9120_set_uart_baud/ch9120_get_uart_baud test.
ch9120: set uart baud 9600.
ch9120: check uart baud ok.
ch9120: ch9120_set_uart_config/ch9120_get_uart_config test.
ch9120: set data_bit 8, parity none, stop_bit 1.
ch9120: check uart data bit ok.
ch9120: check uart parity ok.
ch9120: check uart stop bit ok.
ch9120: ch9120_set_uart_timeout/ch9120_get_uart_timeout test.
ch9120: set uart timeout 144.
ch9120: check uart timeout ok.
ch9120: ch9120_set_source_port_random test.
ch9120: enable source port random.
ch9120: check source port random ok.
ch9120: disable source port random.
ch9120: check source port random ok.
ch9120: ch9120_set_uart_buffer_length/ch9120_get_uart_buffer_length test.
ch9120: set uart buffer length 161.
ch9120: check uart buffer length ok.
ch9120: ch9120_set_uart_flush test/ch9120_get_uart_flush.
ch9120: enable uart flush.
ch9120: check uart flush ok.
ch9120: disable uart flush.
ch9120: check uart flush ok.
ch9120: ch9120_uart_timeout_convert_to_register/ch9120_uart_timeout_convert_to_data test.
ch9120: uart timeout convert to register 0.
ch9120: check uart timeout convert ok.
ch9120: finish register test.
```

```shell
./ch9120 -t net --mode=TCP_CLIENT

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
ch9120: start net test.
ch9120: tcp client dest port 2000, dest ip 192.168.1.10.
ch9120: write LibDriver.
ch9120: finish net test.
```

```shell
./ch9120 -t net --mode=TCP_SERVER

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
ch9120: start net test.
ch9120: tcp server src port 1000, src ip 192.168.1.230.
ch9120: read LibDriver.
ch9120: finish net test.
```

```shell
./ch9120 -t net --mode=UDP_CLIENT

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
ch9120: start net test.
ch9120: udp client dest port 2000, dest ip 192.168.1.10.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: write LibDriver.
ch9120: finish net test.
```

```shell
./ch9120 -t net --mode=UDP_SERVER

ch9120: chip is WCH CH9120.
ch9120: manufacturer is WCH.
ch9120: interface is UART.
ch9120: driver version is 1.0.
ch9120: min supply voltage is 2.1V.
ch9120: max supply voltage is 3.6V.
ch9120: max current is 100.00mA.
ch9120: max temperature is 85.0C.
ch9120: min temperature is -40.0C.
ch9120: start net test.
ch9120: udp server src port 1000, src ip 192.168.1.230.
ch9120: read LibDriver.
ch9120: finish net test.
```

```shell
./ch9120 -e net-init

ch9120: net init.
```

```shell
./ch9120 -e net-deinit

ch9120: net deinit.
```

```shell
./ch9120 -e net-cfg --mode=TCP_CLIENT --sip=192.168.1.230 --sport=1000 --mask=255.255.255.0 --gateway=192.168.1.1 --dip=192.168.1.10 --dport=2000

ch9120: source ip 192.168.1.230.
ch9120: source port 1000.
ch9120: subnet mask 255.255.255.0.
ch9120: gateway 192.168.1.1.
ch9120: dest ip 192.168.1.10.
ch9120: dest port 2000.
```

```shell
./ch9120 -e net-write --data=LibDriver

ch9120: net write LibDriver.
```

```shell
./ch9120 -e net-read

ch9120: net read LibDriver.
```

```shell
./ch9120 -h

Usage:
  ch9120 (-i | --information)
  ch9120 (-h | --help)
  ch9120 (-p | --port)
  ch9120 (-t reg | --test=reg)
  ch9120 (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
  ch9120 (-e net-init | --example=net-init)
  ch9120 (-e net-deinit | --example=net-deinit)
  ch9120 (-e net-cfg | --example=net-cfg) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
         [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
  ch9120 (-e net-write | --example=net-write) [--data=<str>]
  ch9120 (-e net-read | --example=net-read)

Options:
  -e <net-init | net-deinit | net-cfg | net-write | net-read>, --example=<net-init | net-deinit | net-cfg | net-write | net-read>
                             Run the driver example.
      --data=<str>           Set write data.([default: LibDriver])
      --dip=<dip>            Set the dest ip.([default: 192.168.1.10])
      --dport=<dport>        Set dest port.([default: 1000])
      --gateway=<gateway>    Set the gateway.([default: 192.168.1.1])
  -h, --help                 Show the help.
  -i, --information          Show the chip information.
      --mask=<mask>          Set the subnet mask.([default: 255.255.255.0])
      --mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER
                             Set the chip mode.([default: TCP_CLIENT])
  -p, --port                 Display the pin connections of the current board.
      --sip=<sip>            Set the source ip.([default: 192.168.1.230])
      --sport=<sport>        Set source port.([default: 2000])
  -t <reg | net>, --test=<reg | net>
                             Run the driver test.
```

