# HTTP: C++ Web Server

This project is an implementation of the **webserv** subject from **42 School**.  
It is a lightweight HTTP/1.0 server written in C++98, using **epoll** for a single non-blocking event loop.

You can find the original subject [here](./docs/Subject.md).

---

## Features (HTTP/1.0 scope)

* Single non-blocking **epoll** loop for all I/O
* Supports **GET**, **POST** (uploads), and **DELETE**
* **Static file serving** with `index` and optional autoindex
* **Config file** inspired by nginx (ports, roots, error pages, methods, uploads, body limits, CGI)
* **Custom error pages** or built-in defaults
* **CGI execution** (e.g., Python scripts) with proper env + stdin/stdout handling
* **Multi-port listening** (different roots per port)
* Accurate **HTTP status codes** (200, 201, 204, 301/302, 400, 403, 404, 405, 413, 500)

---

## Build & Run

```bash
    make && ./webserv
```
