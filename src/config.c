// SPDX-License-Identifier: GPL-2.0+
// © 2019 Mis012
// © 2020-2021 luka177

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "config.h"
#include "fs_utils.h"
#include <dirent.h>

#define ENTRIES_DIR "/meta/db/entries"
#define GLOBAL_CONFIG_FILE "/meta/db/db.conf"

int config_parse_option(char **_dest, const char *option, const char *buffer) {
	char *temp = strstr(buffer, option);
	if(!temp)
		return -1;
	
	temp += strlen(option);
	while (*temp == ' ')
		temp++;
	char *newline = strchr(temp, '\n');
	if(newline)
		*newline = '\0';
	char *dest = malloc(strlen(temp) + 1);
	if(!dest)
		return 1;
	strcpy(dest, temp);
	*_dest = dest;

	//restore the buffer
	*newline = '\n';

	return 0;
}

int parse_boot_entry_file(struct boot_entry *entry, char *file) {
	int ret;
    FILE *fp;
	unsigned char *buf;
	char *path = malloc(strlen(file) + strlen(ENTRIES_DIR) + strlen("/") + 1);
	strcpy(path, ENTRIES_DIR);
	strcat(path, "/");
	strcat(path, file);
    
	fp = fopen (path, "r");
	if(fp==NULL) {
		return 1;
	}
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */
    
    buf = malloc(fsize + 1);
    
    fread(buf, 1, fsize, fp);
    
	fclose(fp);
    
	buf[fsize] = '\0';
	
	ret = config_parse_option(&entry->title, "title", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: entry \"%s\" - no option 'title'\n", path);
		free(buf);
		return ret;
	}

	ret = config_parse_option(&entry->linux_kernel, "linux", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: entry \"%s\" - no option 'linux'\n", path);
		free(buf);
		return ret;
	}

	ret = config_parse_option(&entry->initrd, "initrd", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: entry \"%s\" - no option 'initrd'\n", path);
		free(buf);
		return ret;
	}

	ret = config_parse_option(&entry->dtb, "dtb", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: entry \"%s\" - no option 'dtb'\n", path);
		free(buf);
		return ret;
	}

	ret = config_parse_option(&entry->options, "options", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: entry \"%s\" - no option 'options'\n", path);
		free(buf);
		return ret;
	}

	free(buf);

	entry->error = false;

	return 0;
}

int entry_count;

int get_entry_count(void) {
	return entry_count;
}

int parse_boot_entries(struct boot_entry **entry_list) {
	int ret;
    printf("Begin parsing entrys.%s");

	ret = entry_count = dir_count_entries(ENTRIES_DIR);
	if (ret < 0) {
		entry_count = 0;
	}

	struct dirent *pDirent;
    DIR *pDir;

    printf("Reading from: %s\n", ENTRIES_DIR);
    pDir = opendir(ENTRIES_DIR);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", ENTRIES_DIR);
    }
  
	int i = 0;
	while((pDirent = readdir(pDir)) != NULL) {
         if(pDirent->d_type==DT_REG){
            printf ("Parsing: %s\n", pDirent->d_name);
            struct boot_entry *entry = entry_list+i;
            ret = parse_boot_entry_file(entry, pDirent->d_name);
            printf ("Parsed: %s, title: %s\n", pDirent->d_name, entry->title);
            if(ret < 0) {
                entry->error = true;
                entry->title = "SYNTAX ERROR";
            }
            i++;
        }
	}
	
	printf ("Parsed evrything\n");
	closedir (pDir);
    //printf("First entry is: %s\n", entry_list->title);
	return 0;
}

int parse_global_config(struct global_config *global_config) {
	int ret;
	FILE *fp;
	unsigned char *buf;

    fp = fopen (GLOBAL_CONFIG_FILE, "r");
	if(fp==NULL) {
		return 1;
	}

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */
    
    buf = malloc(fsize + 1);
    
	fread(buf, 1, fsize, fp);

	fclose(fp);

	ret = config_parse_option(&global_config->default_entry_title, "default", (const char *)buf);
	if(ret < 0) {
		printf("WARNING: lk2nd.conf: - no option 'default'\n");

		global_config->default_entry_title = NULL;
		global_config->timeout = 0;

		return 0;
	}

	char *timeout = NULL;
	ret = config_parse_option(&timeout, "timeout", (const char *)buf);
	if(ret < 0) {
		printf("SYNTAX ERROR: lk2nd.conf - no option 'timeout'\n");
	}

	global_config->timeout = atoi(timeout);

	return 0;
} 
