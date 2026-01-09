# 🚀 Getting Started - Guide Rapide

Vous êtes pressé ? Voici comment démarrer en 5 minutes !

---

## ⚡ Installation Rapide

### 1️⃣ Cloner le repo
```bash
git clone https://github.com/yokozuna47/Projet_Jour5.git
cd Projet_Jour5
```

### 2️⃣ Compiler
```bash
gcc -Wall -Wextra -I. -o ransomware ransomware.c modules.c
```

### 3️⃣ Exécuter
```bash
./ransomware
```

**C'est tout !** ✅

---

## 🎮 Premiers Pas

### Test du Scanner (Module 1)
```
Choix: 1
Chemin à scanner: test_files/
✓ 4 fichiers trouvés
```

### Test du Chiffrement XOR (Module 2)
```
Choix: 2
Fichier source: test_files/documents/rapport.txt
Fichier destination: rapport_encrypted.txt
Clé XOR: mysecretkey
✓ Chiffrement XOR réussi
```

### Test du CRC32 (Module 5)
```
Choix: 5
Fichier à analyser: test_files/documents/rapport.txt
✓ CRC32: 0x7C2C0920
```

---

## 📚 Documentation

| Besoin | Ressource |
|--------|-----------|
| **Vue complète** | [README.md](README.md) |
| **Détails techniques** | [docs/](./docs/) |
| **Contribuer** | [CONTRIBUTING.md](CONTRIBUTING.md) |
| **License** | [LICENSE](LICENSE) |

---

## 🔧 Troubleshooting

### Erreur de compilation : `undefined reference`
**Solution** : S'assurer que modules.c est inclus
```bash
gcc -Wall -Wextra -I. -o ransomware ransomware.c modules.c
```

### Erreur : `No such file or directory`
**Solution** : Vérifier que vous êtes dans le bon dossier
```bash
cd /chemin/vers/Projet_Jour5
ls test_files/  # Vérifier que les fichiers existent
```

### Le programme compile mais ne fait rien
**Solution** : Vérifier que ransomware a les permissions d'exécution
```bash
chmod +x ransomware
./ransomware
```

---

## ✅ Checklist de Validation

Une fois compilé, testez :

- [ ] Option 1 (Scanner) fonctionne
- [ ] Option 2 (XOR) fonctionne
- [ ] Option 3 (Caesar) fonctionne
- [ ] Option 4 (ROT13) fonctionne
- [ ] Option 5 (Checksum) fonctionne
- [ ] Option 6 (Timer) fonctionne
- [ ] Option 7 (Config) fonctionne
- [ ] Option 8 (C2) affiche "Connexion échouée" (normal)

**Si tous les ✓ = Succès ! 🎉**

---

## 🎓 Apprendre les Concepts

### Cryptographie
1. **XOR** : Très simple, symétrique
2. **Caesar** : Facile, substitution
3. **ROT13** : Très facile, Caesar avec shift=13

### Systèmes
1. **Scanner** : Gestion de fichiers/dossiers
2. **Timer** : Timestamps et délais
3. **C2** : Sockets TCP/IP

### Checksum
- **CRC32** : Détection d'erreurs

---

## 🚀 Étapes suivantes

### Pour apprendre plus
```bash
# Lire la documentation des modules
cat docs/PHASE1_GUIDE.md      # Foundations
cat docs/PHASE2_ROT13_CAESAR.md  # Cryptography
cat docs/PHASE3_XOR_CHECKSUM.md  # Advanced
cat docs/MODULE8_C2_CLIENT.md    # Networking
```

### Pour modifier le code
```bash
# Éditer les sources
nano modules.c       # Implémentation
nano ransomware.c    # Programme principal
nano config.txt      # Configuration

# Recompiler
gcc -Wall -Wextra -I. -o ransomware ransomware.c modules.c

# Tester
./ransomware
```

### Pour contribuer
```bash
# Voir CONTRIBUTING.md
cat CONTRIBUTING.md
```

---

## 📊 Structures Principales

### Config (config.txt)
```ini
[WHITELIST]
.txt
.pdf
.doc

[BLACKLIST]
/etc/
/boot/
/.ssh/
```

### C2Command (communication)
```c
typedef struct {
    char command[64];       // ENCRYPT, DECRYPT, STATUS
    char target[256];       // Cible (fichier/dossier)
    char key[128];          // Clé de chiffrement
    int mode;               // 0=XOR, 1=Caesar, 2=ROT13
    int shift;              // Pour Caesar/ROT13
} C2Command;
```

---

## 💡 Tips & Tricks

### Créer des fichiers de test
```bash
echo "Test content" > test.txt
mkdir -p test_folder
```

### Comparer les fichiers
```bash
# Original vs Chiffré (doit être différent)
diff test.txt rapport_encrypted.txt

# Original vs Déchiffré (doit être identique)
diff test.txt rapport_decrypted.txt
```

### Voir le checksum
```bash
# Votre CRC32
./ransomware
Choix: 5
Fichier: test.txt
# Notez le résultat

# Recalculer (doit être identique)
./ransomware
Choix: 5
Fichier: test.txt
```

---

## 🎯 Objectifs d'Apprentissage

Après ce projet, vous comprendrez :

✅ Cryptographie basique (XOR, Caesar, ROT13, CRC32)  
✅ Programmation en C (modularité, gestion mémoire)  
✅ Gestion de fichiers (lecture/écriture, récursion)  
✅ Sockets TCP/IP (communication réseau)  
✅ Architecture logicielle (séparation concerns)  
✅ Concepts de cybersécurité (ransomware éducatif)  

---

## ❓ Questions Fréquentes

**Q: Le code est-il sûr ?**  
R: **NON**. C'est éducatif. XOR et Caesar ne sont pas sécurisés.

**Q: Je peux l'utiliser sur mes fichiers ?**  
R: **Oui**, dans un environnement de test isolé (VM).

**Q: Comment ajouter une nouvelle fonction ?**  
R: Créer un nouveau MODULE dans modules.c (voir CONTRIBUTING.md).

**Q: Pourquoi pas de serveur C2 ?**  
R: C'est un exercice bonus. À implémenter ! 😉

**Q: Comment contribuer ?**  
R: Voir [CONTRIBUTING.md](CONTRIBUTING.md).

---

## 📞 Support

- **Problème** ? → Vérifier [README.md](README.md)
- **Bug trouvé** ? → Créer une Issue
- **Question** ? → Ouvrir une Discussion
- **Idée** ? → Proposer une feature

---

## 📜 License

Ce projet est **ÉDUCATIF UNIQUEMENT**. Voir [LICENSE](LICENSE).

---

**Prêt ? Lancez `./ransomware` et explorez ! 🚀**

*Bon apprentissage !*

---

Dernière mise à jour : 09/01/2026
