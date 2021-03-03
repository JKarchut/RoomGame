Systemy Operacyjne 1: Projekt Gra zwiedzanie pokoi


 <!--*/
  .title  { text-align: center;
             margin-bottom: .2em; }
  .subtitle { text-align: center;
              font-size: medium;
              font-weight: bold;
              margin-top:0; }
  .todo   { font-family: monospace; color: red; }
  .done   { font-family: monospace; color: green; }
  .priority { font-family: monospace; color: orange; }
  .tag    { background-color: #eee; font-family: monospace;
            padding: 2px; font-size: 80%; font-weight: normal; }
  .timestamp { color: #bebebe; }
  .timestamp-kwd { color: #5f9ea0; }
  .org-right  { margin-left: auto; margin-right: 0px;  text-align: right; }
  .org-left   { margin-left: 0px;  margin-right: auto; text-align: left; }
  .org-center { margin-left: auto; margin-right: auto; text-align: center; }
  .underline { text-decoration: underline; }
  #postamble p, #preamble p { font-size: 90%; margin: .2em; }
  p.verse { margin-left: 3%; }
  pre {
    border: 1px solid #ccc;
    box-shadow: 3px 3px 3px #eee;
    padding: 8pt;
    font-family: monospace;
    overflow: auto;
    margin: 1.2em;
  }
  pre.src {
    position: relative;
    overflow: visible;
    padding-top: 1.2em;
  }
  pre.src:before {
    display: none;
    position: absolute;
    background-color: white;
    top: -10px;
    right: 10px;
    padding: 3px;
    border: 1px solid black;
  }
  pre.src:hover:before { display: inline;}
  /* Languages per Org manual */
  pre.src-asymptote:before { content: 'Asymptote'; }
  pre.src-awk:before { content: 'Awk'; }
  pre.src-C:before { content: 'C'; }
  /* pre.src-C++ doesn't work in CSS */
  pre.src-clojure:before { content: 'Clojure'; }
  pre.src-css:before { content: 'CSS'; }
  pre.src-D:before { content: 'D'; }
  pre.src-ditaa:before { content: 'ditaa'; }
  pre.src-dot:before { content: 'Graphviz'; }
  pre.src-calc:before { content: 'Emacs Calc'; }
  pre.src-emacs-lisp:before { content: 'Emacs Lisp'; }
  pre.src-fortran:before { content: 'Fortran'; }
  pre.src-gnuplot:before { content: 'gnuplot'; }
  pre.src-haskell:before { content: 'Haskell'; }
  pre.src-hledger:before { content: 'hledger'; }
  pre.src-java:before { content: 'Java'; }
  pre.src-js:before { content: 'Javascript'; }
  pre.src-latex:before { content: 'LaTeX'; }
  pre.src-ledger:before { content: 'Ledger'; }
  pre.src-lisp:before { content: 'Lisp'; }
  pre.src-lilypond:before { content: 'Lilypond'; }
  pre.src-lua:before { content: 'Lua'; }
  pre.src-matlab:before { content: 'MATLAB'; }
  pre.src-mscgen:before { content: 'Mscgen'; }
  pre.src-ocaml:before { content: 'Objective Caml'; }
  pre.src-octave:before { content: 'Octave'; }
  pre.src-org:before { content: 'Org mode'; }
  pre.src-oz:before { content: 'OZ'; }
  pre.src-plantuml:before { content: 'Plantuml'; }
  pre.src-processing:before { content: 'Processing.js'; }
  pre.src-python:before { content: 'Python'; }
  pre.src-R:before { content: 'R'; }
  pre.src-ruby:before { content: 'Ruby'; }
  pre.src-sass:before { content: 'Sass'; }
  pre.src-scheme:before { content: 'Scheme'; }
  pre.src-screen:before { content: 'Gnu Screen'; }
  pre.src-sed:before { content: 'Sed'; }
  pre.src-sh:before { content: 'shell'; }
  pre.src-sql:before { content: 'SQL'; }
  pre.src-sqlite:before { content: 'SQLite'; }
  /* additional languages in org.el's org-babel-load-languages alist */
  pre.src-forth:before { content: 'Forth'; }
  pre.src-io:before { content: 'IO'; }
  pre.src-J:before { content: 'J'; }
  pre.src-makefile:before { content: 'Makefile'; }
  pre.src-maxima:before { content: 'Maxima'; }
  pre.src-perl:before { content: 'Perl'; }
  pre.src-picolisp:before { content: 'Pico Lisp'; }
  pre.src-scala:before { content: 'Scala'; }
  pre.src-shell:before { content: 'Shell Script'; }
  pre.src-ebnf2ps:before { content: 'ebfn2ps'; }
  /* additional language identifiers per "defun org-babel-execute"
       in ob-*.el */
  pre.src-cpp:before  { content: 'C++'; }
  pre.src-abc:before  { content: 'ABC'; }
  pre.src-coq:before  { content: 'Coq'; }
  pre.src-groovy:before  { content: 'Groovy'; }
  /* additional language identifiers from org-babel-shell-names in
     ob-shell.el: ob-shell is the only babel language using a lambda to put
     the execution function name together. */
  pre.src-bash:before  { content: 'bash'; }
  pre.src-csh:before  { content: 'csh'; }
  pre.src-ash:before  { content: 'ash'; }
  pre.src-dash:before  { content: 'dash'; }
  pre.src-ksh:before  { content: 'ksh'; }
  pre.src-mksh:before  { content: 'mksh'; }
  pre.src-posh:before  { content: 'posh'; }
  /* Additional Emacs modes also supported by the LaTeX listings package */
  pre.src-ada:before { content: 'Ada'; }
  pre.src-asm:before { content: 'Assembler'; }
  pre.src-caml:before { content: 'Caml'; }
  pre.src-delphi:before { content: 'Delphi'; }
  pre.src-html:before { content: 'HTML'; }
  pre.src-idl:before { content: 'IDL'; }
  pre.src-mercury:before { content: 'Mercury'; }
  pre.src-metapost:before { content: 'MetaPost'; }
  pre.src-modula-2:before { content: 'Modula-2'; }
  pre.src-pascal:before { content: 'Pascal'; }
  pre.src-ps:before { content: 'PostScript'; }
  pre.src-prolog:before { content: 'Prolog'; }
  pre.src-simula:before { content: 'Simula'; }
  pre.src-tcl:before { content: 'tcl'; }
  pre.src-tex:before { content: 'TeX'; }
  pre.src-plain-tex:before { content: 'Plain TeX'; }
  pre.src-verilog:before { content: 'Verilog'; }
  pre.src-vhdl:before { content: 'VHDL'; }
  pre.src-xml:before { content: 'XML'; }
  pre.src-nxml:before { content: 'XML'; }
  /* add a generic configuration mode; LaTeX export needs an additional
     (add-to-list 'org-latex-listings-langs '(conf " ")) in .emacs */
  pre.src-conf:before { content: 'Configuration File'; }

  table { border-collapse:collapse; }
  caption.t-above { caption-side: top; }
  caption.t-bottom { caption-side: bottom; }
  td, th { vertical-align:top;  }
  th.org-right  { text-align: center;  }
  th.org-left   { text-align: center;   }
  th.org-center { text-align: center; }
  td.org-right  { text-align: right;  }
  td.org-left   { text-align: left;   }
  td.org-center { text-align: center; }
  dt { font-weight: bold; }
  .footpara { display: inline; }
  .footdef  { margin-bottom: 1em; }
  .figure { padding: 1em; }
  .figure p { text-align: center; }
  .equation-container {
    display: table;
    text-align: center;
    width: 100%;
  }
  .equation {
    vertical-align: middle;
  }
  .equation-label {
    display: table-cell;
    text-align: right;
    vertical-align: middle;
  }
  .inlinetask {
    padding: 10px;
    border: 2px solid gray;
    margin: 10px;
    background: #ffffcc;
  }
  #org-div-home-and-up
   { text-align: right; font-size: 70%; white-space: nowrap; }
  textarea { overflow-x: auto; }
  .linenr { font-size: smaller }
  .code-highlighted { background-color: #ffff00; }
  .org-info-js_info-navigation { border-style: none; }
  #org-info-js_console-label
    { font-size: 10px; font-weight: bold; white-space: nowrap; }
  .org-info-js_search-highlight
    { background-color: #ffff00; color: #000000; font-weight: bold; }
  .org-svg { width: 90%; }
  /*]]>*/-->


/*
*/
<!--*/
 function CodeHighlightOn(elem, id)
 {
   var target = document.getElementById(id);
   if(null != target) {
     elem.cacheClassElem = elem.className;
     elem.cacheClassTarget = target.className;
     target.className = "code-highlighted";
     elem.className   = "code-highlighted";
   }
 }
 function CodeHighlightOff(elem, id)
 {
   var target = document.getElementById(id);
   if(elem.cacheClassElem)
     elem.className = elem.cacheClassElem;
   if(elem.cacheClassTarget)
     target.className = elem.cacheClassTarget;
 }
/*]]>*///-->


    MathJax.Hub.Config({
        displayAlign: "center",
        displayIndent: "0em",

        "HTML-CSS": { scale: 100,
                        linebreaks: { automatic: "false" },
                        webFont: "TeX"
                       },
        SVG: {scale: 100,
              linebreaks: { automatic: "false" },
              font: "TeX"},
        NativeMML: {scale: 100},
        TeX: { equationNumbers: {autoNumber: "AMS"},
               MultLineWidth: "85%",
               TagSide: "right",
               TagIndent: ".8em"
             }
});

Systemy Operacyjne 1: Projekt Gra zwiedzanie pokoi

## Table of Contents


* <a href="#org104313b">1. Zarys projektu</a>
* <a href="#orgd000240">2. Uruchomienie programu</a>
* <a href="#org3ac4cef">3. Formaty plików</a>
* <a href="#orgbbb67b8">4. Komendy gracza</a>
<ul>
* <a href="#org8cc5d3c">4.1. Menu główne</a>
* <a href="#orgee18e14">4.2. W trakcie trwania gry</a>


[5. Wyszukiwanie proponowanej ścieżki](#orgc69bcff)
[6. Uruchomienie nowej gry](#orgfb78749)
[7. Autozapis](#org54a6e24)
[8. Reakcje na sygnały](#orgbb76148)





1 Zarys projektu


Celem projektu jest napisanie gry, w której gracz porządkuje
przedmioty w pomieszczeniach. 



Gra odbywa się na mapie, która jest grafem pomieszczeń. W każdym
pomieszczeniu znajdują się nie więcej niż dwa przedmioty. Gracz
znajduje się w jednym z pomieszczeń, początkowo losowym i nie posiada
żadnych przedmiotów. Gracz może wykonać następujące akcje: 

<ul class="org-ul">
* przejść do dowolnego pomieszczenia, które sąsiaduje z bieżącym
* podnieść dowolny przedmiot znajdujący się w pomieszczeniu, w którym
przebywa, pod warunkiem że ma ze sobą nie więcej niż jeden
przedmiot (nie można przenosić więcej niż dwu przedmiotów na raz)
* położyć dowolny przedmiot, który ma przy sobie w bieżącym
pomieszczeniu, pod warunkiem, że znajduje się tu nie więcej niż
jeden przedmiot.



Każdy przedmiot ma swój unikatowy numer oraz pomieszczenie do
którego jest przypisany (to NIE jest pomieszczenie, gdzie się
początkowo znajduje). Celem gry jest przeniesienie wszystkich
przedmiotów do pomieszczeń, do których są przypisane, wykonując przy
tym jak najmniejszą liczbę ruchów.



Nie jest narzucone w jaki sposób mają być identyfikowane pomieszczenia
i przedmioty, można zaproponować własne podejście. Rozsądnym wydaje
się, żeby były to kolejne liczby naturalne. 



Pewne operacje muszą odbywać w oddzielnych wątkach i jest to
zaznaczone w treści zadania. Nie można z tych wątków
zrezygnować. Można jednak tworzyć wątki, których treść zadania nie
narzuca, jeśli jest taka potrzeba. 





2 Uruchomienie programu


Program uruchamiany jest z następującymi opcjami: 


-b backup-pathgdzie backup-path to ścieżka do pliku. Ścieżka do
pliku, gdzie będzie przechowywany autozapis gry. Opcja jest
nieobowiązkowa. Jeśli nie jest podana, to w zamian użyta jest
wartość zmiennej środowiskowej `$GAME_AUTOSAVE`. Jeśli ta zmienna
nie jest ustawiona, to używany jest plik `.game-autosave` w
katalogu domowym.





3 Formaty plików


Format zapisu pliku mapy i pliku gry należy zaprojektować
samodzielnie. Należy unikać zbędnych konwersji typów na napisy, jeśli
nie jest to absolutnie niezbędne. Format pliku przechowujący stan gry
powinien mieścić w sobie w wszystkie potrzebne informacje, to znaczy: 
kopię mapy, pozycje przedmiotów, pozycję gracza i przedmioty trzymane
przez gracza. 




Do operacji na pikach należy zastosować niskopoziomowe funkcje IO
POSIX. Do operacji na stdin, out, err można użyć buforowanych funkcji
ze standardowego C. 





4 Komendy gracza


Program oczekuje na komendy w dwóch trybach: trybie menu głównego i
trybie gry. Początkowo program oczekuje na komendy w trybie menu
głównego. 




4.1 Menu główne


Menu główne udostępnia następujące komendy:


map-from-dir-tree śckieżka-d ścieżka-fgeneruje mapę
odwzorowującą drzewo katalogów od ścieżka-d w dół, gdzie każdy
katalog to pomieszczenie, a przejścia pomiędzy pomieszczeniami są
pomiędzy katalogiem nadrzędnym, a katalogami w środku. Wynikowa
mapa zapisywana jest do pliku ścieżka-f.
generate-random-map n ścieżkageneruje losową mapę złożoną z
n pomieszczeń, pomieszczenia są połączone w sposób losowy. Sposób
losowania połączeń należy zaproponować samodzielnie. Wynikowa mapa
jest zapisywana do pliku ścieżka. Mapa powinna być grafem spójnym.
start-game ścieżkauruchamia nową grę na mapie z pliku
sciezka
load-game ścieżkaładuje stan gry z pliku ścieżka (zarówno
mapa, jak i stan przedmiotów i gracza).
exitwychodzi z programu





4.2 W trakcie trwania gry


move-to xgracz przechodzi o pomieszczenia x, o ile to
możliwe. Jeśli pomieszczenie x nie sąsiaduje z bieżącym,
wyświetlany jest komunikat.
pick-up ygracz podnosi przedmiot y, o ile dopuszczają to
zasady gry, w przeciwnym wypadku wyświetlany jest odpowiedni
komunikat.
drop zgracz odkłada przedmiot z, o ile jest  to zgodne z
zasadami gry, w przeciwnym wypadku wyświetlany jest odpowiedni
komunikat.
save sciezkazapisuje bieżący stan gry w pliku podanym jako
argument.
find-path k xWyszukuje w miarę krótką ściekę do pomieszczenia
x z użyciem k wątków. Opis metody poszukiwania przedstawiony
jest dalej.
quitkończy wszystkie wątki związane z grą. Wychodzi z gry do
menu głównego. _Uwaga! Wątek autozapisu należy zakończyć tak, aby
zagwarantować, że plik autozapisu nie będzie uszkodzony._



Wszystkie komendy są realizowane w sposób blokujący, to znaczy, nawet
jeśli zadanie odbywa się w oddzielnym wątku, to program nie przetwarza
kolejnych komend zanim nie skończy poprzedniej. 







5 Wyszukiwanie proponowanej ścieżki


Z racji tego, że rozsądne algorytmy do przeszukiwania grafów pojawiają
się dopiero na 4. semestrze, należy skorzystać z metody nierozsądnej: 

<ol class="org-ol">
1. tworzymy <b>k</b> wątków
1. każdy z wątków poszukuje trasy rozpoczynając od bieżącego
wierzchołka i w pętli przechodzi do losowego sąsiada. Pętla kończy
się albo po dojściu do <b>x</b> albo po limicie 1000 kroków.
1. Czekamy na zakończenie wątków.
1. Użytkownik otrzymuje odpowiedź będącą tą trasą ze znalezionych,
która ma najmniej kroków. Jeśli żaden wątek nie doszedł do <b>x</b>,
wyświetlany jest komunikat, że trasy nie znaleziono.





6 Uruchomienie nowej gry


Uruchomienie nowej gry polega na: wczytaniu mapy z pliku. Niech n
będzie liczbą pomieszczeń na mapie. Następnie do mapy dodawane jest 
\(floor(3n/2)\) przedmiotów. Każdy przedmiot jest umieszczany w losowym
pomieszczeniu, tak aby nie przekroczyć limitu 2. Dla każdego
przedmiotu losowane jest również pomieszczenie do którego jest
przypisany, również tak, aby nie przekroczyć limitu 2 na
pomieszczenie. Gracz jest umieszczany w losowym pomieszczeniu i nie ma
żadnego przedmiotu. 





7 Autozapis


W momencie rozpoczęcia gry uruchamiany jest wątek autozapisu. Jeśli od
ostatniego zapisu gry (bądź to autozapisu bądź komendy save) minęło
więcej niż 60 sekund, to bieżący stan gry zapisywany jest do pliku
backup-path. W trakcie autozapisu gra nie przyjmuje żadnych komend
od gracza i wyświetlany jest odpowiedni komunikat.





8 Reakcje na sygnały


Po uruchomieniu gry startowany jest również wątek, który nasłuchuje na
sygnał SIGUSR1. W reakcji na sygnał SIGUSR1 wątek zamienia miejscami
dwa losowo wybrane przedmiot w grze i wypisuje odpowiedni komunikat. 





Created: 2020-12-07 pon 12:23
[Validate](http://validator.w3.org/check?uri=referer)
