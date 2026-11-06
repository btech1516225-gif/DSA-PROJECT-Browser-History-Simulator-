#  Browser History Simulator

> The **Back / Forward** buttons of a web browser, built from scratch in **C** using **two stacks** (implemented with linked lists).

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/YOUR_USERNAME/browser-history-simulator)
[![Run on Replit](https://img.shields.io/badge/Run%20on-Replit-F26207?logo=replit&logoColor=white)](https://replit.com/github.com/YOUR_USERNAME/browser-history-simulator)
![Language: C](https://img.shields.io/badge/language-C-blue)
![Topic: Stacks](https://img.shields.io/badge/data%20structure-stack-green)

*Data Structures Mini-Project #11 · B.Tech CSE, Semester 3*

---

##  What is this project?

Every browser has a **Back** and a **Forward** button. Have you ever wondered how the browser remembers which page to go to?

It uses **two stacks**. This program is a small command-line simulation of exactly that. You type website names, press Back and Forward, and at every step the program shows you what is inside both stacks, so you can *see* the data structure working.

No library or built-in container is used. Both stacks are written from scratch with `struct` + `malloc` + pointers.

---

## ▶ Run it in one click

### Option 1 — GitHub Codespaces (recommended)

1. Click the **Open in GitHub Codespaces** badge at the top of this page (log in to GitHub if asked).
2. Click **Create codespace on main** and wait about a minute. The program is compiled automatically.
3. In the terminal at the bottom, type:

   ```bash
   ./browser
   ```
4. Use the menu (see [Try this](#-try-this-60-second-walkthrough) below).

### Option 2 — Replit

1. Click the **Run on Replit** badge at the top of this page (a free Replit account is needed).
2. Wait for the import to finish and press the **Run** button.

### Option 3 — On your own computer

You need a C compiler (`gcc`). 

```bash
git clone https://github.com/YOUR_USERNAME/browser-history-simulator.git
cd browser-history-simulator

# Linux / macOS
make run

# or, without make (works everywhere, including Windows with MinGW)
gcc main.c -o browser
./browser          # on Windows: browser.exe
```

---

## 🧪 Try this (60-second walkthrough)

Type these in order and watch the two stacks change after every step:

| # | You choose | You type | What to notice |
|---|-----------|----------|----------------|
| 1 | `1` Visit | `youtube.com` | `google.com` moved into the Back stack |
| 2 | `1` Visit | `github.com` | Back stack now has 2 pages |
| 3 | `2` Back | – | `github.com` moved to the Forward stack |
| 4 | `2` Back | – | Forward stack now has 2 pages |
| 5 | `3` Forward | – | A page moves from Forward back to current |
| 6 | `1` Visit | `wikipedia.org` | **Forward stack becomes Empty** (like a real browser!) |
| 7 | `3` Forward | – | `No forward history!` |

---

## 🖥️ Sample output

The menu is printed after every action; it is shortened here with `...`.

```text
----------------------------------
Current Page: google.com
Back Stack: Empty
Forward Stack: Empty
----------------------------------

--- MENU ---
1. Visit URL
2. Back
3. Forward
4. Exit
Enter choice: 1
Enter Website URL: youtube.com

 VISITED : youtube.com

----------------------------------
Current Page: youtube.com
Back Stack: google.com -> 
Forward Stack: Empty
----------------------------------
...
Enter choice: 1
Enter Website URL: github.com

 VISITED : github.com

----------------------------------
Current Page: github.com
Back Stack: youtube.com -> google.com -> 
Forward Stack: Empty
----------------------------------
...
Enter choice: 2

Moved Back to: youtube.com

----------------------------------
Current Page: youtube.com
Back Stack: google.com -> 
Forward Stack: github.com -> 
----------------------------------
...
Enter choice: 1
Enter Website URL: wikipedia.org

 VISITED : wikipedia.org

----------------------------------
Current Page: wikipedia.org
Back Stack: youtube.com -> google.com -> 
Forward Stack: Empty          <-- cleared on a new visit
----------------------------------
```

---

## How it works

### The big idea

Think of two piles of papers and one paper in your hand:

```
   BACK STACK            CURRENT PAGE          FORWARD STACK
 (pages behind you)     (page you are on)     (pages ahead of you)

  ┌─────────────┐
  │ github.com  │ ← top
  ├─────────────┤        youtube.com          ┌──────────────────┐
  │ google.com  │                             │ stackoverflow.com│ ← top
  └─────────────┘                             └──────────────────┘
```

A **stack** is *Last-In-First-Out (LIFO)*. The page you left most recently is the first page you want to return to, which is exactly how Back works. So a stack is the perfect fit.

### The three rules (this is the entire logic)

| Action | Step 1 | Step 2 | Step 3 |
|--------|--------|--------|--------|
| **Visit** `url` | push *current* on **Back** stack | `url` becomes *current* | **clear** the Forward stack |
| **Back** | push *current* on **Forward** stack | pop **Back** stack → becomes *current* | – |
| **Forward** | push *current* on **Back** stack | pop **Forward** stack → becomes *current* | – |

If the stack we need to pop from is empty, the program prints `No back history!` or `No forward history!` and changes nothing.

### Step-by-step trace

| Action | Back stack (top → bottom) | Current | Forward stack (top → bottom) |
|--------|---------------------------|---------|------------------------------|
| Start | *(empty)* | google.com | *(empty)* |
| Visit youtube.com | google.com | youtube.com | *(empty)* |
| Visit github.com | youtube.com, google.com | github.com | *(empty)* |
| Visit stackoverflow.com | github.com, youtube.com, google.com | stackoverflow.com | *(empty)* |
| Back | youtube.com, google.com | github.com | stackoverflow.com |
| Back | google.com | youtube.com | github.com, stackoverflow.com |
| Forward | youtube.com, google.com | github.com | stackoverflow.com |
| Visit wikipedia.org | github.com, youtube.com, google.com | wikipedia.org | *(empty)* ✅ |

---

## 🏗️ Data structure design

Each stack is a **singly linked list** where we always insert and remove at the **head** (the head is the top of the stack).

```c
struct node {
    char url[100];        // the website address
    struct node* next;    // pointer to the node below it in the stack
};

struct node* back_top    = NULL;   // top of the Back stack
struct node* forward_top = NULL;   // top of the Forward stack
char current[100]        = "google.com";   // the page we are on now (home page)
```

```
back_top ──► [github.com|•]──► [youtube.com|•]──► [google.com|NULL]
```

Why a linked list and not an array? The stack can grow as long as the user keeps browsing, so there is **no fixed size limit and no wasted memory**. Each `push` does a `malloc`, each `pop` does a `free`.

### Functions

| Function | What it does | Time |
|----------|--------------|------|
| `push_back(url)` | Pushes a URL on the Back stack | O(1) |
| `push_forward(url)` | Pushes a URL on the Forward stack | O(1) |
| `clear_forward()` | Frees every node of the Forward stack | O(f) |
| `visit(url)` | Visit rule: push current, set new current, clear forward | O(f)* |
| `back()` | Back rule (pop from Back) | O(1) |
| `forward()` | Forward rule (pop from Forward) | O(1) |
| `display()` | Prints current page and both stacks | O(n) |
| `main()` | Menu loop: reads the choice and calls the functions above | – |

`n` = total pages in both stacks, `f` = pages in the Forward stack.
\* Every node freed by `clear_forward()` was pushed earlier, so the cost is paid back over time: **amortised O(1)** per visit.

### Space complexity

**O(n)**, one node per remembered page.

---

##  Edge cases handled

| Situation | What happens |
|-----------|--------------|
| Back pressed with nothing behind | `No back history!`, nothing changes |
| Forward pressed with nothing ahead | `No forward history!`, nothing changes |
| New page visited after going Back | Forward stack is **cleared** (same as real browsers) |
| Menu choice other than 1–4 | `Invalid choice! Try again.` |
| Memory of removed pages | Freed with `free()` on every pop and on `clear_forward()` |

---

## ⚠️ Limitations

- A URL is read with `scanf("%s")`, so it **cannot contain spaces**, and is limited to 99 characters.
- Menu input is expected to be a number.
- No real web page is opened; this is a simulation of the history logic only.
- History is kept in memory only and is lost when the program exits.

### 💡 Ideas to extend

- Save and load the history from a file
- Limit the history size (for example, keep only the last 50 pages)
- Add bookmarks or a "show full history" option

---

## 📁 Project structure

```
browser-history-simulator/
├── main.c                       # complete source code (with comments)
├── Makefile                     # `make` to build, `make run` to build and run
├── README.md                    # this file
├── .gitignore
├── .replit                      # lets the Run button work on Replit
└── .devcontainer/
    └── devcontainer.json        # compiles the program automatically in Codespaces
```

---

## 🎯 Project requirements checklist

From the *Data Structures Mini-Projects* list, **#11 Browser History Simulator** (Stack-Based):

| Requirement | Where it is done |
|-------------|------------------|
| Two stacks, implemented from scratch | `push_back`, `push_forward`, linked-list nodes |
| Visit operation | `visit()` |
| Back operation | `back()` |
| Forward operation | `forward()` |
| Current-page tracking | the `current` variable, shown by `display()` |
| Clear forward stack on a new visit | `clear_forward()` called inside `visit()` |
| Empty-stack and invalid-input handling | checks in `back()`, `forward()` and `main()` |
| Command-line interface | menu in `main()` |

---

## 👥 Team

| Member | Role | Contribution |
|--------|------|--------------|
| *Name 1* | Core data structure implementation | Linked-list stacks, push/pop |
| *Name 2* | Algorithm | Visit / back / forward logic |
| *Name 3* | Interface and testing | Menu, input handling, edge-case tests |
| *Name 4* | Documentation and demo | Report, complexity analysis, README |

*(Replace the names and edit the contributions to match your team.)*

---

⭐ If this project helped you understand stacks, give the repository a star!

