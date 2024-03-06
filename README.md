# jefBoard
![example](example.jpg)
## Cos'è

JefBoard è una scheda di sviluppo basata sul microcontroller Attiny2313 della ATMEL. Si presta allo sviluppo di applicazioni di varia natura e integra la predisposizione per la scheda WiFI ESP-01 (Opzionale) e il connettore per la programmazione ISP dell'Attiny2313.
Alcune caratteristiche:
- JefBoard espone tutti i pin dell'Attiny2313 per il loro utilizzo.
- JefBoard permette la realizzazione di applicazioni con supporto WiFi (il modulo ESP-01 comunica tramite connessione seriale con l'Attiny2313).
- JefBoard può essere assemblata anche senza l'ESP-01 e relativi componenti di alimentazione se non si necessita di supporto WiFi abbassando ulteriormente il costo.
- JefBoard è una scheda di piccole dimensioni 6x4 cm.

# Schema ed elenco componenti

![example](schematic.png)

# PCB Layout
Per reperire la PCB scrivi al mio indirizzo giuseppe.culotta@gmail.com

![example](top.png)

![pcb](pcb.jpg)

![jefboard_r](jefboard_r.PNG)

## Elenco componenti

| Sigla | Valore                        | Tipo			        | Note                                        |
|-------|-------------------------------|-------------------------------|---------------------------------------------|
| C1    | 100n           		| Condesatore poliestere        |				              |    
| C2    | 100u           		| Condesatore elettrolitico     |					      |
| C4    | 10u            		| Condesatore elettrolitico     | (Opzionale - Solo in caso di supporto WIFI) |	
| C5    | 22p            		| Condesatore ceramico          |					      |
| C6    | 22p            		| Condesatore ceramico          | 					      |
| ESP01 |                 		| Connettore pin		| (Opzionale - Solo in caso di supporto WIFI) |
| IC1   | ATtiny2313/ATtiny2313a        | AVR			        |				              |
| IC2   | LM1117DTX 3.3V 		|			        | (Opzionale - Solo in caso di supporto WIFI) |	
| JP1   |                  		| Connettore tipo M100.1	| (Opzionale)                  		      |
| JP2   |                  		| Connettore tipo M100.1	| (Opzionale)                                 |
| LED1  |                  		| LED3MM                        |				              |
| PWR   |                  		| Connettore tipo W237-102      | (Opzionale)                                 |
| Q1    |                   		| Quarzo 4MHZ    	        |	                                      |
| R1    | 10k            		| 1/4w		                |                                             |
| R2    | 10k            		| 1/4w 				| (Opzionale - Solo in caso di supporto WIFI) |	
| R3    | 20k            		| 1/4w 	        		| (Opzionale - Solo in caso di supporto WIFI) |	
| R4    | 220            		| 1/4w                		| 					      |
| RESET1|                  		| Microswitch                   |                                             |
| RESET2|                 		| Microswitch			| (Opzionale - Solo in caso di supporto WIFI) |
| SV2   |                   		| Connettore pin                |                                             |
         
# Caricare un firmware sull'ATTINY2313

Questa sezione verrà documentata in modo più accurato in futuro... Per il momento riporto gli appunti utili per la programmazione degli ATTINY2313 utilizzando Xcode (Mac) e [CrossPack for AVR Development](https://github.com/obdev/CrossPack-AVR).
Come programmatore per l'ISP è stato utilizzato l'USBtinyISP:

![usbtinyisp](usbtinyisp.jpg)

## 1. Impostazione FUSE bits    

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

## 2. Compilazione

- Modificare le righe seguenti nel file Makefile (ATTENZIONE: la riga FUSES deve essere identica alle impostazioni di FUSE Bits dell'Attiny2313; in questo esempio si utilizza un quarzo esterno da 4MHZ):
	```
	DEVICE     = attiny2313
	CLOCK      = 4000000
	PROGRAMMER = -c usbtiny -p attiny2313
	OBJECTS    = main.o
	FUSES      = -U lfuse:w:0xFD:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m
  ```
- effettuare build (verrà generato main.hex)
                                                              
## 3. Collegare l'USBtinyISP

- Assicurarsi di aver correttamente collegato il programmatore al computer e di aver installato i driver per il suo funzionamento

- Collegare l'USBtinyISP al connettore SV2

## 4. Flash

- Caricare il file .hex nel chip: 
   ```
   avrdude -c usbtiny -p t2313 -e -U flash:w:main.hex
   ```
# Utilizzo dell'ESP01 per il supporto WIFI

![esp01](esp-01.jpg)

L'ESP01 è un modulo SOC basato sul chip ESP8266 che permette di aggiungere il supporto al WIFI in modo semplice ed economico.
Prima di inserirlo sulla jefBoard è necessario fare una precisazione:
L'ESP01 viene fornito generalmente con un firmware dotato di soli comandi AT per cui prima di utilizzarlo nei nostri progetti è necessario caricare il firmware nodeMCU (https://it.wikipedia.org/wiki/NodeMCU). Con questo firmware è possibile programmare facilmente l'ESP01 tramite linguaggio LUA ed è possibile compilare una versione custom di nodeMCU con il supporto delle librerie/funzionalità necessarie in base all'utilizzo su https://nodemcu-build.com.

E' necessario inoltre dotarsi di un adattore USB seriale TTL:

![adattatore](adattatore_USB_seriale_TTL.jpg)

## Istruzioni per l’installazione di esptool su MACOSX:

- Scaricare e scompattare esptool (https://github.com/espressif/esptool)

- Assicurarsi di avere Python 1.7 o successivo installato sul sistema

- Spostarsi sulla directory appena scompattata ed eseguire:
   ```
   sudo python setup.py install
   ```

## Istruzioni per flash nodemcu su ESP01
Esistono tanti modi per abilitare la modalità flash su ESP-01 (una ricerca su google è altamente consigliata...). Tempo fa ho realizzato una scheda che per comodità mi permette di riavviare tramite reset l'ESP01 (pulsante 1) mentre metto a massa il pin GPIO0 (pulsante 2):

- Posizionare l’ESP01 e l’interfaccia seriale/USB sulla scheda di programmazione:

  ![adattatore](esp8266/setup.jpg)

- Per settare l’ESP01 in modalità flash tenere premuto il pulsante 2 e contemporaneamente effettuare un reset premendo e rilasciando il pulsante 1; dopo qualche istante rilasciare il pulsante 2.

- Effettuare il comando (nodemcu_base_int.bin è il nome del file del firmware nodemcu da flashare vedi cartella esp8266):
   ```  
   python esptool.py --port /dev/tty.wchusbserialfa140 write_flash 0x00000 nodemcu_base_int.bin
   ```
- (opzionale) restore firmware originale (11/12/2019)
   ``` 
   python esptool.py --port /dev/tty.wchusbserialfd130 write_flash 0x00000 v0.9.2.2\ AT\ Firmware.bin
   ``` 
## Programmazione ESP01 tramite script LUA
Una volta caricato il firmware nodeMCU è possibile caricare gli script LUA. Il file denominato init.lua viene caricato all'avvio in maniera automatica.
E' possibile utilizzare il software ESPlorer (https://github.com/4refr0nt/ESPlorer) sia per caricare sia gli script LUA che per gestire al meglio l'ESP01.

# Utilizzo di jefBoard come server WIFI
In questo caso l'ESP01 funge da server in ascolto sulla porta 8080 tramite connessione WIFI; Ricevuto il comando lo inoltra tramite la connessione seriale verso l'Attiny2313.
Per questo utilizzo è necessario che la scheda sia equipaggiata con l'ESP01 aggiornata con il firmware nodeMCU, ed i relativi componenti. Di seguito un esempio di file init.lua (da caricare sull'ESP01) e del codice da utilizzare sull'Attiny2313:

## init.lua

```
wifi.setmode(wifi.SOFTAP)
cfg={}
cfg.ssid="jefBoard"
wifi.ap.config(cfg)

uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)

sv = net.createServer(net.TCP, 30)

function receiver(sck, data)
  print(data)  
end

if sv then
  sv:listen(8080, function(conn)
    conn:on("receive", receiver)    
  end)
end
```

## main.c

```
#define F_CPU 4000000 UL // 4 MHz Crystal

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define baud rate
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE(((F_CPU / (USART_BAUDRATE * 16 UL))) - 1)

volatile unsigned char value;
/* This variable is volatile so both main and RX interrupt can use it.
 It could also be a uint8_t type */

/* Interrupt Service Routine for Receive Complete
 NOTE: vector name changes with different AVRs see AVRStudio -
 Help - AVR-Libc reference - Library Reference - <avr/interrupt.h>: Interrupts
 for vector names other than USART_RX_vect for Attiny2313 */

void dosomething(); //Exec something

void USART_Init(void) {
  // Set baud rate
  UBRRL = BAUD_PRESCALE; // Load lower 8-bits into the low byte of the UBRR register
  UBRRH = (BAUD_PRESCALE >> 8);
  /* Load upper 8-bits into the high byte of the UBRR register
   Default frame format is 8 data bits, no parity, 1 stop bit
   to change use UCSRC, see AVR datasheet*/

  // Enable receiver and transmitter and receive complete interrupt
  UCSRB = ((1 << TXEN) | (1 << RXEN) | (1 << RXCIE));
}

void USART_SendByte(uint8_t u8Data) {

  // Wait until last byte has been transmitted
  while ((UCSRA & (1 << UDRE)) == 0);

  // Transmit data
  UDR = u8Data;
}

// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t USART_ReceiveByte() {
  while ((UCSRA & (1 << RXC)) == 0);
  return UDR;
}

ISR(USART_RX_vect) {
  if (UDR != 0x0A) value = UDR; //read UART register into value except <RETURN> key
}

void dosomething() {
  //Exec something    
}

int main(void) {

  USART_Init(); // Initialise USART
  sei(); // enable all interrupts

  //If received data from serial match 'd' char exec dosomething() function
  while (1) {
    if (value == 0x64) dosomething(); //ASCII for 'd'     
  }

  return 0;
}
``` 
