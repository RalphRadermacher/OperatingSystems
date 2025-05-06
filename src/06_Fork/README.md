# Aufgabe - Fork & Exec

Schreiben Sie ein C-Programm `fork.c`, das einen Kindprozess erzeugt, wobei der Elternprozess und der Kindprozess jeweils ihre Prozess-Id in der Standardausgabe ausgeben sollen.

Schreiben Sie zwei C-Pogramme `parent.c` und `child.c`. Das Programm `parent.c` soll als erstes Argument den Pfad des kompilierten Programms `child` und ggf. weitere Argumente übergeben bekommen und dann dieses Programm mit den weiteren Argumenten als Kindprozess starten. Das Programm `child` soll lediglich die Argumente der Kommandozeile in der Standausgabe ausgeben (siehe Aufgabe - Argumente).
