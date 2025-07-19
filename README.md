# DTI HLS Core - Deep Tissue Imaging Accelerator

## Project Overview

DTI HLS Core is a High-Level Synthesis (HLS) implementation of a beam propagation method (BPM) for simulating light propagation through biological tissue. This FPGA accelerator is designed to significantly speed up optical simulations used in deep tissue imaging applications.

The accelerator implements a split-step beam propagation algorithm that combines:
- Linear diffraction (using the Alternating Direction Implicit method)
- Nonlinear effects (Kerr effect causing self-phase modulation)
- Two-photon absorption (TPA)
- Linear absorption

## Key Features

- Highly optimized HLS implementation for Xilinx FPGAs
- Fixed-point arithmetic for hardware efficiency
- Processes 256×256 complex field matrices
- Performs 120 propagation steps along the Z-axis
- Achieves high throughput using HLS optimization directives:
  - Memory partitioning
  - Pipelining
  - Dataflow optimization
  - URAM memory implementation

## Target Hardware

- FPGA: Xilinx Kria KV260 Vision AI Starter Kit (xck26-sfvc784-2LV-c)
- Clock frequency: 200 MHz

## Project Structure

```
dti_hls_core/
├── compile_commands.json    # Compilation commands for the project
├── hls_config.cfg           # HLS configuration file
├── source/                  # Source code directory
│   ├── dti_core_ovr.cpp     # Top-level function for the accelerator
│   ├── hls_stub.h           # Minimal HLS stubs for host compilation
│   ├── step_propagators.cpp # Implementation of propagation algorithms
│   └── step_propagators.h   # Declarations and constants
├── testbench/               # Testbench directory
│   ├── step_propagators_tb.cpp  # Main testbench for validation
│   ├── test_utils.cpp       # Utilities for testing
│   ├── test_utils.h         # Utility declarations
│   └── validation_data_main/  # Validation data directory
│       ├── README.md        # Description of validation data
│       └── *.dat            # Validation data files
└── README.md                # This file
```

## Installation and Setup

### Prerequisites

- Xilinx Vitis HLS 2025.1 or later
- Xilinx Vivado 2025.1 or later (for implementation)
- Windows or Linux operating system

### Setup Instructions

1. Clone this repository:
   ```
   git clone <repository-url>
   cd dti_hls_core
   ```

2. Open the project in Vitis HLS:
   ```
   vitis_hls -p dti_hls_core
   ```

3. Import the configuration from `hls_config.cfg`

## Usage

### Running C Simulation

1. In Vitis HLS, select "Run C Simulation"
2. The testbench will validate the implementation against reference data

### Synthesis and Implementation

1. In Vitis HLS, select "Run C Synthesis" to generate RTL
2. Select "Export RTL" to create an IP package
3. The IP can be integrated into a Vivado project for implementation on the target FPGA

## Algorithm Details

The beam propagation algorithm uses a split-step approach:

1. **ADI X Step**: Solves diffraction in the X direction using the ADI method
2. **Nonlinear Operations (First Half-Step)**:
   - Two-photon absorption
   - Kerr effect (nonlinear phase shift)
   - Linear attenuation
3. **ADI Y Step**: Solves diffraction in the Y direction using the ADI method
4. **Nonlinear Operations (Second Half-Step)**:
   - Two-photon absorption
   - Kerr effect (nonlinear phase shift)
   - Linear attenuation

The algorithm processes a 256×256 grid and performs 120 propagation steps along the Z-axis.

## Physical Parameters

The simulation uses the following physical parameters:

- Wave number (k): 10,681,416.0
- Z step size (dz): 1.0e-6 m
- Y step size (dy): 1.7578e-7 m
- X step size (dx): 1.7578e-7 m
- Linear refractive index (n0): 1.36
- Nonlinear refractive index (n2): 3.0e-20 m²/W
- Linear absorption coefficient (alpha): 0.3 m⁻¹
- Two-photon absorption coefficient (beta): 1.0e-11 m/W

## Testing

The project includes a comprehensive testbench that validates:

1. Individual operators (ADI X, ADI Y, nonlinear operations)
2. Matrix operations (B-vector computation, Thomas solver)
3. Full propagation steps (1, 40, 80, and 120 steps)

Test results are compared against reference data with an RMS error threshold of 1e-3.

## License

[Specify the license under which this project is released]

## Acknowledgments

[Include any acknowledgments or references to papers/algorithms used]