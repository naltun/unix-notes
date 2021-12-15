<!--
Unix Notes © 2021 by Noah Altunian is licensed under Attribution 4.0 International. To view a copy
of this license, visit http://creativecommons.org/licenses/by/4.0/
-->
# DNS (Domain Name System)

### General

DNS is one of the most useful mechanisms of the Internet. The easiest way to visualize DNS is to
think of it as a telephone book for the Internet. Imagine you wanted to look up the number for your
local pizza joint. You know the name, but not the number, so what do you do? You open up a telephone
book and search for the name, and you are given the number. You then dial the service, and order your
pizza (e.g. make use of its services).

DNS is essentially the same thing. Whenever you want to use DuckDuckGo for a web search, you type
`https://duckduckgo.com` into your web browser. Unfortunately, your computer can't do much with this
information, since networking internals only understand IP addresses to identify hosts. DNS is then
used to convert the domain name into a corresponding IP address.

The easiest way to understand DNS, at a high level, is to think of it as a distributed database. It
maps domain names to 1-or-more IP addresses hosting the web site or service.

Here's a fun experiment:
```sh
[vagrant@arch unix-notes]$ curl --head --location --silent duckduckgo.com | awk '/200/'
HTTP/2 200
# -I for --head, -L for --location, and -s for --silent
[vagrant@arch unix-notes]$ curl -ILs $(dig +short duckduckgo.com) | awk '/200/'
HTTP/2 200
```

In the first line, we use `curl` to request the index page for DuckDuckGo and grab the response header,
and then we use `awk` to print the HTTP status. In the second, we use `dig +short` to grab the IP address,
and then we use that instead of the domain name. Notice that we get `200` (e.g. `OK`) in both responses.

This essentially means that we can request a service by simply using its IP address. Since keeping
track of tens, if not hundreds of IP addresses is difficult, DNS assists us by using easy-to-remember
names for interacting with the services we love.
