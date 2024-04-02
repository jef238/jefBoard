# Solari Metor Controller (in progress)
![solari_metor](solari_metor.jpg)
## Descrizione

Orologio elettromeccanico prodotto da Solari qualche decennio fa ... Per info consultare: http://www.assosrl.it/catalogo/fuori-commercio/metor.
Il suo funzionamento era basato su una scheda master di controllo a cui gli orologi venivano collegati in parallelo e venivano azionati dalla stessa scheda tramite una tensione di 24v.
la scheda master generava un impulso di durata breve, ogni minuto invertendone alternativamente la polarità. La piccola schedina a bordo dell'orologio si occupava di attivare il motorino DC collegato alla meaccanica delle palette, e di gestire l'interruttore di fine corsa in modo da fermare il movimento del motorino dopo lo scatto del minuto in maniera precisa.
Inutile dire che non è semplice recuperare la scheda originale ed è sicuramente più laborioso riprogettare una scheda che la emuli.

Per lo sviluppo di questa applicazione sono partito da alcuni punti fissi:
- Utilizzare 5 Volt come alimentazione e non 24 in modo da utilizzare la stessa alimentazione della JefBoard.
- Bypassare la circuitazione a bordo dell'orologio preservando lo stesso funzionamento elettromeccanico.

Per ottenere il funzionamento era dunque necessario azionare direttamente il motorino DC ogni 60 secondi e gestire l'interrutore di fine corsa in modo opportuno.

## Componenti

La jefBoard (ovviamente) può essere assemblata senza i componenti relativi al WIFI; per pilotare il motorino DC poi ho utilizzato una scheda driver di piccole dimensioni tipo questa (https://it.aliexpress.com/item/1005006532295626.html):
![l298mini](L298N-Mini.webp)