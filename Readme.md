# Lightweight HTTP server in C
Server shows information about system.
Server listens for GET requests on given port and <br>return requested information. Port is set by argument.<br>
Requests:
- ~/hostname - get host name
- ~/cpu-name - get host cpu name
- ~/load - get current cpu load

## Installation
Server provided with Makefile.
```
$ make
```
## Usage
```
$ ./hinfosvc PORT
```
## Examples
### Input 
```
$ ./hinfosvc 12345 &
$ GET http://localhost:12345/hostname
$ GET http://localhost:12345/cpu-name
$ GET http://localhost:12345/load
```
### Output
```
merlin.fit.vutbr.cz
Intel(R) Xeon(R) CPU E5-2640 0 @ 2.50GHz
65%
```
#### Aleksandr Verevkin (xverev00)