# CSE 426 Graphics Lab Assignment
**Spring 2025 | 4th Year 2nd Semester**

**Student Name:** Yeakin Iqra  
**Student ID:** 21201128  
**Section:** C

---

## Task Submissions

### Task #01(a): Standard Bresenham's Line Drawing Algorithm

**Description:**
Implementation of the classic Bresenham's Line Drawing Algorithm that draws a line between two points P1(x1,y1) and P2(x2,y2). The implementation handles all line orientations including positive/negative slopes, vertical, and horizontal lines.

**Features:**
- Handles all octants (8 orientations)
- Efficient integer-only calculations
- No floating-point operations
---

### Task #01(b): Thick Line Drawing with 8-way Symmetry

**Description:**
Extension of Bresenham's algorithm to draw lines with variable thickness using 8-way symmetry. The implementation calculates and fills the region around the line to create the specified thickness.

**Features:**
- Dynamic thickness adjustment
- Uses perpendicular offset calculation
- Implements 8-way symmetry for uniform thickness
- Interactive thickness control
---

### Task #02: Concentric Circles with Color Gradient

**Description:**
Implementation of the Midpoint Circle Drawing Algorithm to create multiple concentric circles with increasing radius and thickness. Features a smooth color gradient transition from innermost to outermost circle.

**Features:**
- Midpoint circle algorithm with 8-point symmetry
- 10 concentric circles with progressive radius
- Increasing thickness with each circle
- Smooth color gradient (red to blue)
- Efficient drawing without trigonometric functions

---

### Task #03: Liang-Barsky Line Clipping Algorithm

**Description:**
Implementation of the Liang-Barsky Line Clipping Algorithm to clip multiple line segments against a rectangular clipping window. Handles all clipping cases including fully inside, fully outside, and partially intersecting lines.

**Features:**
- Parametric line clipping approach
- Efficient clipping using parametric equations
- Handles all edge cases (inside, outside, partial)
- Visual distinction between original and clipped lines
- Displays clipping window boundary
- Tests with 5 sample lines covering different scenarios

```

```
## Prerequisites

### Software Requirements:
- GCC Compiler
- OpenGL Library
- GLUT (OpenGL Utility Toolkit)
- Standard Math Library

```

### Installation (Windows):
- Install MinGW or Visual Studio
- Download and configure FreeGLUT library
---

## References
1. Computer Graphics: Principles and Practice (3rd Edition) - Foley, van Dam, Feiner, Hughes
2. Course lecture notes - CSE 426, UAP
