# 🕹️ Tetris

Una implementación del clásico juego 'Tetris' diseñado como proyecto de desarrollo en lenguaje C y para ejecución local.

---

## 🚀 Requisitos Previos

Antes de comenzar, para garantizarle una grata experiencia en el uso del juego, asegúrese de tener en su Windows:

* La versión portable del IDE Code::Blocks 20.03 con MinGW incluido.
* La descarga del repositorio original.
* La descarga de la biblioteca gráfica GBT.

Siga la *Guía de Instalación y Configuración* para preparar la experiencia.

---

## ⚠️ Aclaraciones del sistema operativo

El juego fue diseñado y desarrollado para correr en sistemas operativos Windows, no está asegurado su correcta ejecución en otros entornos.

--- 

## 📦 Instalación y Configuración

📍 Sigue estos pasos para poder jugar:

1. Descargar e instalar la versión del IDE Code::Blocks 20.03 (con MinGW incluido).

    1. Ingrese al link 🌎: https://sourceforge.net/projects/codeblocks/files/Binaries/20.03
     
    2. Ingrese a la carpeta **Windows** y descargue el comprimido nombrado *codeblocks-20.03mingw-nosetup.zip*.
    
    3. Cuando se haya descargado, cree una carpeta donde le sea más conveniente y proceda a descomprimir el zip descargado en ella.
    
    4. Siempre que quiera abrir el IDE, hágalo mediante el archivo llamado **CbLauncher.exe** en la carpeta donde alojó los archivos 	descomprimidos, no le podemos asegurar el correcto funcionamiento del IDE si lo hace de otra manera.

2. Descargar el juego.

    1. Ingrese al link 🌎: https://github.com/Nahuel1024/Tetris.git

    2. Oprima el botón verde **<> Code**.

    3. Oprima la opción **Download**, que se encuentra debajo en la parte inferior izquierda. Seguido, comenzará la descarga.

3. Descargar la biblioteca gráfica **GBT** y ubicarla en los archivos del juego.

    1. Ingrese al link 🌎: https://gitlab.com/RodrigoMaranzana/libgbt-dist

    2. Verá una tabla con las carpetas de la libería, haga clic en la que incluye la palabra *release* en su nombre.

    3. Haga clic en el botón **Código** y descargue el **código fuente** en formato **zip**.

    4. Una vez descargada, *extraiga* los archivos en la carpeta donde guarda el proyecto (reemplace los que ya existan).

    5. Ingrese a la carpeta del proyecto (donde descomprimió los archivos de la biblioteca GBT), luego a la carpeta **Bin**, verá un archivo llamado **gbt.dll**.

    6. Si no existe, cree una carpeta y nombrela *Debug* (sin los asteriscos y con la primera en mayúscula). Por último, mueva el archivo **gbt.dll** a esta carpeta.

4. Abra el IDE y seleccione la opción **Open an existing project** que le aparecerá en la hoja de inicio (si no logra verlo, simplemente vaya a la pestaña **File** y seleccione **Open**). Hecho esto, busque los archivos del juego donde los haya descargado y seleccione el archivo llamado **Tetris**.

5. Nótese que se le mostrarán por pantalla todos los archivos que dan vida al juego. Ahora pasemos a configurar la librería gráfica, vaya a la pestaña **Project** y seleccione **Build Options**.

6. Dentro de la ventana de configuración abierta, haga clic en **Linker settings**. Luego, escriba *-lgbt* dentro del recuadro **Other linker options**.

7. Fíjese que a la derecha de **Linker settings**, se encuentra **Search directories**, haga clic en esa opción. En este apartado haremos las últimas dos configuraciones:

    1. Fíjese que ahora está en la sección **Compiler**, dentro de **Search directories**. Haga clic en **Add** y reemplace la ruta que está escrita por *include*, luego confirme los cambios oprimiendo en **OK**.

    2. Ahora, haga clic en **Linker**, que se encuentra al lado de **Compiler**. Haga clic en **Add** y reeemplace todo lo que está escrito por *lib*, luego confirme los cambios oprimiendo en **OK**.