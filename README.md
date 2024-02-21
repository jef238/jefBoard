# jefBoard
## Cos'è

JefBoard è una piattaforma hardware a basso costo basata sul microcontroller Attiny2313 della ATMEL, integra inoltre, la predisposizione per l'inserimento di una scheda WiFI ESP-01 (Opzionale).
JefBoard integra anche il connettore di programmazione per l'ISP dell'Attiny2313.
JefBoard espone tutti i pin dell'Attiny2313 per il loro utilizzo.
JefBoard permette la realizzazione di applicazioni WiFi ready a basso costo senza di fatto predisporre la circuitazione necessaria ad alimentare ed interfacciare tramite connessione seriale l'Attiny2313 ed il modulo ESP-01.
JefBoard può essere assemblata anche senza l'ESP-01 e relativi componenti di alimentazione se non necessari abbassando ulteriormente il costo.
JeBoard è una scheda di piccole dimensioni 00x00.
         
Cosa non è

Non è una piattaforma che integra strumenti software quali IDE come Arduino (almeno per il momento...) E' pertanto necessario utilizzare i tool di ATMEL (vedi sezione ->Programmazione Attiny2313) 
ed è caldamente consigliato utilizzare il firmware NodeMCU sul modulo ESP-01 (vedi sezione ->Flash nodeMCU su ESP-01). 

Funzionalità base

Il firmware di base di JefBoard (vedi sezione -> Firmware di base) mette subito a disposizione le seguenti funzionalità:

. Interfaccia WIFI con DHCP server e server con porta di ascolto xxxx per l'invio dei comandi standard

. Gestione degli output dell'Attiny2313 tramite comandi standard (vedi sezione -> Utilizzo del firmware di base)

. Gestione di input (vedi sezione -> Utilizzo del firmware di base)
