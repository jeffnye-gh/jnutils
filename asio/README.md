# Client/Server example using ASIO

## Intro

This is a simple example of client/server processes using Boost::ASIO as the
comms library.

The client as a few commands such as stop, restart, sendblock.

The connection is somewhat resilient, if either client or server 
disconnects the other will attempt to reconnection.

This example assumes that the client and server both run on the same
local host.

## Requirements

You must have boost ASIO installed and in your LIB path.

The makefile sets std=c++20 but that may not be required.

## Build

```
git clone https://github.com/jeffnye-gh/jnutils.git
cd jnutils/asio
make -j
```

## Usage

Using two terminals on the same machine

1) Server terminal
```
./bin/server
```

You will see:
```
Server listening on port 12345
Waiting for client connection...
```

2) Client terminal
```
./bin/client
```

In the client terminal you will see:
```
Connected to server!
client> 
```
Once connected the server terminal will show:

```
Client connected!
Server is busy doing some work: -
```

Client example commands 
```
stop      - stop the server's (fake) periodic process
restart   - resume the server's (fake) periodic process
sendblock - a block of text from server to client
```
