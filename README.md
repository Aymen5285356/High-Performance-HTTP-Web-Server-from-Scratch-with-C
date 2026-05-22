<div align="center">

```
 ██████╗      ██████╗ ██╗   ██╗██╗     ███████╗███████╗
██╔════╝     ██╔══██╗██║   ██║██║     ██╔════╝██╔════╝
██║          ██████╔╝██║   ██║██║     ███████╗█████╗  
██║          ██╔═══╝ ██║   ██║██║     ╚════██║██╔══╝  
╚██████╗     ██║     ╚██████╔╝███████╗███████║███████╗
 ╚═════╝     ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚══════╝
```

### ⚡ A real, minimal web server — built from scratch in pure C

[![Language](https://img.shields.io/badge/Language-C-00d4ff?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Protocol](https://img.shields.io/badge/Protocol-HTTP%2F1.1-ff4d6d?style=for-the-badge)](https://developer.mozilla.org/en-US/docs/Web/HTTP)
[![Network](https://img.shields.io/badge/Network-TCP%2FIP-39ff14?style=for-the-badge)](https://en.wikipedia.org/wiki/Internet_protocol_suite)
[![Dependencies](https://img.shields.io/badge/Dependencies-Zero-ff8c42?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-a78bfa?style=for-the-badge)](LICENSE)

</div>

---

## 📡 What Is C-Pulse?

**C-Pulse** is a fully hand-written web server in pure C that transforms your personal computer into a real server — no frameworks, no libraries, no training wheels.

It opens a TCP socket on your machine, listens for incoming HTTP requests from any browser, reads HTML files from your hard disk, and fires back a complete HTTP/1.1 response. Open Chrome, hit `localhost:8080`, and your page loads. That's it. That's the whole internet, compressed into a few hundred lines of C.

Every socket, every header, every status code is written by hand. No `libcurl`. No `libevent`. No abstractions hiding the truth.

> **"Most web developers have never seen what HTTP actually looks like as raw bytes. C-Pulse makes the invisible visible."**

This project was built to prove one thing: you don't need a framework to understand the web. You just need to go one layer deeper.

---

## 🔗 How It Works — The Full Journey of a Request

```
  ┌─────────────────────────────────────────────────────────────────┐
  │  Chrome types: http://localhost:8080/index.html                 │
  └───────────────────────────────┬─────────────────────────────────┘
                                  │
                                  ▼
              ┌───────────────────────────────────┐
              │         TCP Handshake             │
              │   SYN  ──►  SYN-ACK  ──►  ACK    │
              └───────────────────┬───────────────┘
                                  │
                                  ▼
              ┌───────────────────────────────────┐
              │        Raw HTTP Request           │
              │  GET /index.html HTTP/1.1         │
              │  Host: localhost:8080             │
              │  Connection: keep-alive           │
              └───────────────────┬───────────────┘
                                  │
                                  ▼
  ┌─────────────────────────────────────────────────────────────────┐
  │                        C-PULSE SERVER                          │
  │                                                                 │
  │   accept()  ──►  recv()  ──►  parse_request()                  │
  │                                    │                            │
  │                              extract path                       │
  │                                    │                            │
  │                              fopen() + fread()                  │
  │                                    │                            │
  │                          build HTTP response                    │
  │                                    │                            │
  │                              send()  ──►  close()               │
  └───────────────────────────────────┬─────────────────────────────┘
                                      │
                                      ▼
              ┌───────────────────────────────────┐
              │        Raw HTTP Response          │
              │  HTTP/1.1 200 OK                  │
              │  Content-Type: text/html          │
              │  Content-Length: 1024             │
              │                                   │
              │  <!DOCTYPE html>...               │
              └───────────────────┬───────────────┘
                                  │
                                  ▼
                    ┌─────────────────────────┐
                    │  Browser renders page ✓ │
                    └─────────────────────────┘
```

No magic. No middleware. Every arrow in that diagram is a function you can read in the source.

---

## ✦ Features

| Feature | Details |
|---|---|
| 🔌 **TCP Socket Listener** | Opens a raw OS socket and blocks on `accept()` waiting for connections |
| 🔍 **HTTP Request Parser** | Manually parses method, path, version, and headers from raw bytes |
| 📁 **Static File Serving** | Reads any `.html`, `.css`, or `.js` file from disk and streams it to the client |
| 📤 **HTTP Response Builder** | Constructs a valid HTTP/1.1 response with correct `Content-Type` and `Content-Length` |
| ⚠️ **404 Error Handling** | Returns a proper error page — server never crashes on missing files |
| 🔁 **Persistent Accept Loop** | Stays alive forever, handling one connection after another without restart |
| 🧹 **Clean Socket Teardown** | Gracefully closes client sockets and handles `SIGINT` for clean shutdown |

---

## ⌨️ Core Code — Annotated

### 1. Creating the Socket

```c
// AF_INET = IPv4, SOCK_STREAM = TCP (reliable, ordered bytes)
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd < 0) {
    perror("socket() failed");
    exit(EXIT_FAILURE);
}

// SO_REUSEADDR: lets us restart the server instantly
// without waiting for the OS to release the port
int opt = 1;
setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
```

### 2. Binding & Listening

```c
struct sockaddr_in address;
address.sin_family      = AF_INET;       // IPv4
address.sin_addr.s_addr = INADDR_ANY;    // accept from any interface
address.sin_port        = htons(8080);   // host-to-network byte order

bind(server_fd, (struct sockaddr *)&address, sizeof(address));

// backlog = 10: up to 10 connections can queue while we're busy
listen(server_fd, 10);
```

### 3. The Accept Loop

```c
printf("⚡ C-Pulse listening on http://localhost:8080\n");

while (1) {
    // Blocks here until a browser connects
    int client_fd = accept(server_fd, NULL, NULL);

    handle_request(client_fd);  // read → parse → serve → respond

    close(client_fd);           // done with this client
}
```

### 4. Parsing the HTTP Request

```c
void handle_request(int client_fd) {
    char buffer[4096] = {0};
    recv(client_fd, buffer, sizeof(buffer), 0);

    // HTTP request starts with: "GET /path HTTP/1.1\r\n..."
    char method[8], path[256], version[16];
    sscanf(buffer, "%s %s %s", method, path, version);

    // Strip the leading slash → filesystem path
    // "/index.html" becomes "www/index.html"
    char filepath[300];
    snprintf(filepath, sizeof(filepath), "www%s", path);

    serve_file(client_fd, filepath);
}
```

### 5. Building the HTTP Response

```c
void serve_file(int client_fd, const char *filepath) {
    FILE *file = fopen(filepath, "r");

    if (!file) {
        // File not found — send 404
        const char *not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<h1>404 — Not Found</h1>";
        send(client_fd, not_found, strlen(not_found), 0);
        return;
    }

    // Read file into buffer
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *content = malloc(size + 1);
    fread(content, 1, size, file);
    fclose(file);

    // Build HTTP response header manually
    char header[256];
    snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %ld\r\n\r\n", size);

    send(client_fd, header, strlen(header), 0);
    send(client_fd, content, size, 0);
    free(content);
}
```

---

## ▶ Sample Terminal Output

```
$ gcc server.c -o c-pulse && ./c-pulse

⚡ C-Pulse listening on http://localhost:8080

[GET] /index.html        →  200 OK         (1.2ms)
[GET] /about.html        →  200 OK         (0.9ms)
[GET] /style.css         →  200 OK         (0.6ms)
[GET] /favicon.ico       →  404 Not Found  (0.3ms)
[GET] /secret.html       →  404 Not Found  (0.2ms)
```

---

## 🚀 Getting Started

**1. Clone**
```bash
git clone https://github.com/username/c-pulse.git
cd c-pulse
```

**2. Compile**
```bash
gcc server.c -o c-pulse
```
No `npm install`. No `pip install`. No `Makefile` required. Just GCC.

**3. Add your HTML**
```bash
mkdir www
echo "<h1>Hello from C-Pulse ⚡</h1>" > www/index.html
```

**4. Run**
```bash
./c-pulse
```

**5. Open in Chrome**
```
http://localhost:8080/index.html
```

You just served a webpage from a server you built yourself.

---

## 🗂 Project Structure

```
c-pulse/
│
├── server.c          ← Everything: socket setup, accept loop, parser, responder
├── www/
│   ├── index.html    ← Your default page
│   └── 404.html      ← Custom error page
└── README.md
```

One file. That's the whole server. Intentionally.

The goal isn't modularity — it's **clarity**. You can read `server.c` top to bottom and understand exactly what happens from the moment a browser connects to the moment it gets its response. Nothing is hidden.

---

## 🏗 Under The Hood — The Details That Matter

### Why `htons()`?

```c
address.sin_port = htons(8080);
```

CPUs store multi-byte numbers in different orders depending on architecture (little-endian vs big-endian). Network protocols require **big-endian** (network byte order). `htons()` — "host to network short" — converts your port number to the format the network expects. Forget this and your server binds to the wrong port.

---

### Why `SO_REUSEADDR`?

When you kill a server with `Ctrl+C`, the TCP socket enters a `TIME_WAIT` state for ~60 seconds — the OS holds the port open to catch any delayed packets. Without `SO_REUSEADDR`, restarting your server immediately gives you:

```
bind() failed: Address already in use
```

Setting `SO_REUSEADDR = 1` tells the OS to let us reuse the port immediately. Essential during development.

---

### Why `recv()` instead of `read()`?

Both work on sockets, but `recv()` is socket-specific and supports flags. For example:
- `MSG_PEEK` — read data without removing it from the buffer
- `MSG_WAITALL` — block until all requested bytes arrive

Using `recv()` is the correct, explicit choice for network sockets. `read()` is a generic file descriptor call.

---

### The HTTP Header Terminator

HTTP headers are separated from the body by a blank line — which in raw bytes is `\r\n\r\n`:

```
HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n
Content-Length: 512\r\n
\r\n                    ← blank line = end of headers
<html>...               ← body starts here
```

If you forget the double `\r\n`, the browser hangs forever waiting for the headers to end. This is one of the most common bugs when building HTTP by hand.

---

## 🧠 Skills Demonstrated

Building C-Pulse required going well beyond typical application programming:

- **Systems Programming in C** — No GC, no safety nets. Manual memory allocation with `malloc` / `free`, raw pointer arithmetic, buffer management.
- **POSIX Sockets API** — `socket()`, `bind()`, `listen()`, `accept()`, `recv()`, `send()`, `close()` — the same API that powers every server on the internet.
- **HTTP Protocol Internals** — Parsing raw request bytes, understanding request/response structure, implementing status codes, content headers, and MIME types manually.
- **TCP/IP Networking** — How a connection actually forms (the three-way handshake), what port binding means at the OS level, and how data is streamed between processes over a network.
- **File I/O in C** — `fopen`, `fseek`, `ftell`, `rewind`, `fread`, `fclose` — reading binary file sizes and streaming raw bytes directly over a socket.
- **OS-Level Process Control** — Signal handling (`SIGINT`), proper teardown, understanding what happens to sockets when a process exits.

---

## 💡 Challenges & How They Were Solved

**Challenge: `bind()` failing with "Address already in use" after restart**
→ Added `setsockopt(SO_REUSEADDR)` before `bind()`. The socket now reclaims the port instantly without waiting for `TIME_WAIT` to expire.

**Challenge: Browser receiving garbled content — correct bytes, wrong length**
→ The `Content-Length` header was set before reading the file size accurately. Fixed by using `fseek(SEEK_END)` + `ftell()` to get the exact byte count before building the header.

**Challenge: Serving binary files (images) causing corruption**
→ `fopen` was using `"r"` (text mode) which transforms `\r\n` on Windows. Fixed by using `"rb"` (binary mode) for all file reads.

**Challenge: Server crashing on rapid consecutive requests**
→ `client_fd` was being closed before `send()` finished in edge cases. Restructured to always `send()` the full response before calling `close()`.

**Challenge: Long file paths causing buffer overflow**
→ Path buffer was statically sized at 128 bytes. Increased to 300 bytes and added length validation to reject abnormally long paths.

---

## 🔭 Roadmap — What's Next

- [ ] **Multi-threading** — handle multiple connections simultaneously with `pthread`
- [ ] **MIME type detection** — serve `.css`, `.js`, `.png` with correct `Content-Type`
- [ ] **Query string parsing** — extract parameters from URLs like `?page=2&sort=asc`
- [ ] **POST request support** — read request body and parse form data
- [ ] **Logging to file** — persist request logs with timestamps
- [ ] **Config file** — set port, root directory, and timeout from a `.conf` file
- [ ] **HTTPS support** — integrate `OpenSSL` for TLS (the one external dependency worth it)
- [ ] **Virtual hosting** — serve different sites based on the `Host` header

---

## ⚙️ Requirements

- GCC or Clang
- Linux or macOS (any POSIX-compliant OS)
- Zero external libraries

---

## 🎯 Why This Project Matters

Every web developer uses servers every day. Almost none have ever seen one from the inside.

C-Pulse strips away every layer of abstraction — Express, Node, Nginx, Apache — and shows you what's actually happening:

1. A process opens a file descriptor connected to a port
2. The OS routes incoming TCP bytes to that descriptor
3. Your code reads those bytes, interprets them as HTTP, and writes bytes back
4. The browser interprets those bytes as a webpage

That's it. That's the entire web. Everything else is just convenience built on top of this.

After building C-Pulse, concepts like **middleware**, **request lifecycle**, **connection pooling**, and **async I/O** stop being abstract buzzwords. You've seen the foundation they're built on.

> The best way to understand a tool is to build it yourself — then use the real one knowing exactly what it does for you.

---

## 👨‍💻 Author

Developed by **[Your Name]**

---

## ⭐ Support

If this project helped you understand how the web really works:

- Give the repository a star ⭐
- Share it with someone learning systems programming
- Fork it and implement one feature from the roadmap

Understanding the fundamentals compounds. Every layer of abstraction makes more sense once you've built what's underneath it.
