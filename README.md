# 🧘 Philosophers

**Philosophers** es una implementación del clásico problema de los *filósofos comensales*, un ejercicio fundamental en concurrencia. El objetivo es gestionar múltiples hilos (o procesos) que comparten recursos (tenedores) sin caer en condiciones de carrera (*race conditions*) ni en *deadlocks*.

Este proyecto pone a prueba la habilidad de trabajar con **multithreading**, sincronización con **mutexes** y temporización precisa, además de asegurar la integridad de los datos en situaciones de alta concurrencia.

## 🎯 Objetivos del proyecto

- Simular el comportamiento de múltiples filósofos que piensan, comen y duermen
- Garantizar la sincronización al compartir recursos (tenedores)
- Evitar condiciones de carrera y bloqueos mutuos
- Implementar un sistema de control para detectar si un filósofo muere de hambre

## 🚀 Funcionalidades principales

- ✅ Creación de múltiples **threads** para cada filósofo
- ✅ Sincronización usando **mutexes** para los tenedores
- ✅ Control de tiempos con precisión milisegundo
- ✅ Detección de muerte de un filósofo si excede `time_to_die` sin comer
- ✅ Control del número de veces que cada filósofo debe comer (opcional)
- ✅ Mensajes sincronizados para visualizar la actividad (pensando, comiendo, durmiendo, muerto)

## 🧠 Tecnologías y conceptos utilizados

- Lenguaje C
- **Pthreads** y sincronización con `pthread_mutex_t`
- Temporización con `gettimeofday` y `usleep`
- Estructuras de datos para la gestión de estados y tiempos
- Gestión de concurrencia segura y eficiente
- Control de errores y limpieza de recursos
