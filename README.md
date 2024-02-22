# jefBoard
![example](example.jpg)
## Cos'è

JefBoard è una piattaforma hardware a basso costo basata sul microcontroller Attiny2313 della ATMEL. Si presta allo sviluppo di applicazioni di varia natura e integra la predisposizione per la scheda WiFI ESP-01 (Opzionale) e il connettore per la programmazione ISP dell'Attiny2313.
Alcune caratteristiche:
- JefBoard espone tutti i pin dell'Attiny2313 per il loro utilizzo.
- JefBoard permette la realizzazione di applicazioni WiFi ready a basso costo senza di fatto predisporre la circuitazione necessaria ad alimentare ed interfacciare tramite connessione seriale l'Attiny2313 ed il modulo ESP-01.
- JefBoard può essere assemblata anche senza l'ESP-01 e relativi componenti di alimentazione se non necessari abbassando ulteriormente il costo.
- JeBoard è una scheda di piccole dimensioni 00x00.
         
## Cosa non è

Non è una piattaforma che integra strumenti software IDE come Arduino (almeno per il momento...). E' pertanto necessario utilizzare i tool di ATMEL (vedi sezione ->Appunti di programmazione Attiny2313) 
ed è caldamente consigliato utilizzare il firmware NodeMCU sul modulo ESP-01 (vedi sezione ->Flash nodeMCU su ESP-01). 

## Funzionalità base

Il firmware di base di JefBoard (vedi cartella ->Firmware di base) mette subito a disposizione le seguenti funzionalità:

- Interfaccia WIFI con DHCP server per l'invio dei comandi all'Attiny2313 (vedi sezione -> Utilizzo del firmware di base)
- Gestione degli output dell'Attiny2313 tramite comandi standard 
- Gestione di input (vedi sezione -> Utilizzo del firmware di base)

# Utilizzo del firmware di base
(work in progress)

# Flash nodeMCU su ESP-01
(work in progress)

# Appunti di programmazione dell'ATTINY2313

Questa sezione verrà documentata in modo più accurato in futuro... Per il momento riporto gli appunti utili per la programmazione degli ATTINY2313

## Impostazione FUSE bits    

- Utilizzare AVR Calculator per ottenere la stringa corretta (http://www.engbedded.com/fusecalc)

    ESEMPI:
    ```
    /* Oscillatore interno 1MHZ */     -U lfuse:w:0x64:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
    /* Quarzo esterno da 3 a 8MHZ */   -U lfuse:w:0xfd:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m     
    ```
- Impostare i FUSE Bits nell'Attiny2313:
   ```
   avrdude -c usbtiny -p t2313 -e -U lfuse:w:0xfd:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
   ```


## Creazione progetto    

- Posizionarsi nella directory dove si deve creare il progetto:
  ```
  avr-project NOMEPROGETTO
  ```                                                 


## Compilazione

- Modificare le righe seguenti nel file Makefile (ATTENZIONE: la riga FUSES deve essere identica alle impostazioni di FUSE Bits dell'Attiny2313):
	```
	DEVICE     = attiny2313
	CLOCK      = 4000000
	PROGRAMMER = -c usbtiny -p attiny2313
	OBJECTS    = main.o
	FUSES      = -U lfuse:w:0xFD:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m
  ```
- modificare il codice nel file main.c

- effettuare build

                                                            
                                                                   
## Flash

- Caricare il file .hex nel chip: 
   ```
   avrdude -c usbtiny -p t2313 -e -U flash:w:main.hex
   ```
