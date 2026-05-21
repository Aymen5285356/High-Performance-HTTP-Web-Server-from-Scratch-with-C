# ⚡ C-Pulse

> A real, minimal web server built from scratch in C — zero external dependencies.

![Language](https://img.shields.io/badge/Language-C-00d4ff?style=flat-square)
![Protocol](https://img.shields.io/badge/Protocol-HTTP%2F1.1-ff4d6d?style=flat-square)
![Network](https://img.shields.io/badge/Network-TCP%2FIP-39ff14?style=flat-square)
![Dependencies](https://img.shields.io/badge/Dependencies-Zero-ff8c42?style=flat-square)

---

## 📡 Overview

**C-Pulse** is a fully hand-written web server in pure C that turns your personal computer into a real server. It listens for incoming browser requests over **TCP/IP**, parses raw **HTTP** messages, reads **HTML files** from disk, and sends them back as proper HTTP responses — no frameworks, no libraries, just the OS sockets API.

Every header, every status code, every byte is written manually. This is the web as it actually works under the hood.

---

## 🔗 How It Works

```
Browser (Chrome)
      │
      │  HTTP Request
      ▼
 TCP Socket  ◄──────────────────────────────┐
      │                                     │
      ▼                                     │
 C-Pulse Server                             │
      │                                     │
      │  fopen() / fread()                  │
      ▼                                     │
 File System (reads .html file)             │
      │                                     │
      │  HTTP/1.1 200 OK + content          │
      └─────────────────────────────────────┘
                    send() → Browser renders page
```

---

## ✦ Features

| Feature | Description |
|---|---|
| 🔌 **TCP Socket Listener** | Opens a real socket and listens for incoming connections |
| 🔍 **HTTP Request Parser** | Manually parses method, path, and headers from raw HTTP |
| 📁 **Static File Serving** | Reads and serves HTML files directly from disk |
| 📤 **HTTP Response Builder** | Builds complete HTTP/1.1 responses with correct headers |
| ⚠️ **404 Error Handling** | Returns a proper error page when a file is not found |
| 🔁 **Connection Loop** | Stays alive to handle multiple requests without restart |

---

## ⌨️ Core Code — Socket Setup

```c
// Create TCP socket
int server_fd = socket(AF_INET, SOCK_STREAM, 0);

// Bind to port 8080
struct sockaddr_in address;
address.sin_family      = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port        = htons(8080);

bind(server_fd, (struct sockaddr *)&address, sizeof(address));
listen(server_fd, 10);

// Accept & respond in a loop
while (1) {
    int client_fd = accept(server_fd, NULL, NULL);
    handle_request(client_fd);
    close(client_fd);
}
```

---

## 🚀 Getting Started

**1. Clone the repository**
```bash
git clone https://github.com/username/c-pulse.git
cd c-pulse
```

**2. Compile with GCC**
```bash
gcc server.c -o c-pulse
```
No dependencies — just GCC. Works on Linux and macOS.

**3. Run the server**
```bash
./c-pulse
```

**4. Open in your browser**
```
http://localhost:8080/index.html
```

---

## ▶ Sample Output

```
✔ C-Pulse listening on http://localhost:8080

[GET] /index.html   →  200 OK        (1.2ms)
[GET] /about.html   →  200 OK        (0.9ms)
[GET] /missing.html →  404 Not Found (0.4ms)
```

---

## 🗂 Project Structure

```
c-pulse/
├── server.c        # Main server — socket setup, accept loop
├── handler.c       # HTTP request parser & response builder
├── files.c         # File I/O — read HTML from disk
├── www/
│   ├── index.html  # Default served page
│   └── 404.html    # Error page
└── README.md
```

---

## 🧠 Skills Demonstrated

- **Systems Programming in C** — Manual memory management, file descriptors, low-level code with no abstractions
- **POSIX Sockets API** — `socket()`, `bind()`, `listen()`, `accept()`, `send()`, `close()` from scratch
- **HTTP Protocol Internals** — Parsing raw requests, building responses, implementing status codes manually
- **TCP/IP Networking** — Deep understanding of how data travels from browser to server through network layers
- **File I/O in C** — Reading files with `fopen` / `fread` / `fclose` and streaming content over a socket

---

## ⚙️ Requirements

- GCC or Clang
- Linux or macOS (POSIX-compliant OS)
- No external libraries required



<div align="center">
  Built with raw C · Zero Dependencies · Real Sockets · Real HTTP
</div>
