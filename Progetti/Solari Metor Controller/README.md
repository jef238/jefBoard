# Solari Metor Controller (in progress)
![solari_metor](solari_metor.jpg)
## Descrizione

Orologio elettromeccanico prodotto da Solari qualche decennio fa ... Per info consultare: http://www.assosrl.it/catalogo/fuori-commercio/metor.
Il suo funzionamento era basato su una scheda master di controllo a cui gli orologi venivano collegati in parallelo e venivano azionati dalla stessa scheda tramite una tensione di 24v.
Inutile dire che non è semplice recuperare la scheda originale ed è sicuramente più laborioso riprogettare una scheda che la emuli.
Dal punto di vista del funzionamento l'orologio è dotato di una scheda interna che aziona un motorino DC che a sua volta aziona la meccanica delle palette. Un interruttore meccanico funge da fine corsa in modo da far avanzare la meccanica di 1 minuto alla volta.


Per lo sviluppo di questa applicazione sono partito da alcuni punti fissi:
- Utilizzare 5 Volt come alimentazione e non 24 in modo da utilizzare la stessa alimentazione della JefBoard.
- Bypassare la circuitazione a bordo dell'orologio preservando lo stesso funzionamento elettromeccanico.

Per ottenere il funzionamento era dunque necessario pilotare direttamente il motorino DC e gestire l'interrutore di fine corsa in modo opportuno.

## Schema elettrico