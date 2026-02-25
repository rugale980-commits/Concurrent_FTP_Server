# 🌐 Concurrent FTP Server
## Multi-Client File Transfer System

---

## ⚙️ Technology
**C Programming (Linux System Programming)**

---

## 📌 Project Overview

This project is a Concurrent FTP Server implemented in C on Linux that enables multiple clients to connect to a server and download files concurrently. The server uses socket programming and process management to support parallel file transfers.

It provides a strong practical understanding of Linux networking, file subsystem, process subsystem, and building a simple protocol-driven client-server system.

---

## ✨ Key Features

---

### 👥 Multi-Client Support (Concurrency)
- Handles multiple clients at the same time.
- Uses process-based concurrency (`fork()`) to create a separate child process per connection.

---

### 📁 File Transfer over TCP
- Uses TCP socket communication to ensure reliable transfer.
- Client requests a file name, server validates and sends it.

---

### 🔗 Simple Protocol Design (Header + Data)
Implements a clean protocol like:

- Server first sends a header  
  Example: `OK <size>\n` or error message
- Then transmits the file in chunks using `read()` and `write()`
- Helps students learn real protocol design used in networking systems.

---

### 🐧 Linux System Call Usage (Core Focus)

**File subsystem**
- `open`
- `read`
- `close`
- `stat`

**Network subsystem**
- `socket`
- `bind`
- `listen`
- `accept`
- `connect`
- `send`
- `recv`

**Process subsystem**
- `fork`
- `wait`
- `exit`

---

### ⚠️ Proper Error Handling
Handles cases like:

- File not found
- Client disconnect
- Invalid requests
- Permission issues

---

### 💡 Demonstrates Real-World Concepts
- Socket communication
- Client-server architecture
- Concurrent programming
- Linux system calls
- Transfer reliability

---

## 📚 Learning Outcomes

- Deep understanding of Linux TCP/IP socket programming
- Practical knowledge of client-server architecture
- Hands-on experience with:
  - fork-based concurrency
  - file transfer in chunks
  - protocol design (header + payload)
- Strong command over system programming in C
- Confidence to explain networking + OS concepts in interviews
