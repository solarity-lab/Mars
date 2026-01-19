# 🟠 Mars – A Grid Programming Language 🟠

## Tutorial

---

## What is a Grid Programming Language?

A **Grid Programming Language** is a programming model where data is stored and manipulated inside a **two-dimensional grid** (rows and columns).

Instead of variables and memory addresses, programs operate by:

* Creating a grid
* Moving a **cursor** to a specific cell
* Reading or writing values at the cursor position

Mars is an experimental grid-based programming language designed to explore this concept.

---

## Core Concepts

* **Grid**: A 2D table of cells (rows × columns)
* **Cell**: A single position in the grid, which may contain a value or `Null`
* **Cursor**: Points to the currently active cell
* All operations act on the **current cursor position**

---

## Control Statements in Mars

---

### `CREAT X, Y`

Create a new grid.

* Creates a grid with:

  * **X rows**
  * **Y columns**
* All cells are initialized to `Null`
* The cursor is automatically set to **(0, 0)**
* If a grid already exists, it should be closed before creating a new one

**Example**

```
CREAT 10, 10
```

---

### `MOVE X, Y`

Move the cursor to a specific cell.

* The grid must be created before using this command
* Moves the cursor to:

  * **row X**
  * **column Y**
* Coordinates are zero-based

**Example**

```
MOVE 3, 4
```

---

### `WRITE VALUE`

Write a value into the current cell.

* Writes `VALUE` to the cell at the current cursor position
* Overwrites any existing value in that cell

**Example**

```
WRITE 3
```

---

### `READ`

Print the entire grid.

* Displays the current state of the grid
* Shows all cells, including `Null` cells
* Used for debugging or inspecting the grid

**Example**

```
READ
```

---

### `CLOSE`

Destroy the current grid and free memory.

* Releases all memory used by the grid
* Resets the grid state to `Null`
* After `CLOSE`, no grid exists
* `MOVE`, `READ`, or `WRITE` cannot be used until a new grid is created

**Example**

```
CLOSE
```

---

## Example Program

```
CREAT 5, 5
MOVE 3, 4
WRITE 3
READ
CLOSE
```

This program:

1. Creates a 5×5 grid
2. Moves the cursor to cell (3,4)
3. Writes the value `3` into that cell
4. Prints the grid
5. Frees all allocated memory

---

## Notes

* All commands are executed sequentially
* Mars is designed for simplicity and experimentation
* Future versions may include:

  * Reading individual cells
  * Ranges and rows
  * Expressions and formulas

  * Variables and control flow
