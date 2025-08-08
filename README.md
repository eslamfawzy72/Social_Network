
# Social Network Friend Recommendation System

This project is a **social network application** that recommends friends based on **mutual connections**, built entirely from scratch without using standard library data structures.

---

## 🔍 Overview

The application simulates a social network where users can:
- Register and log in
- Add and view friends
- Receive friend recommendations based on mutual connections
- Search users and handle friend requests

The system uses custom-built **graph**, **hash table**, and **priority queue** implementations to manage user data and efficiently suggest new connections.

---

## 💡 Features

- 🧠 **Friend Recommendation Algorithm**  
  Recommends users with the highest number of mutual friends using a priority queue.

- 📊 **Graph-Based Network Modeling**  
  Each user is a node; friendships are edges between nodes in an undirected graph.

- ⚙️ **Custom Data Structures**  
  Implemented from scratch:
  - Graph (adjacency list)
  - Hash Table (for storing user data)
  - Priority Queue (for ranked friend suggestions)

- 🔐 **Console Authentication System**  
  Users can securely sign up and log in with simple input validation.

---

## 🎮 User Features

After logging in, users can:

- 👤 **View Profile** – Display personal user information.
- 👥 **View Friends** – List all connected friends.
- 🔍 **Search Users** – Find other users by name or username.
- 🤝 **People You May Know** – Suggest friends based on shared connections.
- 📬 **Show Friend Requests** – View and respond to pending requests.
- 🚪 **Logout or Exit** – End the session securely.

---

## 📦 Tech Stack

- **Language**: C++  
- **Environment**: Console application  
- **Libraries**: No STL data structures used for learning purposes

---

## 🛠️ Implementation Highlights

- Graph used to model social connections.
- Hash Table used to store and access user records efficiently.
- Priority Queue used to sort potential friends based on mutual connections.
- Custom input handling and colorized console output using `ConsoleUtils`.

---

## 🚀 How to Run

```bash
g++ FinalProject.cpp -o social_network
./social_network
