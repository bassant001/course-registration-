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

## ⚡ Technologies Used
- C++
- Object-Oriented Programming (OOP)
- STL (unordered_map, unordered_set, vector)
- File Handling (CSV)

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
## 🚀 My Contribution

* Designed and implemented a **complete notification system** between students and admin:

  * Students send course add/drop requests
  * Admin reviews and responds to requests
  * Students receive responses through notifications
  * Notifications are cleared after being viewed to avoid duplication

* Developed **request handling system** for course management:

  * `exception_registration()` to send course add requests after semester start
  * `deleting_registred()` for course drop requests
  * Prevented duplicate or invalid requests using tracking sets

* Worked on **advanced validation logic**, including:

  * Ensuring course exists before processing
  * Preventing deletion of non-registered courses
  * Checking prerequisites before allowing registration
  * Enforcing minimum and maximum credit hour constraints

* Built **request tracking mechanism** using:

  * Counters (`counterR`, `counterD`) to control requested hours
  * Sets to track pending add/drop operations

* Developed **student interaction features**, including:

  * `view_notification()` to display admin responses once
  * `search_courses()` for course lookup
  * Menu-driven interface for user actions

* Contributed to **data persistence using CSV files**, including:

  * Loading and saving courses, registrations
  * Maintaining consistency across sessions

* Assisted in improving **system flow and integration** between:

  * Student module
  * Admin module
  * Data storage layer

    
---

## 🏁 Conclusion

This system simulates a real-world academic registration platform with both student and admin functionalities, using object-oriented programming and efficient data structures.

---
