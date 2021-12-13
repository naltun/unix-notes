<!--
Unix Notes © 2021 by Noah Altunian is licensed under Attribution 4.0 International. To view a copy
of this license, visit http://creativecommons.org/licenses/by/4.0/
-->
# DHCP (Dynamic Host Configuration Protocol)

### General

DHCP is a protocol which maintains assigning IP addresses, subnet masks and gateways to our devices.
DHCP is immensely useful because it dynamically handles assigning (called leasing) IP addresses, alleviating
the need for a system administrator to do manual work. Likewise, it prevents duplicate IP addresses
from being assigned.

If you have not altered your home network devices, more than likely your router is handling DHCP
and has a DHCP server.

### How it works

When connecting to a network, your device attempts to find a DHCP server to request an IP address,
among other things. The table below highlights these steps by defining each step's name and what it
does:

```sh
+-------------------+--------------------------------------------------------------------------------------------------+
| 1 | DHCP Discover | The client broadcasts a message which searches for a DHCP server                                 |
+---+---------------+--------------------------------------------------------------------------------------------------+
| 2 | DHCP Offer    | The DHCP server responds with a DHCP offer, containing IP address, subnet mask, lease time, etc. |
+---+---------------+--------------------------------------------------------------------------------------------------+
| 3 | DHCP Request  | The client sends a message to the DHCP server indicating the offer is accepted                   |
+---+---------------+--------------------------------------------------------------------------------------------------+
| 4 | DHCP Ack      | The server responds with an acknowledgement of the DHCP server offer                             |
+-------------------+--------------------------------------------------------------------------------------------------+
```

### Using `dhclient`

Although DHCP handles assigning your IP address, etc., it is possible to refresh these details by using
`dhclient`. To obtain a new lease, simply run the following:

```sh
dhclient
```
