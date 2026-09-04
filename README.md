# 🛡️ BattleGuard: Secure Army Access Control Using RFID and CAN Communication

## 📌 Project Overview

**BattleGuard** is a distributed embedded security and access control system designed to control entry using **RFID authentication** and **CAN communication**.

The project consists of **three LPC2129-based nodes** connected through a CAN network.

* **Node 1** receives the RFID card data through UART and verifies whether the RFID number is authorized.
* If the RFID number is correct, Node 1 sends a CAN message to **Node 2**.
* Node 2 receives the authorized message and controls the door motor using **PWM**.
* If the RFID number is incorrect, Node 1 sends a CAN message to **Node 3**.
* Node 3 receives the unauthorized message and activates an **LED and buzzer** as a security alert.

The project demonstrates the practical integration of **RFID, UART, CAN communication, PWM, GPIO, and motor control** using the **LPC2129 ARM7 microcontroller**.

---

# 🎯 Objectives

The main objectives of this project are:

* To implement RFID-based access control.
* To receive RFID data using UART communication.
* To verify authorized and unauthorized RFID cards.
* To establish communication between multiple nodes using CAN.
* To control a door mechanism after successful authentication.
* To generate PWM for motor control.
* To activate an LED and buzzer during unauthorized access.
* To demonstrate a distributed embedded security system.

---

# 🏗️ System Architecture

```text
                         ┌─────────────┐
                         │  RFID CARD  │
                         └──────┬──────┘
                                │
                                │ RFID Detection
                                ▼
                    ┌────────────────────────┐
                    │         NODE 1         │
                    │  RFID Authentication   │
                    │                        │
                    │       LPC2129          │
                    │                        │
                    │  UART Communication    │
                    │  RFID Verification     │
                    └───────────┬────────────┘
                                │
                         CAN Communication
                                │
                   ┌────────────┴────────────┐
                   │                         │
                   ▼                         ▼
          AUTHORIZED RFID             UNAUTHORIZED RFID
                   │                         │
                   │ CAN Message             │ CAN Message
                   ▼                         ▼
          ┌─────────────────┐       ┌─────────────────┐
          │     NODE 2      │       │     NODE 3      │
          │  Door Control   │       │ Security Alert  │
          │                 │       │                 │
          │    LPC2129      │       │    LPC2129      │
          │                 │       │                 │
          │   PWM Output    │       │     LED ON      │
          │   Motor Control │       │   Buzzer ON     │
          └─────────────────┘       └─────────────────┘
```

---

# 🔄 Working Principle

## Step 1: RFID Detection

An RFID card is placed near the RFID reader.

The RFID reader detects the card and sends its RFID number serially to **Node 1**.

UART communication is used between the RFID reader and the LPC2129 microcontroller.

```text
RFID Card
    │
    ▼
RFID Reader
    │
    │ UART Communication
    ▼
Node 1 - LPC2129
```

---

## Step 2: RFID Authentication

Node 1 receives the RFID number through UART.

The received RFID number is stored and compared with a predefined authorized RFID number.

Example:

```c
unsigned char authorized_rfid[] = "9827368AHY62";
```

If both RFID numbers match:

```text
ACCESS GRANTED
```

If the RFID number does not match:

```text
ACCESS DENIED
```

---

# 🟢 Authorized Access Process

When the RFID card is authorized:

1. Node 1 verifies the RFID number.
2. Node 1 sends an authorized message through CAN.
3. Node 2 receives the CAN message.
4. Node 2 generates a PWM signal.
5. The motor rotates and operates the door mechanism.
6. The door opens for the required movement or angle.

```text
Authorized RFID
       │
       ▼
Node 1 Authentication
       │
       ▼
CAN Message
       │
       ▼
Node 2
       │
       ▼
PWM Generation
       │
       ▼
Motor Control
       │
       ▼
Door Opens
```

---

# 🔴 Unauthorized Access Process

When the RFID card is unauthorized:

1. Node 1 detects that the RFID number is invalid.
2. Node 1 sends an unauthorized message through CAN.
3. Node 3 receives the CAN message.
4. Node 3 activates the LED.
5. Node 3 activates the buzzer.

```text
Unauthorized RFID
       │
       ▼
Node 1 Authentication
       │
       ▼
CAN Message
       │
       ▼
Node 3
       │
       ├────► LED ON
       │
       └────► BUZZER ON
```

---

# 🧩 Node Description

## 🟡 Node 1 – RFID Authentication Node

### Main Functions

