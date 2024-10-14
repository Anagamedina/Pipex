
# Mejorando el Testeo de Pipex

Para mejorar tus pruebas y diagnóstico en tu proyecto Pipex, se recomienda evaluar diferentes escenarios, que involucran casos con archivos inexistentes, permisos, comandos no válidos, y salidas esperadas. A continuación se muestran varios escenarios de prueba que puedes incluir.

## Casos de Prueba Propuestos para Pipex

### 1. Archivo de entrada no existe:
- Si el archivo de entrada (`infile`) no existe, tu programa debe devolver un error.
- Ejemplo de prueba:
    ```bash
    ./pipex nonexistent_file "grep texto" "wc -w" outfile
    ```

    - Resultado esperado: 
    ```bash
    Error: Cannot open INPUT file: No such file or directory
    ```

### 2. Archivo de salida sin permisos de escritura:
- Si el archivo de salida (`outfile`) existe pero no tiene permisos de escritura, tu programa debe devolver un error.
- Ejemplo de prueba:
    ```bash
    chmod 444 outfile  # Quita permisos de escritura
    ./pipex infile "ls -l" "wc -l" outfile
    ```

    - Resultado esperado:
    ```bash
    Error: Cannot open OUTPUT file: Permission denied
    ```

### 3. Comando no encontrado:
- Si uno de los comandos pasados no se encuentra en el sistema o no tiene permisos de ejecución, tu programa debe devolver un error.
- Ejemplo de prueba:
    ```bash
    ./pipex infile "./script.sh" "wc -l" outfile
    ```

    - Resultado esperado:
    ```bash
    Error: Command not found: No such file or directory
    ```

### 4. Simular el mismo escenario en bash para comparar resultados:
- Para verificar la salida de tu programa, puedes ejecutar el mismo comando en bash y luego comparar los archivos de salida.
- Ejemplo de comparación:
    ```bash
    < infile_bash grep texto | wc -w > outfile_bash
    ./pipex infile "grep texto" "wc -w" outfile
    diff outfile outfile_bash
    ```

    - El comando `diff` debe devolver una salida vacía si ambos archivos son iguales.

## Casos de Permisos:

- Verifica y ajusta los permisos de los archivos de entrada y salida.
- Por ejemplo, si deseas probar archivos con permisos restringidos:
    ```bash
    chmod 000 infile  # Sin permisos de lectura
    ./pipex infile "ls -l" "wc -l" outfile
    ```

    - Resultado esperado:
    ```bash
    Error: Cannot open INPUT file: Permission denied
    ```

- Revisa los permisos actuales con:
    ```bash
    ls -l infile outfile
    ```

## Resultados y Permisos en Detalle:

- Los permisos de los archivos en formato octal:
  - `0644`: El propietario tiene permiso de lectura y escritura, mientras que el grupo y otros solo tienen permiso de lectura.
  - `chmod 644 outfile` asegurará que tu archivo de salida solo pueda ser escrito por el propietario.

    ```bash
    # Archivo con permisos 0644:
    # -rw-r--r-- 1 usuario grupo  tamaño fecha outfile
    ```

## Sugerencia Adicional:

- Considera capturar los errores estándar y redirigirlos a un archivo o variable para facilitar el debugging.
    - Ejemplo:
        ```bash
        ./pipex infile "grep texto" "wc -w" outfile 2> error_log
        ```

        Esto puede ayudarte a verificar errores sin interrumpir el flujo de salida estándar.

## Conclusión:

Estos casos de prueba asegurarán que tu proyecto Pipex maneje correctamente diferentes tipos de errores comunes como archivos inexistentes, permisos insuficientes y comandos no válidos. Asegúrate de comparar siempre los resultados de `pipex` con los de bash para validar que el comportamiento sea el esperado.
