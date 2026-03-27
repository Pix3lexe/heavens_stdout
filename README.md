# heavens_stdout -- a program that speaks to your soul

**heavens_stdout** is a fun homage to Terry Davis and TempleOS, where you can talk with a randomizer acting as god.
Simply press the **Talk to Me** button to start the interaction.

---

## Build Instructions

1. Make sure you have **Qt6**, **CMake** and a C++ compiler installed on your system.

2. Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/Pix3lexe/heavens_stdout.git
cd heavens_stdout
```

3. Initialize git submodules

```bash
git submodule update --init --recursive
```

4. Build with **cmake**

```bash
mkdir build && cd build
cmake ..
make -j $(nproc)
```

---

<div align="center">
  <img src="https://github.com/user-attachments/assets/8dfd759f-f80c-430a-8d1c-616fe364cca3"/>
  <img src="https://github.com/user-attachments/assets/ad0fabb9-1be6-4fc8-b081-28d9c4a376da"/>
</div>
