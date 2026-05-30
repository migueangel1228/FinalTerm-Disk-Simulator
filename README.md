# FinalTerm-Disk-Simulator

## 1. Descripción general

Este proyecto es una simulación en C++ de dos temas relacionados con discos duros para un trabajo final universitario. Cubre:
1. **Geometría de la unidad de disco**: simulación de las características físicas de un HDD a partir de su tamaño.
2. **Algoritmos de planificación de disco**: implementación y comparación de FCFS, SCAN y C-SCAN para atender solicitudes de E/S.

El proyecto tiene una estructura modular y se ejecuta desde la línea de comandos.

## 2. Problema 1: Geometría de la unidad de disco

### Descripción
Esta parte del simulador modela la estructura física de un HDD. El usuario proporciona el tamaño del disco en gigabytes (GB) y el número de pistas o de platos. Luego, el programa calcula el parámetro faltante con una fórmula simplificada.

### Características principales
- Calcula la geometría del disco (sectores, pistas y platos).
- Usa un tamaño estándar de sector de 512 bytes.
- Toma 1 GB como 1,000,000,000 bytes para los cálculos.
- Valida la entrada del usuario para evitar errores.
- Muestra un resumen con los valores calculados.

## 3. Problema 2: Planificación de disco

### Descripción
Esta parte implementa tres algoritmos de planificación de disco para procesar solicitudes de E/S. La simulación se ejecuta sobre un disco con 5,000 cilindros (0-4999) y atiende 1,000 solicitudes generadas aleatoriamente.

### Algoritmos implementados
1. **FCFS (First-Come, First-Served)**: atiende las solicitudes en el orden en que llegan.
2. **SCAN (algoritmo del ascensor)**: la cabeza del disco se mueve en una dirección, atiende las solicitudes de ese recorrido y luego invierte la dirección.
3. **C-SCAN (SCAN circular)**: similar a SCAN, pero solo atiende solicitudes en una dirección. Al llegar al extremo, regresa al inicio sin atender solicitudes durante el retorno.

### Características principales
- Genera 1,000 solicitudes aleatorias de cilindros.
- Usa la semilla fija `2023` para que los resultados sean reproducibles.
- Acepta la posición inicial de la cabeza como argumento de línea de comandos o de forma interactiva.
- SCAN usa por defecto la dirección `UP`.
- Calcula e informa el movimiento total de la cabeza para cada algoritmo.
- Muestra la secuencia de solicitudes atendidas para verificación.
- Exporta un resumen de resultados a un archivo CSV.

## 4. Estructura del proyecto

El proyecto está organizado en los siguientes directorios y archivos:

```
FinalTerm-Disk-Simulator/
├── include/                # Archivos de encabezado
│   ├── DiskDrive.h
│   ├── DiskScheduler.h
│   ├── ScheduleResult.h
│   └── Utils.h
├── src/                    # Archivos fuente
│   ├── DiskDrive.cpp
│   ├── DiskScheduler.cpp
│   ├── main.cpp
│   └── Utils.cpp
├── data/                   # Datos de salida
│   └── results.csv
└── README.md               # Este archivo
```

## 5. Compilación

**Requisitos previos**:
- Un compilador compatible con C++17, por ejemplo `g++`.

**Pasos de compilación**:
1. Abre una terminal en la raíz del proyecto.
2. Ejecuta los siguientes comandos para compilar el proyecto en Windows:
   ```powershell
   g++ -Iinclude -c src/DiskDrive.cpp -o obj/DiskDrive.o
   g++ -Iinclude -c src/DiskScheduler.cpp -o obj/DiskScheduler.o
   g++ -Iinclude -c src/Utils.cpp -o obj/Utils.o
   g++ -Iinclude -c src/main.cpp -o obj/main.o
   g++ obj/*.o -o bin/disksim.exe
   ```
3. El ejecutable se generará en `bin/disksim.exe`.

## 6. Ejecución

Puedes ejecutar el simulador de dos maneras:

