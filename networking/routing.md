<!--
Unix Notes © 2021 by Noah Altunian is licensed under Attribution 4.0 International. To view a copy
of this license, visit http://creativecommons.org/licenses/by/4.0/
-->
# Routing

### General

Every time a device connects to a network, routing is involved. In short, routing is the mechanism
of sending an IP packet from point A to point B to point C, until it reaches its final destination.
On Unix machines, details on how packets are forwarded are stored in a kernel structure called the
routing table. When updating your system's configuration you must update the routing table.

The routing table is used for configuring both static and dynamic routing. To view the routing tables
without performing a DNS lookup, run the following:

```sh
# Use netstat -rn for shorthand. -r is for displaying the routing table, and -n keeps the IP addresses
# unresolved (tl;dr don't translate IP addresses to hostnames).
# I also chose to use awk + tabulate for pretty-printing the contents in an ASCII table.
[vagrant@arch ~]$ netstat --route --numeric | awk 'NR > 1' | tabulate
-----------  --------  ---------------  -----  ---  ------  ----  -----
Destination  Gateway   Genmask          Flags  MSS  Window  irtt  Iface
0.0.0.0      10.0.2.2  0.0.0.0          UG     0    0       0     eth0
10.0.2.0     0.0.0.0   255.255.255.0    U      0    0       0     eth0
10.0.2.2     0.0.0.0   255.255.255.255  UH     0    0       0     eth0
10.0.2.3     0.0.0.0   255.255.255.255  UH     0    0       0     eth0
-----------  --------  ---------------  -----  ---  ------  ----  -----
```

Let's break this down.

### Understanding routing tables

There is a lot of useful information here:

* Destination: the destination network or host
* Gateway: the gateway address ('*' represents no address being set)
* Genmask: the netmask for the destination network
    * 255.255.255.255 is for a host destination
    * 0.0.0.0 is for a default route
* Flags: details for each route
    * U - the route is up
    * H - the target is a host, and is the only possible destination
    * G - use the gateway
    * R - reinstate the route for dynamic hosting
    * M - modified from the routing daemon or redirect
    * A - installed by addrconf
    * C - cache entry
    * ! - reject route
* MSS: the default maximum segment size for TCP connections
* Window: the default window size for TCP connections
* irtt: the initial round trip time, used by the kernel to optimize the TCP parameters
* Iface: the interface which will handle the packets

The routing table for your system is based on your TCP/IP configuration and is automatically set.
You can modify this configuration using the ip and route tools.

### Modifying your routing tables

You can use these commands to add / delete routes:

```sh
# Add a route with route
route add -net 10.0.2.0/24 gw 10.0.2.2
# Delete a route with route
route del -net 10.0.2.0/24
```
