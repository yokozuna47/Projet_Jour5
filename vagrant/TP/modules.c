/*
 * modules.c - Implémentations de tous les modules
 * 
 * Ce fichier contient TOUTES les implémentations des fonctions
 * déclarées dans les fichiers .h
 * 
 * INSTRUCTIONS :
 * 1. Suivre l'ordre des modules (1 à 8)
 * 2. Implémenter chaque fonction selon les instructions du TP_Jour5.md
 * 3. Compiler avec : gcc -I. -o ransomware ransomware.c modules.c
 * 4. Tester avec : ./ransomware
 */

// ============================================================================
// MODULE 1 : SCANNER DE FICHIERS
// ============================================================================
#include "scanner.h"

/*
 * Fonction : scan_directory
 * Description : Scan un répertoire (non récursif)
 * Paramètres :
 *   - path : Chemin du répertoire à scanner
 *   - files : Tableau pour stocker les chemins de fichiers
 *   - max_files : Nombre maximum de fichiers
 * Retour : Nombre de fichiers trouvés
 */
int scan_directory(const char *path, char files[][MAX_PATH], int max_files) {
	(void)path; (void)files; (void)max_files;
	// TODO : Implémenter selon MODULE 1 du TP_Jour5.md
	
	return 0;
}

/*
 * Fonction : scan_recursive
 * Description : Scan récursivement un répertoire
 */
int scan_recursive(const char *path, char files[][MAX_PATH], int max_files, int current_count) {
	(void)path; (void)files; (void)max_files; (void)current_count;
	// TODO : Implémenter selon MODULE 1 du TP_Jour5.md
	return 0;
}

/*
 * Fonction : should_exclude
 * Description : Vérifie si un fichier doit être exclu
 */
int should_exclude(const char *filename) {
	(void)filename;
	// TODO : Implémenter selon MODULE 1 du TP_Jour5.md
	
	return 0;
}


// ============================================================================
// MODULE 2 : CHIFFREMENT XOR
// ============================================================================
#include "xor_crypto.h"

/*
 * Fonction : xor_buffer
 * Description : XOR un buffer avec une clé
 */
void xor_buffer(char *buffer, size_t size, const char *key, size_t key_len) {
    // TODO : Implémenter selon MODULE 2 du TP_Jour5.md
    
}

/*
 * Fonction : xor_encrypt_file
 * Description : Chiffre un fichier avec XOR
 */
int xor_encrypt_file(const char *input, const char *output, const char *key) {
    // TODO : Implémenter selon MODULE 2 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : xor_decrypt_file
 * Description : Déchiffre un fichier avec XOR (identique à encrypt)
 */
int xor_decrypt_file(const char *input, const char *output, const char *key) {
    // TODO : Implémenter selon MODULE 2 du TP_Jour5.md
    
    return 0;
}


// ============================================================================
// MODULE 3 : CHIFFREMENT CÉSAR
// ============================================================================
#include "caesar_crypto.h"

/*
 * Fonction : caesar_char
 * Description : Applique César à un caractère
 */
char caesar_char(char c, int shift) {
    // TODO : Implémenter selon MODULE 3 du TP_Jour5.md
    
    return c;
}

/*
 * Fonction : caesar_encrypt_file
 * Description : Chiffre un fichier avec César
 */
int caesar_encrypt_file(const char *input, const char *output, int shift) {
    // TODO : Implémenter selon MODULE 3 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : caesar_decrypt_file
 * Description : Déchiffre un fichier avec César
 */
int caesar_decrypt_file(const char *input, const char *output, int shift) {
    // TODO : Implémenter selon MODULE 3 du TP_Jour5.md
    
    return 0;
}


// ============================================================================
// MODULE 4 : ROT13
// ============================================================================
#include "rot13_crypto.h"

/*
 * Fonction : rot13_char
 * Description : ROT13 d'un caractère (utilise César avec shift=13)
 */
char rot13_char(char c) {
    // TODO : Implémenter selon MODULE 4 du TP_Jour5.md
    
    return c;
}

/*
 * Fonction : rot13_file
 * Description : Chiffre/Déchiffre un fichier avec ROT13
 */
int rot13_file(const char *input, const char *output) {
    // TODO : Implémenter selon MODULE 4 du TP_Jour5.md
    
    return 0;
}


// ============================================================================
// MODULE 5 : CHECKSUM (CRC32)
// ============================================================================
#include "checksum.h"

/*
 * Fonction : crc32
 * Description : Calcule le CRC32 d'un buffer
 */
uint32_t crc32(const unsigned char *data, size_t length) {
    // TODO : Implémenter selon MODULE 5 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : calculate_crc32
 * Description : Calcule le CRC32 d'un fichier
 */
uint32_t calculate_crc32(const char *filepath) {
    // TODO : Implémenter selon MODULE 5 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : verify_integrity
 * Description : Vérifie l'intégrité d'un fichier
 */
int verify_integrity(const char *filepath, uint32_t expected_crc) {
    // TODO : Implémenter selon MODULE 5 du TP_Jour5.md
    
    return 0;
}


// ============================================================================
// MODULE 6 : TIMER
// ============================================================================
#include "timer.h"

/*
 * Fonction : get_current_timestamp
 * Description : Récupère le timestamp actuel (secondes depuis epoch)
 */
long get_current_timestamp() {
    // TODO : Implémenter selon MODULE 6 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : wait_seconds
 * Description : Attend N secondes
 */
void wait_seconds(int seconds) {
    // TODO : Implémenter selon MODULE 6 du TP_Jour5.md
    
}

/*
 * Fonction : wait_until
 * Description : Attend jusqu'à un timestamp précis
 */
void wait_until(long target_timestamp) {
    // TODO : Implémenter selon MODULE 6 du TP_Jour5.md
    
}


// ============================================================================
// MODULE 7 : CONFIGURATION
// ============================================================================
#include "config.h"

/*
 * Fonction : load_config
 * Description : Charge la configuration depuis un fichier
 */
Config* load_config(const char *filepath) {
    // TODO : Implémenter selon MODULE 7 du TP_Jour5.md
    
    return NULL;
}

/*
 * Fonction : is_allowed
 * Description : Vérifie si un fichier est autorisé
 */
int is_allowed(const Config *cfg, const char *filepath) {
    // TODO : Implémenter selon MODULE 7 du TP_Jour5.md
    
    return 0;
}

/*
 * Fonction : free_config
 * Description : Libère la mémoire de la config
 */
void free_config(Config *cfg) {
    // TODO : Implémenter selon MODULE 7 du TP_Jour5.md
    
}


// ============================================================================
// MODULE 8 : CLIENT C2
// ============================================================================
#include "c2_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 * Fonction : c2_connect
 * Description : Connexion au serveur C2
 */
int c2_connect(const char *ip, int port) {
    // TODO : Implémenter selon MODULE 8 du TP_Jour5.md
    
    return -1;
}

/*
 * Fonction : c2_send_command
 * Description : Envoie une commande et attend la réponse
 */
C2Response c2_send_command(int sockfd, const C2Command *cmd) {
    // TODO : Implémenter selon MODULE 8 du TP_Jour5.md
    
    C2Response resp;
    memset(&resp, 0, sizeof(resp));
    resp.status = -1;
    return resp;
}

/*
 * Fonction : c2_disconnect
 * Description : Ferme la connexion
 */
void c2_disconnect(int sockfd) {
    // TODO : Implémenter selon MODULE 8 du TP_Jour5.md
    
}
