# Solari Metor Controller
![solari_metor](solari_metor.jpg)
## Descrizione

Orologio elettromeccanico prodotto da Solari qualche decennio fa ... Per info consultare: http://www.assosrl.it/catalogo/fuori-commercio/metor.
Il suo funzionamento era basato su una scheda master di controllo a cui gli orologi venivano collegati in parallelo e venivano azionati dalla stessa scheda tramite una tensione di 24v.
Inutile dire che non è semplice recuperare la scheda originale ed è sicuramente più laborioso riprogettare una scheda che la emuli.

I requisiti che ho mantenuto sono i seguenti:
- Utilizzare 5 Volt come alimentazione e non 24 in modo da utilizzare la stessa alimentazione della JefBoard.
- Bypassare la circuitazione a bordo dell'orologio preservando lo stesso funzionamento elettromeccanico.