* Initializes UART communication.
* Initializes CAN communication.
* Receives RFID data through UART.
* Stores the received RFID number.
* Compares the RFID number with the authorized RFID number.
* Sends a CAN message for authorized access.
* Sends a CAN message for unauthorized access.

### Input

```text
RFID Reader → UART → LPC2129
```

### Output

```text
Correct RFID → CAN Message → Node 2

Wrong RFID   → CAN Message → Node 3
```

---

## 🟢 Node 2 – Door Control Node

### Main Functions

* Initializes CAN communication.
* Initializes PWM.
* Waits for an authorized CAN message.
* Generates PWM output.
* Controls the motor.
* Opens the door mechanism.

### Input

```text
Node 1 → CAN → Node 2
```

### Output

```text
LPC2129 → PWM → Motor Driver → Motor → Door
```

---

## 🔴 Node 3 – Security Alert Node

### Main Functions

* Initializes CAN communication.
* Receives the unauthorized access message.
* Activates an LED.
* Activates a buzzer.

### Input

```text
Node 1 → CAN → Node 3
```

### Output

```text
LED → ON

BUZZER → ON
```

---

# 📡 Communication Protocols Used

## UART Communication

UART communication is used between the **RFID Reader and Node 1**.

The RFID reader transmits the RFID card number serially to the LPC2129.

```text
RFID Reader
     │
     │ UART
     ▼
Node 1 - LPC2129
```

---

## CAN Communication

CAN communication is used between the three LPC2129 nodes.

Node 1 sends the authentication result through the CAN network.

```text
                     CAN BUS
        ─────────────────────────────────

             Node 1
        RFID Authentication
                │
                │
        ┌───────┴───────┐
        │               │
        ▼               ▼
      Node 2          Node 3
   Door Control    Security Alert
```

---

## PWM

PWM is used in **Node 2** for controlling the motor.

The PWM signal is generated by the LPC2129 and applied to the motor control circuit.

```text
LPC2129
    │
    │ PWM
    ▼
Motor Driver
    │
    ▼
DC Motor / Door Motor
```

---

# 📨 CAN Message Flow

The project uses CAN messages to communicate the authentication result.

| Condition         | CAN Message            | Destination | Action       |
| ----------------- | ---------------------- | ----------- | ------------ |
| Authorized RFID   | Access Granted Message | Node 2      | Open Door    |
| Unauthorized RFID | Access Denied Message  | Node 3      | LED + Buzzer |

Example CAN identifiers:

```text
Authorized Access   → CAN ID: 0x101

Unauthorized Access → CAN ID: 0x102
```

---

# ⚙️ Complete Project Workflow

```text
START
  │
  ▼
Initialize Node 1
  │
  ├── UART Initialization
  │
  └── CAN Initialization
  │
  ▼
Wait for RFID Card
  │
  ▼
Receive RFID Number
Using UART
  │
  ▼
Compare RFID Number
  │
  ├─────────────────────┐
  │                     │
  ▼                     ▼
AUTHORIZED          UNAUTHORIZED
  │                     │
  ▼                     ▼
CAN Message        CAN Message
Access Granted     Access Denied
  │                     │
  ▼                     ▼
NODE 2              NODE 3
  │                     │
  ▼                     ▼
PWM MOTOR          LED ON
CONTROL             BUZZER ON
  │
  ▼
DOOR OPENS
```

---

# 🔌 Hardware Components

| Component               |    Quantity | Purpose                          |
| ----------------------- | ----------: | -------------------------------- |
| LPC2129 Microcontroller |           3 | Controller for all three nodes   |
| RFID Reader             |           1 | Reads RFID card number           |
| RFID Card/Tag           |   1 or more | User authentication              |
| CAN Transceiver         |           3 | CAN physical layer communication |
| DC Motor                |           1 | Door mechanism control           |
| Motor Driver            |           1 | Drives the motor                 |
| LED                     |           1 | Unauthorized access indication   |
| Buzzer                  |           1 | Security alert                   |
| Power Supply            | As required | Power for the system             |

---

# 💻 Software and Development Tools

* Keil µVision
* Embedded C
* Proteus
* LPC2129
* Git
* GitHub

---

# 📂 Repository Structure

```text
BattleGuard-Secure-Army-Access-Control/
│
├── README.md
│
├── Node1_RFID_Authentication/
│   ├── main.c
│   ├── header.h
│   ├── uart.h
│   ├── can.h
│   └── lcd.h
│
├── Node2_Door_Control/
│   ├── main.c
│   ├── header.h
│   ├── can.h
│   └── pwm.h
│
└── Node3_Security_Alert/
    ├── main.c
    ├── header.h
    ├── can.h
    └── gpio.h
```

