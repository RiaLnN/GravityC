# GravityC: N-Body Orbital Mechanics Simulation

A lightweight, high-performance 2D orbital mechanics and gravity simulation written in pure C (C11) using SDL3.

## Features
* **N-Body Gravity Simulation:** Uses Newton's law of universal gravitation to calculate interactions between all bodies simultaneously ($O(N^2)$ complexity).
* **Perfect Inelastic Collisions:** When two celestial bodies collide, they merge into a single body conserving total momentum and dynamically recalculating the new radius based on combined volume. $$m_{1} \vec{v}_{1} + m_{2} \vec{v}_{2} = m_{total} \vec{v}_{new}$$
* **Custom Pixel-Buffer Renderer:** Instead of using standard SDL shapes, the engine directly manipulates a raw XRGB8888 pixel buffer for high-performance software rendering.
* **Pre-configured Scenarios:** Includes presets for the Solar System, random particle chaos, and a Saturn-like planetary ring system.

## Technical Stack
* **Language:** Pure C (C11)
* **Graphics Library:** SDL3 (Simple DirectMedia Layer)
* **Build System:** GCC / Clang

## Mathematical Concept
The gravitational force between bodies $A$ and $B$ is calculated using:
$$F = G \frac{m_A m_B}{r^2}$$

To prevent division by zero when bodies are extremely close, a softening factor is applied to the squared distance ($r^2 + 1.0$). Collision merging recalculates the radius assuming uniform density in 2D space:
$$R_{new} = \sqrt{R_A^2 + R_B^2}$$

## How to Run

1. Install SDL3 library on your system.
2. Compile the project using GCC:
   ```bash
   gcc main.c logic.c simulation.c ui.c -o gravity_sim -lSDL3 -lm
