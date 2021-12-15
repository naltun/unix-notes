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

### Building Blocks of DNS

DNS is made up of various components. Let's learn about them.

#### Name Servers

The name server is the core block of DNS, and are tasked with answering DNS queries. If a client asks
for DuckDuckGo and one name server doesn't know the details, it will redirect the client to another
name server. This continues until the answer is found.

Name servers are broken into two categories: authoritative, and recursive. Authoritative name servers
know the exact details clients are looking for. Conversely, recursive name servers pass your query
onto other name servers, until the authoritative name server is found. It is possible for recursive
name servers to cache query responses from authoritative name servers. If this is the case, the recursive
name server will return the query results.

#### Zone Files

Name servers have files called zone files. These files contain the configuration for how name servers
store or cache information on domains, or where to look for the details if the name is non-authoritative.

#### Resource Records

Zone files are made up of resource records, which are entries of information for hosts, other name
servers, and similar resources. These entries are composed of the following:

```
+--------------------+----------------------------------------------------------------+
| Record name        | name of the record                                             |
+--------------------+----------------------------------------------------------------+
| TTL (Time To Live) | time after which we obtain a new resource record on a resource |
+--------------------+----------------------------------------------------------------+
| Class              | namespace for a specific piece of data in a record             |
+--------------------+----------------------------------------------------------------+
| Type               | type of data stored in the record                              |
+--------------------+----------------------------------------------------------------+
| Data               | data stored for a specific record type                         |
+--------------------+----------------------------------------------------------------+
```
