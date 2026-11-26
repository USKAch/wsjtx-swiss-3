# WSJT-SWISS 3 – Manuale

WSJT-SWISS 3 è un'edizione di [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) 3.0.2 per lo **Swiss XMAS Contest** dell'USKA. Durante un QSO del contest le stazioni si scambiano il loro cantone, ad es. **ZH** o **BE**. WSJT-SWISS 3 registra i QSO, crea il log Cabrillo e lo invia direttamente all'USKA.

Regolamento del contest: https://uska.ch/contest/schweizer-contest-kw/

**Importante:**

- WSJT-SWISS 3 si installa **accanto** al tuo WSJT-X abituale. Il tuo WSJT-X e le sue impostazioni non vengono modificati.
- I nominativi con suffisso (/P, /M ecc.) e i nominativi con quattro lettere dopo la cifra (ad es. HB9HSLU) non funzionano nel contest.
- Solo WSJT-SWISS 3 mostra correttamente i cantoni; anche le stazioni che colleghi hanno quindi bisogno di WSJT-SWISS 3.

---

## 1. Download

**[⬇ Scarica WSJT-SWISS 3 per Windows](https://github.com/USKAch/wsjtx-swiss-3/releases/download/v3.0.2-swiss2/wsjtx-3.0.2-swiss2-win64.exe)** (versione 3.0.2-swiss2, file `wsjtx-3.0.2-swiss2-win64.exe`)

Le versioni precedenti si trovano sulla [pagina Releases](https://github.com/USKAch/wsjtx-swiss-3/releases).

Il browser o l'antivirus può segnalare un installatore sconosciuto. Controlla che provenga dalla pagina Releases del progetto e corrisponda alla versione desiderata prima di conservarlo o eseguirlo.

- **Chrome:** cliccare su «Mantieni» oppure, in «Download», scegliere «Mantieni file pericoloso».
- **Edge:** «Mantieni» → «Mostra altro» → «Mantieni comunque».

## 2. Installazione

1. Avviare l'installatore.
2. Se compare «PC protetto da Windows» (SmartScreen), controllare origine e versione. **Ulteriori informazioni** mostra i dettagli; **Esegui comunque** permette poi di continuare l'installazione se si sceglie di procedere.
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
2. Scegliere **3.580 MHz (80 m)** o **7.055 MHz (40 m)** nella lista delle frequenze. Entrambe le voci hanno la descrizione **Swiss**. Consultare il bando attuale del contest.
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

Rispetta il termine d'invio indicato nel regolamento attuale del contest.

1. Controlla **View → Contest log**, poi scegli **File → Inviare il log all'USKA …**.
2. Controlla la data UTC del log attuale e i dati della stazione. La prima volta completa nome, indirizzo ed e-mail. Questi dati vengono memorizzati. Il nominativo proviene da **Settings → General**.
3. Clicca su **Continua**. Il programma crea automaticamente il file Cabrillo e apre la finestra d'invio. Non occorre esportare prima un file o scegliere una cartella.
4. Controlla il numero di QSO, il contest e l'e-mail di conferma. Il contest digitale corrispondente alla data di dicembre viene preselezionato se disponibile sul portale. Altrimenti seleziona quello corretto.
5. Leggi la dichiarazione, spunta **Faccio questa dichiarazione** e clicca su **Invia il log**.

L'USKA conferma la ricezione per e-mail con il log allegato. Controlla lo spam se la conferma manca. Non si può inviare un log vuoto. In caso di avvisi, controlla i dettagli prima di proseguire o annullare. Correggi un log rifiutato nell'applicazione e ricomincia l'invio.

I file generati restano nella sottocartella **Cabrillo** della cartella dei log WSJT-SWISS, in una cartella separata per ogni tentativo. **File → Open log directory** apre questa cartella. In caso di problemi di connessione, puoi usare il file su https://contestlog.uska.ch/submit. Se la ricezione è incerta, controlla prima le e-mail per evitare un doppio invio.

**File → Export Cabrillo log …** resta disponibile per una copia separata. Dopo **Save**, scegli un nome di file `.cbr`. La finestra parte dalla cartella dei log e ricorda l'ultima cartella d'esportazione usata con successo. Dopo il salvataggio puoi inviare il file, aprire il sito oppure scegliere **Più tardi** per conservare solo la copia locale.

## 6. Compatibilità

**New Call on Band** è attivo nello schema predefinito in **Settings → Colors**. Le scelte salvate vengono conservate dopo un'importazione o un aggiornamento. Se l'opzione è disattivata nel tuo profilo, selezionala oppure usa **Reset Highlighting** per ripristinare lo schema predefinito.

| Situazione | Risultato |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest con scambio dei cantoni |
| WSJT-SWISS 3 ↔ WSJT-X | I QSO normali funzionano; i cantoni vengono mostrati in modo errato |
| QSO FT4/FT8 normali fuori dal contest | Come con WSJT-X; per questi disattivare «Special operating activity» |

## 7. Finestre e schermate

La [guida illustrata alle finestre](Window-reference.md) descrive l'avvio, tutte le schede Settings, il log, l'invio, l'esportazione e le altre visualizzazioni. La guida dettagliata è in inglese, come gran parte delle etichette del programma. Le schermate usano un profilo dimostrativo senza radio collegata.

| Finestra | Uso |
|---|---|
| First start / importazione | Scegliere la lingua, cercare e controllare il profilo prima di copiarlo. |
| Swiss XMAS Contest | Scegliere il cantone, modificabile in seguito in Advanced. |
| Finestra principale / Wide Graph | Decodificare le stazioni, scegliere la frequenza e svolgere i QSO; il waterfall mostra i segnali. |
| Settings: General, Radio, Audio | Configurare nominativo, locator, regione, controllo radio e audio. |
| Settings: Tx Macros, Reporting | Preparare messaggi liberi e registrazione automatica dei contatti. |
| Settings: Frequencies, Colors | Gestire frequenze e colori dei nuovi nominativi per banda. |
| Settings: Advanced, Alerts, Filters | Scegliere Swiss XMAS e cantone, avvisi e filtri. |
| Contest Log / Log QSO | Controllare i contatti o aggiungere un QSO manualmente. |
| Nuova giornata del contest | Salvare o conservare il vecchio log, oppure iniziare una tabella vuota. |
| Inviare il log all'USKA | Controllare i dati, generare il file automaticamente e confermare la dichiarazione prima dell'invio. |
| Export Cabrillo | Salvare una copia aggiuntiva; non serve per l'invio normale. |
| Avvisi del portale / conferma | Controllare gli errori; l'e-mail con il log allegato è la ricevuta. |
| Astronomical Data, Echo/Fast Graph, Message Averaging | Strumenti per altri modi, non necessari per il contest Swiss FT4. |
| Fox Log, Active Stations, Message Creator, QSY Monitor | Strumenti DXpedition, elenco stazioni e cambi di frequenza. |
| Palette Designer / colori | Personalizzare waterfall e colori dei messaggi. |
| Configurations / Change Operator | Cambiare configurazione della stazione o operatore. |
| Scelta di file, carattere o colore | Selezionare l'elemento indicato nel titolo; Annulla abbandona la scelta. |
| Download Samples, Equalization Tools, Help | Registrazioni d'esempio, calibrazione e informazioni sul programma. |
| Errori e conferme | Controllare percorso, dispositivo o dati indicati prima di proseguire. |
