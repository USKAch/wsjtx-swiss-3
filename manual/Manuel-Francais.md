# WSJT-SWISS 3 – Manuel

WSJT-SWISS 3 est une édition de [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) 3.0.2 pour le **Swiss XMAS Contest** de l'USKA. Pendant un QSO du concours, les stations échangent leur canton, p. ex. **ZH** ou **BE**. WSJT-SWISS 3 enregistre les QSO, crée le log Cabrillo et l'envoie directement à l'USKA.

Règlement du concours : https://uska.ch/contest/schweizer-contest-kw/

**Important :**

- WSJT-SWISS 3 s'installe **à côté** de ton WSJT-X habituel. Ton WSJT-X et ses réglages ne sont pas modifiés.
- Les indicatifs avec suffixe (/P, /M, etc.) et les indicatifs avec quatre lettres après le chiffre (p. ex. HB9HSLU) ne fonctionnent pas dans le concours.
- Seul WSJT-SWISS 3 affiche correctement les cantons ; tes correspondants ont donc aussi besoin de WSJT-SWISS 3.

---

## 1. Téléchargement

L'installateur `wsjtx-…-win64.exe` se trouve sur la [page Releases](https://github.com/USKAch/wsjtx-swiss-3/releases).

Le navigateur ou l'antivirus peut avertir au sujet d'un installateur inconnu. Vérifie qu'il provient de la page Releases du projet et correspond à la version souhaitée avant de le conserver ou de l'exécuter.

- **Chrome :** cliquer sur « Conserver » ou, dans « Téléchargements », choisir « Conserver le fichier dangereux ».
- **Edge :** « Conserver » → « Afficher plus » → « Conserver quand même ».

## 2. Installation

1. Lancer l'installateur.
2. Si « Windows a protégé votre ordinateur » (SmartScreen) apparaît, vérifier la source et la version. **Informations complémentaires** affiche les détails ; **Exécuter quand même** permet ensuite de poursuivre l'installation si tu le souhaites.
3. WSJT-SWISS 3 est installé dans `C:\WSJTX-SWISS3`. Dans le menu Démarrer, il s'appelle **WSJT-SWISS 3**.

Après le concours, tu peux le supprimer sous **Paramètres Windows → Applications** (désinstaller « WSJT-SWISS 3 »).

## 3. Premier démarrage

### Reprendre les réglages

Au premier démarrage, WSJT-SWISS 3 demande s'il doit rechercher sur ton PC les réglages de WSJT-X ou d'une version précédente de WSJT-SWISS. Rien n'est recherché ni copié sans ta confirmation.

1. Cliquer sur **« Rechercher »**.
2. La liste montre tous les réglages trouvés, avec l'indicatif, le transceiver et la date de dernière utilisation. En dessous, tu vois les détails de l'entrée sélectionnée, p. ex. les cartes son et l'emplacement du fichier.
3. Sélectionner l'entrée que tu utilises pour ta station et cliquer sur **« Reprendre la sélection »**.

Les réglages sont copiés pour WSJT-SWISS 3 ; l'original reste inchangé. Avant d'émettre, vérifie les onglets **Radio** et **Audio** sous **File → Settings**.

Tu peux choisir la langue des fenêtres WSJT-SWISS (Deutsch, Français, Italiano, English) en haut de la fenêtre. Elle s'applique aussi aux autres messages de WSJT-SWISS. Le reste de l'interface de WSJT-X est en anglais.

### Choisir le canton

Ensuite, WSJT-SWISS 3 te demande ton canton. Il est transmis à chaque QSO du concours. Tu pourras le modifier plus tard sous **File → Settings → Advanced**.

Le mode Swiss XMAS est déjà activé (**File → Settings → Advanced → Special operating activity : Swiss XMAS**) et tu appelles « CQ XMAS ».

## 4. Trafic

1. Sous **Mode**, choisir **FT4**.
2. Choisir **3.580 MHz (80 m)** ou **7.055 MHz (40 m)** dans la liste des fréquences. Les deux entrées portent la description **Swiss**. Consulter l'annonce actuelle du concours.
3. Cliquer sur **Enable Tx** pour appeler CQ, ou double-cliquer sur une station pour lui répondre.

L'échange des cantons se fait automatiquement pendant le QSO :

```
Station A (ZH)                 Station B (BE)
──────────────────────────────────────────────
CQ XMAS HB9AAA JN47
                               HB9AAA HB9BBB 1A BE
HB9BBB HB9AAA R 1A ZH
                               HB9AAA HB9BBB RR73
```

Le « 1A » devant le canton fait partie du format des messages et n'a pas de signification.

Les QSO terminés sont inscrits automatiquement dans le log du concours, avec **599** et le canton comme report (p. ex. « 599 BE »). Le log du concours se trouve sous **View → Contest log**.

### Deuxième journée du concours

Les deux journées numériques sont des concours distincts, avec des envois de logs distincts. Tu peux contacter à nouveau le deuxième jour les stations du premier jour.

Si tu démarres WSJT-SWISS 3 un nouveau jour et que le log du concours contient encore des QSO d'un jour précédent, le programme demande :

