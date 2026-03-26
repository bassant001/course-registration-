# 🎓 Course Registration System

## 📌 Overview

This project is a **Course Registration System** designed to manage student course enrollment, academic records, and administrative operations.

It allows:

* Students to register and manage courses
* Admins to manage courses, prerequisites, and grades
* Full tracking of academic progress

---

## 🧠 System Design

### 👤 User (Base Class)

Represents a general system user.

#### Features:

* Register & login system
* Input validation (email, password, ID)
* Stores data in maps and CSV files

---

### 🎓 Student

Derived from User.

#### Features:

* Register / drop courses
* Check prerequisites
* View grades & GPA
* Receive notifications
* Generate academic reports

#### Data Structures:

* `unordered_set` → registered courses
* `unordered_map` → completed courses + grades

---

### 🛠️ Admin

Responsible for managing the system.

#### Features:

* Add new courses
* Set prerequisites
* Manage student grades
* Handle student requests
* Send notifications

---

## ⚙️ System Features

* 📚 Course Registration System
* 📊 GPA Calculation
* 🔐 Login & Authentication
* 🔔 Notification System
* 📁 File Handling (CSV storage)
* 🔄 Dynamic Data Structures

---

## 📂 Data Structures Used

* `unordered_map`
* `unordered_set`
* `vector`

---

## 🚀 How to Run

1. Compile the project:

```bash
g++ main.cpp -o system
```

2. Run:

```bash
./system
```

---

## 👥 Team Members

* Bassant Mohamed
* Omnia Mohamed Salah
* Omar Gamal
* Omar Badr
* Amira Ali
* Salma Magdy
* Omar Ashraf

---

## 🏁 Conclusion

This system simulates a real-world academic registration platform with both student and admin functionalities, using object-oriented programming and efficient data structures.

---
