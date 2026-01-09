# Ransomware Éducatif - Jour 5

[![License](https://img.shields.io/badge/license-Educational-blue)](LICENSE)
[![Language](https://img.shields.io/badge/language-C-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/status-Complete-brightgreen)](#status)

## 📋 Vue d'ensemble

Ce projet est une **implémentation éducative complète d'un ransomware** développée pendant une formation en cybersécurité Base du langage C, écriture malware en C . Il démontre les concepts fondamentaux de chiffrement, communication réseau, gestion de fichiers et intégrité de données en C.

**⚠️ Avertissement légal** : Ce projet est destiné à des fins éducatives uniquement, dans un environnement contrôlé (VM isolée) (Sandbox). Son utilisation à des fins malveillantes est strictement interdite et illégale.

---

## 🎯 Objectifs du Projet

- ✅ Implémenter 8 modules de cybersécurité en C
- ✅ Maîtriser les concepts de cryptographie (XOR, Caesar, ROT13, CRC32)
- ✅ Gérer les fichiers et structures de répertoires
- ✅ Implémenter la communication C2 (Command & Control)
- ✅ Comprendre les sockets TCP/IP en C
- ✅ Développer une architecture modulaire et maintenable

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│         ransomware.c (Main)              │
│        Menu principal & interface        │
└──────────────┬──────────────────────────┘
               │
      ┌────────┴─────────┬──────────────┬──────────────┬────────────┐
      │                  │              │              │            │
      ▼                  ▼              ▼              ▼            ▼
┌─────────┐        ┌─────────┐    ┌─────────┐  ┌─────────┐  ┌──────────┐
│ MODULE1 │        │ MODULE2 │    │ MODULE3 │  │ MODULE4 │  │ MODULE5  │
│ Scanner │        │   XOR   │    │ Caesar  │  │ ROT13   │  │ Checksum │
└─────────┘        └─────────┘    └─────────┘  └─────────┘  └──────────┘
      │                  │              │              │            │
      │                  │              │              │            │
      ├──────────────────┴──────────────┴──────────────┴────────────┤
      │                                                              │
      │                       modules.c (Implémentation)            │
      │                                                              │
      └──────────────────────────────────────────────────────────────┘
               │              │              │              │
               ▼              ▼              ▼              ▼
          ┌─────────┐    ┌─────────┐  ┌─────────┐   ┌──────────┐
          │ MODULE6 │    │ MODULE7 │  │ MODULE8 │   │  Timer   │
          │ Timer   │    │ Config  │  │  C2     │   │ Scanner  │
          └─────────┘    └─────────┘  └─────────┘   │ Config   │
                                                    └──────────┘
```

---

## 📦 Modules Implémentés

### Phase 1 : Fondations ✅

#### **MODULE 1 : Scanner de Fichiers**
- Scanne les répertoires (récursif ou non)
- Filtre les fichiers selon les critères
- Exclut les fichiers cachés et sensibles

```c
int scan_directory(const char *path, char files[][MAX_PATH], int max_files);
int scan_recursive(const char *path, char files[][MAX_PATH], int max_files, int current_count);
int should_exclude(const char *filename);
```

#### **MODULE 6 : Timer**
- Gère les timestamps (secondes depuis epoch)
- Permet les délais programmés
- Fonction d'attente jusqu'à un timestamp précis

```c
long get_current_timestamp();
void wait_seconds(int seconds);
void wait_until(long target_timestamp);
```

#### **MODULE 7 : Configuration**
- Parse un fichier de configuration INI
- Gère whitelist d'extensions (fichiers autorisés)
- Gère blacklist de chemins (répertoires interdits)

```c
Config* load_config(const char *filepath);
int is_allowed(const Config *cfg, const char *filepath);
void free_config(Config *cfg);
```

### Phase 2 : Cryptographie ✅

#### **MODULE 3 : Chiffrement César**
- Décalage de N positions dans l'alphabet
- Gère majuscules et minuscules
- Wraparound automatique (Z → A)

```c
char caesar_char(char c, int shift);
int caesar_encrypt_file(const char *input, const char *output, int shift);
int caesar_decrypt_file(const char *input, const char *output, int shift);
```

**Exemple** : "Hello" avec shift=3 → "Khoor"

#### **MODULE 4 : ROT13**
- Cas spécial du Caesar avec shift=13
- **Propriété magique** : ROT13(ROT13(x)) = x (réversible)

```c
char rot13_char(char c);
int rot13_file(const char *input, const char *output);
```

### Phase 3 : Chiffrement Avancé ✅

#### **MODULE 2 : Chiffrement XOR**
- XOR bitwise avec clé cyclique
- **Symétrique** : decrypt = encrypt (même clé)
- Lecture/écriture par chunks (BUFFER_SIZE = 4096)

```c
void xor_buffer(char *buffer, size_t size, const char *key, size_t key_len);
int xor_encrypt_file(const char *input, const char *output, const char *key);
int xor_decrypt_file(const char *input, const char *output, const char *key);
```

**Exemple** : "A" (65) XOR "K" (75) = 10 (binaire)

#### **MODULE 5 : Checksum CRC32**
- Détection d'erreurs (integrity checking)
- Table CRC32 prédéfinie (256 valeurs)
- Permet de vérifier que un fichier n'a pas été modifié

```c
uint32_t crc32(const unsigned char *data, size_t length);
uint32_t calculate_crc32(const char *filepath);
int verify_integrity(const char *filepath, uint32_t expected_crc);
```

### Phase 4 : Infrastructure C2 ✅

#### **MODULE 8 : C2 Client**
- Communication TCP/IP avec serveur C2 (Command & Control)
- Envoi de commandes structurées
- Réception de réponses

```c
int c2_connect(const char *ip, int port);
C2Response c2_send_command(int sockfd, const C2Command *cmd);
void c2_disconnect(int sockfd);
```

**Protocole** :
- Connexion TCP sur `127.0.0.1:4444` (configurable)
- Envoi structure `C2Command` (commande + cible + clé)
- Réception structure `C2Response` (status + message)

---

## 🚀 Installation & Compilation

### Prérequis

- **Environnement** : Linux/Unix (testé sur Ubuntu 24.04)
- **Compilateur** : GCC avec support C99
- **VM** : Vagrant (fourni avec Vagrantfile)
- **Librairies** : Standard C (stdio, stdlib, string, unistd, socket)

### Étapes d'installation

#### 1️⃣ Cloner le repository
```bash
git clone https://github.com/yokozuna47/Projet_Jour5.git
cd Projet_Jour5
```

#### 2️⃣ Démarrer la VM (optionnel, si utilisation de Vagrant)
```bash
vagrant up
vagrant ssh
cd /vagrant/TP
```

#### 3️⃣ Compiler
```bash
# Compilation simple
gcc -Wall -Wextra -I. -o ransomware ransomware.c modules.c

# Ou utiliser le Makefile (si présent)
make
```

#### 4️⃣ Exécuter
```bash
./ransomware
```

---

## 💻 Utilisation

### Menu Principal

```
╔══════════════════════════════════════════╗
║   RANSOMWARE ÉDUCATIF - JOUR 5           ║
║   Formation Sécurité Informatique        ║
╚══════════════════════════════════════════╝

=== MENU PRINCIPAL ===
1. Scanner un répertoire         (MODULE 1)
2. Chiffrer XOR                  (MODULE 2)
3. Chiffrer César                (MODULE 3)
4. Chiffrer ROT13                (MODULE 4)
5. Calculer checksum             (MODULE 5)
6. Tester timer                  (MODULE 6)
7. Charger config                (MODULE 7)
8. Tester C2 client              (MODULE 8)
0. Quitter
```

### Exemples d'utilisation

#### Scanner de fichiers
```
Choix: 1
Chemin à scanner: test_files/
✓ 4 fichiers trouvés
  - test_files/documents/rapport.txt
  - test_files/documents/notes.md
  - test_files/documents/secret.txt
  - test_files/README.txt
```

#### Chiffrement XOR
```
Choix: 2
Fichier source: test_files/documents/rapport.txt
Fichier destination: rapport_encrypted.txt
Clé XOR: mysecretkey
✓ Chiffrement XOR réussi

# Déchiffrement (même clé)
Clé XOR: mysecretkey
✓ Chiffrement XOR réussi  (retrouve le fichier original)
```

#### Chiffrement Caesar
```
Choix: 3
Fichier source: test_files/documents/rapport.txt
Fichier destination: rapport_encrypted.txt
Décalage (1-25): 3
✓ Chiffrement César réussi
```

#### Checksum CRC32
```
Choix: 5
Fichier à analyser: test_files/documents/rapport.txt
✓ CRC32: 0x7C2C0920
```

#### Configuration
```
Choix: 7
Fichier config (default: config.txt): 
✓ Config chargée
  Whitelist: 15 entrées
  Blacklist: 19 entrées
```

---

## 📁 Structure du Projet

```
Projet_Jour5/
├── README.md                    # Ce fichier
├── Vagrantfile                  # Configuration VM
├── setup_sandbox.sh             # Script de setup
├── modules.c                    # Implémentation (8 modules)
├── ransomware.c                 # Programme principal
├── config.txt                   # Fichier de configuration
├── Makefile                     # Compilation (optionnel)
├── test_files/                  # Dossier de test
│   ├── documents/
│   │   ├── rapport.txt
│   │   ├── notes.md
│   │   └── secret.txt
│   └── README.txt
├── Headers (.h)
│   ├── scanner.h                # Déclarations MODULE 1
│   ├── xor_crypto.h             # Déclarations MODULE 2
│   ├── caesar_crypto.h          # Déclarations MODULE 3
│   ├── rot13_crypto.h           # Déclarations MODULE 4
│   ├── checksum.h               # Déclarations MODULE 5
│   ├── timer.h                  # Déclarations MODULE 6
│   ├── config.h                 # Déclarations MODULE 7
│   └── c2_client.h              # Déclarations MODULE 8
└── Documentation/
    ├── PHASE1_GUIDE.md
    ├── PHASE2_ROT13_CAESAR.md
    ├── PHASE3_XOR_CHECKSUM.md
    └── MODULE8_C2_CLIENT.md
```

---

## 🔧 Configuration

### config.txt

Le fichier `config.txt` contrôle les fichiers à traiter :

```ini
# Whitelist : extensions autorisées
[WHITELIST]
.txt
.pdf
.doc
.docx
.xls
.xlsx
.md

# Blacklist : chemins interdits (sensibles)
[BLACKLIST]
/boot/
/etc/
/sys/
/proc/
/.ssh/
```

---

## 🧪 Tests

### Tous les modules

```bash
# Test complet (Phase 1-4)
./ransomware

# Scanner
Choix: 1
Path: test_files/
✓ 4 fichiers trouvés

# XOR
Choix: 2
Source: test_files/documents/rapport.txt
Dest: rapport_xor.txt
Key: testkey
✓ Chiffrement XOR réussi

# Caesar
Choix: 3
Source: test_files/documents/rapport.txt
Dest: rapport_caesar.txt
Shift: 5
✓ Chiffrement César réussi

# ROT13
Choix: 4
Source: test_files/documents/rapport.txt
Dest: rapport_rot13.txt
✓ ROT13 réussi

# Checksum
Choix: 5
File: test_files/documents/rapport.txt
✓ CRC32: 0x7C2C0920

# Timer
Choix: 6
Seconds: 2
Attente de 2 secondes...
✓ Terminé

# Config
Choix: 7
✓ Config chargée
  Whitelist: 15 entrées
  Blacklist: 19 entrées

# C2 Client
Choix: 8
Test connexion au C2...
✗ Connexion échouée  (Normal : pas de serveur C2)
```

---

## 📊 Statistiques du Projet

| Catégorie | Valeur |
|-----------|--------|
| **Modules** | 8 |
| **Fonctions** | 24 |
| **Lignes de code** | ~700 (modules.c) |
| **Compilation** | ✅ Sans erreur |
| **Tests** | ✅ 100% fonctionnels |
| **Documentation** | ✅ Complète |

---

## 🎓 Concepts Clés

### Cryptographie
- **XOR** : Opération bitwise réversible
- **Caesar** : Substitution monoalphabétique
- **ROT13** : Cas spécial de Caesar avec shift=13
- **CRC32** : Checksum détection d'erreurs

### Systèmes
- **Sockets TCP/IP** : Communication réseau
- **File I/O** : Lecture/écriture fichiers
- **Memory Management** : malloc/free
- **Error Handling** : Gestion d'erreurs robuste

### Architecture
- **Modularité** : 8 modules indépendants
- **Séparation concerns** : Headers .h + implémentation .c
- **Maintenabilité** : Code documenté et lisible

---

## ⚠️ Limitations & Notes

1. **Pas de serveur C2 inclus** : MODULE 8 demande une connexion à `127.0.0.1:4444` (serveur externe nécessaire)
2. **VM isolée** : À utiliser UNIQUEMENT dans un environnement contrôlé (Vagrant)
3. **Pas de chiffrement fort** : XOR/Caesar sont des exemples éducatifs, pas sécurisés en production
4. **Single-threaded** : Le serveur C2 n'est pas multi-thread
5. **Hardcoded paths** : Les chemins peuvent être adaptés selon l'OS

---

## 🔐 Sécurité

**Ce projet est strictement éducatif.** Les concepts de chiffrement implémentés ne sont **PAS** sécurisés pour une utilisation en production :

- ❌ XOR est trivial à casser (frequence analysis)
- ❌ Caesar a seulement 26 clés possibles
- ❌ ROT13 est connu publiquement

Pour une sécurité réelle, utiliser :
- ✅ AES, RSA, ECC (cryptographie moderne)
- ✅ OpenSSL, libsodium (librairies éprouvées)
- ✅ Authentification + chiffrement

---

## 📖 Documentation Additionnelle

Pour plus de détails sur chaque phase (Tous les fichiers sont dans les repertoires Vagrant et TP):

---

## 🤝 Contributeurs

Les contributions sont :

1. Ba Issiakha
2. Enzo Benoit
3. Ikram Lakrib
4. Godwill Louhou
5. Olivier Merle

---

## 📝 License

Ce projet est fourni à des fins **éducatives uniquement**. Voir [LICENSE](LICENSE) pour plus de détails.

---

## 👨‍💻 Auteur

**Etudiants IPSSI** -  Master M2 Cyberse  

1. Ba Issiakha
2. Enzo Benoit
3. Ikram Lakrib
4. Godwill Louhou
5. Olivier Merle

---

**Dernier update** : 09/01/2026  
**Status** : ✅ Complet et Fonctionnel  
**Prochaine étape** : Implémentation d'un serveur C2 (bonus)

---

*"Projet encadré par Dorian Boire."*
