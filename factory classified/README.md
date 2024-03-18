# Week 3 Factory
---
CPSE2 Herkansing 10/03/2024 - Opdracht 3 - Luke Tenback
Dit programma is een BMPTK programma, je runt het dus met `bmptk-make run`

Om dit programma te gebruiken moet je in objects.txt het type object wat je op het scherm wilt zien, gevolgd door de positie hiervan.

Voor de foto zet je hierna neer hoe het bestand van de foto heet, vervolgens de groote van de foto.
Voor een rechthoek zet je neer waar je de tweede hoek wilt hebben en de kleur.
Voor een cirkel zet je neer welke diameter deze heeft en dan de kleur.
En dan als laatst heb je ook nog keuze uit een lijn waarvoor je de end coördinaten neerzet en een kleur.

Voorbeeld:
```cpp
picture 338 322 my_picture.png 100 100
circle 20 20 100 yellow
rectangle 262 20 356 234 red
line 153 279 203 450 blue
```

Zodra het programma runt kun je met de muis objecten vastpakken en verplatens, vervolgens weer loslaten door de muisknop los te laten.