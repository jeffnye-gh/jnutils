# Client/Server example using ASIO

# Intro

This is a simple example of client/server processes using Boost::ASIO as the
comms library.

The client has a few commands such as stop, restart, sendblock.

The connection is somewhat resilient, if either client or server 
disconnects the other will attempt to reconnection.

This example assumes that the client and server both run on the same
local host.

# Requirements

You must have boost ASIO installed and in your LIB path.

The makefile sets std=c++20 but that may not be required.

# Build

```
git clone https://github.com/jeffnye-gh/jnutils.git
cd jnutils/asio
make -j
```

# Usage

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
# GDB commands

ASIO mimics GDB but makes some simplifications to the RSP protocol.

## Breakpoints and Watchpoints

- break [location] or b [location]: Set a breakpoint at a specified location.
- watch [expression]: Set a watchpoint for an expression (triggers when the expression's value changes).
- info breakpoints or info b: List all breakpoints.
- delete [breakpoint number]: Delete a specified breakpoint.
- disable [breakpoint number]: Disable a breakpoint.
- enable [breakpoint number]: Enable a breakpoint.

## Running and Stepping

- run [arguments] or r [arguments]: Start the program with optional arguments.
- continue or c: Continue program execution until the next breakpoint.
- step or s: Step into a function (executes the next line of code, entering functions if necessary).
- next or n: Step over a function (executes the next line of code, but does not enter functions).
- finish: Continue running until the current function returns.
- until [location]: Run until a specified location.

## Examining Variables and Memory

- print [expression] or p [expression]: Print the value of an expression.
- display [expression]: Display the value of an expression every time the program stops.
- info locals: Show all local variables in the current stack frame.
- info variables [regexp]: List global variables, optionally matching a regex.
- x [address]: Examine memory at the specified address.

## Control Stack and Frame Manipulation

- backtrace or bt: Display the current call stack.
- frame [frame number]: Select a specific stack frame.
- info frame: Display information about the current stack frame.

## Program State

- info registers: Show the contents of CPU registers.
- info threads: List all threads.
- thread [thread number]: Switch to a specific thread.
- signal [signal]: Send a signal to the program being debugged.

## File and Symbol Information

- info files: Show information about loaded executable and symbol files.
- info functions [regexp]: List all defined functions, optionally matching a regex.
- info sharedlibrary: Show information about shared libraries.

## GDB Settings and Customization

- set variable [variable] = [value]: Change the value of a variable.
- set [option]: Set various GDB options (e.g., set args to specify program arguments).
- show [option]: Show the current setting of an option.
- define [command]: Define a new custom GDB command.

## Exiting GDB

- quit or q: Exit GDB.
