<!--
Unix Notes © 2021 by Noah Altunian is licensed under Attribution 4.0 International. To view a copy
of this license, visit http://creativecommons.org/licenses/by/4.0/
-->
# UDP vs TCP

### General

Both TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) are part of the Internet
protocol suite, commonly known as TCP/IP. TCP / UDP are different methods for sending information
across the Internet, and are commonly used for communication between devices connected to the Internet.

### Quick Comparison

| TCP           | UDP                           |
|---------------|-------------------------------|
| Slower        | Faster                        |
| More reliable | No guaranteed transfer        |
| Unicast       | Unicast, multicast, broadcast |

### TCP

#### General

TCP is the most common protocol. It is very reliable and is used in HTTP (surfing the web), SMTP
(sending emails), and for transfering files (FTP). If one needs to ensure all sent data is received,
then TCP is the right protocol to use.

Here's an example:

When one connects to a website (https://duckduckgo.com), TCP is used to ensure that 1) text, 2) resources
(e.g. *.jpgs, *.pngs, etc.), and 3) code (HTML/JavaScript) are received by the device that initiated
the connection. TCP will ensure that all requested resources arrive at their destination, and that packets
are transmitted / received in the correct order.

TCP is connection-oriented, meaning that a connection is established between two devices and is only
terminated once all resources have been sent. This connection is defined in the three-way handshake.

#### Three-way handshake

The procedure for establishing a connection over TCP is defined in the three-way handshake. Here's
a diagram showing the procedure:

```
+--------+       SYN       +--------+
| Device | --------------> | Server |
+--------+                 +--------+ 
                         /
                        /
                       /
                      /
                     /
                 SYN-ACK 
                   /
                  /
                 /
                /
               /
              /
             /
            /
+--------+       ACK       +--------+
| Device | --------------> | Server |
+--------+                 +--------+ 
```

Let's break this down in the example of requesting https://duckduckgo.com:

1. Your device requests https://duckduckgo.com
    * A message, called a SYN (Synchronize Sequence Number) is sent to the DuckDuckGo server
2. DuckDuckGo responds with an acknowledgement message
    * This message is called a SYN-ACK
3. When your device receives the SYN-ACK message from DuckDuckGo's server, you send an ACK message
    * This message, called ACK, finalizes the three-way handshake and establishes the connection

The three-way handshake is now complete, and a connection is established. This connection will terminate
once all data is verified as having been sent.

#### Understanding packet transfer

Data sent over TCP/IP are sent in network packets. These packets are tiny pieces of the overall data
being sent, and once all data is received from the device that initiated the three-way handshake,
the packets must be reassemlbed. Once these packets are assembled, the resulting data is composed of
the resources that your device requested (e.g. DuckDuckGo's CSS, HTMl and JavaScript files, including
any/all icons, JPEGs, etc.).

TCP will ensure that all data sent is received. If any packets are lost in transmission, TCP allows
for your device to flag the server and let it know that it must send its packets again. This will
continue until all packets are received. Once this happens, TCP will terminate the connection. This
terminatation is similar to the three-way handshake, instead sending FIN and FIN-ACK messages.

### UDP

#### General

UDP, another popular protocol in TCP/IP, is much simpler and faster than TCP. The trade-off is that
it is less reliable.

UDP is useful in scenarios where data loss is acceptable. Examples streaming video and audio files,
or when playing a multiplayer videogame.

One initial difference from TCP is that UDP is connectionless. That is, it does not establish a
connection before sending packets. Another difference is that UDP does not seek to guarantee packets
are successfully received, and it does not enforce a specific order of transferring packets. Because
of this, UDP is sometimes referred to as a "fire and forget" protocol.

Where TCP is more like having a formal conversation between two people, UDP is more akin to the news
broadcaster on your television. Sure, you may be trying to listen while you prepare your breakfast,
but it is OK if you don't understand everything they tell you.

Let's look at a diagram showing how UDP works:

```
+--------+    Request   +--------+
| Device | -----------> | Server |
+--------+              +--------+ 

+--------+    Response  +--------+
| Device | <----------- | Server |
+--------+              +--------+ 

+--------+    Response  +--------+
| Device | <----------- | Server |
+--------+              +--------+ 

+--------+    Response  +--------+
| Device | <----------- | Server |
+--------+              +--------+ 
```

### Final thoughts

Generally speaking, UDP is faster. It is a simpler protocol and does not verify a connection before
sending data, nor does it validate data transfer ("fire and forget"). It simply sends data to any
device that requests data, and does so until the requesting device disconnects or all data is sent.

It is important to note that being faster is _not_ better. Everything is circumstantial. That is,
if speed is important and data loss is acceptable, then UDP is the answer. Conversely, if some data 
latency is acceptable and data loss is unacceptable, then TCP is the right choice.

In the end, UDP and TCP are both necessary protocols for ensuring a robust and flexible Internet
protocol suite.
