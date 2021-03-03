<div id="content">

# Systemy Operacyjne 1: Projekt Gra zwiedzanie pokoi

<div id="table-of-contents">

## Table of Contents

<div id="text-table-of-contents">

*   [1\. Zarys projektu](#org104313b)
*   [2\. Uruchomienie programu](#orgd000240)
*   [3\. Formaty plików](#org3ac4cef)
*   [4\. Komendy gracza](#orgbbb67b8)
    *   [4.1\. Menu główne](#org8cc5d3c)
    *   [4.2\. W trakcie trwania gry](#orgee18e14)
*   [5\. Wyszukiwanie proponowanej ścieżki](#orgc69bcff)
*   [6\. Uruchomienie nowej gry](#orgfb78749)
*   [7\. Autozapis](#org54a6e24)
*   [8\. Reakcje na sygnały](#orgbb76148)

</div>

</div>

<div id="outline-container-org104313b" class="outline-2">

## <span class="section-number-2">1</span> Zarys projektu

<div class="outline-text-2" id="text-1">

Celem projektu jest napisanie gry, w której gracz porządkuje przedmioty w pomieszczeniach.

Gra odbywa się na mapie, która jest grafem pomieszczeń. W każdym pomieszczeniu znajdują się nie więcej niż dwa przedmioty. Gracz znajduje się w jednym z pomieszczeń, początkowo losowym i nie posiada żadnych przedmiotów. Gracz może wykonać następujące akcje:

*   przejść do dowolnego pomieszczenia, które sąsiaduje z bieżącym
*   podnieść dowolny przedmiot znajdujący się w pomieszczeniu, w którym przebywa, pod warunkiem że ma ze sobą nie więcej niż jeden przedmiot (nie można przenosić więcej niż dwu przedmiotów na raz)
*   położyć dowolny przedmiot, który ma przy sobie w bieżącym pomieszczeniu, pod warunkiem, że znajduje się tu nie więcej niż jeden przedmiot.

Każdy przedmiot ma swój unikatowy numer oraz pomieszczenie do którego jest przypisany (to NIE jest pomieszczenie, gdzie się początkowo znajduje). Celem gry jest przeniesienie wszystkich przedmiotów do pomieszczeń, do których są przypisane, wykonując przy tym jak najmniejszą liczbę ruchów.

Nie jest narzucone w jaki sposób mają być identyfikowane pomieszczenia i przedmioty, można zaproponować własne podejście. Rozsądnym wydaje się, żeby były to kolejne liczby naturalne.

Pewne operacje muszą odbywać w oddzielnych wątkach i jest to zaznaczone w treści zadania. Nie można z tych wątków zrezygnować. Można jednak tworzyć wątki, których treść zadania nie narzuca, jeśli jest taka potrzeba.

</div>

</div>

<div id="outline-container-orgd000240" class="outline-2">

## <span class="section-number-2">2</span> Uruchomienie programu

<div class="outline-text-2" id="text-2">

Program uruchamiany jest z następującymi opcjami:

<dl class="org-dl">

<dt>-b backup-path</dt>

<dd>gdzie backup-path to ścieżka do pliku. Ścieżka do pliku, gdzie będzie przechowywany autozapis gry. Opcja jest nieobowiązkowa. Jeśli nie jest podana, to w zamian użyta jest wartość zmiennej środowiskowej `$GAME_AUTOSAVE`. Jeśli ta zmienna nie jest ustawiona, to używany jest plik `.game-autosave` w katalogu domowym.</dd>

</dl>

</div>

</div>

<div id="outline-container-org3ac4cef" class="outline-2">

## <span class="section-number-2">3</span> Formaty plików

<div class="outline-text-2" id="text-3">

Format zapisu pliku mapy i pliku gry należy zaprojektować samodzielnie. Należy unikać zbędnych konwersji typów na napisy, jeśli nie jest to absolutnie niezbędne. Format pliku przechowujący stan gry powinien mieścić w sobie w wszystkie potrzebne informacje, to znaczy: kopię mapy, pozycje przedmiotów, pozycję gracza i przedmioty trzymane przez gracza.

Do operacji na pikach należy zastosować niskopoziomowe funkcje IO POSIX. Do operacji na stdin, out, err można użyć buforowanych funkcji ze standardowego C.

</div>

</div>

<div id="outline-container-orgbbb67b8" class="outline-2">

## <span class="section-number-2">4</span> Komendy gracza

<div class="outline-text-2" id="text-4">

Program oczekuje na komendy w dwóch trybach: trybie menu głównego i trybie gry. Początkowo program oczekuje na komendy w trybie menu głównego.

</div>

<div id="outline-container-org8cc5d3c" class="outline-3">

### <span class="section-number-3">4.1</span> Menu główne

<div class="outline-text-3" id="text-4-1">

Menu główne udostępnia następujące komendy:

<dl class="org-dl">

<dt>map-from-dir-tree śckieżka-d ścieżka-f</dt>

<dd>generuje mapę odwzorowującą drzewo katalogów od **ścieżka-d** w dół, gdzie każdy katalog to pomieszczenie, a przejścia pomiędzy pomieszczeniami są pomiędzy katalogiem nadrzędnym, a katalogami w środku. Wynikowa mapa zapisywana jest do pliku **ścieżka-f**.</dd>

<dt>generate-random-map n ścieżka</dt>

<dd>generuje losową mapę złożoną z **n** pomieszczeń, pomieszczenia są połączone w sposób losowy. Sposób losowania połączeń należy zaproponować samodzielnie. Wynikowa mapa jest zapisywana do pliku **ścieżka**. Mapa powinna być grafem spójnym.</dd>

<dt>start-game ścieżka</dt>

<dd>uruchamia nową grę na mapie z pliku **sciezka**</dd>

<dt>load-game ścieżka</dt>

<dd>ładuje stan gry z pliku **ścieżka** (zarówno mapa, jak i stan przedmiotów i gracza).</dd>

<dt>exit</dt>

<dd>wychodzi z programu</dd>

</dl>

</div>

</div>

<div id="outline-container-orgee18e14" class="outline-3">

### <span class="section-number-3">4.2</span> W trakcie trwania gry

<div class="outline-text-3" id="text-4-2">

<dl class="org-dl">

<dt>move-to x</dt>

<dd>gracz przechodzi o pomieszczenia x, o ile to możliwe. Jeśli pomieszczenie x nie sąsiaduje z bieżącym, wyświetlany jest komunikat.</dd>

<dt>pick-up y</dt>

<dd>gracz podnosi przedmiot **y**, o ile dopuszczają to zasady gry, w przeciwnym wypadku wyświetlany jest odpowiedni komunikat.</dd>

<dt>drop z</dt>

<dd>gracz odkłada przedmiot **z**, o ile jest to zgodne z zasadami gry, w przeciwnym wypadku wyświetlany jest odpowiedni komunikat.</dd>

<dt>save sciezka</dt>

<dd>zapisuje bieżący stan gry w pliku podanym jako argument.</dd>

<dt>find-path k x</dt>

<dd>Wyszukuje w miarę krótką ściekę do pomieszczenia **x** z użyciem **k** wątków. Opis metody poszukiwania przedstawiony jest dalej.</dd>

<dt>quit</dt>

<dd>kończy wszystkie wątki związane z grą. Wychodzi z gry do menu głównego. _Uwaga! Wątek autozapisu należy zakończyć tak, aby zagwarantować, że plik autozapisu nie będzie uszkodzony._</dd>

</dl>

Wszystkie komendy są realizowane w sposób blokujący, to znaczy, nawet jeśli zadanie odbywa się w oddzielnym wątku, to program nie przetwarza kolejnych komend zanim nie skończy poprzedniej.

</div>

</div>

</div>

<div id="outline-container-orgc69bcff" class="outline-2">

## <span class="section-number-2">5</span> Wyszukiwanie proponowanej ścieżki

<div class="outline-text-2" id="text-5">

Z racji tego, że rozsądne algorytmy do przeszukiwania grafów pojawiają się dopiero na 4\. semestrze, należy skorzystać z metody nierozsądnej:

1.  tworzymy **k** wątków
2.  każdy z wątków poszukuje trasy rozpoczynając od bieżącego wierzchołka i w pętli przechodzi do losowego sąsiada. Pętla kończy się albo po dojściu do **x** albo po limicie 1000 kroków.
3.  Czekamy na zakończenie wątków.
4.  Użytkownik otrzymuje odpowiedź będącą tą trasą ze znalezionych, która ma najmniej kroków. Jeśli żaden wątek nie doszedł do **x**, wyświetlany jest komunikat, że trasy nie znaleziono.

</div>

</div>

<div id="outline-container-orgfb78749" class="outline-2">

## <span class="section-number-2">6</span> Uruchomienie nowej gry

<div class="outline-text-2" id="text-6">

Uruchomienie nowej gry polega na: wczytaniu mapy z pliku. Niech **n** będzie liczbą pomieszczeń na mapie. Następnie do mapy dodawane jest \(floor(3n/2)\) przedmiotów. Każdy przedmiot jest umieszczany w losowym pomieszczeniu, tak aby nie przekroczyć limitu 2\. Dla każdego przedmiotu losowane jest również pomieszczenie do którego jest przypisany, również tak, aby nie przekroczyć limitu 2 na pomieszczenie. Gracz jest umieszczany w losowym pomieszczeniu i nie ma żadnego przedmiotu.

</div>

</div>

<div id="outline-container-org54a6e24" class="outline-2">

## <span class="section-number-2">7</span> Autozapis

<div class="outline-text-2" id="text-7">

W momencie rozpoczęcia gry uruchamiany jest wątek autozapisu. Jeśli od ostatniego zapisu gry (bądź to autozapisu bądź komendy save) minęło więcej niż 60 sekund, to bieżący stan gry zapisywany jest do pliku **backup-path**. W trakcie autozapisu gra nie przyjmuje żadnych komend od gracza i wyświetlany jest odpowiedni komunikat.

</div>

</div>

<div id="outline-container-orgbb76148" class="outline-2">

## <span class="section-number-2">8</span> Reakcje na sygnały

<div class="outline-text-2" id="text-8">

Po uruchomieniu gry startowany jest również wątek, który nasłuchuje na sygnał SIGUSR1\. W reakcji na sygnał SIGUSR1 wątek zamienia miejscami dwa losowo wybrane przedmiot w grze i wypisuje odpowiedni komunikat.

</div>

</div>

</div>

<div id="postamble" class="status">

Created: 2020-12-07 pon 12:23

[Validate](http://validator.w3.org/check?uri=referer)

</div>
