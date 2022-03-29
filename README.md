# Organizzazione Cartelle  
Come potete vedere ho scritto entrambi i software presenti in [DIANA-Recruitment](https://github.com/team-diana/DIANA-Recruitment).  
Le cartelle sono organizzare nel seguente modo:
* Probe_Tool_1
  * C, contiene la prima parte dell'esercizio Probe Tool scritta in C
  * Java, lo stesso ma in Java
* Probe_Tool_2, contiene la seconda parte dell'esercizio Probe Tool scritta in C
* Service_Tool, l'esercizio Service Tool in C

# Probe Tool  
Per il primo esercizio come intuibile ho scritto due versioni, una in C ed una in Java.  
## C  
Ho cercato di mantenere una sorta di divisione tra i diversi tipi di dati andando a creare degli ADT.  
Prevalentemente l'ho fatto poichè l'esercizio a mio parere si prestava piuttosto bene alla programmazione ad oggetti, in particolar modo la prima parte, e quindi volevo iniziare già a 'definire' quelle che sarebbero poi state le classi di un successivo tentativo in Java.  
## Java  
Nulla di più rispetto alla versione in C. Siccome mentre scrivevo la prima parte pensavo a quanto sarebbe stato più facile implementarla a oggetti ho deciso di provarci.  
Comunque non ci ho speso troppo tempo ed in effetti non è chissà quanto articolata.

# Service Tool
Ad essere onesti penso di non aver pienamente compreso la richiesta della traccia; ho comunque provato ad implementare il programma così come l'ho inteso.  
Nonostante ho l'impressione di aver un tantino esagerato il risultato finale mi piaceva ed ho quindi deciso di caricare anche questo.  
### P.S
Siccome ho utilizzato la libreria _pthread.h_ è necessario aggiungere -lpthread nella compilazione:  
```
gcc -o Service_Tool.exe Service_Tool.c -lpthread
```
