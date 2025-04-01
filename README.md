# A Flat for Rent – Tenant Allocation Simulation in C

This project is a C-based simulation of a tenant assignment system for apartment units in a predefined building grid. The program reads a list of tenants with their individual constraints from an input file and attempts to allocate each tenant to a valid apartment according to specific neighborhood rules.

### Program Description

- The building is represented as an 11x8 matrix (internally padded to 12x9 for safety).
- Each tenant is defined by a **serial index** and a **maximum number of neighbors** they can live with.
- The placement logic checks two main conditions:
  1. The number of non-zero adjacent cells (neighbors) must not exceed the allowed value.
  2. Some tenants are incompatible with certain others, based on fixed rules (handled by `check2`).
- If a suitable location is found, the tenant is placed.
- If no valid apartment is available, the system prints a message indicating the tenant must look elsewhere.
- Finally, the completed apartment matrix is written to an output file.

### Technical Highlights

- Grid-based logical simulation with a focus on **neighbor conditions**.
- **Constraint checking** using two-layered validation.
- File I/O: reads structured input and writes final results to a text file.
- Modular C functions, with clear separation of logic.

### Educational Value

This project demonstrates core concepts in:
- **Constraint satisfaction problems** (CSP) in a simplified spatial context.
- Use of **2D arrays for simulation** and managing real-world mapping.
- **File handling in C**: reading structured input, cleaning strings, and formatted output.
- Modular thinking and function-driven design.
- Applying **logic gates and rule validation** for decision making.

It's a great exercise in combining algorithmic decision-making with practical I/O and memory-safe programming in C.
