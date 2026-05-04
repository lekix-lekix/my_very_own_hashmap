# 🗂️ my_very_own_hashmap

> A from-scratch implementation of a generic hash map in modern C++.

---

## 📌 Overview

Small implementation of a **generic hash map** in C++. This educational project covers the core concepts behind hash tables while leveraging modern C++ features: templates, RAII, smart pointers, and automatic resizing.

---

## ✨ Features

- **Partial genericity** via C++ templates — works with any value pair
- **Collision resolution by chaining** — each bucket holds a linked list of key/value pairs
- **Automatic resizing & rehashing** — the table dynamically grows based on the load factor
- **RAII memory management** — owning buckets via `std::unique_ptr`, no memory leaks possible

---

### Collision Resolution — Chaining

When two keys hash to the same bucket, entries are **chained** in a linked list. Lookup then walks the list to find the exact key match.

### Resizing & Rehashing

When the **load factor** (`nb_elements / nb_buckets`) exceeds a defined threshold, the table:
1. Allocates a new bucket array (x2 the current capacity)
2. Recomputes the hash of every existing element
3. Reinserts all elements into the new table

This guarantees **amortized O(1)** performance for common operations.

### RAII Memory Management

Buckets are owned via `std::unique_ptr`, which means:
- Destroying the hashmap automatically frees all memory
- No manual `delete` calls needed
- Exception-safe by design
