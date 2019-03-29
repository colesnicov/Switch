## Seznamte se, IRQSwitch.

### IRQSwitch je sada nastroju (Trid) pro obsluhu stisknuti tlacitek.

**MIT Licence**

***!!Knihovna je stale ve vyvoji!!***

***Plne podporuje pouze Arduino! ale da se snadno upravit pro dalsi platformy.* - Testovano na Arduino UNO, AtMega168/328, AtTiny13/85.**

Trida **'IRQSwitch'** v sobe ukryva celou logiku pro detekci ruznych druhu udalosti nad tlacitkem. Podporuje nasledujici metody obsluhy tlacitek: 
- `isClicked()`		- Jednoduche stisknuti
- `getClickCount()`	- Pocet stisknuti tlacitka (mezi cikly, nebo mezi pristupy k teto metode)
- `isHolded()`			- Udrzovani tlacitka ve stisknutem stavu
- `getHoldedTime()`	- Doba v milisekundach, po kterou je tlacitko udrzovano ve stisknutem stavu.

Pokud nechcete sami vytvaret rutinu zmeny stavu tlacitek, je mozne k tomu pouzit Tridu **'IRQSwitchHandler'** ktera je schopna tlacitka i vytvaret.

Trida **'IRQSwitchHandler'** v sobe ukryva iterator, ktery projde vlastnim seznamem tlacitek a upravi jejich stavy podle stavu pinu ke kterym jsou pridruzeny. Obsahuje nasledujici metody:

- `AddButton(b)`					- Prida jiz existujici tlacitko.
- `Update(ms)`						- Aktualizuje stavy tlacitek. @see examples/.
- `CreateButton(name[10], pin)`	- Vytvori novetlacitko a vrati jeho ID v seznamu Handleru.
- `GetButton(id)`					- Vrati ukazatel na tlacitko podle jeho ID.

V pripade potizi nebo napadu:
- [Issues](http://github.com/colesnicov/IRQSwitch/issues/) jsou vitany.
- [PullRequests](http://github.com/colesnicov/IRQSwitch/pulls/) jsou vitany ale jsou dukladne zvazovany.

Vsechny tridy jsou komentovany a vsechny moznosti knihovny jsou dobre predvedeny v [ukazkach](http://github.com/colesnicov/IRQSwitch/examples/).



