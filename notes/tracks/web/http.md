### TCP/IP

IPv4 addresses are 32 bit and IPv6 addresses are 128 bit

Common port numbers:

- FTP 21
- SMTP 25
- HTTP 80

Addresses are made up of IP address + port number, ie: `1.2.3.4:80`

### DNS

DNS is a mapping between a URL and server's IP address. DNS are servers that resolve the IP address from the URL.


### HTTP

HTTP is all about what goes inside the "envelope" of the request and the response.

Request:

```
GET / HTTP/1.1
Host: www.example.com
...
```

`GET` specifies the action, `/` is the root directory, `HTTP/1.1` is the version of protocol. We also specify the host.

Response:

```
HTTP/1.1 200 OK
Content-Type: text/html
```

Common Status Codes:

- 200 OK
- 301 Moved Permanently
- 307 Internal Redirect
- 403 Forbidden
- 404 Not Found
- 500 Internal Server Error