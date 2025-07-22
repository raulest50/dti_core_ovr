

# Comandos de Terminal para Simulación y Síntesis en Vitis HLS

Este documento explica los comandos de terminal necesarios para realizar simulación C y síntesis HLS en el proyecto dti_hls_core.

## Comandos para Simulación C (C Simulation)

La simulación C permite verificar la funcionalidad del código antes de la síntesis, ejecutando el código C/C++ con un testbench.

### Comando básico para simulación C:

```powershell
vitis-run --mode hls --csim --config hls_config.cfg --work_dir .
```

#### Explicación de parámetros:
- `--mode hls`: Especifica que se está utilizando el modo HLS (High-Level Synthesis)
- `--csim`: Indica que se desea ejecutar la simulación C
- `--config hls_config.cfg`: Especifica el archivo de configuración del proyecto
- `--work_dir .`: Establece el directorio de trabajo actual como directorio del proyecto

### Comando alternativo usando TCL script:

```powershell
vitis_hls -f scripts/run_csim.tcl
```

#### Explicación:
- `vitis_hls`: Herramienta principal de Vitis HLS
- `-f scripts/run_csim.tcl`: Ejecuta un script TCL que contiene los comandos para la simulación C

### Opciones adicionales para simulación:

Para depuración y análisis más detallado, se pueden añadir estas opciones:

```powershell
vitis-run --mode hls --csim --config hls_config.cfg --work_dir . --hls.csim.debug
```

Para ejecutar el ejecutable de simulación directamente (después de compilarlo):

```powershell
cd hls\csim\build
.\csim.exe
```

## Comandos para Síntesis HLS (C Synthesis)

La síntesis HLS convierte el código C/C++ en RTL (Verilog/VHDL) para implementación en FPGA.

### Comando básico para síntesis:

```powershell
v++ -c --mode hls --config hls_config.cfg --work_dir .
```

#### Explicación de parámetros:
- `-c`: Indica compilación
- `--mode hls`: Especifica que se está utilizando el modo HLS
- `--config hls_config.cfg`: Especifica el archivo de configuración del proyecto
- `--work_dir .`: Establece el directorio de trabajo actual como directorio del proyecto

### Comando alternativo usando TCL script:

```powershell
vitis_hls -f scripts/run_csynth.tcl
```

### Opciones adicionales para síntesis:

Para especificar opciones de optimización adicionales:

```powershell
v++ -c --mode hls --config hls_config.cfg --work_dir . --hls.clock 200 --hls.clock_uncertainty 2%
```

## Configuración del Proyecto (hls_config.cfg)

El archivo `hls_config.cfg` contiene la configuración del proyecto y es esencial para ambos comandos. Incluye:

```
part=xck26-sfvc784-2LV-c  # FPGA target (Kria KV260)

[hls]
flow_target=vivado         # Target flow
package.output.format=ip_catalog  # Output format
syn.top=dti_core_ovr       # Top-level function
clock=200                  # Clock period (ns)
clock_uncertainty=2%       # Clock uncertainty
syn.file=./source/dti_core_ovr.cpp  # Source files
...
```

## Flujo de Trabajo Completo

Para un flujo de trabajo completo, se recomienda seguir estos pasos:

1. **Simulación C para verificar funcionalidad**:
   ```powershell
   vitis-run --mode hls --csim --config hls_config.cfg --work_dir .
   ```

2. **Síntesis C para generar RTL**:
   ```powershell
   v++ -c --mode hls --config hls_config.cfg --work_dir .
   ```

3. **Co-simulación para verificar RTL** (opcional):
   ```powershell
   vitis_hls -f scripts/run_cosim.tcl
   ```

4. **Exportar IP para integración en Vivado**:
   ```powershell
   vitis_hls -f scripts/export_ip.tcl
   ```

## Notas Importantes

- Asegúrese de que las variables de entorno de Vitis estén configuradas correctamente antes de ejecutar estos comandos.
- Los archivos de registro y reportes se generan en los directorios `logs/` y `reports/`.
- Para proyectos grandes como este, la síntesis puede requerir mucho tiempo y recursos computacionales.
- Si la síntesis falla, revise los logs en `logs/hls_compile.log` para identificar problemas.

## Recomendaciones para Optimización

- Utilice pragmas HLS adecuados para optimizar el diseño (pipeline, unroll, dataflow).
- Siga las directrices de dataflow canónico para evitar errores de síntesis.
- Considere reducir la complejidad del diseño si la síntesis falla debido al tamaño.
- Verifique los reportes de síntesis para identificar cuellos de botella y oportunidades de optimización.

## Problemas Comunes y Soluciones

### Error en Simulación C

Si encuentra errores durante la simulación C, verifique:

1. **Rutas de archivos**: Asegúrese de que las rutas a los archivos de datos sean correctas y accesibles.
2. **Problemas de dataflow**: Corrija las regiones de dataflow para seguir las reglas canónicas:
   - No declare variables estáticas dentro de regiones dataflow
   - Solo incluya llamadas a funciones y declaraciones de streams en regiones dataflow

### Error en Síntesis

Si la síntesis falla con "Pre-synthesis failed", considere:

1. **Complejidad excesiva**: El diseño puede ser demasiado grande (más de 50 millones de instrucciones después de unroll).
2. **Problemas de dataflow**: Corrija las violaciones de dataflow canónico.
3. **Reducir factores de unroll**: Disminuya los factores de unroll para reducir la complejidad.

## Recursos Adicionales

- **Guía de Usuario UG1399**: Contiene información detallada sobre el uso correcto de dataflow.
- **Guía de Usuario UG902**: Referencia completa para Vitis HLS.
- **Directorio `.junie`**: Contiene guías específicas para este proyecto, incluyendo:
  - `hls_guidelines.md`: Mejores prácticas para HLS
  - `KV260_resources.md`: Información sobre los recursos disponibles en la plataforma KV260
