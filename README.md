# Fundamentos y Arquitectura de Motores de Videojuegos 2D en C++
### Luis Mario Solares Ramos 321057110
### Username Github: lmSolares

#### Error diagonal

#### Ejecución 
Se muestra la ejecución del programa

![](media/ejecucion.mp4)

#### Commits
Para ver los commmits que se hicieron se puede ver el archivo *log.txt* donde se encuentra la salida del comando

```bash
git log
```

#### Ejercicio opcional
Hice el ejercicio opcional de confinar al personaje en la ventana, mi lógica fue que dentro de la función *PhysicsUpdate*
(donde se actualiza la posición) podemos verificar si al calcular la nueva posición está queda fuera de los límites
que establecemos, entonces la coordenada donde se saldría no la actualizamos y la mantenemos en el límite, i.e si al 
calcular la nueva posición en *x* es menor a *0*, entonces *x* se mantendrá en *0*. Pasa lo mismo en los cuatro límites
que se establecieron. Se adjunta la demostración del resultado: 

![](media/limites.mp4)
