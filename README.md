
# Seznamte se, IRQSwitch.

## IRQSwitch je sada nastroju (Trid) pro obsluhu stisknuti tlacitek na Embedded zarizenich.

- ***!!Knihovna je stale ve vyvoji!!***
- ***Neni vazana na nekterou z rodin MCU!!***
- ***Handler pro usnadneni prace s Arduino!*** 

------------------------------------

Trida **'IRQSwitch'** v sobe ukryva celou logiku pro detekci ruznych druhu udalosti nad tlacitkem. Podporuje nasledujici metody obsluhy tlacitek: 
- `isClicked()`		- Jednoduche stisknuti
- `getClickCount()`	- Pocet stisknuti tlacitka (mezi cikly, nebo mezi pristupy k teto metode)
- `isHolded()`		- Udrzovani tlacitka ve stisknutem stavu
- `getHoldedTime()`	- Doba v milisekundach, po kterou je tlacitko udrzovano ve stisknutem stavu.

### Arduino
Pokud nechcete sami vytvaret rutinu zmeny stavu tlacitek, je mozne k tomu pouzit Tridu **'IRQSwitchArduino'**.

Trida **'IRQSwitchArduino'** v sobe ukryva iterator, ktery projde seznamem pridanych tlacitek a upravi jejich stavy podle stavu pinu ke kterym jsou pridruzeny. Obsahuje nasledujici metody:

- `AddButton(button, pin)`	- Prida tlacitko.
- `Update(ms)`				- Aktualizuje stavy tlacitek. 
- `GetButton(pin)`			- Vrati ukazatel na tlacitko podle jeho cisla pinu.
@see examples/.

V pripade potizi nebo napadu:
- [Issues](http://github.com/colesnicov/IRQSwitch/issues/) jsou vitany.
- [PullRequests](http://github.com/colesnicov/IRQSwitch/pulls/) jsou vitany ale budou dukladne zvazovany.

Vsechny tridy jsou komentovany a vsechny moznosti knihovny jsou dobre predvedeny v [ukazkach](http://github.com/colesnicov/IRQSwitch/tree/master/examples/).

**MIT Licence**
