# 🕹️ Tetris

Una implementación del clásico juego 'Tetris' diseñado como proyecto de desarrollo en lenguaje C y optimizado para ejecución local.

---

## 🚀 Requisitos Previos

Antes de comenzar, asegúrate de tener instalado lo siguiente en tu Windows:

* La versión portable del IDE Code::Blocks 20.03 con MinGW incluido.
* La librería gráfica GBT descargada y preparada como se indica en la fuía de instalación y configuración.

** ⚠️ Aclaraciones del sistema operativo **

El juego fue diseñado y desarrollado para correr en sistemas operativos Windows, no está asegurado su correcta ejecución en otros entornos.

---

## 📦 Instalación y Configuración

📍 Sigue estos pasos para poder jugar:

### 1. Descargar e instalar la versión portable del IDE Code::Blocks 20.03 (con MinGW incluido), ingrese al link que dejamos debajo.
	
Link 🌎:

### 2. Viajar al repositorio del **tetris** que dejamos debajo y descargar todos los archivos.

Link 🌎: https://github.com/Nahuel1024/Tetris.git

### 3. Abra el IDE y seleccione la opción **Open an existing project** que le aparecerá en la hoja de inicio (si no logra verlo, simplemente vaya a la pestaña **File** y seleccione **Open**). Hecho esto, busque los archivos del juego donde los haya descargado y seleccione el archivo llamado **Tetris**.

### 4. Nótese que se le mostrarán por pantalla todos los archivos que dan vida al juego. Ahora pasemos a configurar la librería gráfica, vaya a la pestaña **Project** y seleccione **Build Options**.

### 5. Dentro de la ventana de configuración abierta, haga clic en **Linker settings**. Luego, escriba *-lgbt* dentro del recuadro **Other linker options**.

### 6. Fíjese que a la derecha de **Linker settings**, se encuentra **Search directories**, haga clic en esa opción. En este apartado haremos las últimas dos configuraciones:

	### 6.1. Fíjese que ahora está en la sección **Compiler**, dentro de **Search directories**. Haga clic en **Add** y reemplace la ruta que está escrita por *include*, luego confirme los cambios oprimiendo en **OK**.

	### 6.2. Ahora, haga clic en **Linker**, que se encuentra al lado de **Compiler**. Haga clic en **Add** y reeemplace todo lo que está escrito por *lib*, luego confirme los cambios oprimiendo en **OK**.