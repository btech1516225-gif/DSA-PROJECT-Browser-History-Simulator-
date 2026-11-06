# Browser History Simulator

Mini Project 11 - Data Structures (B.Tech AIML, Sem 3)
Language: C



## About the project

In this project we made the **Back** and **Forward** buttons of a web browser using **two stacks**.

Both stacks are made using linked lists in C. We did not use any ready-made library or container, everything is written with `struct`, `malloc` and pointers. After every action the program prints both stacks, so you can actually see what is going on inside.

##How to run:
1=DOWNLOAD THE MAIN file.
2=run it on vs code.

### Option 1: GitHub Codespaces (easiest, no installation)

1. Click the **Open in GitHub Codespaces** button above (login to GitHub if it asks).
2. Click **Create codespace on main** and wait for about 1 minute. The code gets compiled automatically.
3. In the terminal at the bottom, type:
   ```
   ./browser
   ```



### Option 3: On your own laptop

You need `gcc` installed.

```
git clone https://github.com/YOUR_USERNAME/browser-history-simulator.git
cd browser-history-simulator
gcc main.c -o browser
./browser
```

On Windows the last line is `browser.exe`. If you have `make`, you can also just type `make run`.





## Functions

| Function | What it does |
|----------|--------------|
| `push_back(url)` | pushes a URL on the Back stack |
| `push_forward(url)` | pushes a URL on the Forward stack |
| `clear_forward()` | deletes all the nodes of the Forward stack |
| `visit(url)` | goes to a new URL (rule 1 above) |
| `back()` | goes one page back (rule 2) |
| `forward()` | goes one page forward (rule 3) |
| `display()` | prints the current page and both stacks |
| `main()` | shows the menu and calls the functions |




