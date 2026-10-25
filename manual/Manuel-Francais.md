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

Les navigateurs et les antivirus bloquent parfois le téléchargement, parce que le fichier est rarement téléchargé. C'est une fausse alerte.

- **Chrome :** cliquer sur « Conserver » ou, dans « Téléchargements », choisir « Conserver le fichier dangereux ».
- **Edge :** « Conserver » → « Afficher plus » → « Conserver quand même ».

## 2. Installation

1. Lancer l'installateur.
2. Si l'avertissement « Windows a protégé votre ordinateur » (SmartScreen) apparaît, cliquer sur **« Informations complémentaires »** puis sur **« Exécuter quand même »**. Le programme n'est pas signé avec un certificat commercial, ce qui est habituel pour un logiciel open source.
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
2. Régler la bande et la fréquence selon le règlement et l'annonce de l'USKA.
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

Le log doit parvenir à l'USKA dans les 8 jours qui suivent le concours.

1. Choisir **File → Export Cabrillo log …**.
2. Les champs sont préremplis pour le Swiss XMAS Contest. La première fois, complète ton nom, ton adresse et ton e-mail ; ils sont mémorisés. L'accusé de réception de l'USKA est envoyé à cette adresse e-mail.
3. Cliquer sur **Save**. Le nom de fichier proposé est ton indicatif dans « Documents », p. ex. `HB9BLA.cbr` ; confirmer avec **Enregistrer**.
4. À la question de savoir si le log doit être envoyé maintenant, cliquer sur **« Envoyer maintenant à l'USKA »**.
5. Dans la fenêtre « Envoyer le log à l'USKA », vérifier le concours (il est présélectionné d'après la date des QSO), lire la déclaration et cocher **« Je fais cette déclaration »**.
6. Cliquer sur **« Envoyer le log »**.

À la fin, la fenêtre indique « L'USKA a reçu ton log … », et tu reçois par e-mail une confirmation avec le log en pièce jointe. Si elle n'arrive pas, vérifie ton dossier de spam.

Tu peux aussi envoyer plus tard un log enregistré : **File → Envoyer un log Cabrillo à l'USKA …**. Si l'envoi direct ne fonctionne pas, utilise la page web https://contestlog.uska.ch/submit.

## 6. Compatibilité

| Situation | Résultat |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Concours avec échange des cantons |
| WSJT-SWISS 3 ↔ WSJT-X | Les QSO normaux fonctionnent ; les cantons sont mal affichés |
| QSO FT4/FT8 normaux hors concours | Comme avec WSJT-X ; désactiver pour cela « Special operating activity » |
