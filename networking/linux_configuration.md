<!--
Unix Notes © 2021 by Noah Altunian is licensed under Attribution 4.0 International. To view a copy
of this license, visit http://creativecommons.org/licenses/by/4.0/
-->
# Linux Network Configuration

### Section 1: Network Interfaces

#### General

A network interface is the mechanism for mapping the software side of networking to the hardware devices
that enable networking. You can review your existing network interfaces by running the following:

```sh
# -a to show all available interfaces, even if they are down
[vagrant@arch ~]$ ifconfig -a
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.2.15  netmask 255.255.255.0  broadcast 10.0.2.255
        inet6 fe80::f5cd:acf7:ffaf:1844  prefixlen 64  scopeid 0x20<link>
        ether 08:00:27:62:38:6a  txqueuelen 1000  (Ethernet)
        RX packets 426066  bytes 569822031 (543.4 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 54479  bytes 4344949 (4.1 MiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

eth1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 2607:fb90:5e32:d4e1:d1fb:3e03:0:4b4  prefixlen 128  scopeid 0x0<global>
        inet6 fe80::9523:a442:c176:89f8  prefixlen 64  scopeid 0x20<link>
        inet6 2607:fb90:5e32:d4e1:2e29:50aa:cd1a:565a  prefixlen 64  scopeid 0x0<global>
        ether 08:00:27:4c:4e:df  txqueuelen 1000  (Ethernet)
        RX packets 17310  bytes 3765945 (3.5 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 8126  bytes 2174509 (2.0 MiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

#### ifconfig

`ifconfig(8)` is a tool for configuring network interfaces. This is important because your kernel
device drivers and network won't know how to talk with each other unless these interfaces exist.
`ifconfig` runs when your computer boots and uses configuration files, although you can manually
update your network interfaces using the command. By running `ifconfig` without arguments, you will
see the interface names, followed by detailed information:

```
Interface name
       |
       |             Detailed information
       |                      |
       |                      |
       |   ___________________|___________________
       |   |                                     |
       v   v                                     v
      lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
              inet 127.0.0.1  netmask 255.0.0.0
              inet6 ::1  prefixlen 128  scopeid 0x10<host>
              loop  txqueuelen 1000  (Local Loopback)
              RX packets 0  bytes 0 (0.0 B)
              RX errors 0  dropped 0  overruns 0  frame 0
              TX packets 0  bytes 0 (0.0 B)
              TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

Although you can name your network interfaces, common default names include:
* eth0, ethernet
* wlan0, wireless
* lo, loopback

The number (e.g. eth0) denotes the order in a series of related interfaces. If we look at the first
figure:

```sh
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
          ...
eth1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
```

We can see that my virtual machine has two ethernet network interfaces. Also, the loopback interface
represents your device on the network, and only you can make use of it.

#### Interface states

Network interfaces may be **up** or **down**. This reflects whether you or your device can make use
of them. Interfaces that are **up** may be used, and interfaces that are **down** may not.

If we look at a previous example:

```
                State
                  |
                  |
                  |
                  v
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
```

We can see that interface eth0 is set to up and can be used. To alter the state of an interface,
(e.g. eth0), simply run the following:

```sh
# Up
ifconfig eth0 up
# Down
ifconfig eth0 down
```

#### ip

Although `ifconfig` is standard on all Linux boxes, a newer command `ip(8)` has been added since Linux
kernel version 2.2. Likewise, it allows us to alter our network interfaces. Here are some examples:

```sh
# Show details for all interfaces, even if they are down
ip link show
# Show IP address for each interface
ip address show
# Bring interface up (using eth1 as an example)
ip link set eth1 up
# Bring interface down (using eth1 as an example)
ip link set eth1 down
# Add an interface (using eth1 as an example)
ip address add 10.0.2.15/24 dev eth1
```