- **« Exporter d'abord ce log »** – enregistrer l'ancien log comme fichier Cabrillo (et l'envoyer), puis commencer avec un log vide.
- **« Commencer un nouveau log de concours »** – commencer tout de suite avec un log vide.
- **« Conserver le log »** – ne rien changer.

Dans tous les cas, les QSO restent dans ton fichier log ADIF (`wsjtx_log.adi`).

## 5. Envoyer le log

Respecte le délai d'envoi du règlement actuel du concours.

1. Vérifie **View → Contest log**, puis choisis **File → Envoyer le log à l'USKA …**.
2. Vérifie la date UTC du log actuel et les coordonnées préremplies. La première fois, complète ton nom, ton adresse et ton e-mail. Ces données sont mémorisées. L'indicatif provient de **Settings → General**.
3. Clique sur **Continuer**. Le programme crée automatiquement le fichier Cabrillo et ouvre la fenêtre d'envoi. Aucun export préalable ni choix de dossier n'est nécessaire.
4. Vérifie le nombre de QSO, le concours et l'e-mail de confirmation. Le concours numérique correspondant à une date de décembre est présélectionné s'il est proposé par le portail. Sinon, sélectionne le bon concours.
5. Lis la déclaration, coche **Je fais cette déclaration**, puis clique sur **Envoyer le log**.

L'USKA confirme la réception par e-mail avec le log joint. Vérifie le dossier de spam si la confirmation manque. Un log vide ne peut pas être envoyé. En cas d'avertissement, vérifie les détails avant de poursuivre ou d'annuler. Corrige un log rejeté dans l'application, puis recommence l'envoi.

Les fichiers générés restent dans le sous-dossier **Cabrillo** du dossier de logs WSJT-SWISS, dans un dossier distinct pour chaque tentative. **File → Open log directory** ouvre ce dossier. En cas de problème de connexion, utilise le fichier sur https://contestlog.uska.ch/submit. Si la réception est incertaine, vérifie d'abord tes e-mails avant de renvoyer le log.

**File → Export Cabrillo log …** permet toujours de créer une sauvegarde séparée. Après **Save**, choisis un nom de fichier `.cbr`. Le dialogue commence dans le dossier de logs et mémorise le dernier dossier d'export utilisé avec succès. Tu peux ensuite envoyer le fichier, ouvrir le site web ou choisir **Plus tard** pour conserver uniquement la copie locale.

## 6. Compatibilité

**New Call on Band** est activé dans le schéma par défaut sous **Settings → Colors**. Les choix enregistrés sont conservés lors d'un import ou d'une mise à jour. Si l'option est désactivée dans ton profil, coche-la ou utilise **Reset Highlighting** pour retrouver les réglages par défaut.

| Situation | Résultat |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Concours avec échange des cantons |
| WSJT-SWISS 3 ↔ WSJT-X | Les QSO normaux fonctionnent ; les cantons sont mal affichés |
| QSO FT4/FT8 normaux hors concours | Comme avec WSJT-X ; désactiver pour cela « Special operating activity » |

## 7. Fenêtres et captures d'écran

La [référence illustrée des fenêtres](Window-reference.md) décrit les dialogues de démarrage, tous les onglets Settings, le log, l'envoi, l'export et les affichages supplémentaires. Cette référence détaillée est en anglais, comme la plupart des libellés du programme. Les captures utilisent un profil de démonstration sans radio connectée.

| Fenêtre | Utilisation |
|---|---|
| First start / reprise des réglages | Choisir la langue, rechercher puis vérifier le profil à copier. |
| Swiss XMAS Contest | Choisir le canton, modifiable ensuite sous Advanced. |
| Fenêtre principale / Wide Graph | Décoder les stations, choisir la fréquence et effectuer les QSO ; le waterfall affiche les signaux. |
| Settings: General, Radio, Audio | Régler indicatif, locator, région, commande du transceiver et audio. |
| Settings: Tx Macros, Reporting | Préparer les messages libres et la journalisation automatique. |
| Settings: Frequencies, Colors | Gérer les fréquences et la mise en évidence des nouveaux indicatifs par bande. |
| Settings: Advanced, Alerts, Filters | Choisir Swiss XMAS et le canton, les alertes et les filtres. |
| Contest Log / Log QSO | Vérifier les contacts ou ajouter un QSO manuellement. |
| Nouvelle journée du concours | Sauvegarder l'ancien log, le conserver ou commencer une table vide. |
| Envoyer le log à l'USKA | Vérifier les données, générer le fichier automatiquement et confirmer la déclaration avant l'envoi. |
| Export Cabrillo | Enregistrer une copie supplémentaire ; inutile pour l'envoi normal. |
| Avertissement du portail / confirmation | Vérifier les erreurs ; l'e-mail avec le log joint constitue l'accusé de réception. |
| Astronomical Data, Echo/Fast Graph, Message Averaging | Outils pour d'autres modes, inutiles pour le concours Swiss FT4. |
| Fox Log, Active Stations, Message Creator, QSY Monitor | Outils DXpedition, liste de stations et changements de fréquence. |
| Palette Designer / couleurs | Personnaliser le waterfall et les couleurs des messages. |
| Configurations / Change Operator | Changer de configuration de station ou d'opérateur. |
| Choix de fichier, police ou couleur | Choisir l'élément indiqué par le titre ; Annuler abandonne le choix. |
| Download Samples, Equalization Tools, Help | Enregistrements d'exemple, étalonnage et informations du programme. |
| Erreurs et confirmations | Lire le chemin, le périphérique ou les données concernés avant de poursuivre. |
