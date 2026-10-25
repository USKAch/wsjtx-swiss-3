# WSJT-SWISS 3 – Manuale

WSJT-SWISS 3 è un'edizione di [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) 3.0.2 per lo **Swiss XMAS Contest** dell'USKA. Durante un QSO del contest le stazioni si scambiano il loro cantone, ad es. **ZH** o **BE**. WSJT-SWISS 3 registra i QSO, crea il log Cabrillo e lo invia direttamente all'USKA.

Regolamento del contest: https://uska.ch/contest/schweizer-contest-kw/

**Importante:**

- WSJT-SWISS 3 si installa **accanto** al tuo WSJT-X abituale. Il tuo WSJT-X e le sue impostazioni non vengono modificati.
- I nominativi con suffisso (/P, /M ecc.) e i nominativi con quattro lettere dopo la cifra (ad es. HB9HSLU) non funzionano nel contest.
- Solo WSJT-SWISS 3 mostra correttamente i cantoni; anche le stazioni che colleghi hanno quindi bisogno di WSJT-SWISS 3.

---

## 1. Download

L'installatore `wsjtx-…-win64.exe` si trova sulla [pagina Releases](https://github.com/USKAch/wsjtx-swiss-3/releases).

Browser e antivirus a volte bloccano il download perché il file viene scaricato raramente. È un falso allarme.

- **Chrome:** cliccare su «Mantieni» oppure, in «Download», scegliere «Mantieni file pericoloso».
- **Edge:** «Mantieni» → «Mostra altro» → «Mantieni comunque».

## 2. Installazione

1. Avviare l'installatore.
2. Se compare l'avviso «PC protetto da Windows» (SmartScreen), cliccare su **«Ulteriori informazioni»** e poi su **«Esegui comunque»**. Il programma non è firmato con un certificato commerciale, cosa normale per il software open source.
3. WSJT-SWISS 3 viene installato in `C:\WSJTX-SWISS3`. Nel menu Start si chiama **WSJT-SWISS 3**.

Dopo il contest puoi rimuoverlo in **Impostazioni di Windows → App** (disinstallare «WSJT-SWISS 3»).

## 3. Primo avvio

### Importare le impostazioni

Al primo avvio WSJT-SWISS 3 chiede se deve cercare sul tuo PC le impostazioni di WSJT-X o di una versione precedente di WSJT-SWISS. Senza la tua conferma non viene cercato né copiato nulla.

1. Cliccare su **«Cerca»**.
2. L'elenco mostra tutte le impostazioni trovate, con nominativo, ricetrasmettitore e data dell'ultimo utilizzo. Sotto vedi i dettagli della voce selezionata, ad es. le schede audio e la posizione del file.
3. Selezionare la voce che usi per la tua stazione e cliccare su **«Importa la selezione»**.

Le impostazioni vengono copiate per WSJT-SWISS 3; l'originale resta invariato. Prima di trasmettere, controlla le schede **Radio** e **Audio** in **File → Settings**.

La lingua delle finestre di WSJT-SWISS (Deutsch, Français, Italiano, English) si sceglie in alto nella finestra. Vale anche per gli altri messaggi di WSJT-SWISS. Il resto dell'interfaccia di WSJT-X è in inglese.

### Scegliere il cantone

Poi WSJT-SWISS 3 ti chiede il tuo cantone. Viene trasmesso con ogni QSO del contest. Potrai modificarlo più tardi in **File → Settings → Advanced**.

La modalità Swiss XMAS è già attivata (**File → Settings → Advanced → Special operating activity: Swiss XMAS**) e chiami «CQ XMAS».

## 4. Traffico

1. In **Mode** scegliere **FT4**.
2. Impostare banda e frequenza secondo il regolamento e il bando dell'USKA.
3. Cliccare su **Enable Tx** per chiamare CQ, oppure fare doppio clic su una stazione per risponderle.

Lo scambio dei cantoni avviene automaticamente durante il QSO:

```
Stazione A (ZH)                Stazione B (BE)
──────────────────────────────────────────────
CQ XMAS HB9AAA JN47
                               HB9AAA HB9BBB 1A BE
HB9BBB HB9AAA R 1A ZH
                               HB9AAA HB9BBB RR73
```

L'«1A» davanti al cantone fa parte del formato dei messaggi e non ha alcun significato.

I QSO conclusi vengono inseriti automaticamente nel log del contest, con **599** e il cantone come rapporto (ad es. «599 BE»). Il log del contest si trova in **View → Contest log**.

### Seconda giornata del contest

Le due giornate digitali sono contest separati con invii dei log separati. Il secondo giorno puoi collegare di nuovo le stazioni del primo giorno.

Se avvii WSJT-SWISS 3 in un nuovo giorno e il log del contest contiene ancora QSO di un giorno precedente, il programma chiede:

- **«Esportare prima questo log»** – salvare il vecchio log come file Cabrillo (e inviarlo), poi iniziare con un log vuoto.
- **«Iniziare un nuovo log del contest»** – iniziare subito con un log vuoto.
- **«Mantenere il log»** – non cambiare nulla.

In ogni caso i QSO restano nel tuo file log ADIF (`wsjtx_log.adi`).

## 5. Inviare il log

Il log deve arrivare all'USKA entro 8 giorni dal contest.

1. Scegliere **File → Export Cabrillo log …**.
2. I campi sono precompilati per lo Swiss XMAS Contest. La prima volta completa nome, indirizzo ed e-mail; vengono memorizzati. La conferma di ricezione dell'USKA viene inviata a questo indirizzo e-mail.
3. Cliccare su **Save**. Il nome del file proposto è il tuo nominativo in «Documenti», ad es. `HB9BLA.cbr`; confermare con **Salva**.
4. Alla domanda se inviare ora il log, cliccare su **«Invia ora all'USKA»**.
5. Nella finestra «Inviare il log all'USKA» controllare il contest (è preselezionato in base alla data dei QSO), leggere la dichiarazione e spuntare **«Faccio questa dichiarazione»**.
6. Cliccare su **«Invia il log»**.

Alla fine la finestra indica «L'USKA ha ricevuto il tuo log …» e ricevi per e-mail una conferma con il log allegato. Se non arriva, controlla la cartella dello spam.

Puoi anche inviare più tardi un log salvato: **File → Inviare un log Cabrillo all'USKA …**. Se l'invio diretto non funziona, usa la pagina web https://contestlog.uska.ch/submit.

## 6. Compatibilità

| Situazione | Risultato |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest con scambio dei cantoni |
| WSJT-SWISS 3 ↔ WSJT-X | I QSO normali funzionano; i cantoni vengono mostrati in modo errato |
| QSO FT4/FT8 normali fuori dal contest | Come con WSJT-X; per questi disattivare «Special operating activity» |