### Modo interactivo
Ejecuta el programa sin argumentos para ver un menú. El comando cambia según el sistema operativo.

**En Windows (PowerShell):**
```powershell
.\bin\disksim.exe
```

**En Linux/macOS:**
```bash
./bin/disksim
```

El programa pedirá elegir qué simulación ejecutar.

### Argumento de línea de comandos
Puedes proporcionar la posición inicial de la cabeza para la simulación de planificación de disco como argumento.

**En Windows (PowerShell):**
```powershell
.\bin\disksim.exe [posicion_inicial_cabeza]
```

Ejemplo:
```powershell
.\bin\disksim.exe 1234
```

**En Linux/macOS:**
```bash
./bin/disksim [posicion_inicial_cabeza]
```

Ejemplo:
```bash
./bin/disksim 1234
```

Si se proporciona un argumento, el menú seguirá apareciendo, pero la simulación de planificación usará esa posición si se selecciona.

La dirección inicial de SCAN es `UP` por defecto. Si quieres cambiarla, debes modificar la creación de `DiskScheduler` en `src/main.cpp` y pasar `DiskScheduler::Direction::DOWN`, o cambiar el valor por defecto en `include/DiskScheduler.h`.

## 7. Formato de entrada y salida

### Entrada
- **Geometría del disco**: el programa solicitará el tamaño del disco en GB y el número de pistas o de platos.
- **Planificación de disco**: el programa pedirá la posición inicial de la cabeza si no se proporciona por línea de comandos.

### Salida
- **Consola**: los resultados de las simulaciones se imprimen en consola.
- **Archivo CSV**: los resultados de la planificación de disco, incluyendo el movimiento total y el promedio por algoritmo, se guardan en `data/results.csv`.

## 8. Explicación de los algoritmos

- **FCFS**: procesa las solicitudes en el mismo orden en que fueron recibidas.
- **SCAN**: atiende las solicitudes en una dirección y luego invierte el sentido.
- **C-SCAN**: atiende solicitudes en una sola dirección y, al llegar al final, regresa al inicio para continuar.

## 9. Ejemplos de salida

### Ejemplo de entrada y salida

**Problema 1**
```
Entrada:
  Tamaño del disco: 10
  Opción: t
  Número de pistas: 128

Salida:
  Resumen de geometría con tamaño, sectores, pistas y platos calculados.
```

**Problema 2**
```
Entrada:
  Posición inicial de la cabeza: 1234

Salida:
  Movimiento total y promedio para FCFS, SCAN y C-SCAN.
  Archivo generado: data/results.csv
```

### Simulación de DiskDrive
```
--- Resumen de geometría de la unidad de disco ---
Tamano del disco: 10 GB
Tamano del sector: 512 bytes
Total de sectores: 19531250
Pistas calculadas (por plato): 128
Platos calculados: 60
-----------------------------------------------
```

### Simulación de DiskScheduler
```
--- Algoritmo: FCFS ---
Orden de atencion y movimiento:
  Solicitud: 1632, Movimiento: 399
  Solicitud: 4815, Movimiento: 3183
  ...
Movimiento total de la cabeza: 1956381 cilindros
Movimiento promedio de la cabeza: 1956.38 cilindros
------------------------------------
```

## 10. Suposiciones y limitaciones

- **Geometría del disco**: la fórmula `sectores * pistas * platos = total_sectores` es una simplificación. En este modelo se asume un número fijo de sectores por pista (256) para que el cálculo sea determinista. Los HDD reales tienen una estructura más compleja.
- **Planificación**: la simulación no considera latencia en cada rotacion ni tiempo de transferencia de datos; solo se enfoca en el tiempo de búsqueda, es decir, el movimiento de la cabeza.

## 11. Autor

- **Autor**: Miguel Angel Padilla Rosero
- **Curso**: Sistemas Operativos
- **Asignación**: Parcial final del curso

Este proyecto fue desarrollado como solución al parcial final.
