EKRAN PODGL�DU:
<preview_screen.png>
<preview_screen2.png>

Podgl�d widoku u�ytkownika z kamery. Zielona i niebieska ramka to ramki kalibracyjne - u�ytkownik musi trzyma� praw� r�ke tak, aby sk�ra jego d�oni wype�nia�a niebiesk� ramk� w ca�o�ci. Na tej podstawie s� wyznaczane parametry pocz�tkowe dla algorytmu camshift.

Lewa r�ka u�ytkownika musi znajdowa� si� wewn�trz zielonej ramki. Zaci�ni�cie pi�ci (lub usuni�cie r�ki poza obszar ramki) a nast�pnie powr�t do pozycji pocz�tkowej rozpoznawane jest jako gest aktywacji.

Czerwona elipsa pokazuje po�o�enie prawej r�ki (wynik �ledzenia algorytmu camshift).



EKRAN MENU:
<menu_screen.png>

Wizualizacja menu. U�ytkownik ruchami r�k mo�e nawigowa� po menu.



KONSOLA:
<console_screen.png>

W konsoli wy�wietlane s� pomocnicze informacje pozwalaj�ce �ledzi� przebieg programu. Wy�wietlane s� informacje o znalezionych gestach "GESTURE FOUND", numery gest�w mo�na por�wna� z nazwami sta�ych zdefiniowanych w pliku Gesture.hpp.

Dodatkowo pojawia si� informacja o sterowaniu maszyn� stan�w menu ("Keeper: ...") oraz efekt wykonywania kodu podpi�tego pod akcje menu - w obecnej wersji wypisuj�cego tylko na konsol� informacje o uruchamianej akcji ("Akcja: ...").


BACKPROJECTION:
<backprojection_screen.png>
<backprojection_screen2.png>
<backprojection_screen3.png>

Opis backprojection znajduje si� tutaj:
http://opencv.itseez.com/doc/tutorials/imgproc/histograms/back_projection/back_projection.html

Jest to wykorzystywane przez algorytm camshift (u nas �ledzenie prawej r�ki). Dodatkowo wyliczony backprojection u�ywamy do wykrywania lewej r�ki. Liczymy ilo�� dopasowanych punkt�w wewn�trz zielonego prostok�ta. Je�li spadnie poni�ej pewnego poziomu oznacza to, �e zmniejszy�o si� pole powierzchni r�ki (np. zosta�a zaci�ni�ta w pi��). Zar�wno �ledzenie r�ki jak i zaciskanie z punktu widzenia backprojection zosta�y pokazane na do��czonych obrazkach.