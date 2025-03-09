# Minitalk

## 📌 Summary
Minitalk is a small data exchange program that facilitates communication between a client and a server using UNIX signals. The purpose of this project is to deepen the understanding of signals and inter-process communication in UNIX-based systems.

---

## 📜 Project Description
This project consists of two executables:
- **server**: Starts first and prints its PID (Process ID). It listens for signals sent by the client and reconstructs the transmitted message.
- **client**: Takes the server PID and a string as arguments, then sends the string to the server using only UNIX signals.

The server must be able to:
- Receive messages from multiple clients without restarting.
- Display messages as soon as they are received, without excessive delay.

---

## ⚙️ Allowed Functions
To complete the mandatory part, only the following functions are allowed:
- `write`
- `ft_printf` (or an equivalent custom implementation)
- `signal`
- `sigemptyset`, `sigaddset`, `sigaction`
- `kill`
- `getpid`
- `malloc`, `free`
- `pause`, `sleep`, `usleep`
- `exit`

The communication must be done **exclusively** using the signals:
- `SIGUSR1`
- `SIGUSR2`

---

## 🚀 Features
✅ Sends and receives messages using UNIX signals.
✅ Supports communication with multiple clients in a row.
✅ Efficient message transfer without excessive delay.
✅ Proper error handling to prevent crashes and memory leaks.

---

## 🎯 Bonus Features
🔹 **Acknowledgment System:** The server confirms receipt of each message by sending a signal back to the client.
🔹 **Unicode Support:** The client can send multi-byte characters, ensuring compatibility with a wider range of text inputs.

---

## 🛠️ Compilation & Usage
### **1️⃣ Compilation**
Run the following command to compile the project:
```bash
make
```
This will generate two executables: `server` and `client`.

### **2️⃣ Running the Server**
Start the server first:
```bash
./server
```
It will display its PID, which you will need for the client.

### **3️⃣ Sending a Message**
Run the client with the server PID and the message you want to send:
```bash
./client <SERVER_PID> "Your message here"
```
Example:
```bash
./client 12345 "Hello, World!"
```

---

## 📌 Additional Notes
- The project follows **42's Norm** and does not allow memory leaks or segmentation faults.
- A Makefile is provided with the required rules: `all`, `clean`, `fclean`, `re`, and `bonus`.

---

## 📜 License
This project is part of the **42 School curriculum** and follows its guidelines.

---

## 📞 Contact
For any inquiries or issues, feel free to open an **issue** on GitHub or reach out to me!

