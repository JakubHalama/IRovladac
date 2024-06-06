# IRovladac

Tento program umožňuje řídit tři LED diody (červenou, zelenou a modrou) pomocí infračerveného dálkového ovladače a desky Arduino.


Hardware požadavky:


Deska Arduino

IR přijímač (připojený k pinu 12)

Červená LED (připojená k pinu 6)

Zelená LED (připojená k pinu 5)

Modrá LED (připojená k pinu 9)
Postup:

Připojte IR přijímač k pinu 12 na desce Arduino.

Připojte červenou LED k pinu 6, zelenou LED k pinu 5 a modrou LED k pinu 9 na desce Arduino.

Nahrajte kód do Arduina.

Otevřete sériový monitor v Arduino IDE (nastavte rychlost na 9600 baudů).


Jak používat:


Zapněte sériový monitor pro sledování výstupů.

Použijte dálkový ovladač k zadání hodnot (0-255) pro jednotlivé LED diody v následujícím pořadí:

První hodnota nastaví jas červené LED.

Druhá hodnota nastaví jas zelené LED.

Třetí hodnota nastaví jas modré LED.


Pro zadání hodnot:


Stiskněte tlačítka na dálkovém ovladači odpovídající číslům (0-9).

Každý stisk tlačítka zobrazí aktuální stav zadávaného čísla v sériovém monitoru.

Po zadání čísla stiskněte tlačítko ENTER (EQ) na dálkovém ovladači, aby se hodnota nastavila na aktuální LED.

Po nastavení modré LED (třetí hodnoty) se cyklus opakuje a můžete zadávat hodnoty znovu od červené LED.