Each node contains **one main source file (`main.c`)** containing the main program and function implementations.

The `.h` header files contain:

* Function declarations
* Macros
* Register definitions
* Structures
* Common header inclusions

---

# 🗂️ File Description

## Node 1 – RFID Authentication

| File       | Description                                          |
| ---------- | ---------------------------------------------------- |
| `main.c`   | Main program, RFID verification and CAN transmission |
| `header.h` | Common header file                                   |
| `uart.h`   | UART-related declarations and definitions            |
| `can.h`    | CAN-related structures and declarations              |
| `lcd.h`    | LCD-related declarations                             |

---

## Node 2 – Door Control

| File       | Description                                  |
| ---------- | -------------------------------------------- |
| `main.c`   | Main program, CAN reception and door control |
| `header.h` | Common header file                           |
| `can.h`    | CAN-related structures and declarations      |
| `pwm.h`    | PWM-related declarations and definitions     |

---

## Node 3 – Security Alert

| File       | Description                                   |
| ---------- | --------------------------------------------- |
| `main.c`   | Main program, CAN reception and alert control |
| `header.h` | Common header file                            |
| `can.h`    | CAN-related structures and declarations       |
| `gpio.h`   | GPIO-related declarations and definitions     |

---

# 🔐 Security Logic

The security decision is made at **Node 1**.

```text
                RFID CARD
                    │
                    ▼
              RFID READER
                    │
                   UART
                    │
                    ▼
                 NODE 1
                    │
            RFID ID MATCH?
                    │
            ┌───────┴───────┐
            │               │
           YES              NO
            │               │
            ▼               ▼
       CAN TO NODE 2   CAN TO NODE 3
            │               │
            ▼               ▼
        OPEN DOOR       SECURITY ALERT
                        LED + BUZZER
```

---

# 🧠 Concepts Demonstrated

This project demonstrates the following embedded system concepts:

* Embedded C Programming
* ARM7 LPC2129 Microcontroller
* UART Communication
* CAN Communication
* RFID Interfacing
* PWM Generation
* Motor Control
* GPIO Programming
* LED Interfacing
* Buzzer Interfacing
* Distributed Embedded Systems
* RFID-Based Access Control

---

# 🚀 Future Enhancements

The project can be further improved by adding:

* Multiple authorized RFID cards.
* RFID database storage.
* Password or PIN verification.
* Automatic door closing.
* Servo motor-based angle control.
* GSM-based security alerts.
* CAN error monitoring.
* Emergency access mode.

---

# ▶️ How to Run the Project

1. Create separate Keil projects for Node 1, Node 2, and Node 3.
2. Add the respective `main.c` file and header files to each project.
3. Configure the target microcontroller as LPC2129.
4. Connect the nodes through the CAN communication network using appropriate CAN transceivers.
5. Connect the RFID reader to Node 1 through UART.
6. Connect the motor driver and motor to Node 2.
7. Connect the LED and buzzer to Node 3.
8. Build each node program separately.
9. Generate the HEX file for each node.
10. Load the corresponding HEX file into each LPC2129 node in Proteus or hardware.
11. Run the system.
12. Scan an authorized or unauthorized RFID card.

---

# 📋 Expected Output

## Authorized RFID Card

```text
RFID Card Detected

RFID ID Verified

Access Granted

CAN Message Sent to Node 2

Node 2 Received Message

Door Opening...
```

---

## Unauthorized RFID Card

```text
RFID Card Detected

RFID ID Verification Failed

Access Denied

CAN Message Sent to Node 3

Node 3 Received Message

Security Alert Activated

LED ON

BUZZER ON
```

---

# 📄 Project Title

## 🛡️ BattleGuard: Secure Army Access Control Using RFID and CAN Communication

---

# 👨‍💻 Author

**Madhanraj B**

B.E. Electrical and Electronics Engineering

---

# 🏁 Conclusion

**BattleGuard** is an embedded access control system that combines **RFID authentication and CAN communication** using three LPC2129-based nodes.

Node 1 acts as the authentication node and verifies the RFID card through UART communication. Based on the authentication result, it sends a CAN message to either Node 2 or Node 3.

* **Authorized access** activates Node 2, which controls the door motor using PWM.
* **Unauthorized access** activates Node 3, which turns ON the LED and buzzer.

The project demonstrates how multiple embedded controllers can communicate and perform different tasks in a distributed security system.
